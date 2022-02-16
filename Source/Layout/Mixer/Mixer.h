/*
  ==============================================================================

    Mixer.h
    Created: 23 Jan 2022 1:43:49pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./GainSlider/GainSlider.h"

class Mixer : public juce::Component
{
public:
    //==========================================================================
    Mixer(juce::AudioProcessorValueTreeState& vts);
    ~Mixer();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    GainSlider* mainVolume;
    GainSlider* track1;
    GainSlider* track2;
    GainSlider* track3;
    GainSlider* track4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Mixer)
};