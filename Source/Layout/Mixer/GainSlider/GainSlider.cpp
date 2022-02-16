/*
  ==============================================================================

    GainSlider.cpp
    Created: 31 Jan 2022 8:36:37pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "GainSlider.h"

GainSlider::GainSlider(juce::String& sliderName, int sliderKey, juce::AudioProcessorValueTreeState& vts)
    : parameters(vts)
{
    gainSlider.reset(new juce::Slider(sliderName));
    addAndMakeVisible(*gainSlider);
    gainSlider->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider->setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    // ValueTreeState Attachment
    attachment.reset(new SliderAttachment(parameters,
                     "gain" + std::to_string(sliderKey),
                     *gainSlider));

    sliderLabel.reset(new juce::Label(sliderName, sliderName));
    addAndMakeVisible(*sliderLabel);
    sliderLabel->setText(sliderName, juce::dontSendNotification);
    sliderLabel->setJustificationType(juce::Justification::centred);
}

GainSlider::~GainSlider()
{
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