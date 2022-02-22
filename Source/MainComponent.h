#pragma once

#include <JuceHeader.h>
#include "./Layout/MainLayoutComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent     :   public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent(juce::AudioProcessorValueTreeState& vts);
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    MainLayoutComponent mainLayout;
    juce::AudioDeviceManager deviceManager;
    std::unique_ptr<juce::AudioDeviceSelectorComponent> audioSettings;
    juce::DialogWindow::LaunchOptions dialogOptions;
    juce::AudioProcessorValueTreeState& parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
