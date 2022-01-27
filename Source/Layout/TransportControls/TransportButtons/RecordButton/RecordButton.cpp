/*
  ==============================================================================

    RecordButton.cpp
    Created: 26 Jan 2022 1:58:46pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#include "RecordButton.h"

//==============================================================================
RecordButton::RecordButton(juce::String& name, juce::Colour normalColour, juce::Colour overColour, juce::Colour downColour) : ShapeButton(name, normalColour, overColour, downColour)
{
    //========================================================================== 
    // Define the path for the button shape
    juce::Path recordPath;
    auto localOrigin = this->getPosition();
    auto localBounds = this->getLocalBounds();
    recordPath.addEllipse(localOrigin.getX() + 5, localOrigin.getY() + 5,
                          localBounds.getWidth() - 5, localBounds.getHeight() - 5);

    this->setShape(recordPath, true, true, false);
    //==========================================================================
}

RecordButton::~RecordButton()
{

}

void RecordButton::resized()
{

}