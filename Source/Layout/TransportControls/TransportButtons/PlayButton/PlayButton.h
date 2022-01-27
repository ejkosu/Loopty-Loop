/*
  ==============================================================================

    PlayButton.h
    Created: 26 Jan 2022 1:59:12pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PlayButton : public juce::ShapeButton
{
public:
    //==========================================================================
    PlayButton(juce::String& name, juce::Colour normalColour, juce::Colour overColour, juce::Colour downColour);
    ~PlayButton();

    //==========================================================================
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayButton)
};