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

//bci code


//#include "stdafx.h"

//
/*
Simple udp client
*/
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 1024  //Max length of buffer
#define PORT 8889   //The port on which to listen for incoming data

//bci code ends

#include "MainComponent.h"
#include "CustomGUIComponent.h"
#include <string>


//==============================================================================
struct MidiDeviceListEntry : ReferenceCountedObject
{
    MidiDeviceListEntry (const String& deviceName) : name (deviceName) {}

    String name;
    ScopedPointer<MidiInput> inDevice;
    ScopedPointer<MidiOutput> outDevice;

    typedef ReferenceCountedObjectPtr<MidiDeviceListEntry> Ptr;
};

//==============================================================================
struct MidiCallbackMessage : public Message
{
    MidiCallbackMessage (const MidiMessage& msg) : message (msg) {}
    MidiMessage message;
};

//==============================================================================
class MidiDeviceListBox : public ListBox,
private ListBoxModel
{
public:
    //==============================================================================
    MidiDeviceListBox (const String& name,
                       MainContentComponent& contentComponent,
                       bool isInputDeviceList)
    : ListBox (name, this),
      parent (contentComponent),
      isInput (isInputDeviceList)
    {
        setOutlineThickness (1);
        setMultipleSelectionEnabled (true);
        setClickingTogglesRowSelection (true);
    }

    //==============================================================================
    int getNumRows() override
    {
        return isInput ? parent.getNumMidiInputs()
                       : parent.getNumMidiOutputs();
    }

    //==============================================================================
    void paintListBoxItem (int rowNumber, Graphics &g,
                           int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
            g.fillAll (Colours::lightblue);
        else if (rowNumber % 2)
            g.fillAll (Colour (0xffeeeeee));


        g.setColour (Colours::black);
        g.setFont (height * 0.7f);

        if (isInput)
        {
            if (rowNumber < parent.getNumMidiInputs())
                g.drawText (parent.getMidiDevice (rowNumber, true)->name,
                            5, 0, width, height,
                            Justification::centredLeft, true);
        }
        else
        {
            if (rowNumber < parent.getNumMidiOutputs())
                g.drawText (parent.getMidiDevice (rowNumber, false)->name,
                            5, 0, width, height,
                            Justification::centredLeft, true);
        }
    }

    //==============================================================================
    void selectedRowsChanged (int) override
    {
        SparseSet<int> newSelectedItems = getSelectedRows();
        if (newSelectedItems != lastSelectedItems)
        {
            for (int i = 0; i < lastSelectedItems.size(); ++i)
            {
                if (! newSelectedItems.contains (lastSelectedItems[i]))
                    parent.closeDevice (isInput, lastSelectedItems[i]);
            }

            for (int i = 0; i < newSelectedItems.size(); ++i)
            {
                if (! lastSelectedItems.contains (newSelectedItems[i]))
                    parent.openDevice (isInput, newSelectedItems[i]);
            }

            lastSelectedItems = newSelectedItems;
        }
    }

    //==============================================================================
    void syncSelectedItemsWithDeviceList (const ReferenceCountedArray<MidiDeviceListEntry>& midiDevices)
    {
        SparseSet<int> selectedRows;
        for (int i = 0; i < midiDevices.size(); ++i)
            if (midiDevices[i]->inDevice != nullptr || midiDevices[i]->outDevice != nullptr)
                selectedRows.addRange (Range<int> (i, i+1));

        lastSelectedItems = selectedRows;
        updateContent();
        setSelectedRows (selectedRows, dontSendNotification);
    }

private:
    //==============================================================================
    MainContentComponent& parent;
    bool isInput;
    SparseSet<int> lastSelectedItems;
};

//==============================================================================
MainContentComponent::MainContentComponent ()
    : midiInputLabel ("Midi Input Label", "MIDI Input:"),
      midiOutputLabel ("Midi Output Label", "MIDI Output:"),
      incomingMidiLabel ("Incoming Midi Label", "Received MIDI messages:"),
      outgoingMidiLabel ("Outgoing Midi Label", "Play the keyboard to send MIDI messages..."),
      midiKeyboard (keyboardState, MidiKeyboardComponent::horizontalKeyboard),
      midiMonitor ("MIDI Monitor"),
      pairButton ("MIDI Bluetooth devices..."),
      midiInputSelector (new MidiDeviceListBox ("Midi Input Selector", *this, true)),
      midiOutputSelector (new MidiDeviceListBox ("Midi Input Selector", *this, false))
{
	extern int GLOBAL_WINDOW_WIDTH;
	extern int GLOBAL_WINDOW_HEIGHT;
	setSize(GLOBAL_WINDOW_HEIGHT, GLOBAL_WINDOW_WIDTH);

    addLabelAndSetStyle (midiInputLabel);
    addLabelAndSetStyle (midiOutputLabel);
    //addLabelAndSetStyle (incomingMidiLabel);
    //addLabelAndSetStyle (outgoingMidiLabel);

    midiKeyboard.setName ("MIDI Keyboard");
    //addAndMakeVisible (midiKeyboard);

    midiMonitor.setMultiLine (true);
    midiMonitor.setReturnKeyStartsNewLine (false);
    midiMonitor.setReadOnly (true);
    midiMonitor.setScrollbarsShown (true);
    midiMonitor.setCaretVisible (false);
    midiMonitor.setPopupMenuEnabled (false);
    midiMonitor.setText (String());
    //addAndMakeVisible (midiMonitor);

    if (! BluetoothMidiDevicePairingDialogue::isAvailable())
        pairButton.setEnabled (false);

    //addAndMakeVisible (pairButton);
    pairButton.addListener (this);
    keyboardState.addListener (this);
	switchStateButton.addListener(this);
	startButton.addListener(this);
    addAndMakeVisible (midiInputSelector);
    addAndMakeVisible (midiOutputSelector);
	//Ben defined button
	addAndMakeVisible(switchStateButton);
	addAndMakeVisible(startButton);
	switchStateButton.setButtonText("Configure");
	startButton.setButtonText("Start");
	Logger::outputDebugString("YELLO IN CONSTRUCTOR");
	//bci_osc();

    startTimer (500);
}

void MainContentComponent::bci_osc()
{
	//bci code

	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising... ");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Ready!.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//Bind the server port
	if (bind(s, (LPSOCKADDR)&si_other, sizeof(si_other)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//start communication
	while (1)
	{

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		int action = -1;

		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			//exit(EXIT_FAILURE);
		}

		//MainContentComponent::handleNoteOn2:midi

		if (strcmp(buf, "blink") == 0 || strcmp(buf, "left-wink") == 0 || strcmp(buf, "right-wink") == 0) { action = 3; }
		else if (strcmp(buf, "smile") == 0) { action = 4; }
		else if (strcmp(buf, "raise-brow") == 0) { action = 6; }
		else if (strcmp(buf, "clench") == 0) { action = 5; }
		else if (strcmp(buf, "furrow") == 0) { action = 2; }
		else if (strcmp(buf, "button1") == 0) { action = 0; }
		else if (strcmp(buf, "button2") == 0) { action = 1; }

		//midiOutput->sendMessageNow(MidiMessage::noteOn(1, action, 1.0f));
		if (action != -1) {
			int midiNoteNumber = map[action];
			std::string stringNoteNumber = std::to_string(midiNoteNumber);
			Logger::outputDebugString(stringNoteNumber);
			Logger::outputDebugString(buf);
			MidiMessage m(MidiMessage::noteOn(1, midiNoteNumber, 1.0f));
			m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
			sendToOutputs(m);
		}

	}

	closesocket(s);
	WSACleanup();


	//bci code ends
}
//==============================================================================
void MainContentComponent::addLabelAndSetStyle (Label& label)
{
    label.setFont (Font (15.00f, Font::plain));
    label.setJustificationType (Justification::centredLeft);
    label.setEditable (false, false, false);
    label.setColour (TextEditor::textColourId, Colours::black);
    label.setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label);
}

//==============================================================================
MainContentComponent::~MainContentComponent()
{
    stopTimer();
    midiInputs.clear();
    midiOutputs.clear();
    keyboardState.removeListener (this);
	switchStateButton.removeListener(this);
	startButton.removeListener(this);
    midiInputSelector = nullptr;
    midiOutputSelector = nullptr;
    midiOutputSelector = nullptr;
}

//==============================================================================
void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

//==============================================================================
void MainContentComponent::resized()
{
    const int margin = 10;
	switchStateButton.setBounds(488, 416, 150, 24);
	startButton.setBounds(288, 416, 75, 24);

    midiInputLabel.setBounds (margin, margin,
                              (getWidth() / 2) - (2 * margin), 24);

    midiOutputLabel.setBounds ((getWidth() / 2) + margin, margin,
                               (getWidth() / 2) - (2 * margin), 24);

    midiInputSelector->setBounds (margin, (2 * margin) + 24,
                                  (getWidth() / 2) - (2 * margin),
                                  (getHeight() / 2) - ((4 * margin) + 24 + 24));

    midiOutputSelector->setBounds ((getWidth() / 2) + margin, (2 * margin) + 24,
                                   (getWidth() / 2) - (2 * margin),
                                   (getHeight() / 2) - ((4 * margin) + 24 + 24));

    pairButton.setBounds (margin, (getHeight() / 2) - (margin + 24),
                          getWidth() - (2 * margin), 24);

    outgoingMidiLabel.setBounds (margin, getHeight() / 2, getWidth() - (2*margin), 24);
    midiKeyboard.setBounds (margin, (getHeight() / 2) + (24 + margin), getWidth() - (2*margin), 64);

    incomingMidiLabel.setBounds (margin, (getHeight() / 2) + (24 + (2 * margin) + 64),
                                 getWidth() - (2*margin), 24);

    int y = (getHeight() / 2) + ((2 * 24) + (3 * margin) + 64);
    midiMonitor.setBounds (margin, y,
                           getWidth() - (2*margin), getHeight() - y - margin);
}

//==============================================================================
void MainContentComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == &pairButton)
        RuntimePermissions::request (
            RuntimePermissions::bluetoothMidi,
            [] (bool wasGranted) { if (wasGranted) BluetoothMidiDevicePairingDialogue::open(); } );
	if (buttonThatWasClicked == &switchStateButton) 
	{
		CustomGUIComponent* customGUIComponent = new CustomGUIComponent();
		this->setVisible(false);
		customGUIComponent->setVisible(true);
		this->addChildComponent(customGUIComponent);
		this->setVisible(customGUIComponent);
		Logger::outputDebugString("YELLO");

	//	bci_osc();
	}
	else if (buttonThatWasClicked == &startButton)
	{
		bci_osc();
	}
}

//==============================================================================
bool MainContentComponent::hasDeviceListChanged (const StringArray& deviceNames, bool isInputDevice)
{
    ReferenceCountedArray<MidiDeviceListEntry>& midiDevices = isInputDevice ? midiInputs
                                                                            : midiOutputs;

    if (deviceNames.size() != midiDevices.size())
        return true;

    for (int i = 0; i < deviceNames.size(); ++i)
        if (deviceNames[i] != midiDevices[i]->name)
            return true;

    return false;
}

MidiDeviceListEntry::Ptr MainContentComponent::findDeviceWithName (const String& name, bool isInputDevice) const
{
    const ReferenceCountedArray<MidiDeviceListEntry>& midiDevices = isInputDevice ? midiInputs
                                                                                  : midiOutputs;

    for (int i = 0; i < midiDevices.size(); ++i)
        if (midiDevices[i]->name == name)
            return midiDevices[i];

    return nullptr;
}

void MainContentComponent::closeUnpluggedDevices (StringArray& currentlyPluggedInDevices, bool isInputDevice)
{
    ReferenceCountedArray<MidiDeviceListEntry>& midiDevices = isInputDevice ? midiInputs
                                                                            : midiOutputs;

    for (int i = midiDevices.size(); --i >= 0;)
    {
        MidiDeviceListEntry& d = *midiDevices[i];

        if (! currentlyPluggedInDevices.contains (d.name))
        {
            if (isInputDevice ? d.inDevice != nullptr
                              : d.outDevice != nullptr)
                closeDevice (isInputDevice, i);

            midiDevices.remove (i);
        }
    }
}

void MainContentComponent::updateDeviceList (bool isInputDeviceList)
{
    StringArray newDeviceNames = isInputDeviceList ? MidiInput::getDevices()
                                                   : MidiOutput::getDevices();

    if (hasDeviceListChanged (newDeviceNames, isInputDeviceList))
    {

        ReferenceCountedArray<MidiDeviceListEntry>& midiDevices
            = isInputDeviceList ? midiInputs : midiOutputs;

        closeUnpluggedDevices (newDeviceNames, isInputDeviceList);

        ReferenceCountedArray<MidiDeviceListEntry> newDeviceList;

        // add all currently plugged-in devices to the device list
        for (int i = 0; i < newDeviceNames.size(); ++i)
        {
            MidiDeviceListEntry::Ptr entry = findDeviceWithName (newDeviceNames[i], isInputDeviceList);

            if (entry == nullptr)
                entry = new MidiDeviceListEntry (newDeviceNames[i]);

            newDeviceList.add (entry);
        }

        // actually update the device list
        midiDevices = newDeviceList;

        // update the selection status of the combo-box
        if (MidiDeviceListBox* midiSelector = isInputDeviceList ? midiInputSelector : midiOutputSelector)
            midiSelector->syncSelectedItemsWithDeviceList (midiDevices);
    }
}

//==============================================================================
void MainContentComponent::timerCallback ()
{
    updateDeviceList (true);
    updateDeviceList (false);
}

//==============================================================================
void MainContentComponent::handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{

	
	midiNoteNumber = map[midiNoteNumber];
	std::string stringNoteNumber = std::to_string(midiNoteNumber);
	Logger::outputDebugString(stringNoteNumber);
	//Destroying input
	//midiNoteNumber = midiNoteNumber % 7;//7 because user can have 7 options
	//Now I can put it in the map

	//midiNoteNumber = map[midiNoteNumber];//gets the users mapping data

	//midiNoteNumber += 72;//Calibrate it back to the 4th octave

	//std::string stringNoteNumber2 = std::to_string(midiNoteNumber);
	//Logger::outputDebugString(stringNoteNumber2);
    MidiMessage m (MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity));
    m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
    sendToOutputs (m);
}


//==============================================================================
void MainContentComponent::handleNoteOn2(int midiNoteNumber)
{
	//handleNoteOn();
	
}
//==============================================================================
void MainContentComponent::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    MidiMessage m (MidiMessage::noteOff (midiChannel, midiNoteNumber, velocity));
    m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
    sendToOutputs (m);
}

//==============================================================================
void MainContentComponent::sendToOutputs(const MidiMessage& msg)
{
    for (int i = 0; i < midiOutputs.size(); ++i)
        if (midiOutputs[i]->outDevice != nullptr)
            midiOutputs[i]->outDevice->sendMessageNow (msg);
}

//==============================================================================
void MainContentComponent::handleIncomingMidiMessage (MidiInput* /*source*/, const MidiMessage &message)
{
    // This is called on the MIDI thread

    if (message.isNoteOnOrOff())
        postMessage (new MidiCallbackMessage (message));
}

//==============================================================================
void MainContentComponent::handleMessage (const Message& msg)
{
    // This is called on the message loop

    const MidiMessage& mm = dynamic_cast<const MidiCallbackMessage&> (msg).message;
    String midiString;
    midiString << (mm.isNoteOn() ? String ("Note on: ") : String ("Note off: "));
    midiString << (MidiMessage::getMidiNoteName (mm.getNoteNumber(), true, true, true));
    midiString << (String (" vel = "));
    midiString << static_cast<int>(mm.getVelocity());
    midiString << "\n";

    midiMonitor.insertTextAtCaret (midiString);
}

//==============================================================================
void MainContentComponent::openDevice (bool isInput, int index)
{
    if (isInput)
    {
        jassert (midiInputs[index]->inDevice == nullptr);
        midiInputs[index]->inDevice = MidiInput::openDevice (index, this);

        if (midiInputs[index]->inDevice == nullptr)
        {
            DBG ("MainContentComponent::openDevice: open input device for index = " << index << " failed!" );
            return;
        }

        midiInputs[index]->inDevice->start();
    }
    else
    {
        jassert (midiOutputs[index]->outDevice == nullptr);
        midiOutputs[index]->outDevice = MidiOutput::openDevice (index);

        if (midiOutputs[index]->outDevice == nullptr)
            DBG ("MainContentComponent::openDevice: open output device for index = " << index << " failed!" );
    }
}

//==============================================================================
void MainContentComponent::closeDevice (bool isInput, int index)
{
    if (isInput)
    {
        jassert (midiInputs[index]->inDevice != nullptr);
        midiInputs[index]->inDevice->stop();
        midiInputs[index]->inDevice = nullptr;
    }
    else
    {
        jassert (midiOutputs[index]->outDevice != nullptr);
        midiOutputs[index]->outDevice = nullptr;
    }
}

//==============================================================================
int MainContentComponent::getNumMidiInputs() const noexcept
{
    return midiInputs.size();
}

//==============================================================================
int MainContentComponent::getNumMidiOutputs() const noexcept
{
    return midiOutputs.size();
}

//==============================================================================
ReferenceCountedObjectPtr<MidiDeviceListEntry>
MainContentComponent::getMidiDevice (int index, bool isInput) const noexcept
{
    return isInput ? midiInputs[index] : midiOutputs[index];
}
