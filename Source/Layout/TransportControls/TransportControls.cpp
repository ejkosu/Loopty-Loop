/*
  ==============================================================================

    TransportControls.cpp
    Created: 23 Jan 2022 1:42:21pm
    Author:  Aaron Ennis

  ==============================================================================
*/
#include "TransportControls.h"


//==============================================================================

TransportControls::TransportControls(juce::AudioProcessorValueTreeState& vts, juce::AudioSampleBuffer* fileBuffer, juce::AudioAppComponent* mainComponent, juce::DialogWindow::LaunchOptions& dialogOptions)
    : parameters(vts), transportButtons(vts)
{
    addAndMakeVisible(transportButtons);
    addAndMakeVisible(loadTrackButton);
    addAndMakeVisible(loadLoopButton);
    addAndMakeVisible(saveLoopButton);
    addAndMakeVisible(audioSettingsButton);

    loadTrackButton.setButtonText("Load Track");
    loadTrackButton.onClick = [this, &vts, fileBuffer, mainComponent] {loadTrackButtonClicked(vts, fileBuffer, mainComponent); };
    loadLoopButton.setButtonText("Load Loop");
    loadLoopButton.onClick = [this] {loadLoopButtonClicked(); };
    saveLoopButton.setButtonText("Save Loop");
    saveLoopButton.onClick = [this] {saveLoopButtonClicked(); };
    audioSettingsButton.setButtonText("Audio Settings");
    audioSettingsButton.onClick = [this, &dialogOptions] {audioSettingsButtonClicked(dialogOptions); };
    formatManager.registerBasicFormats();
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
                         juce::GridItem(loadLoopButton).withMargin(20.0f),
                         juce::GridItem(saveLoopButton).withMargin(20.0f),
                         juce::GridItem(audioSettingsButton).withMargin(20.0f) };

    buttonGrid.performLayout(getLocalBounds());

}

/*
*   This is a modified version of the boilerplate file load callback provided
*   in the Juce demos at:
*   https://docs.juce.com/master/tutorial_playing_sound_files.html
*/

void TransportControls::loadTrackButtonClicked(juce::AudioProcessorValueTreeState& vts, juce::AudioSampleBuffer* fileBuffer, juce::AudioAppComponent* mainComponent)
{
    auto trackIndex = (int)vts.getParameterAsValue("armedTrackId").getValue() - 1; // -1 to correct index to the array of buffers

    if (trackIndex >= 0 && trackIndex < 4) {
        fileChooser = std::make_unique<juce::FileChooser>("Select a wave file to load...",
            juce::File{}, "*.wav");

        auto fileChooserFlags = juce::FileBrowserComponent::openMode |
            juce::FileBrowserComponent::canSelectFiles;

        fileChooser->launchAsync(fileChooserFlags, [this, fileBuffer, trackIndex, mainComponent](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file == juce::File{}) return;
                std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
                if (reader.get() != nullptr)
                {
                    auto duration = (float)reader->lengthInSamples / reader->sampleRate;
                    if (duration < 30)
                    {
                        fileBuffer[trackIndex].setSize(2, (int)reader->lengthInSamples);
                        reader->read(&fileBuffer[trackIndex],
                            0,
                            (int)reader->lengthInSamples,
                            0,
                            true,
                            true);
                        // Update the armed track ID in APVTS
                        juce::Value playback = parameters.getParameterAsValue("playback");
                        playback = true;
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

void TransportControls::loadLoopButtonClicked() {}

void TransportControls::saveLoopButtonClicked() {}

void TransportControls::audioSettingsButtonClicked(juce::DialogWindow::LaunchOptions& dialogOptions)
{
    dialogOptions.launchAsync();

}