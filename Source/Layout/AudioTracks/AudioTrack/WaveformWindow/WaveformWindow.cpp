/*
  ==============================================================================

    WaveformWindow.cpp
    Created: 24 Jan 2022 7:51:01pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "WaveformWindow.h"

//==============================================================================
WaveformWindow::WaveformWindow()
{
    
}

WaveformWindow::~WaveformWindow()
{

}

void WaveformWindow::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void WaveformWindow::resized()
{
    juce::FlexBox waveformBox;
    waveformBox.performLayout(getLocalBounds().toFloat());
}