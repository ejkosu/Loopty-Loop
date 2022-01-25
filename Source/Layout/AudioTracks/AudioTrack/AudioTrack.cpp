/*
  ==============================================================================

    AudioTrack.cpp
    Created: 23 Jan 2022 1:39:42pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "AudioTrack.h"

//==============================================================================
AudioTrack::AudioTrack(int t)
{
    trackNumber = t;
    addAndMakeVisible(trackLabel);
    trackLabel.setFont(juce::Font (30.0f, juce::Font::bold));
    trackLabel.setText(juce::String(t), juce::dontSendNotification);
    trackLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    trackLabel.setJustificationType(juce::Justification::centredLeft);
    
    addAndMakeVisible(trackWaveformWindow);
    addAndMakeVisible(controlButtonsArea);
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
    juce::Grid labelGrid;
    auto gridItemMargin = this->getHeight() / 10;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    labelGrid.templateRows = { Track(Fr(1)) };
    labelGrid.templateColumns = { Track(Fr(1)), Track(Fr(5)), 
                                  Track(Fr(2)), Track(Fr(2)) };

    labelGrid.items = { juce::GridItem(trackLabel).withMargin(gridItemMargin), 
                        juce::GridItem(trackWaveformWindow).withMargin(gridItemMargin),
                        juce::GridItem(controlButtonsArea).withMargin(gridItemMargin) };

    labelGrid.performLayout(getLocalBounds());


}