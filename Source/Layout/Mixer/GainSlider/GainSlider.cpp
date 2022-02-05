/*
  ==============================================================================

    GainSlider.cpp
    Created: 31 Jan 2022 8:36:37pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "GainSlider.h"

GainSlider::GainSlider(juce::String& sliderName, int sliderKey)
{
    gainSlider = new juce::Slider(sliderName);
    addAndMakeVisible(*gainSlider);
    gainSlider->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider->setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    sliderLabel = new juce::Label(sliderName, sliderName);
    addAndMakeVisible(*sliderLabel);
    sliderLabel->setText(sliderName, juce::dontSendNotification);
    sliderLabel->setJustificationType(juce::Justification::centred);
}

GainSlider::~GainSlider()
{
    delete gainSlider;
    delete sliderLabel;
}

void GainSlider::resized()
{
    juce::Grid gainSliderGrid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    gainSliderGrid.templateRows = { Track(Fr(3)), Track(Fr(1)) };
    gainSliderGrid.templateColumns = { Track(Fr(1)) };

    gainSliderGrid.items = { juce::GridItem(*gainSlider), juce::GridItem(*sliderLabel) };

    gainSliderGrid.performLayout(getLocalBounds());
}