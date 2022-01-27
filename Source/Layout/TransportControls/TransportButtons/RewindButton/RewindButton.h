/*
  ==============================================================================

    RewindButton.h
    Created: 26 Jan 2022 2:00:16pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class RewindButton : public juce::ShapeButton
{
public:
    //==========================================================================
    RewindButton(juce::String& name, juce::Colour normalColour, juce::Colour overColour, juce::Colour downColour);
    ~RewindButton();

    //==========================================================================
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RewindButton)
};