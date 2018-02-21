
================================================================

DEVELOPMENT:
------------

OPENING CODE:
1. Open BCI-Drums.sln in Visual Studio.
Location: BCI_Drums/Builds/VisualStudio2015/

USING UDP/OSC PORTS:
1. Incoming port in JUCE is 8889, use the same to send OSC messages from python/MATLAB to JUCE.
2. If sending data from python->MATLAB->JUCE, outgoing port for MATLAB must be 8889; and outgoing port for python must be same as incoming port for MATLAB (other than 8889)

DATA PASSING:
1. JUCE will accept only following string values:
"left"
"right"
"smile"
"clench"
"furrow"
"raise-brow"
"blink"

OTHER NOTES:
1.server.py
    -comment lines: 421-436 to disable testing without headset
    
2. demo.bat
    -placeholder for single starting point script file. Edit this once Machine Learning module is complete.

PENDING:
1. MATLAB Machine Learning model trainer and classifier. You may not change the python code and keep the same for both - training and classifying.
2. Parallel thread implementation for bci_osc in JUCE. Currently, this module runs as a serial execution thereby inhibiting re-configuration of mapping. To re-configure mapping, the application needs to be force-killed and re-opened.

================================================================

RUNNING APPLICATION (without Machine Learning):
------------
1. Open loopMidi
2. Open Studio One and then the song - BCI-Drums
3. Run server.py in BCI_Drums/Application
4. Run application from VisualStudio or run executable:
BCI_Drums/Builds/VisualStudio2015/Debug/MidiTest.exe
5. Provide mapping
6. Click Next
7. Select 'BCI-Drums-Midi' in Midi in and out
8. Click Start

================================================================

TRAINING:
location: BCI_Drums/Application/training/

1. Open 'training.m' in matlab
2. A window should pop up. Make appropriate selection from the dropdown menu (e.g smile, clench, etc)
3. click 'start'
4. Make the facial expression
5. After pre-set recording duration (default=5seconds), the recording will stop and a message 'saved' will appear on the window
6. Check the folder 'training/data/' for all the recordings
7. You can change the pre-set recording duration by changing the value of variable 'timeSlice' in 'trainingModule.m'

================================================================

SETUP:
Software:
1. MATLAB R2016b+
2. JUCE
3. Python 2.7.x
4. MS Visual Studio 2015+
5. Studio One Professional
6. EZDrummer
7. LoopMIDI
8. EMOTIV PRO / Xavier Control Panel 

Hardware:
1. EMOTIV Epoc+
2. USB Buttons with switcher

Steps:
1. Open Emotiv PRO / Xavier Control panel
2. Connect the EMOTIV USB dongle
3. Turn on the headset and wear it.
4. Look at the Xavier dashboard to see which sensors are not green, adjust sensor locations on head accordingly.
5. Once at least 10 are green, you're good to go. Aim for all green.
6. Connect the USB buttons switch and the buttons.
7. Open loopMIDI
8. Open Studio One template
9. Open demo.bat
