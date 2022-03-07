#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(juce::AudioProcessorValueTreeState& vts, juce::AudioThumbnail** thumbnails)
    : mainLayout(vts, fileBuffer, this, dialogOptions, thumbnails, deviceManager),
      juce::AudioAppComponent(deviceManager),
      parameters(vts)
{
    this->thumbnails = thumbnails;
    position = 0;
    recMaxLength = 661500; // 15 sec at 44100khz

    // Set up the buffers for recorded input
    recBuffer[0].setSize(2, recMaxLength, false, true);
    recBuffer[1].setSize(2, recMaxLength, false, true);
    recBuffer[2].setSize(2, recMaxLength, false, true);
    recBuffer[3].setSize(2, recMaxLength, false, true);

    // Set up for the audio device manager. We'll display this in a DialogWindow.
    deviceManager.initialise(2, 2, nullptr, true);
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

    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
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
        // If we are starting a new recording, clear the thumbnail and set up to
        // write the waveform for a new one.
        if (position == 0)
        {
            thumbnails[armedTrackIndex]->clear();
            thumbnails[armedTrackIndex]->reset(numOutputChannels, 44100, 44100 * 30);
        }
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
                        outBuffer[sample] = inBuffer[sample];
                        ++recSamplesWritten;
                    }

                    // addBlock writes all channels to the thumbnail at once, so we want
                    // to call it only on the first pass through the channel loop
                    if (channel == 0)
                    {
                       thumbnails[armedTrackIndex]->addBlock(position, *bufferToFill.buffer, outputSamplesOffset, outputSamplesRemaining);
                    }

                    // Update the length in num. of samples for this recorded buffer
                    recordedLengths[armedTrackIndex] = position + recSamplesWritten;
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
            // Determine if we are using the recorded buffer or the file buffer
            if (*parameters.getRawParameterValue("recording") == 0.0f &&
                *parameters.getRawParameterValue("isRecorded" + std::to_string(i + 1)) == 1.0f)
            {
                // Determine how many samples can be written
                int recSamplesRemaining = recordedLengths[i] - position;
                int samplesFromTrack = juce::jmin(outputSamplesRemaining, recSamplesRemaining);
                if (samplesFromTrack > maxSamplesWritten)
                    maxSamplesWritten = samplesFromTrack;

                // Write the recorded samples
                if (samplesFromTrack > 0)
                {
                    for (auto channel = 0; channel < numOutputChannels; ++channel)
                    {
                        bufferToFill.buffer->addFrom(channel,
                            outputSamplesOffset,
                            recBuffer[i],
                            channel % numInputChannels,
                            position,
                            samplesFromTrack);
                    }
                }   
            }
            else if (fileBuffer[i].getNumSamples() &&
                     *parameters.getRawParameterValue("isRecorded" + std::to_string(i + 1)) != 1.0f)
            {
                // Determine how many samples can be written
                int fileSamplesRemaining = fileBuffer[i].getNumSamples() - position;
                int samplesFromTrack = juce::jmin(outputSamplesRemaining, fileSamplesRemaining);
                if (samplesFromTrack > maxSamplesWritten)
                    maxSamplesWritten = samplesFromTrack;

                // Write the file samples
                if (samplesFromTrack > 0)
                {
                    for (auto channel = 0; channel < numOutputChannels; ++channel)
                    {
                        bufferToFill.buffer->addFrom(channel,
                            outputSamplesOffset,
                            fileBuffer[i],
                            channel % numInputChannels,
                            position,
                            samplesFromTrack);
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
            position >= 661500)
            position = 0;
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
