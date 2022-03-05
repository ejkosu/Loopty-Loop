/*
  ==============================================================================

    WaveformWindow.h
    Created: 24 Jan 2022 7:51:01pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveformWindow : public juce::Component, private juce::ChangeListener
{
public:
    //==========================================================================
    WaveformWindow(int t, juce::AudioThumbnail** thumbnails);
    ~WaveformWindow();

    //==========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    
    juce::Component waveformWindow;
    juce::AudioThumbnail* thumbnail;

    void drawEmptyWindow(juce::Graphics& g, juce::Rectangle<int>& waveformBounds);
    void drawWaveform(juce::Graphics& g, juce::Rectangle<int>& waveformBounds);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformWindow)
};
