/*
  ==============================================================================

    MainLayoutComponent.cpp
    Created: 23 Jan 2022 2:00:50pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "MainLayoutComponent.h"

//==============================================================================
MainLayoutComponent::MainLayoutComponent(juce::AudioProcessorValueTreeState& vts)
    : audioTracks(vts),
    mixer(vts)
{
    addAndMakeVisible(audioTracks);
    addAndMakeVisible(transportControls);
    addAndMakeVisible(mixer);
}

MainLayoutComponent::~MainLayoutComponent()
{

}

//==============================================================================
void MainLayoutComponent::paint(juce::Graphics& g)
{

}

void MainLayoutComponent::resized()
{
    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    // Build the grid as two rows and two columns with the top row twice as
    // high as the bottom. The columns are equal width.
    grid.templateRows = { Track(Fr(2)), Track(Fr(1)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)) };

    // Plug the sections into the grid so that the audio tracks span the two
    // columns in the first row. The transport controls and mixer will be in
    // their own cells on the bottom row.
    grid.items = { juce::GridItem(audioTracks).withArea(1, juce::GridItem::Span(2)), juce::GridItem(transportControls), juce::GridItem(mixer) };

    grid.performLayout(getLocalBounds());
}