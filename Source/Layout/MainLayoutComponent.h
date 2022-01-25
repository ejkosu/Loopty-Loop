/*
  ==============================================================================

    MainLayoutComponent.h
    Created: 23 Jan 2022 2:00:50pm
    Author:  Aaron Ennis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./AudioTracks/AudioTracks.h"
#include "./TransportControls/TransportControls.h"
#include "./Mixer/Mixer.h"

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

    AudioTracks audioTracks;
    TransportControls transportControls;
    Mixer mixer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLayoutComponent)
};