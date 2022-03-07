/*
  ==============================================================================

    TransportControls.cpp
    Created: 23 Jan 2022 1:42:21pm
    Author:  Aaron Ennis

  ==============================================================================
*/
#include "TransportControls.h"


//==============================================================================

TransportControls::TransportControls(juce::AudioProcessorValueTreeState& vts,
                                     juce::AudioSampleBuffer* fileBuffer,
                                     juce::AudioAppComponent* mainComponent,
                                     juce::DialogWindow::LaunchOptions& dialogOptions,
                                     juce::AudioThumbnail** thumbnails,
                                     juce::AudioDeviceManager& manager)
    : parameters(vts),
      transportButtons(vts),
      deviceManager(manager)
{
    addAndMakeVisible(transportButtons);
    addAndMakeVisible(loadTrackButton);
    addAndMakeVisible(audioSettingsButton);

    loadTrackButton.setButtonText("Load Track");
    loadTrackButton.onClick = [this, &vts, fileBuffer, mainComponent, thumbnails] {loadTrackButtonClicked(vts, fileBuffer, mainComponent, thumbnails); };
    loadLoopButton.setButtonText("Load Loop");
    loadLoopButton.onClick = [this] {loadLoopButtonClicked(); };
    saveLoopButton.setButtonText("Save Loop");
    saveLoopButton.onClick = [this] {saveLoopButtonClicked(); };

    audioSettingsButton.setButtonText("Audio Settings");
    audioSettingsButton.onClick = [this, &dialogOptions] {audioSettingsButtonClicked(dialogOptions); };
    formatManager.registerBasicFormats();

    // Add custom parameter listener so Load Track button is disabled while recording
    parameters.addParameterListener("recording", this);
}

TransportControls::~TransportControls()
{

}

void TransportControls::paint(juce::Graphics& g)
{

}

void TransportControls::resized()
{
    juce::Grid buttonGrid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;


    auto localBounds = getLocalBounds();

    juce::GridItem::Margin transportMargin(getLocalBounds().getHeight() * 0.1f,
                                           getLocalBounds().getWidth() * 0.1f,
                                           getLocalBounds().getHeight() * 0.1f,
                                           getLocalBounds().getWidth() * 0.1f);

    buttonGrid.templateRows = { Track(Fr(1)), Track(Fr(1)) };
    buttonGrid.templateColumns = { Track(Fr(1)), Track(Fr(1)),
                                   Track(Fr(1)), Track(Fr(1)) };


    buttonGrid.items = { juce::GridItem(transportButtons).withMargin(transportMargin).withArea(1, juce::GridItem::Span(4)), 
                         juce::GridItem(loadTrackButton).withMargin(20.0f),
                         juce::GridItem(audioSettingsButton).withMargin(20.0f) };

    buttonGrid.performLayout(getLocalBounds());

}

/*
*   This is a modified version of the boilerplate file load callback provided
*   in the Juce demos at:
*   https://docs.juce.com/master/tutorial_playing_sound_files.html
*/

void TransportControls::loadTrackButtonClicked(juce::AudioProcessorValueTreeState& vts, juce::AudioSampleBuffer* fileBuffer, juce::AudioAppComponent* mainComponent, juce::AudioThumbnail** thumbnails)
{
    auto trackIndex = (int)vts.getParameterAsValue("armedTrackId").getValue() - 1; // -1 to correct index to the array of buffers

    if (trackIndex >= 0 && trackIndex < 4) {
        fileChooser = std::make_unique<juce::FileChooser>("Select a wave file to load...",
            juce::File{}, "*.wav");

        auto fileChooserFlags = juce::FileBrowserComponent::openMode |
            juce::FileBrowserComponent::canSelectFiles;

        fileChooser->launchAsync(fileChooserFlags, [this, fileBuffer, trackIndex, mainComponent, &vts, thumbnails](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file == juce::File{}) return;
                std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
                if (reader.get() != nullptr)
                {
                    auto duration = (float)reader->lengthInSamples / reader->sampleRate;
                    if (duration < 30)
                    {
                        // Update the VTS to show loading in progress
                        juce::Value loading = parameters.getParameterAsValue("loadingFile");
                        loading = true;

                        // File reading / resampling based on this forum thread:
                        // https://forum.juce.com/t/resampling-an-audiosamplebuffer/14287/7
                        juce::AudioSampleBuffer temp;
                        juce::ScopedPointer<juce::LagrangeInterpolator> resampler = new juce::LagrangeInterpolator();
                        juce::AudioDeviceManager::AudioDeviceSetup currentAudioSetup;
                        deviceManager.getAudioDeviceSetup(currentAudioSetup);
                        double ratio = reader->sampleRate / currentAudioSetup.sampleRate;

                        // Set up the temp buffer and fileBuffer
                        temp.setSize((int)reader->numChannels, (int)reader->lengthInSamples);
                        temp.clear();
                        fileBuffer[trackIndex].setSize(2, (int)(((double)reader->lengthInSamples) / ratio));
                        fileBuffer[trackIndex].clear();

                        // Read the file into the temp buffer
                        reader->read(&temp, 0, (int)reader->lengthInSamples, 0, true, true);

                        // Resample the audio and write it into fileBuffer
                        const float** inputs = temp.getArrayOfReadPointers();
                        float** outputs = fileBuffer[trackIndex].getArrayOfWritePointers();
                        for (int c = 0; (c < temp.getNumChannels() && c < 2); c++)
                        {
                            resampler->reset();
                            resampler->process(ratio, inputs[c], outputs[c], fileBuffer[trackIndex].getNumSamples());
                        }
                        
                        // If the file was mono, double it across both channels
                        if (temp.getNumChannels() == 1)
                        {
                            resampler->process(ratio, inputs[0], outputs[1], fileBuffer[trackIndex].getNumSamples());
                        }

                        // Set the thumbnail source
                        thumbnails[trackIndex]->setSource(new juce::FileInputSource(file));

                        // Update the VTS so the track does not use its recorded buffer
                        juce::Value isRecorded = parameters.getParameterAsValue("isRecorded" + std::to_string(trackIndex + 1));
                        isRecorded = false;
                        loading = false;
                    }
                    else
                    {
                        perror("the file is too long");
                    }
                }
            });
    }
    else
    {
        perror("No track selected");
    }
}

void TransportControls::audioSettingsButtonClicked(juce::DialogWindow::LaunchOptions& dialogOptions)
{
    dialogOptions.launchAsync();

    juce::Value playback = parameters.getParameterAsValue("playback");
    juce::Value recording = parameters.getParameterAsValue("playback");
    playback = false;
    recording = false;
}

// Disable the Load Track button while recording
void TransportControls::parameterChanged(const juce::String& parameterID, float newValue) {
    if (parameterID == "recording" && newValue == 1.0f)
    {
        loadTrackButton.setEnabled(false);
    }
    else
    {
        loadTrackButton.setEnabled(true);
    }
}