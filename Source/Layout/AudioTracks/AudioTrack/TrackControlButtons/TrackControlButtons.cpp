/*
  ==============================================================================

    TrackControlButtons.cpp
    Created: 24 Jan 2022 7:51:52pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "TrackControlButtons.h"

//==============================================================================
TrackControlButtons::TrackControlButtons(int id, juce::AudioProcessorValueTreeState& vts)
    : trackId(id), parameters(vts)
{
    this->armBtn = new juce::ToggleButton("Arm");
    this->muteBtn = new juce::ToggleButton("Mute");
    // "Rev" text changed for demonstration of ValueTreeState
    this->revBtn = new juce::ToggleButton("Rev False");
    this->soloBtn = new juce::ToggleButton("Solo");

    // ValueTreeState attachments
    revAttachment.reset(new ButtonAttachment(parameters,
                                             "rev" + std::to_string(trackId),
                                             *revBtn));

    this->armBtn->changeWidthToFitText();
    this->muteBtn->changeWidthToFitText();
    this->soloBtn->changeWidthToFitText();
    this->revBtn->changeWidthToFitText();

    addAndMakeVisible(*armBtn);
    addAndMakeVisible(*muteBtn);
    addAndMakeVisible(*revBtn);
    addAndMakeVisible(*soloBtn);
}

TrackControlButtons::~TrackControlButtons()
{
    delete armBtn;
    delete muteBtn;
    delete revBtn;
    delete soloBtn;
}

void TrackControlButtons::paint(juce::Graphics& g)
{
    juce::Grid buttonsArea;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    buttonsArea.templateRows = { Track(Fr(1)), Track(Fr(1)) };
    buttonsArea.templateColumns = { Track(Fr(1)), Track(Fr(1)) };

    buttonsArea.items = { juce::GridItem(armBtn), juce::GridItem(revBtn),
                         juce::GridItem(muteBtn), juce::GridItem(soloBtn) };

    buttonsArea.performLayout(getLocalBounds());
}

void TrackControlButtons::resized()
{
    // Demonstration of ValueTreeState, can remove
    if (parameters.getParameterAsValue("rev" + std::to_string(trackId)) == true) {
        revBtn->setButtonText("Rev True");
    }
    else {
        revBtn->setButtonText("Rev False");
    }
}
