/*
  ==============================================================================

    TransportButtons.cpp
    Created: 26 Jan 2022 11:40:10am
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "TransportButtons.h"

//==============================================================================
TransportButtons::TransportButtons()
{
    rewindBtn = new RewindButton(juce::String("Rewind"), juce::Colours::black, juce::Colours::black, juce::Colours::black);
    stopBtn = new StopButton(juce::String("Stop"), juce::Colours::black, juce::Colours::black, juce::Colours::black);
    playBtn = new PlayButton(juce::String("Play"), juce::Colours::green, juce::Colours::green, juce::Colours::green);
    recordBtn = new RecordButton(juce::String("Record"), juce::Colours::red, juce::Colours::red, juce::Colours::red);

    addAndMakeVisible(*rewindBtn);
    addAndMakeVisible(*stopBtn);
    addAndMakeVisible(*playBtn);
    addAndMakeVisible(*recordBtn);
}

TransportButtons::~TransportButtons()
{
    delete rewindBtn;
    delete stopBtn;
    delete playBtn;
    delete recordBtn;

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
