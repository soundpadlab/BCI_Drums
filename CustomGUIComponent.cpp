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

//[Headers] You can add your own extra header files here...
#include "MainComponent.h"
#include <map>
#include <string>
//[/Headers]

#include "CustomGUIComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//extern int map[7];
//[/MiscUserDefs]

//==============================================================================
CustomGUIComponent::CustomGUIComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	/*for (int i = 0; i < 7; i++)
	{
		map[i] = i;
	}*/
	translator.insert(std::pair<std::string, int>("C4", 0));
	translator.insert(std::pair<std::string, int>("C#4", 1));
	translator.insert(std::pair<std::string, int>("D4", 2));
	translator.insert(std::pair<std::string, int>("Eb4", 3));
	translator.insert(std::pair<std::string, int>("E4", 4));
	translator.insert(std::pair<std::string, int>("F4", 5));
	translator.insert(std::pair<std::string, int>("F#4", 6));
	translator.insert(std::pair<std::string, int>("G4", 7));
	translator.insert(std::pair<std::string, int>("Ab4", 8));
	translator.insert(std::pair<std::string, int>("A4", 9));
	translator.insert(std::pair<std::string, int>("Bb4", 10));
	translator.insert(std::pair<std::string, int>("B4", 11));

    //[/Constructor_pre]

    addAndMakeVisible (comboBox = new ComboBox ("new combo box"));
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (String());
    comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox->addItem (TRANS("One Shot Pad"), 1);
    comboBox->addItem (TRANS("Shaker Pad"), 2);
    comboBox->addItem (TRANS("Tamborine Pad"), 3);
    comboBox->addItem (TRANS("Snare 1"), 4);
    comboBox->addItem (TRANS("Snare 2"), 5);
    comboBox->addItem (TRANS("Hi-Hat 1"), 6);
    comboBox->addItem (TRANS("Hi-Hat 2"), 7);
    comboBox->addItem (TRANS("Cymbal 4"), 8);
    comboBox->addItem (TRANS("Cymbal 2"), 9);
    comboBox->addItem (TRANS("Cymbal 1"), 10);
    comboBox->addItem (TRANS("Kick"), 11);
    comboBox->addItem (TRANS("Floortom 2"), 12);
    comboBox->addItem (TRANS("Raktom 3"), 13);
    comboBox->addItem (TRANS("Raktom 2"), 14);
    comboBox->addItem (TRANS("Raktom 1"), 15);
    comboBox->addItem (TRANS("Ride"), 16);
    comboBox->addItem (TRANS("Ride 2"), 17);
    comboBox->addItem (TRANS("Cymbal 3"), 18);
    comboBox->addItem (TRANS("Floortom 1"), 19);
    comboBox->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Button 1")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Button 2")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (comboBox2 = new ComboBox ("new combo box"));
    comboBox2->setEditableText (false);
    comboBox2->setJustificationType (Justification::centredLeft);
    comboBox2->setTextWhenNothingSelected (String());
    comboBox2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox2->addItem (TRANS("One Shot Pad"), 1);
    comboBox2->addItem (TRANS("Shaker Pad"), 2);
    comboBox2->addItem (TRANS("Tamborine Pad"), 3);
    comboBox2->addItem (TRANS("Snare 1"), 4);
    comboBox2->addItem (TRANS("Snare 2"), 5);
    comboBox2->addItem (TRANS("Hi-Hat 1"), 6);
    comboBox2->addItem (TRANS("Hi-Hat 2"), 7);
    comboBox2->addItem (TRANS("Cymbal 4"), 8);
    comboBox2->addItem (TRANS("Cymbal 2"), 9);
    comboBox2->addItem (TRANS("Cymbal 1"), 10);
    comboBox2->addItem (TRANS("Kick"), 11);
    comboBox2->addItem (TRANS("Floortom 2"), 12);
    comboBox2->addItem (TRANS("Raktom 3"), 13);
    comboBox2->addItem (TRANS("Raktom 2"), 14);
    comboBox2->addItem (TRANS("Raktom 1"), 15);
    comboBox2->addItem (TRANS("Ride"), 16);
    comboBox2->addItem (TRANS("Ride 2"), 17);
    comboBox2->addItem (TRANS("Cymbal 3"), 18);
    comboBox2->addItem (TRANS("Floortom 1"), 19);
    comboBox2->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Furrow")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (comboBox3 = new ComboBox ("new combo box"));
    comboBox3->setEditableText (false);
    comboBox3->setJustificationType (Justification::centredLeft);
    comboBox3->setTextWhenNothingSelected (String());
    comboBox3->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox3->addItem (TRANS("One Shot Pad"), 1);
    comboBox3->addItem (TRANS("Shaker Pad"), 2);
    comboBox3->addItem (TRANS("Tamborine Pad"), 3);
    comboBox3->addItem (TRANS("Snare 1"), 4);
    comboBox3->addItem (TRANS("Snare 2"), 5);
    comboBox3->addItem (TRANS("Hi-Hat 1"), 6);
    comboBox3->addItem (TRANS("Hi-Hat 2"), 7);
    comboBox3->addItem (TRANS("Cymbal 4"), 8);
    comboBox3->addItem (TRANS("Cymbal 2"), 9);
    comboBox3->addItem (TRANS("Cymbal 1"), 10);
    comboBox3->addItem (TRANS("Kick"), 11);
    comboBox3->addItem (TRANS("Floortom 2"), 12);
    comboBox3->addItem (TRANS("Raktom 3"), 13);
    comboBox3->addItem (TRANS("Raktom 2"), 14);
    comboBox3->addItem (TRANS("Raktom 1"), 15);
    comboBox3->addItem (TRANS("Ride"), 16);
    comboBox3->addItem (TRANS("Ride 2"), 17);
    comboBox3->addItem (TRANS("Cymbal 3"), 18);
    comboBox3->addItem (TRANS("Floortom 1"), 19);
    comboBox3->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Blink")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (comboBox4 = new ComboBox ("new combo box"));
    comboBox4->setEditableText (false);
    comboBox4->setJustificationType (Justification::centredLeft);
    comboBox4->setTextWhenNothingSelected (String());
    comboBox4->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox4->addItem (TRANS("One Shot Pad"), 1);
    comboBox4->addItem (TRANS("Shaker Pad"), 2);
    comboBox4->addItem (TRANS("Tamborine Pad"), 3);
    comboBox4->addItem (TRANS("Snare 1"), 4);
    comboBox4->addItem (TRANS("Snare 2"), 5);
    comboBox4->addItem (TRANS("Hi-Hat 1"), 6);
    comboBox4->addItem (TRANS("Hi-Hat 2"), 7);
    comboBox4->addItem (TRANS("Cymbal 4"), 8);
    comboBox4->addItem (TRANS("Cymbal 2"), 9);
    comboBox4->addItem (TRANS("Cymbal 1"), 10);
    comboBox4->addItem (TRANS("Kick"), 11);
    comboBox4->addItem (TRANS("Floortom 2"), 12);
    comboBox4->addItem (TRANS("Raktom 3"), 13);
    comboBox4->addItem (TRANS("Raktom 2"), 14);
    comboBox4->addItem (TRANS("Raktom 1"), 15);
    comboBox4->addItem (TRANS("Ride"), 16);
    comboBox4->addItem (TRANS("Ride 2"), 17);
    comboBox4->addItem (TRANS("Cymbal 3"), 18);
    comboBox4->addItem (TRANS("Floortom 1"), 19);
    comboBox4->addListener (this);

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Smile")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (comboBox5 = new ComboBox ("new combo box"));
    comboBox5->setEditableText (false);
    comboBox5->setJustificationType (Justification::centredLeft);
    comboBox5->setTextWhenNothingSelected (String());
    comboBox5->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox5->addItem (TRANS("One Shot Pad"), 1);
    comboBox5->addItem (TRANS("Shaker Pad"), 2);
    comboBox5->addItem (TRANS("Tamborine Pad"), 3);
    comboBox5->addItem (TRANS("Snare 1"), 4);
    comboBox5->addItem (TRANS("Snare 2"), 5);
    comboBox5->addItem (TRANS("Hi-Hat 1"), 6);
    comboBox5->addItem (TRANS("Hi-Hat 2"), 7);
    comboBox5->addItem (TRANS("Cymbal 4"), 8);
    comboBox5->addItem (TRANS("Cymbal 2"), 9);
    comboBox5->addItem (TRANS("Cymbal 1"), 10);
    comboBox5->addItem (TRANS("Kick"), 11);
    comboBox5->addItem (TRANS("Floortom 2"), 12);
    comboBox5->addItem (TRANS("Raktom 3"), 13);
    comboBox5->addItem (TRANS("Raktom 2"), 14);
    comboBox5->addItem (TRANS("Raktom 1"), 15);
    comboBox5->addItem (TRANS("Ride"), 16);
    comboBox5->addItem (TRANS("Ride 2"), 17);
    comboBox5->addItem (TRANS("Cymbal 3"), 18);
    comboBox5->addItem (TRANS("Floortom 1"), 19);
    comboBox5->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Clench")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Raise Eyebrows")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (comboBox6 = new ComboBox ("new combo box"));
    comboBox6->setEditableText (false);
    comboBox6->setJustificationType (Justification::centredLeft);
    comboBox6->setTextWhenNothingSelected (String());
    comboBox6->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox6->addItem (TRANS("One Shot Pad"), 1);
    comboBox6->addItem (TRANS("Shaker Pad"), 2);
    comboBox6->addItem (TRANS("Tamborine Pad"), 3);
    comboBox6->addItem (TRANS("Snare 1"), 4);
    comboBox6->addItem (TRANS("Snare 2"), 5);
    comboBox6->addItem (TRANS("Hi-Hat 1"), 6);
    comboBox6->addItem (TRANS("Hi-Hat 2"), 7);
    comboBox6->addItem (TRANS("Cymbal 4"), 8);
    comboBox6->addItem (TRANS("Cymbal 2"), 9);
    comboBox6->addItem (TRANS("Cymbal 1"), 10);
    comboBox6->addItem (TRANS("Kick"), 11);
    comboBox6->addItem (TRANS("Floortom 2"), 12);
    comboBox6->addItem (TRANS("Raktom 3"), 13);
    comboBox6->addItem (TRANS("Raktom 2"), 14);
    comboBox6->addItem (TRANS("Raktom 1"), 15);
    comboBox6->addItem (TRANS("Ride"), 16);
    comboBox6->addItem (TRANS("Ride 2"), 17);
    comboBox6->addItem (TRANS("Cymbal 3"), 18);
    comboBox6->addItem (TRANS("Floortom 1"), 19);
    comboBox6->addListener (this);

    addAndMakeVisible (comboBox7 = new ComboBox ("new combo box"));
    comboBox7->setEditableText (false);
    comboBox7->setJustificationType (Justification::centredLeft);
    comboBox7->setTextWhenNothingSelected (String());
    comboBox7->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox7->addItem (TRANS("One Shot Pad"), 1);
    comboBox7->addItem (TRANS("Shaker Pad"), 2);
    comboBox7->addItem (TRANS("Tamborine Pad"), 3);
    comboBox7->addItem (TRANS("Snare 1"), 4);
    comboBox7->addItem (TRANS("Snare 2"), 5);
    comboBox7->addItem (TRANS("Hi-Hat 1"), 6);
    comboBox7->addItem (TRANS("Hi-Hat 2"), 7);
    comboBox7->addItem (TRANS("Cymbal 4"), 8);
    comboBox7->addItem (TRANS("Cymbal 2"), 9);
    comboBox7->addItem (TRANS("Cymbal 1"), 10);
    comboBox7->addItem (TRANS("Kick"), 11);
    comboBox7->addItem (TRANS("Floortom 2"), 12);
    comboBox7->addItem (TRANS("Raktom 3"), 13);
    comboBox7->addItem (TRANS("Raktom 2"), 14);
    comboBox7->addItem (TRANS("Raktom 1"), 15);
    comboBox7->addItem (TRANS("Ride"), 16);
    comboBox7->addItem (TRANS("Ride 2"), 17);
    comboBox7->addItem (TRANS("Cymbal 3"), 18);
    comboBox7->addItem (TRANS("Floortom 1"), 19);
    comboBox7->addListener (this);

    addAndMakeVisible (switchStateButton = new TextButton ("new button"));
    switchStateButton->setButtonText (TRANS("Switch State"));
    switchStateButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

	extern int GLOBAL_WINDOW_WIDTH;
	extern int GLOBAL_WINDOW_HEIGHT;
	setSize(GLOBAL_WINDOW_HEIGHT, GLOBAL_WINDOW_WIDTH);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CustomGUIComponent::~CustomGUIComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    comboBox = nullptr;
    label = nullptr;
    label2 = nullptr;
    comboBox2 = nullptr;
    label3 = nullptr;
    comboBox3 = nullptr;
    label4 = nullptr;
    comboBox4 = nullptr;
    label5 = nullptr;
    comboBox5 = nullptr;
    label6 = nullptr;
    label7 = nullptr;
    comboBox6 = nullptr;
    comboBox7 = nullptr;
    switchStateButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CustomGUIComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CustomGUIComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    comboBox->setBounds (208, 32, 150, 24);
    label->setBounds (24, 32, 150, 24);
    label2->setBounds (24, 96, 150, 24);
    comboBox2->setBounds (208, 96, 150, 24);
    label3->setBounds (24, 160, 150, 24);
    comboBox3->setBounds (208, 160, 150, 24);
    label4->setBounds (24, 224, 150, 24);
    comboBox4->setBounds (208, 224, 150, 24);
    label5->setBounds (24, 288, 150, 24);
    comboBox5->setBounds (208, 288, 150, 24);
    label6->setBounds (24, 352, 150, 24);
    label7->setBounds (24, 416, 150, 24);
    comboBox6->setBounds (208, 352, 150, 24);
    comboBox7->setBounds (208, 416, 150, 24);
    switchStateButton->setBounds (112, 488, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CustomGUIComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox)
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
		std::string stringOnScreen = comboBoxThatHasChanged->getText().toStdString();
		map[0] = translator[stringOnScreen];
		std::string testString = std::to_string(translator[stringOnScreen]);
		Logger::outputDebugString(stringOnScreen);
		Logger::outputDebugString(testString);
        //[/UserComboBoxCode_comboBox]
    }
    else if (comboBoxThatHasChanged == comboBox2)
    {
        //[UserComboBoxCode_comboBox2] -- add your combo box handling code here..
		std::string stringOnScreen = comboBoxThatHasChanged->getText().toStdString();
		map[1] = translator[stringOnScreen];
		Logger::outputDebugString(stringOnScreen);
        //[/UserComboBoxCode_comboBox2]
    }
    else if (comboBoxThatHasChanged == comboBox3)
    {
        //[UserComboBoxCode_comboBox3] -- add your combo box handling code here..
		std::string stringOnScreen = comboBoxThatHasChanged->getText().toStdString();
		map[2] = translator[stringOnScreen];
		Logger::outputDebugString(stringOnScreen);
        //[/UserComboBoxCode_comboBox3]
    }
    else if (comboBoxThatHasChanged == comboBox4)
    {
        //[UserComboBoxCode_comboBox4] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox4]
    }
    else if (comboBoxThatHasChanged == comboBox5)
    {
        //[UserComboBoxCode_comboBox5] -- add your combo box handling code here..
		std::string stringOnScreen = comboBoxThatHasChanged->getText().toStdString();
		map[4] = translator[stringOnScreen];
		Logger::outputDebugString(stringOnScreen);
        //[/UserComboBoxCode_comboBox5]
    }
    else if (comboBoxThatHasChanged == comboBox6)
    {
        //[UserComboBoxCode_comboBox6] -- add your combo box handling code here..
		std::string stringOnScreen = comboBoxThatHasChanged->getText().toStdString();
		map[5] = translator[stringOnScreen];
		Logger::outputDebugString(stringOnScreen);
        //[/UserComboBoxCode_comboBox6]
    }
    else if (comboBoxThatHasChanged == comboBox7)
    {
        //[UserComboBoxCode_comboBox7] -- add your combo box handling code here..
		std::string stringOnScreen = comboBoxThatHasChanged->getText().toStdString();
		map[6] = translator[stringOnScreen];
		Logger::outputDebugString(stringOnScreen);
        //[/UserComboBoxCode_comboBox7]
    }

    //[UsercomboBoxChanged_Post]
	/*for (int i = 0; i < 7; i++)
	{
		std::string printNumber = std::to_string(map[i]);
		Logger::outputDebugString(printNumber);
	}*/
    //[/UsercomboBoxChanged_Post]
}

void CustomGUIComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == switchStateButton)
    {
        //[UserButtonCode_switchStateButton] -- add your button handler code here..
		/*extern MainContentComponent* mainState;*/
		MainContentComponent* mainContentComponent = new MainContentComponent();
		this->setVisible(false);
		mainContentComponent->setVisible(true);
		this->addChildComponent(mainContentComponent);
		this->setVisible(mainContentComponent);
        //[/UserButtonCode_switchStateButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CustomGUIComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <COMBOBOX name="new combo box" id="eb7e4d230a59ea12" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="208 32 150 24" editable="0"
            layout="33" items="One Shot Pad&#10;Shaker Pad&#10;Tamborine Pad&#10;Snare 1&#10;Snare 2&#10;Hi-Hat 1&#10;Hi-Hat 2&#10;Cymbal 4&#10;Cymbal 2&#10;Cymbal 1&#10;Kick&#10;Floortom 2&#10;Raktom 3&#10;Raktom 2&#10;Raktom 1&#10;Ride&#10;Ride 2&#10;Cymbal 3&#10;Floortom 1"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="8a74a111fa9f4fbc" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="24 32 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Button 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="459a40e04a1eb76b" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="24 96 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Button 2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="4ba7edeaef8641c0" memberName="comboBox2"
            virtualName="" explicitFocusOrder="0" pos="208 96 150 24" editable="0"
            layout="33" items="One Shot Pad&#10;Shaker Pad&#10;Tamborine Pad&#10;Snare 1&#10;Snare 2&#10;Hi-Hat 1&#10;Hi-Hat 2&#10;Cymbal 4&#10;Cymbal 2&#10;Cymbal 1&#10;Kick&#10;Floortom 2&#10;Raktom 3&#10;Raktom 2&#10;Raktom 1&#10;Ride&#10;Ride 2&#10;Cymbal 3&#10;Floortom 1"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="f5b242103ab04083" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="24 160 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Furrow" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="2fb595819ad0b7e" memberName="comboBox3"
            virtualName="" explicitFocusOrder="0" pos="208 160 150 24" editable="0"
            layout="33" items="One Shot Pad&#10;Shaker Pad&#10;Tamborine Pad&#10;Snare 1&#10;Snare 2&#10;Hi-Hat 1&#10;Hi-Hat 2&#10;Cymbal 4&#10;Cymbal 2&#10;Cymbal 1&#10;Kick&#10;Floortom 2&#10;Raktom 3&#10;Raktom 2&#10;Raktom 1&#10;Ride&#10;Ride 2&#10;Cymbal 3&#10;Floortom 1"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="95b6ac890e744b67" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="24 224 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Blink" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="8b28d5ddad15728a" memberName="comboBox4"
            virtualName="" explicitFocusOrder="0" pos="208 224 150 24" editable="0"
            layout="33" items="One Shot Pad&#10;Shaker Pad&#10;Tamborine Pad&#10;Snare 1&#10;Snare 2&#10;Hi-Hat 1&#10;Hi-Hat 2&#10;Cymbal 4&#10;Cymbal 2&#10;Cymbal 1&#10;Kick&#10;Floortom 2&#10;Raktom 3&#10;Raktom 2&#10;Raktom 1&#10;Ride&#10;Ride 2&#10;Cymbal 3&#10;Floortom 1"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="9ab26cf5f1e49ba5" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="24 288 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Smile" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="a7182e0cec5bf312" memberName="comboBox5"
            virtualName="" explicitFocusOrder="0" pos="208 288 150 24" editable="0"
            layout="33" items="One Shot Pad&#10;Shaker Pad&#10;Tamborine Pad&#10;Snare 1&#10;Snare 2&#10;Hi-Hat 1&#10;Hi-Hat 2&#10;Cymbal 4&#10;Cymbal 2&#10;Cymbal 1&#10;Kick&#10;Floortom 2&#10;Raktom 3&#10;Raktom 2&#10;Raktom 1&#10;Ride&#10;Ride 2&#10;Cymbal 3&#10;Floortom 1"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="d3c9e06f8c480e2b" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="24 352 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Clench" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c60cb02c3757d4e9" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="24 416 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Raise Eyebrows" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="c704ef09838ee1ce" memberName="comboBox6"
            virtualName="" explicitFocusOrder="0" pos="208 352 150 24" editable="0"
            layout="33" items="One Shot Pad&#10;Shaker Pad&#10;Tamborine Pad&#10;Snare 1&#10;Snare 2&#10;Hi-Hat 1&#10;Hi-Hat 2&#10;Cymbal 4&#10;Cymbal 2&#10;Cymbal 1&#10;Kick&#10;Floortom 2&#10;Raktom 3&#10;Raktom 2&#10;Raktom 1&#10;Ride&#10;Ride 2&#10;Cymbal 3&#10;Floortom 1"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="3ae670b881a37c04" memberName="comboBox7"
            virtualName="" explicitFocusOrder="0" pos="208 416 150 24" editable="0"
            layout="33" items="One Shot Pad&#10;Shaker Pad&#10;Tamborine Pad&#10;Snare 1&#10;Snare 2&#10;Hi-Hat 1&#10;Hi-Hat 2&#10;Cymbal 4&#10;Cymbal 2&#10;Cymbal 1&#10;Kick&#10;Floortom 2&#10;Raktom 3&#10;Raktom 2&#10;Raktom 1&#10;Ride&#10;Ride 2&#10;Cymbal 3&#10;Floortom 1"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="8d97ad08df3bd0ff" memberName="switchStateButton"
              virtualName="" explicitFocusOrder="0" pos="112 488 150 24" buttonText="Switch State"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
