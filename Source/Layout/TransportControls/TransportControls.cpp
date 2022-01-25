/*
  ==============================================================================

    TransportControls.cpp
    Created: 23 Jan 2022 1:42:21pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "TransportControls.h"

//==============================================================================
TransportControls::TransportControls()
{

}

TransportControls::~TransportControls()
{

}

void TransportControls::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void TransportControls::resized()
{
    juce::FlexBox transportControlsBox;
    transportControlsBox.performLayout(getLocalBounds().toFloat());
}