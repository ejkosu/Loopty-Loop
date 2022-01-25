/*
  ==============================================================================

    AudioTrack.h
    Created: 23 Jan 2022 1:39:42pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./WaveformWindow/WaveformWindow.h"
#include "./TrackControlButtons/TrackControlButtons.h"

class AudioTrack : public juce::Component
{
public:
    //==========================================================================
    AudioTrack(int t);
    ~AudioTrack();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    int trackNumber;
    juce::Label trackLabel;
    WaveformWindow trackWaveformWindow;
    TrackControlButtons controlButtonsArea;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTrack)

};