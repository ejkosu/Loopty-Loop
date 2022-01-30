/*
  ==============================================================================

    Knob.cpp
    Created: 30 Jan 2022 1:44:28pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "Knob.h"

//==============================================================================
Knob::Knob(juce::String& knobName, int trackNumber)
{
    knob = new juce::Slider(knobName);
    addAndMakeVisible(*knob);
    knob->setSliderStyle(juce::Slider::SliderStyle::Rotary);
    knob->setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    knobLabel = new juce::Label(knobName, knobName);
    addAndMakeVisible(*knobLabel);
    knobLabel->setText(knobName, juce::dontSendNotification);
    knobLabel->setJustificationType(juce::Justification::centred);
}

Knob::~Knob()
{
    delete knob;
    delete knobLabel;
}

//void Knob::paint(juce::Graphics& g)
//{
//
//}

void Knob::resized()
{
    juce::Grid knobGrid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    knobGrid.templateRows = { Track(Fr(3)), Track(Fr(1)) };
    knobGrid.templateColumns = { Track(Fr(1)) };

    knobGrid.items = { juce::GridItem(*knob), juce::GridItem(*knobLabel) };

    knobGrid.performLayout(getLocalBounds());

}