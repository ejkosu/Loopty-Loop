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

    // Play callback
    this->playBtn->onClick = [this] {
        juce::Value playback = parameters.getParameterAsValue("playback");
        playback = true;
    };

    // Stop callback
    this->stopBtn->onClick = [this] {
        juce::Value playback = parameters.getParameterAsValue("playback");
        playback = false;
    };

    // Record Button callback
    this->recordBtn->onClick = [this] {
        juce::Value recordValue = parameters.getParameterAsValue("record");
        if ((bool)recordValue.getValue() == false)
        {
            recordValue = true;
        }
        else
        {
            recordValue = false;
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
