/*
  ==============================================================================

    This file contains the basic framework code for a JUCE processor.

  ==============================================================================
*/

#include "AudioProcessor.h"

//==============================================================================
LooptyLoopAudioProcessor::LooptyLoopAudioProcessor()
{
}

LooptyLoopAudioProcessor::~LooptyLoopAudioProcessor()
{

}

//==============================================================================
const juce::String LooptyLoopAudioProcessor::getName() const
{
    return {};
}

bool LooptyLoopAudioProcessor::acceptsMidi() const
{
    return false;
}

bool LooptyLoopAudioProcessor::producesMidi() const
{
    return false;
}

bool LooptyLoopAudioProcessor::isMidiEffect() const
{
    return false;
}

double LooptyLoopAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LooptyLoopAudioProcessor::getNumPrograms()
{
    return 1;
}

int LooptyLoopAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LooptyLoopAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String LooptyLoopAudioProcessor::getProgramName(int index)
{
    return {};
}

void LooptyLoopAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void LooptyLoopAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void LooptyLoopAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LooptyLoopAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return false;
}
#endif

void LooptyLoopAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
}

//==============================================================================
bool LooptyLoopAudioProcessor::hasEditor() const
{
    return false;
}

juce::AudioProcessorEditor* LooptyLoopAudioProcessor::createEditor()
{
    return nullptr;
}

//==============================================================================
void LooptyLoopAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LooptyLoopAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LooptyLoopAudioProcessor();
}
