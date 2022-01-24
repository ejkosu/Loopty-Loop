/*
  ==============================================================================

    AudioTracks.cpp
    Created: 23 Jan 2022 1:40:28pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "AudioTracks.h"

//==============================================================================
AudioTracks::AudioTracks()
{

}

AudioTracks::~AudioTracks()
{

}

void AudioTracks::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::blue);
}

void AudioTracks::resized()
{
    juce::FlexBox audioTracksBox;
    audioTracksBox.performLayout(getLocalBounds().toFloat());
}