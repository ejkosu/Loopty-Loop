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
    AudioTracks(juce::AudioProcessorValueTreeState& vts);
    ~AudioTracks();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    AudioTrack* audioTrack01;
    AudioTrack* audioTrack02;
    AudioTrack* audioTrack03;
    AudioTrack* audioTrack04;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTracks)
};