/*
  ==============================================================================

    Mixer.cpp
    Created: 23 Jan 2022 1:43:49pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "Mixer.h"

//==============================================================================
Mixer::Mixer(juce::AudioProcessorValueTreeState& vts)
{
    mainVolume = new GainSlider(juce::String("Main"), 0, vts);
    track1 = new GainSlider(juce::String("1"), 1, vts);
    track2 = new GainSlider(juce::String("2"), 2, vts);
    track3 = new GainSlider(juce::String("3"), 3, vts);
    track4 = new GainSlider(juce::String("4"), 4, vts);
    
    addAndMakeVisible(*mainVolume);
    addAndMakeVisible(*track1);
    addAndMakeVisible(*track2);
    addAndMakeVisible(*track3);
    addAndMakeVisible(*track4);
}

Mixer::~Mixer()
{
    delete mainVolume;
    delete track1;
    delete track2;
    delete track3;
    delete track4;
}

void Mixer::paint(juce::Graphics& g)
{

}

void Mixer::resized()
{
    juce::Grid mixerGrid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    mixerGrid.templateRows = { Track(Fr(1)) };
    mixerGrid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)),
                                 Track(Fr(1)), Track(Fr(1)) };

    mixerGrid.items = { juce::GridItem(mainVolume), juce::GridItem(track1),
                       juce::GridItem(track2), juce::GridItem(track3),
                       juce::GridItem(track4) };

    mixerGrid.performLayout(getLocalBounds());
}