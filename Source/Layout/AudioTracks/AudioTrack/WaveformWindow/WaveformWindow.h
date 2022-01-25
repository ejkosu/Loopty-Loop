/*
  ==============================================================================

    WaveformWindow.h
    Created: 24 Jan 2022 7:51:01pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveformWindow : public juce::Component
{
public:
    //==========================================================================
    WaveformWindow();
    ~WaveformWindow();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    
    juce::Component waveformWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformWindow)
};
