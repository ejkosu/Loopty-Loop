/*
  ==============================================================================

    AudioTracks.cpp
    Created: 23 Jan 2022 1:40:28pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "AudioTracks.h"

//==============================================================================
AudioTracks::AudioTracks(juce::AudioProcessorValueTreeState& vts, juce::AudioThumbnail** thumbnails)
{
    audioTrack01 = std::make_unique<AudioTrack>(1, vts, thumbnails);
    audioTrack02 = std::make_unique<AudioTrack>(2, vts, thumbnails);
    audioTrack03 = std::make_unique<AudioTrack>(3, vts, thumbnails);
    audioTrack04 = std::make_unique<AudioTrack>(4, vts, thumbnails);
    addAndMakeVisible(*audioTrack01);
    addAndMakeVisible(*audioTrack02);
    addAndMakeVisible(*audioTrack03);
    addAndMakeVisible(*audioTrack04);
}

AudioTracks::~AudioTracks()
{

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