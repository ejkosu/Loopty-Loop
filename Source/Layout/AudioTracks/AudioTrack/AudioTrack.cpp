/*
  ==============================================================================

    AudioTrack.cpp
    Created: 23 Jan 2022 1:39:42pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "AudioTrack.h"

//==============================================================================
AudioTrack::AudioTrack(int t, juce::AudioProcessorValueTreeState& vts)
    : controlButtonsArea(t, vts)
{
    trackNumber = t;
    addAndMakeVisible(trackLabel);
    trackLabel.setFont(juce::Font(30.0f, juce::Font::bold));
    trackLabel.setText(juce::String(t), juce::dontSendNotification);
    trackLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    trackLabel.setJustificationType(juce::Justification::centredLeft);

    addAndMakeVisible(trackWaveformWindow);
    addAndMakeVisible(controlButtonsArea);

    panKnob = new Knob(juce::String("Pan"), t, vts);
    slipKnob = new Knob(juce::String("Slip"), t, vts);

    addAndMakeVisible(*panKnob);
    addAndMakeVisible(*slipKnob);

}

AudioTrack::~AudioTrack()
{
    delete slipKnob;
    delete panKnob;
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
                        juce::GridItem(panKnob).withMargin(gridItemMargin),
                        juce::GridItem(slipKnob).withMargin(gridItemMargin) };

    trackGrid.performLayout(getLocalBounds());


}