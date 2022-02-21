#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(juce::AudioProcessorValueTreeState& vts)
    : mainLayout(vts, fileBuffer, this),
    parameters(vts)
{
    position = 0;
    addAndMakeVisible(mainLayout);
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{   /* code adpated from https://docs.juce.com/master/tutorial_looping_audio_sample_buffer.html */
    auto numInputChannels = 2;
    auto numOutputChannels = 2;

    auto outputSamplesRemaining = bufferToFill.numSamples;
    auto outputSamplesOffset = bufferToFill.startSample;

    // Playback stopped
    // You must use getRawParameterValue in the audio thread! See this forum thread for explanation:
    // https://forum.juce.com/t/update-audioprocessorvaluetreestate-from-process-block/17958/19
    if (*parameters.getRawParameterValue("playback") == 0.0f) {
        for (int i = 0; i < 4; i++)
        {
            if (fileBuffer[i].getNumSamples())
            {
                for (auto channel = 0; channel < numOutputChannels; ++channel)
                {
                    bufferToFill.buffer->addSample(channel,
                        outputSamplesOffset,
                        0.0f);

                    outputSamplesOffset += 1;
                }
            }
        }
        return;
    }

    // Playback playing
    while (outputSamplesRemaining > 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (fileBuffer[i].getNumSamples())
            {
                auto bufferSamplesRemaining = fileBuffer[0].getNumSamples() - position;
                auto samplesThisTime = juce::jmin(outputSamplesRemaining, bufferSamplesRemaining);

                for (auto channel = 0; channel < numOutputChannels; ++channel)
                {
                    bufferToFill.buffer->addFrom(channel,
                        outputSamplesOffset,
                        fileBuffer[i],
                        channel % numInputChannels,
                        position,
                        samplesThisTime);
                }

                outputSamplesRemaining -= samplesThisTime;
                outputSamplesOffset += samplesThisTime;
                position += samplesThisTime;

                if (position == fileBuffer[0].getNumSamples())
                    position = 0;
            }
        }
    }
}

void MainComponent::releaseResources()
{
    for (auto i = 0; i < 4; i++) 
    {
    fileBuffer[i].setSize(0, 0);
    }
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    mainLayout.setBounds(0, 0, getWidth(), getHeight());
}