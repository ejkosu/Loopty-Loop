/*
  ==============================================================================

    TransportControls.h
    Created: 23 Jan 2022 1:42:21pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class TransportControls : public juce::Component
{
public:
    //==========================================================================
    TransportControls();
    ~TransportControls();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportControls)
};