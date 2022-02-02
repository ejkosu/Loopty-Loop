/*
  ==============================================================================

    TrackControlButtons.cpp
    Created: 24 Jan 2022 7:51:52pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "TrackControlButtons.h"

//==============================================================================
TrackControlButtons::TrackControlButtons(int id, GuiParameters& params)
    : GuiParams{ params },
    trackId{ id }
{
    this->armBtn = new juce::ToggleButton("Arm");
    this->muteBtn = new juce::ToggleButton("Mute");
    this->revBtn = new juce::ToggleButton("Rev");
    this->soloBtn = new juce::ToggleButton("Solo");

    // Callback on button click
    this->revBtn->onClick = [this] {
        GuiParams.revs[trackId-1] = this->revBtn->getToggleState();
    };

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
    // Demonstration of callbacks, can remove
    if (GuiParams.revs[trackId-1] == true) {
        revBtn->setButtonText("Rev True");
    }
    else {
        revBtn->setButtonText("Rev False");
    }
}