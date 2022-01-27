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
    addAndMakeVisible(transportButtons);
}

TransportControls::~TransportControls()
{

}

void TransportControls::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
}

void TransportControls::resized()
{
    juce::FlexBox transportControlsBox;
    transportControlsBox.justifyContent = juce::FlexBox::JustifyContent::center;
    transportControlsBox.alignContent = juce::FlexBox::AlignContent::center;
    transportControlsBox.flexDirection = juce::FlexBox::Direction::column;
    transportControlsBox.items.add(juce::FlexItem(transportButtons).withMinWidth(getLocalBounds().getWidth()/3).withMinHeight(getLocalBounds().getHeight()/3).withMargin(getLocalBounds().getHeight() / 10));
    transportControlsBox.performLayout(getLocalBounds().toFloat());
}