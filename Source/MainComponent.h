#pragma once

#include <JuceHeader.h>
#include "./Layout/MainLayoutComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent     :   public juce::AudioAppComponent,
                            juce::ChangeListener,
                            juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    MainComponent(juce::AudioProcessorValueTreeState& vts, juce::AudioThumbnail** thumbnails);
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::AudioSampleBuffer recBuffer[4];
    juce::AudioSampleBuffer fileBuffer[4];

    int position;
    int recordedLengths[4];
    int recMaxLength;
    int slips[4];

    enum { panIndex };
    juce::dsp::ProcessSpec spec;
    juce::dsp::ProcessorChain<juce::dsp::Panner<float>> fxChains[4];
    juce::AudioSampleBuffer fxBuffer;

    MainLayoutComponent mainLayout;
    juce::AudioDeviceManager deviceManager;
    juce::AudioProcessorValueTreeState& parameters;
    juce::AudioThumbnail** thumbnails;

    //==============================================================================
    inline int getMaxNumSamples();
    inline bool getSoloSilence(int trackId);
    inline void applyPan(int trackIndex, juce::AudioBuffer<float>& outputAudio, int startSample, int numSamples);
    inline void setPan(int trackIndex, float newValue);
    void changeListenerCallback(juce::ChangeBroadcaster* x) override;
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
