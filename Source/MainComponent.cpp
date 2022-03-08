#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(juce::AudioProcessorValueTreeState& vts, juce::AudioThumbnail** thumbnails)
    : mainLayout(vts, fileBuffer, this, dialogOptions, thumbnails, deviceManager),
      juce::AudioAppComponent(deviceManager),
      parameters(vts),
      fxChains(),
      slips(),
      recordedLengths()
{
    this->thumbnails = thumbnails;
    position = 0;
    recMaxLength = 1323000; // 30 sec at 44100khz
    fxBuffer.setSize(2, 8192, false, true);

    // Set up the buffers for recorded input
    recBuffer[0].setSize(2, recMaxLength, false, true);
    recBuffer[1].setSize(2, recMaxLength, false, true);
    recBuffer[2].setSize(2, recMaxLength, false, true);
    recBuffer[3].setSize(2, recMaxLength, false, true);

    // Set up custom parameter listeners
    parameters.addParameterListener("playback", this);
    parameters.addParameterListener("arm1", this);
    parameters.addParameterListener("arm2", this);
    parameters.addParameterListener("arm3", this);
    parameters.addParameterListener("arm4", this);
    parameters.addParameterListener("solo1", this);
    parameters.addParameterListener("solo2", this);
    parameters.addParameterListener("solo3", this);
    parameters.addParameterListener("solo4", this);

    // Set up for the audio device manager. We'll display this in a DialogWindow.
    deviceManager.initialise(2, 2, nullptr, true);
    deviceManager.addChangeListener(this);
    audioSettings.reset(new juce::AudioDeviceSelectorComponent(deviceManager, 0, 2, 0, 2, false, false, true, true));
    audioSettings->setSize(600, 500);
    dialogOptions.dialogTitle = juce::String("Audio Settings");
    dialogOptions.dialogBackgroundColour = juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    dialogOptions.content.set(&*audioSettings, false);

    addAndMakeVisible(mainLayout);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2);
    }

    setSize(800, 600);
}

MainComponent::~MainComponent()
{
    deviceManager.removeChangeListener(this);
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // Prepare the fx processors used for panning
    spec.maximumBlockSize = 8192;
    spec.numChannels = 2;
    spec.sampleRate = sampleRate;

    for (int i = 0; i < 4; i++)
    {
        fxChains[i].prepare(spec);
    }
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{   /* code adpated from https://docs.juce.com/master/tutorial_looping_audio_sample_buffer.html */
    auto numInputChannels = 2;
    auto numOutputChannels = 2;

    auto outputSamplesRemaining = bufferToFill.numSamples;
    auto outputSamplesOffset = bufferToFill.startSample;

    //Audio Input
    auto* device = deviceManager.getCurrentAudioDevice();
    auto activeInputChannels = device->getActiveInputChannels();
    auto activeOutputChannels = device->getActiveOutputChannels();
    //calculate the number of channels to process input from
    auto maxInputChannels = activeInputChannels.getHighestBit() + 1;
    auto maxOutputChannels = activeOutputChannels.getHighestBit() + 1;

    int armedTrackIndex = (int)parameters.getParameterAsValue("armedTrackId").getValue() - 1;

    // Save the input if recording
    if (*parameters.getRawParameterValue("recording") == 1.0f)
    {
        for (auto channel = 0; channel < maxOutputChannels; ++channel)
        {
            // If this output channel is inactive, do not save the input channel
            if (activeOutputChannels[channel] && maxInputChannels > 0)
            {
                auto actualInputChannel = channel % maxInputChannels;


                if (activeInputChannels[channel] && armedTrackIndex >= 0 && armedTrackIndex <= 3)
                {
                    auto* inBuffer = bufferToFill.buffer->getReadPointer(actualInputChannel, outputSamplesOffset);
                    auto* outBuffer = recBuffer[armedTrackIndex].getWritePointer(channel, position);
                    int recSamplesWritten = 0;

                    for (auto sample = 0; (sample < outputSamplesRemaining) && (sample < recMaxLength); ++sample)
                    {
                        if (position + sample < recMaxLength)
                        {
                            outBuffer[sample] = inBuffer[sample];
                            ++recSamplesWritten;
                        }
                    }

                    // addBlock writes all channels to the thumbnail at once, so we want
                    // to call it only on the first pass through the channel loop
                    if (channel == 0)
                    {
                        thumbnails[armedTrackIndex]->addBlock(position, *bufferToFill.buffer, outputSamplesOffset, outputSamplesRemaining);
                    }

                    // Update the length in num. of samples for this recorded buffer
                    if (recordedLengths[armedTrackIndex] < position + recSamplesWritten)
                    {
                        recordedLengths[armedTrackIndex] = position + recSamplesWritten;
                    }
                    bufferToFill.buffer->clear(channel, outputSamplesOffset, outputSamplesRemaining);
                }
            }
        }
    }

    // Clear the input buffer
    for (auto channel = 0; channel < maxOutputChannels; ++channel)
    {
        bufferToFill.buffer->clear(channel, outputSamplesOffset, outputSamplesRemaining);
    }

    // Playback stopped
    // You must use getRawParameterValue in the audio thread! See this forum thread for explanation:
    // https://forum.juce.com/t/update-audioprocessorvaluetreestate-from-process-block/17958/19
    if (*parameters.getRawParameterValue("playback") == 0.0f) {
        while (outputSamplesRemaining > 0)
        {
            for (auto channel = 0; channel < numOutputChannels; ++channel)
            {
                bufferToFill.buffer->addSample(channel,
                    outputSamplesOffset,
                    0.0f);
            }
            outputSamplesOffset += 1;
            outputSamplesRemaining -= 1;
        }
        return;
    }

    // Playback playing
    while (outputSamplesRemaining > 0)
    {
        int maxSamplesWritten = 0;
        
        for (int i = 0; i < 4; i++)
        {
            bool soloSilence = getSoloSilence(i+1);
            bool isReversed = *parameters.getRawParameterValue("rev" + std::to_string(i + 1)) == 1.0f;
            float gain = (*parameters.getRawParameterValue("gain0") *
                          *parameters.getRawParameterValue("gain" + std::to_string(i + 1)));
            int slip = slips[i]; // 0.25 seconds at 44.1khz

            // Determine if we are using the recorded buffer or the file buffer
            if (*parameters.getRawParameterValue("recording") == 0.0f &&
                *parameters.getRawParameterValue("isRecorded" + std::to_string(i + 1)) == 1.0f &&
                *parameters.getRawParameterValue("mute" + std::to_string(i + 1)) == 0.0f &&
                !soloSilence)
            {
                // Determine how many samples can be written
                int recSamplesRemaining = recordedLengths[i] - position - slip;
                int samplesFromTrack = juce::jmin(outputSamplesRemaining, recSamplesRemaining);
                if (samplesFromTrack > maxSamplesWritten)
                    maxSamplesWritten = samplesFromTrack;

                if (samplesFromTrack > 0)
                {
                    // Write the recorded samples to the fxBuffer
                    fxBuffer.clear();
                    {
                        for (auto channel = 0; channel < numOutputChannels; ++channel)
                        {
                            auto* inBuffer = recBuffer[i].getReadPointer(channel, 0);
                            auto* outBuffer = fxBuffer.getWritePointer(channel, 0);

                            for (auto sample = 0; sample < samplesFromTrack; ++sample)
                            {
                                if (isReversed)
                                {
                                    outBuffer[sample] += inBuffer[recordedLengths[i] - position - slip - sample] * gain;
                                }
                                else
                                {
                                    outBuffer[sample] += inBuffer[position + slip + sample] * gain;
                                }
                            }
                        }
                    }

                    // Apply pan for this track
                    setPan(i, *parameters.getRawParameterValue("pan" + std::to_string(i + 1)));
                    applyPan(i, fxBuffer, 0, samplesFromTrack);

                    // Write from the fxBuffer to output
                    for (auto channel = 0; channel < numOutputChannels; ++channel)
                    {
                        auto* inBuffer = fxBuffer.getReadPointer(channel, 0);
                        auto* outBuffer = bufferToFill.buffer->getWritePointer(channel, outputSamplesOffset);

                        for (auto sample = 0; sample < samplesFromTrack; ++sample)
                        {
                            outBuffer[sample] += inBuffer[sample];
                        }
                    }
                }
            }
            else if (fileBuffer[i].getNumSamples() &&
                     *parameters.getRawParameterValue("isRecorded" + std::to_string(i + 1)) != 1.0f &&
                     *parameters.getRawParameterValue("mute" + std::to_string(i + 1)) == 0.0f &&
                     !soloSilence)
            {
                // Determine how many samples can be written
                int fileSamplesRemaining = fileBuffer[i].getNumSamples() - position - slip;
                int samplesFromTrack = juce::jmin(outputSamplesRemaining, fileSamplesRemaining);
                if (samplesFromTrack > maxSamplesWritten)
                    maxSamplesWritten = samplesFromTrack;

                if (samplesFromTrack > 0)
                {
                    // Write the file samples to the fxBuffer
                    fxBuffer.clear();
                    {
                        for (auto channel = 0; channel < numOutputChannels; ++channel)
                        {
                            auto* inBuffer = fileBuffer[i].getReadPointer(channel, 0);
                            auto* outBuffer = fxBuffer.getWritePointer(channel, 0);

                            for (auto sample = 0; sample < samplesFromTrack; ++sample)
                            {
                                if (isReversed)
                                {
                                    outBuffer[sample] += inBuffer[fileBuffer[i].getNumSamples() - position - slip - sample] * gain;
                                }
                                else
                                {
                                    outBuffer[sample] += inBuffer[position + sample + slip] * gain;
                                }
                            }
                        }
                    }

                    // Apply pan for this track
                    setPan(i, *parameters.getRawParameterValue("pan" + std::to_string(i + 1)));
                    applyPan(i, fxBuffer, 0, samplesFromTrack);

                    // Write from the fxBuffer to output
                    for (auto channel = 0; channel < numOutputChannels; ++channel)
                    {
                        auto* inBuffer = fxBuffer.getReadPointer(channel, 0);
                        auto* outBuffer = bufferToFill.buffer->getWritePointer(channel, outputSamplesOffset);

                        for (auto sample = 0; sample < samplesFromTrack; ++sample)
                        {
                            outBuffer[sample] += inBuffer[sample];
                        }
                    }
                }
            }
        }

        // Advance the position pointer
        if (maxSamplesWritten > 0)
        {
            outputSamplesRemaining -= maxSamplesWritten;
            outputSamplesOffset += maxSamplesWritten;
            position += maxSamplesWritten;
        }
        else
        {
            // If maxSamplesWritten = 0, then we are recording while nothing else is playing
            position += outputSamplesRemaining;
            outputSamplesOffset += outputSamplesRemaining;
            outputSamplesRemaining = 0;
        }


        // Loop if position has passed the max number of samples and we aren't recording, OR
        // the position is past 30 seconds
        int maxSamples = getMaxNumSamples();
        if ((position >= maxSamples && (*parameters.getRawParameterValue("recording") == 0.0f)) ||
            position >= 1323000)
        {
            // Reset the position
            position = 0;

            // Update the slip values (max 0.25sec at 44.1khz)
            for (int i = 0; i < 4; i++)
            {
                slips[i] = (int)(11025 * *parameters.getRawParameterValue("slip" + std::to_string(i + 1)));
            }
        }
    }
}

void MainComponent::releaseResources()
{
    for (auto i = 0; i < 4; i++) 
    {
    fileBuffer[i].setSize(0, 0);
    }
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    mainLayout.setBounds(0, 0, getWidth(), getHeight());
}

//=================================================================================
inline int MainComponent::getMaxNumSamples()
{
    // Returns the maximum number of samples in any active buffer (either recBuffer or fileBuffer).
    int max = 0;

    for (int i = 0; i < 4; i++)
    {
        if (*parameters.getRawParameterValue("isRecorded" + std::to_string(i + 1)) == 1.0f)
        {
            if (recordedLengths[i] > max) {
                max = recordedLengths[i];
            }
        }
        else if (fileBuffer[i].getNumSamples() > max)
        {
            max = fileBuffer[i].getNumSamples();
        }
    }

    return max;
}

// Returns a bool indicating if a track should be silenced because of Solo
inline bool MainComponent::getSoloSilence(int trackId)
{
    for (int i = 1; i <= 4; i++)
    {
        if (*parameters.getRawParameterValue("solo" + std::to_string(i)) == 1.0f &&
            trackId != i)
        {
                return true;
        }
    }
    return false;
}

// Applies pan to the given AudioBuffer based on the given track's panning level
inline void MainComponent::applyPan(int trackIndex, juce::AudioBuffer<float>& outputAudio, int startSample, int numSamples)
{
    auto block = juce::dsp::AudioBlock<float>(outputAudio);
    auto blockToUse = block.getSubBlock((size_t)startSample, (size_t)numSamples);
    auto contextToUse = juce::dsp::ProcessContextReplacing<float>(blockToUse);
    fxChains[trackIndex].process(contextToUse);
}

// Sets the panning level for a given track
inline void MainComponent::setPan(int trackIndex, float newValue)
{
    auto& panner = fxChains[trackIndex].template get<panIndex>();
    panner.setPan(newValue);
}

// Update the sample rate for the fxChains when sample rate is changed
void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* x)
{
    juce::dsp::ProcessSpec newSpec{};
    juce::AudioDeviceManager::AudioDeviceSetup newAudioSetup;
    deviceManager.getAudioDeviceSetup(newAudioSetup);

    newSpec.maximumBlockSize = 8192;
    newSpec.numChannels = 2;
    newSpec.sampleRate = newAudioSetup.sampleRate;

    for (int i = 0; i < 4; i++)
    {
        fxChains[i].prepare(spec);
    }
}


void MainComponent::parameterChanged(const juce::String& parameterID, float newValue)
{
    // Update the slip values based on the VTS when paused at position = 0
    if (position == 0 && *parameters.getRawParameterValue("playback") == 0.0f)
    {
        if (parameterID == "slip1" ||
            parameterID == "slip2" ||
            parameterID == "slip3" ||
            parameterID == "slip4")
        {
            for (int i = 0; i < 4; i++)
            {
                slips[i] = (int)(11025 * *parameters.getRawParameterValue("slip" + std::to_string(i + 1)));
            }
        }
    }

    // Update the armed track ID when Arm buttons are clicked
    if (parameterID == "arm1" ||
        parameterID == "arm2" ||
        parameterID == "arm3" ||
        parameterID == "arm4")
    {
        int armedTrackId = 0;

        for (int i = 1; i <= 4; i++)
        {
            float buttonState = *parameters.getRawParameterValue("arm" + std::to_string(i));
            if (buttonState == 1.0f)
            {
                armedTrackId = i;
            }
        }

        juce::Value val = parameters.getParameterAsValue("armedTrackId");
        val = armedTrackId;
    }

    // Update the soloed track ID when Solo buttons are clicked
    if (parameterID == "solo1" ||
        parameterID == "solo2" ||
        parameterID == "solo3" ||
        parameterID == "solo4")
    {
        int soloedTrackId = 0;

        for (int i = 1; i <= 4; i++)
        {
            float buttonState = *parameters.getRawParameterValue("solo" + std::to_string(i));
            if (buttonState == 1.0f)
            {
                soloedTrackId = i;
            }
        }

        juce::Value val = parameters.getParameterAsValue("soloedTrackId");
        val = soloedTrackId;
    }
}