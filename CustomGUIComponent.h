/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_C158D961EF0A43A6__
#define __JUCE_HEADER_C158D961EF0A43A6__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
extern int map[7];

extern std::map<std::string, int> translator;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CustomGUIComponent  : public Component,
                            public ComboBoxListener,
                            public ButtonListener
{
public:
    //==============================================================================
    CustomGUIComponent ();
    ~CustomGUIComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	//int map[7];
	//std::map<std::string, int> translator;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> comboBox;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<ComboBox> comboBox2;
    ScopedPointer<Label> label3;
    ScopedPointer<ComboBox> comboBox3;
    ScopedPointer<Label> label4;
    ScopedPointer<ComboBox> comboBox4;
    ScopedPointer<Label> label5;
    ScopedPointer<ComboBox> comboBox5;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label7;
    ScopedPointer<ComboBox> comboBox6;
    ScopedPointer<ComboBox> comboBox7;
    ScopedPointer<TextButton> switchStateButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomGUIComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_C158D961EF0A43A6__
