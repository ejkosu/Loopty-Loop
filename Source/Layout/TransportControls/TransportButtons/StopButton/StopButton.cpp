/*
  ==============================================================================

    StopButton.cpp
    Created: 26 Jan 2022 1:59:42pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "StopButton.h"

//==============================================================================
StopButton::StopButton(juce::String& name, juce::Colour normalColour, juce::Colour overColour, juce::Colour downColour) : ShapeButton(name, normalColour, overColour, downColour)
{
    //========================================================================== 
    // Define the path for the button shape
    juce::Path stopPath;
    auto localOrigin = this->getPosition();
    auto localBounds = this->getLocalBounds();
    stopPath.addRectangle(localOrigin.getX() + 5, localOrigin.getY() + 5,
                          localBounds.getWidth() - 5, localBounds.getHeight() - 5);

    this->setShape(stopPath, true, true, false);
    //==========================================================================
}

StopButton::~StopButton()
{

}

void StopButton::resized()
{

}