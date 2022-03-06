/*
  ==============================================================================

    AudioTracks.h
    Created: 23 Jan 2022 1:33:43pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./AudioTrack/AudioTrack.h"

class AudioTracks : public juce::Component
{
public:
    //==========================================================================
    AudioTracks(juce::AudioProcessorValueTreeState& vts, juce::AudioThumbnail** thumbnails);
    ~AudioTracks();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    std::unique_ptr<AudioTrack> audioTrack01;
    std::unique_ptr<AudioTrack> audioTrack02;
    std::unique_ptr<AudioTrack> audioTrack03;
    std::unique_ptr<AudioTrack> audioTrack04;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTracks)
};