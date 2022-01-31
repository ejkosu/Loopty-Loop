/*
  ==============================================================================

    Knob.h
    Created: 30 Jan 2022 1:44:28pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Knob : public juce::Component
{
public:
    //==========================================================================
    Knob(juce::String& knobName, int trackNumber);
    ~Knob();

    //==========================================================================
    //void paint(juce::Graphics& g) override;
    void resized() override;

private:

    juce::Slider* knob;
    juce::Label* knobLabel;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};