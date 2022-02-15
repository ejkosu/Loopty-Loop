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
    GainSlider(juce::String& sliderName, int sliderKey, juce::AudioProcessorValueTreeState& vts);
    ~GainSlider();

    //==========================================================================
    void resized() override;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

private:

    std::unique_ptr<juce::Slider> gainSlider;
    std::unique_ptr<juce::Label> sliderLabel;

    std::unique_ptr<SliderAttachment> attachment;
    juce::AudioProcessorValueTreeState& parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainSlider)
};