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
    armBtn = std::make_unique<juce::ToggleButton>("Arm");
    muteBtn = std::make_unique<juce::ToggleButton>("Mute");
    revBtn = std::make_unique<juce::ToggleButton>("Rev");
    soloBtn = std::make_unique<juce::ToggleButton>("Solo");

    // ValueTreeState attachments
    revAttachment.reset(new ButtonAttachment(parameters,
                                             "rev" + std::to_string(trackId),
                                             *revBtn));
    muteAttachment.reset(new ButtonAttachment(parameters,
                                              "mute" + std::to_string(trackId),
                                              *muteBtn));
    armAttachment.reset(new ButtonAttachment(parameters,
                                             "arm" + std::to_string(trackId),
                                             *armBtn));
    soloAttachment.reset(new ButtonAttachment(parameters,
                                              "solo" + std::to_string(trackId),
                                              *soloBtn));

    // Add custom parameter listener
    parameters.addParameterListener("recording", this);

    this->armBtn->onClick = [this] {
        bool buttonState = this->armBtn->getToggleState();
        bool isRecording = (bool)parameters.getParameterAsValue("recording").getValue();

        if (buttonState == true && !isRecording)
        {
            // Update the armed track ID in APVTS
            juce::Value armedTrackId = parameters.getParameterAsValue("armedTrackId");
            armedTrackId = trackId;

            // De-select all Arm buttons besides this one
            for (int i = 1; i <= 4; i++) {
                if (trackId != i) {
                    juce::Value otherButton = parameters.getParameterAsValue("arm" + std::to_string(i));
                    otherButton = false;
                }
            }
        }
    };

    this->soloBtn->onClick = [this] {
        // Update the soloed track ID in APVTS
        juce::Value soloedTrackId = parameters.getParameterAsValue("soloedTrackId");
        soloedTrackId = trackId;

        // De-select all Solo buttons besides this one
        for (int i = 1; i <= 4; i++) {
            juce::Value buttonState = parameters.getParameterAsValue("solo" + std::to_string(i));
            if (trackId != i) {
                buttonState = false;
            }
        }
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

}

void TrackControlButtons::paint(juce::Graphics& g)
{
    juce::Grid buttonsArea;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    buttonsArea.templateRows = { Track(Fr(1)), Track(Fr(1)) };
    buttonsArea.templateColumns = { Track(Fr(1)), Track(Fr(1)) };

    buttonsArea.items = { juce::GridItem(*armBtn), juce::GridItem(*revBtn),
                         juce::GridItem(*muteBtn), juce::GridItem(*soloBtn) };

    buttonsArea.performLayout(getLocalBounds());
}

void TrackControlButtons::resized()
{
}

void TrackControlButtons::parameterChanged(const juce::String& parameterID, float newValue) {
    // Disable "Arm" buttons when recording
    if (parameterID == "recording" && newValue == 1.0f)
    {
        this->armBtn->setEnabled(false);
    }
    else if (parameterID == "recording")
    {
        this->armBtn->setEnabled(true);
    }
}