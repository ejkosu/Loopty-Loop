/*
  ==============================================================================

    AudioTrack.cpp
    Created: 23 Jan 2022 1:39:42pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "AudioTrack.h"

//==============================================================================
AudioTrack::AudioTrack(int t, 
                       juce::AudioProcessorValueTreeState& vts, 
                       juce::AudioThumbnail** thumbnails,
                       juce::AudioDeviceManager& manager)
    : trackWaveformWindow(t, thumbnails, vts, manager),
      controlButtonsArea(t, vts)
{
    trackNumber = t;
    addAndMakeVisible(trackLabel);
    trackLabel.setFont(juce::Font(30.0f, juce::Font::bold));
    trackLabel.setText(juce::String(t), juce::dontSendNotification);
    trackLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    trackLabel.setJustificationType(juce::Justification::centredLeft);

    addAndMakeVisible(trackWaveformWindow);
    addAndMakeVisible(controlButtonsArea);

    panKnob = std::make_unique<Knob>(juce::String("Pan"), t, vts);
    slipKnob = std::make_unique<Knob>(juce::String("Slip"), t, vts);

    addAndMakeVisible(*panKnob);
    addAndMakeVisible(*slipKnob);

}

AudioTrack::~AudioTrack()
{

}

//==============================================================================
void AudioTrack::paint(juce::Graphics& g)
{

}

void AudioTrack::resized()
{
    juce::Grid trackGrid;
    auto gridItemMargin = this->getHeight() / 10;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    trackGrid.templateRows = { Track(Fr(1)) };
    trackGrid.templateColumns = { Track(Fr(1)), Track(Fr(5)), 
                                  Track(Fr(2)), Track(Fr(1)), Track(Fr(1)) };

    trackGrid.items = { juce::GridItem(trackLabel).withMargin(gridItemMargin),
                        juce::GridItem(trackWaveformWindow).withMargin(gridItemMargin),
                        juce::GridItem(controlButtonsArea).withMargin(gridItemMargin),
                        juce::GridItem(*panKnob).withMargin(gridItemMargin),
                        juce::GridItem(*slipKnob).withMargin(gridItemMargin) };

    trackGrid.performLayout(getLocalBounds());


}