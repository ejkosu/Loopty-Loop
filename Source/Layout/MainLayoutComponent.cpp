/*
  ==============================================================================

    MainLayoutComponent.cpp
    Created: 23 Jan 2022 2:00:50pm
    Author:  aaron

  ==============================================================================
*/

#include "MainLayoutComponent.h"

//==============================================================================
MainLayoutComponent::MainLayoutComponent()
{

}

MainLayoutComponent::~MainLayoutComponent()
{

}

//==============================================================================
void MainLayoutComponent::paint(juce::Graphics& g)
{
    g.fillCheckerBoard(getLocalBounds().toFloat(), 25, 25, juce::Colours::grey, juce::Colours::lightgrey);
}

void MainLayoutComponent::resized()
{

}