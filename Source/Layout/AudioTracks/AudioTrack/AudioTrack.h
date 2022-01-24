/*
  ==============================================================================

    AudioTrack.h
    Created: 23 Jan 2022 1:39:42pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AudioTrack : public juce::Component
{
public:
    //==========================================================================
    AudioTrack();
    ~AudioTrack();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    juce::String trackNumber;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTrack)

};