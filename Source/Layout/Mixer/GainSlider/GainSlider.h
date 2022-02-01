/*
  ==============================================================================

    GainSlider.h
    Created: 31 Jan 2022 8:36:37pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class GainSlider : public juce::Component
{
public:
    //==========================================================================
    GainSlider(juce::String& sliderName, int sliderKey);
    ~GainSlider();

    //==========================================================================
    void resized() override;

private:

    juce::Slider* gainSlider;
    juce::Label* sliderLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainSlider)
};