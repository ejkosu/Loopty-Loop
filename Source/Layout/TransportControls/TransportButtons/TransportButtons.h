/*
  ==============================================================================

    TransportButtons.h
    Created: 26 Jan 2022 11:40:10am
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./PlayButton/PlayButton.h"
#include "./RecordButton/RecordButton.h"
#include "./RewindButton/RewindButton.h"
#include "./StopButton/StopButton.h"

class TransportButtons : public juce::Component
{
public:
    //==========================================================================
    TransportButtons(juce::AudioProcessorValueTreeState& vts);
    ~TransportButtons();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    RewindButton* rewindBtn;
    StopButton* stopBtn;
    PlayButton* playBtn;
    RecordButton* recordBtn;

    juce::AudioProcessorValueTreeState& parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportButtons)
};