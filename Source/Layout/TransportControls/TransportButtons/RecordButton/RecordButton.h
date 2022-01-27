/*
  ==============================================================================

    RecordButton.h
    Created: 26 Jan 2022 1:58:46pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class RecordButton : public juce::ShapeButton
{
public:
    //==========================================================================
    RecordButton(juce::String& name, juce::Colour normalColour, juce::Colour overColour, juce::Colour downColour);
    ~RecordButton();

    //==========================================================================
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RecordButton)
};