/*
  ==============================================================================

    TransportButtons.cpp
    Created: 26 Jan 2022 11:40:10am
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "TransportButtons.h"

//==============================================================================
TransportButtons::TransportButtons(juce::AudioProcessorValueTreeState& vts)
    : parameters(vts)
{
    rewindBtn = std::make_unique<RewindButton>(juce::String("Rewind"), juce::Colours::black, juce::Colours::black, juce::Colours::black);
    stopBtn = std::make_unique<StopButton>(juce::String("Stop"), juce::Colours::black, juce::Colours::black, juce::Colours::black);
    playBtn = std::make_unique<PlayButton>(juce::String("Play"), juce::Colours::green, juce::Colours::green, juce::Colours::green);
    recordBtn = std::make_unique<RecordButton>(juce::String("Record"), juce::Colours::red, juce::Colours::red, juce::Colours::red);

    addAndMakeVisible(*rewindBtn);
    addAndMakeVisible(*stopBtn);
    addAndMakeVisible(*playBtn);
    addAndMakeVisible(*recordBtn);

    // Add custom parameter listener so Record button is disabled while loading a file
    parameters.addParameterListener("loadingFile", this);

    // Play callback
    this->playBtn->onClick = [this] {
        juce::Value playback = parameters.getParameterAsValue("playback");
        playback = true;
    };

    // Stop callback
    this->stopBtn->onClick = [this] {
        juce::Value playback = parameters.getParameterAsValue("playback");
        playback = false;

        juce::Value recording = parameters.getParameterAsValue("recording");
        recording = false;
    };

    // Record callback
    this->recordBtn->onClick = [this] {
        int armedTrackId = (int)parameters.getParameterAsValue("armedTrackId").getValue();
        juce::Value recording = parameters.getParameterAsValue("recording");

        // Stop recording if we are recording, else start recording
        if ((bool)recording.getValue() == true)
        {
            recording = false;
        }
        else if (armedTrackId >= 1 && armedTrackId <= 4)
        {
            juce::Value recording = parameters.getParameterAsValue("recording");
            recording = true;

            juce::Value isRecorded = parameters.getParameterAsValue("isRecorded" + std::to_string(armedTrackId));
            isRecorded = true;

            juce::Value playback = parameters.getParameterAsValue("playback");
            playback = true;
        }
    };
}

TransportButtons::~TransportButtons()
{

}

void TransportButtons::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colours::blue);
}

void TransportButtons::resized()
{
    juce::Grid transportGrid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    transportGrid.templateRows = { Track(Fr(1)) };
    transportGrid.templateColumns = { Track(Fr(1)), Track(Fr(1)),
                                      Track(Fr(1)), Track(Fr(1)) };

    transportGrid.items = { juce::GridItem(*rewindBtn), 
                            juce::GridItem(*stopBtn),
                            juce::GridItem(*playBtn),
                            juce::GridItem(*recordBtn) };

    transportGrid.performLayout(getLocalBounds());
}

// Disable the record button while loading a file
void TransportButtons::parameterChanged(const juce::String& parameterID, float newValue) {
    if (parameterID == "loadingFile" && newValue == 1.0f)
    {
        this->recordBtn->setEnabled(false);
    }
    else
    {
        this->recordBtn->setEnabled(true);
    }
}