/*
  ==============================================================================

    Mixer.cpp
    Created: 23 Jan 2022 1:43:49pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "Mixer.h"

//==============================================================================
Mixer::Mixer()
{

}

Mixer::~Mixer()
{

}

void Mixer::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::red);
}

void Mixer::resized()
{
    juce::FlexBox mixerBox;
    mixerBox.performLayout(getLocalBounds().toFloat());
}