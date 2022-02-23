/*
  ==============================================================================

    TransportControls.h
    Created: 23 Jan 2022 1:42:21pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./TransportButtons/TransportButtons.h"

class TransportControls : public juce::Component
{
public:
    //==========================================================================
    TransportControls(juce::AudioProcessorValueTreeState& vts, juce::DialogWindow::LaunchOptions& dialogOptions);
    ~TransportControls();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    TransportButtons transportButtons;
    juce::TextButton loadTrackButton;
    juce::TextButton loadLoopButton;
    juce::TextButton saveLoopButton;
    juce::TextButton audioSettingsButton;
    std::unique_ptr<juce::FileChooser> fileChooser;
    juce::AudioFormatManager formatManager;
    juce::AudioProcessorValueTreeState& parameters;

    void loadTrackButtonClicked();
    void loadLoopButtonClicked();
    void saveLoopButtonClicked();
    void audioSettingsButtonClicked(juce::DialogWindow::LaunchOptions& dialogOptions);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportControls)
};