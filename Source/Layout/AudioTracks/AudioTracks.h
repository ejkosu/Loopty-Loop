/*
  ==============================================================================

    AudioTracks.h
    Created: 23 Jan 2022 1:33:43pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AudioTracks : public juce::Component
{
public:
    //==========================================================================
    AudioTracks();
    ~AudioTracks();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTracks)
};