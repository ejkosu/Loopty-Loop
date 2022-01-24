/*
  ==============================================================================

    Mixer.h
    Created: 23 Jan 2022 1:43:49pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Mixer : public juce::Component
{
public:
    //==========================================================================
    Mixer();
    ~Mixer();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Mixer)
};