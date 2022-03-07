/*
  ==============================================================================

    WaveformWindow.h
    Created: 24 Jan 2022 7:51:01pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveformWindow : public juce::Component, 
                       private juce::ChangeListener,
                       private juce::AudioProcessorValueTreeState::Listener
{
public:
    //==========================================================================
    WaveformWindow(int t, juce::AudioThumbnail** thumbnails, juce::AudioProcessorValueTreeState& vts);
    ~WaveformWindow();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    
    int trackId;
    juce::Component waveformWindow;
    juce::AudioThumbnail* thumbnail;
    juce::AudioProcessorValueTreeState& parameters;

    void drawEmptyWindow(juce::Graphics& g, juce::Rectangle<int>& waveformBounds);
    void drawWaveform(juce::Graphics& g, juce::Rectangle<int>& waveformBounds);
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformWindow)
};
