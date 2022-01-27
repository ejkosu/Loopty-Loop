/*
  ==============================================================================

    StopButton.h
    Created: 26 Jan 2022 1:59:42pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class StopButton : public juce::ShapeButton
{
public:
    //==========================================================================
    StopButton(juce::String& name, juce::Colour normalColour, juce::Colour overColour, juce::Colour downColour);
    ~StopButton();

    //==========================================================================
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StopButton)
};