/*
  ==============================================================================

    MainLayoutComponent.h
    Created: 23 Jan 2022 2:00:50pm
    Author:  aaron

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MainLayoutComponent   :   public juce::Component
{
public:
    //=========================================================================
    MainLayoutComponent();
    ~MainLayoutComponent() override;

    //=========================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLayoutComponent);
};