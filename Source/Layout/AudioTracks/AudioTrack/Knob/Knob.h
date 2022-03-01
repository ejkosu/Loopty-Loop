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
    Knob(juce::String& knobName, int trackNumber, juce::AudioProcessorValueTreeState& vts);
    ~Knob();

    //==========================================================================
    //void paint(juce::Graphics& g) override;
    void resized() override;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

private:

    std::unique_ptr<juce::Slider> knob;
    std::unique_ptr<juce::Label> knobLabel;

    std::unique_ptr<SliderAttachment> attachment;

    juce::AudioProcessorValueTreeState& parameters;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};