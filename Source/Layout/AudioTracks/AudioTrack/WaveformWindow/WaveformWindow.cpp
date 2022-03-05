/*
  ==============================================================================

    WaveformWindow.cpp
    Created: 24 Jan 2022 7:51:01pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "WaveformWindow.h"

//==============================================================================
WaveformWindow::WaveformWindow(int t, juce::AudioThumbnail** thumbnails)
{
    this->thumbnail = thumbnails[t-1];
}

WaveformWindow::~WaveformWindow()
{

}

void WaveformWindow::paint(juce::Graphics& g)
{
    juce::Rectangle<int> waveformBounds(getLocalBounds());

    if (this->thumbnail->getNumChannels() == 0)
    {
        drawEmptyWindow(g, waveformBounds);
    }
    else
    {
        drawWaveform(g, waveformBounds);
    }
}

void WaveformWindow::resized()
{

}

void WaveformWindow::drawEmptyWindow(juce::Graphics& g, juce::Rectangle<int>& waveformBounds)
{
    g.setColour(juce::Colours::lightgrey);
    g.fillRect(waveformBounds);
    g.setColour(juce::Colours::black);
    g.drawFittedText("Arm this track, then click Record or Load Track",
                      waveformBounds, juce::Justification::centred, 1);
}

void WaveformWindow::drawWaveform(juce::Graphics& g, juce::Rectangle<int>& waveformBounds)
{
    g.setColour(juce::Colours::lightgrey);
    g.fillRect(waveformBounds);
    g.setColour(juce::Colours::black);
    thumbnail->drawChannels(g, waveformBounds, 0.0f, thumbnail->getTotalLength(), 1.0f);
}