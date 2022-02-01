/*
    Filename:       Main.cpp
    Authors:        Aaron Ennis, Erik Kreager, Ben Church
    Organization:   Oregon State University
    Description:    This application is the project for our capstone course for
                    Computer Science. The application is a simple audio looping
                    sampler built using the JUCE framework (www.juce.com). It
                    is a four-track audio looping sampler that allows the user
                    to record or import audio files as tracks and plays them
                    back as a layered loop. It also allows for some simple
                    manipulation of the tracks in real time (reverse, pan,
                    slip, etc.).
*/

#include <JuceHeader.h>
#include "MainComponent.h"
#include "AudioProcessor.h"

//==============================================================================
class LooptyLoopApplication     :   public juce::JUCEApplication
{
public:
    //==============================================================================
    LooptyLoopApplication() {}

    const juce::String getApplicationName() override { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    //==============================================================================
    void initialise(const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code.
        audioProcessor.reset(new LooptyLoopAudioProcessor());
        parameters.reset(new juce::AudioProcessorValueTreeState(
            *audioProcessor,
            nullptr,
            juce::Identifier("VTS"),
            {
                std::make_unique<juce::AudioParameterBool>("rev1",           // parameterID
                                                           "Reverse 1",      // parameter name
                                                           false),           // default value
                std::make_unique<juce::AudioParameterBool>("rev2",
                                                           "Reverse 2",
                                                           false),
                std::make_unique<juce::AudioParameterBool>("rev3",
                                                           "Reverse 3",
                                                           false),
                std::make_unique<juce::AudioParameterBool>("rev4",
                                                           "Reverse 4",
                                                           false)
            }));

        mainWindow.reset(new MainWindow(getApplicationName(), *parameters));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    :   public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name, juce::AudioProcessorValueTreeState& vts)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons),
            parameters(vts)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(parameters), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
           #else
            setResizable(true, true);
            centreWithSize(getWidth(), getHeight());
           #endif

            setVisible(true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        juce::AudioProcessorValueTreeState& parameters;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<LooptyLoopAudioProcessor> audioProcessor;
    std::unique_ptr<juce::AudioProcessorValueTreeState> parameters;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (LooptyLoopApplication)
