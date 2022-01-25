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
    this->audioTrack01 = new AudioTrack(1);
    this->audioTrack02 = new AudioTrack(2);
    this->audioTrack03 = new AudioTrack(3);
    this->audioTrack04 = new AudioTrack(4);
    addAndMakeVisible(*audioTrack01);
    addAndMakeVisible(*audioTrack02);
    addAndMakeVisible(*audioTrack03);
    addAndMakeVisible(*audioTrack04);
}

AudioTracks::~AudioTracks()
{
    delete audioTrack01;
    delete audioTrack02;
    delete audioTrack03;
    delete audioTrack04;
}

void AudioTracks::paint(juce::Graphics& g)
{
 
}

void AudioTracks::resized()
{
    juce::Grid tracksArea;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    tracksArea.templateRows = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };
    tracksArea.templateColumns = { Track(Fr(1)) };
    tracksArea.items = { juce::GridItem(*audioTrack01), juce::GridItem(*audioTrack02),
                         juce::GridItem(*audioTrack03), juce::GridItem(*audioTrack04) };

    tracksArea.performLayout(getLocalBounds());
}