/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "CustomGUIComponent.h"
#include <map>

extern int map[7];
int map[7];
extern std::map<std::string, int> translator;
std::map<std::string, int> translator;

//==============================================================================
class MidiTestApplication  : public JUCEApplication
{
public:
    //==============================================================================
    MidiTestApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        ignoreUnused (commandLine);
        mainWindow = new MainWindow (getApplicationName());
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

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
        ignoreUnused (commandLine);
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
			//inits the map
			for (int i = 0; i < 7; i++)
			{
				map[i] = i;
			}
			//inits the translator
			translator.insert(std::pair<std::string, int>("One Shot Pad", 1));
			translator.insert(std::pair<std::string, int>("Shaker Pad", 2));
			translator.insert(std::pair<std::string, int>("Tamborine Pad", 3));
			translator.insert(std::pair<std::string, int>("Snare 1", 4));
			translator.insert(std::pair<std::string, int>("Snare 2", 6));
			translator.insert(std::pair<std::string, int>("Hi-Hat 1", 7));
			translator.insert(std::pair<std::string, int>("Hi-Hat 2", 10));
			translator.insert(std::pair<std::string, int>("Cymbal 4", 27));
			translator.insert(std::pair<std::string, int>("Cymbal 2", 29));
			translator.insert(std::pair<std::string, int>("Cymbal 1", 31));
			translator.insert(std::pair<std::string, int>("Kick", 34));
			translator.insert(std::pair<std::string, int>("Floortom 2", 41));
			translator.insert(std::pair<std::string, int>("Raktom 3", 45));
			translator.insert(std::pair<std::string, int>("Raktom 2", 47));
			translator.insert(std::pair<std::string, int>("Raktom 1", 48));
			translator.insert(std::pair<std::string, int>("Ride", 51));
			translator.insert(std::pair<std::string, int>("Ride 2", 53));
			translator.insert(std::pair<std::string, int>("Cymbal 3", 57));
			translator.insert(std::pair<std::string, int>("Floortom 1", 75));








            setContentOwned (new CustomGUIComponent(), true);
			

            setResizable (true, false);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #endif

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
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
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (MidiTestApplication)
