/*
  ==============================================================================

    TransportControls.cpp
    Created: 23 Jan 2022 1:42:21pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "TransportControls.h"

//==============================================================================
TransportControls::TransportControls()
{
    addAndMakeVisible(transportButtons);
    addAndMakeVisible(loadTrackButton);
    addAndMakeVisible(loadLoopButton);
    addAndMakeVisible(saveLoopButton);
    addAndMakeVisible(audioSettingsButton);

    loadTrackButton.setButtonText("Load Track");
    loadTrackButton.onClick = [this] {loadTrackButtonClicked(); };
    loadLoopButton.setButtonText("Load Loop");
    loadLoopButton.onClick = [this] {loadLoopButtonClicked(); };
    saveLoopButton.setButtonText("Save Loop");
    saveLoopButton.onClick = [this] {saveLoopButtonClicked(); };
    audioSettingsButton.setButtonText("Audio Settings");
    audioSettingsButton.onClick = [this] {audioSettingsButtonClicked(); };
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
void TransportControls::loadTrackButtonClicked()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select a wave file to load...",
                                                       juce::File{}, "*.wav");

    auto fileChooserFlags = juce::FileBrowserComponent::openMode |
                            juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            
            if (file == juce::File{}) return;

            std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

            if (reader.get() != nullptr)
            {
                // This is where we will need the code that does what is needed
                // to actually load the file into the track's buffer.
            }
        });
}

void TransportControls::loadLoopButtonClicked() {}

void TransportControls::saveLoopButtonClicked() {}

void TransportControls::audioSettingsButtonClicked() {}