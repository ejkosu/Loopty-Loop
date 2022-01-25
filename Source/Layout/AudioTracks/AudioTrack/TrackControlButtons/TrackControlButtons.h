/*
  ==============================================================================

    TrackControlButtons.h
    Created: 24 Jan 2022 7:51:52pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class TrackControlButtons : public juce::Component
{
public:
    //==========================================================================
    TrackControlButtons();
    ~TrackControlButtons();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    juce::ToggleButton* armBtn;
    juce::ToggleButton* muteBtn;
    juce::ToggleButton* revBtn;
    juce::ToggleButton* soloBtn;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackControlButtons)
};