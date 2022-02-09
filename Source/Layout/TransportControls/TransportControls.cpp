/*
  ==============================================================================

    TransportControls.cpp
    Created: 23 Jan 2022 1:42:21pm
    Author:  Aaron Ennis

  ==============================================================================
*/
#include "TransportControls.h"


//==============================================================================
TransportControls::TransportControls(juce::AudioSampleBuffer& fileBuffer)
{
    addAndMakeVisible(transportButtons);
    addAndMakeVisible(loadTrackButton);
    loadTrackButton.setButtonText("Load Track");
    loadTrackButton.onClick = [this, &fileBuffer] {loadTrackButtonClicked(&fileBuffer); };
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

    loadTrackButton.setSize(20, 10);
    buttonGrid.templateRows = { Track(Fr(1)), Track(Fr(1)) };
    buttonGrid.templateColumns = { Track(Fr(1)), Track(Fr(1)),
                                   Track(Fr(1)), Track(Fr(1)) };

    buttonGrid.items = { juce::GridItem(transportButtons).withArea(1, juce::GridItem::Span(4)), juce::GridItem(loadTrackButton) };

    buttonGrid.justifyContent = juce::Grid::JustifyContent::center;
    buttonGrid.alignContent = juce::Grid::AlignContent::center;

    buttonGrid.performLayout(getLocalBounds());

}

/*
*   This is a modified version of the boilerplate file load callback provided
*   in the Juce demos at:
*   https://docs.juce.com/master/tutorial_playing_sound_files.html
*/
void TransportControls::loadTrackButtonClicked(juce::AudioSampleBuffer* fileBuffer)
{
    fileChooser = std::make_unique<juce::FileChooser>("Select a wave file to load...",
                                                       juce::File{}, "*.wav");

    auto fileChooserFlags = juce::FileBrowserComponent::openMode |
                            juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(fileChooserFlags, [this, fileBuffer](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            
            if (file == juce::File{}) return;

            std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

            if (reader.get() != nullptr)
            {
                auto duration = (float)reader->lengthInSamples / reader->sampleRate;               // [3]

                if (duration < 2)
                {
                    fileBuffer.setSize((int)reader->numChannels, (int)reader->lengthInSamples);  // [4]
                    reader->read(fileBuffer,                                                      // [5]
                        0,                                                                //  [5.1]
                        (int)reader->lengthInSamples,                                    //  [5.2]
                        0,                                                                //  [5.3]
                        true,                                                             //  [5.4]
                        true);                                                            //  [5.5]
                }
                else
                {
                    // handle the error that the file is 2 seconds or longer..
                }
            }
            }
        });
}