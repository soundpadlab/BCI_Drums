import sys
import os
import platform
import time
import ctypes
import ConfigParser

import threading
from threading import Thread

if sys.platform.startswith('win32'):
    import msvcrt
elif sys.platform.startswith('linux'):
    import atexit
    from select import select

from ctypes import *

from array import *
from ctypes import *
from __builtin__ import exit
from socket import *
from pynput import keyboard

configParser = ConfigParser.RawConfigParser()   
configFilePath = r'sensitivity.conf'
configParser.read(configFilePath)

s_blink = float(configParser.get('sensitivity-config', 'blink'))
s_smile = float(configParser.get('sensitivity-config', 'smile'))
s_raisebr = float(configParser.get('sensitivity-config', 'raise-brows'))
s_clench = float(configParser.get('sensitivity-config', 'clench'))
s_frown = float(configParser.get('sensitivity-config', 'frown'))
s_lwink = float(configParser.get('sensitivity-config', 'left-wink'))
s_rwink = float(configParser.get('sensitivity-config', 'right-wink'))


count_b = 0
count_lw = 0
count_rw = 0
count_fr = 0
count_sm = 0
count_cl = 0
count_eb = 0

count_limit_b = float(configParser.get('sensitivity-config', 'count_limit_blink'))
count_limit_lw = float(configParser.get('sensitivity-config', 'count_limit_left_wink'))
count_limit_rw = float(configParser.get('sensitivity-config', 'count_limit_right_wink'))
count_limit_fr = float(configParser.get('sensitivity-config', 'count_limit_frown'))
count_limit_sm = float(configParser.get('sensitivity-config', 'count_limit_smile'))
count_limit_cl = float(configParser.get('sensitivity-config', 'count_limit_clench'))
count_limit_eb = float(configParser.get('sensitivity-config', 'count_limit_raise_brows'))

BROADCAST_PORT = 8889
SOCKET = socket(AF_INET, SOCK_DGRAM)
SOCKET.bind(('', 0))
SOCKET.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)

try:
    if sys.platform.startswith('win32'):
        libEDK = cdll.LoadLibrary("bin/win32/edk.dll")
    elif sys.platform.startswith('linux'):
        srcDir = os.getcwd()
        if platform.machine().startswith('arm'):
            libPath = srcDir + "/../../bin/armhf/libedk.so"
        else:
            libPath = srcDir + "/../../bin/linux64/libedk.so"
        libEDK = CDLL(libPath)
    else:
        raise Exception('System not supported.')
except Exception as e:
    print ("Error: cannot load EDK lib:", e)
    exit()

write = sys.stdout.write
IEE_EmoEngineEventCreate = libEDK.IEE_EmoEngineEventCreate
IEE_EmoEngineEventCreate.restype = c_void_p
eEvent = IEE_EmoEngineEventCreate()

IEE_EmoEngineEventGetEmoState = libEDK.IEE_EmoEngineEventGetEmoState
IEE_EmoEngineEventGetEmoState.argtypes = [c_void_p, c_void_p]
IEE_EmoEngineEventGetEmoState.restype = c_int

IS_GetTimeFromStart = libEDK.IS_GetTimeFromStart
IS_GetTimeFromStart.argtypes = [ctypes.c_void_p]
IS_GetTimeFromStart.restype = c_float

IEE_EmoStateCreate = libEDK.IEE_EmoStateCreate
IEE_EmoStateCreate.restype = c_void_p
eState = IEE_EmoStateCreate()

IS_GetWirelessSignalStatus = libEDK.IS_GetWirelessSignalStatus
IS_GetWirelessSignalStatus.restype = c_int
IS_GetWirelessSignalStatus.argtypes = [c_void_p]
##
IS_FacialExpressionGetSmileExtent = libEDK.IS_FacialExpressionGetSmileExtent
IS_FacialExpressionGetSmileExtent.restype = c_float
IS_FacialExpressionGetSmileExtent.argtypes = [c_void_p]

IS_FacialExpressionGetClenchExtent = libEDK.IS_FacialExpressionGetClenchExtent
IS_FacialExpressionGetClenchExtent.restype = c_float
IS_FacialExpressionGetClenchExtent.argtypes = [c_void_p]

IS_FacialExpressionGetEyebrowExtent = libEDK.IS_FacialExpressionGetEyebrowExtent
IS_FacialExpressionGetEyebrowExtent.restype = c_float
IS_FacialExpressionGetEyebrowExtent.argtypes = [c_void_p]

##
IS_FacialExpressionIsBlink = libEDK.IS_FacialExpressionIsBlink
IS_FacialExpressionIsBlink.restype = c_int
IS_FacialExpressionIsBlink.argtypes = [c_void_p]

IS_FacialExpressionIsLeftWink = libEDK.IS_FacialExpressionIsLeftWink
IS_FacialExpressionIsLeftWink.restype = c_int
IS_FacialExpressionIsLeftWink.argtypes = [c_void_p]

IS_FacialExpressionIsRightWink = libEDK.IS_FacialExpressionIsRightWink
IS_FacialExpressionIsRightWink.restype = c_int
IS_FacialExpressionIsRightWink.argtypes = [c_void_p]

# Engine Functions
EngineGetNextEvent = libEDK.IEE_EngineGetNextEvent
EngineGetNextEvent.restype = c_int
EngineGetNextEvent.argtypes = [c_void_p]

EmoEngineEventGetType = libEDK.IEE_EmoEngineEventGetType
EmoEngineEventGetType.restype = c_int
EmoEngineEventGetType.argtypes = [c_void_p]

EmoEngineEventGetUserId = libEDK.IEE_EmoEngineEventGetUserId
EmoEngineEventGetUserId.restype = c_int
EmoEngineEventGetUserId.argtypes = [c_void_p]

EmoEngineEventGetEmoState = libEDK.IEE_EmoEngineEventGetEmoState
EmoEngineEventGetEmoState.restype = c_int
EmoEngineEventGetEmoState.argtypes = [c_void_p, c_void_p]
# -------------------------------------------------------------------------

def logEmoState(userID, eState):

    global count_b, count_lw, count_rw, count_fr, count_sm, count_cl, count_eb, count_limit_b, count_limit_lw, count_limit_rw, count_limit_fr, count_limit_sm, count_limit_cl, count_limit_eb, s_blink, s_smile, s_raisebr, s_clench, s_frown, s_lwink, s_rwink

    FacialExpressionStates = {}
    FacialExpressionStates[FE_FROWN] = 0
    FacialExpressionStates[FE_SMILE] = IS_FacialExpressionGetSmileExtent(eState)
    FacialExpressionStates[FE_CLENCH] = IS_FacialExpressionGetClenchExtent(eState)

##    print "BLINK: %.6f | SMILE: %.6f | RAISE-BROWS: %.6f | %.6f, %.6f, %.6f %.6f\n" % (IS_FacialExpressionIsBlink(eState), FacialExpressionStates[FE_SMILE], IS_FacialExpressionGetEyebrowExtent(eState), IS_FacialExpressionIsLeftWink(eState), IS_FacialExpressionIsRightWink(eState), FacialExpressionStates[FE_FROWN], FacialExpressionStates[FE_CLENCH])
    
    sum = IS_FacialExpressionIsBlink(eState) + IS_FacialExpressionIsLeftWink(eState) + IS_FacialExpressionIsRightWink(eState) + FacialExpressionStates[FE_FROWN] + FacialExpressionStates[FE_SMILE] + FacialExpressionStates[FE_CLENCH] + IS_FacialExpressionGetEyebrowExtent(eState)
    if (sum>0):    
##        SOCKET.sendto("%.6f, %.6f, %.6f, %.6f, %.6f, %.6f \n" % (IS_FacialExpressionIsBlink(eState), IS_FacialExpressionIsLeftWink(eState), IS_FacialExpressionIsRightWink(eState), FacialExpressionStates[FE_FROWN], FacialExpressionStates[FE_SMILE], FacialExpressionStates[FE_CLENCH]), ('127.0.0.1', BROADCAST_PORT))
        if (IS_FacialExpressionIsBlink(eState)>=s_blink):
            count_b += 1
            if (count_b >= count_limit_b):
                print('Blink');
                SOCKET.sendto("blink", ('127.0.0.1', BROADCAST_PORT))
                count_b = 0
        elif (IS_FacialExpressionIsLeftWink(eState)>=s_lwink):
            count_lw += 1
            if (count_lw >= count_limit_lw):
                print('Blink');
                SOCKET.sendto("left-wink", ('127.0.0.1', BROADCAST_PORT))
                count_lw = 0
        elif (IS_FacialExpressionIsRightWink(eState)>=s_rwink):
            count_rw += 1
            if (count_rw >= count_limit_rw):
                print('Blink');
                SOCKET.sendto("right-wink", ('127.0.0.1', BROADCAST_PORT))
                count_rw = 0
        elif (FacialExpressionStates[FE_FROWN]>=s_frown):
            count_fr += 1
            if (count_fr >= count_limit_fr):
                print('Frown');
                SOCKET.sendto("furrow", ('127.0.0.1', BROADCAST_PORT))
                count_fr = 0
        elif (FacialExpressionStates[FE_SMILE]>=s_smile):
            count_sm += 1
            if (count_sm >= count_limit_sm):
                print('Smile');
                SOCKET.sendto("smile", ('127.0.0.1', BROADCAST_PORT))
                count_sm = 0
        elif (FacialExpressionStates[FE_CLENCH]>=s_clench):
            count_cl += 1
            if (count_cl >= count_limit_cl):
                print('Clench');
                SOCKET.sendto("clench", ('127.0.0.1', BROADCAST_PORT))
                count_cl = 0
        elif (IS_FacialExpressionGetEyebrowExtent(eState)>=s_raisebr):
            count_eb += 1
            if (count_eb >= count_limit_eb):
                print('Raise Eyebrows');
                SOCKET.sendto("raise-brow", ('127.0.0.1', BROADCAST_PORT))
                count_eb = 0

    
def kbhit():
    ''' Returns True if keyboard character was hit, False otherwise.
    '''
    if sys.platform.startswith('win32'):
        return msvcrt.kbhit()   
    else:
        dr,dw,de = select([sys.stdin], [], [], 0)
        return dr != []

# -------------------------------------------------------------------------

userID = c_uint(0)
user   = pointer(userID)
option = c_int(0)
state  = c_int(0)
composerPort = c_uint(1726)
timestamp    = c_float(0.0)

FE_SUPPRISE = 0x0020 
FE_FROWN    = 0x0040
FE_SMILE    = 0x0080
FE_CLENCH   = 0x0100

PM_EXCITEMENT = 0x0001,
PM_RELAXATION = 0x0002,
PM_STRESS     = 0x0004,
PM_ENGAGEMENT = 0x0008,

PM_INTEREST   = 0x0010,
PM_FOCUS      = 0x0020


def facialExp():
    if libEDK.IEE_EngineConnect("Emotiv Systems-5") != 0:
            print "Emotiv Engine start up failed."
            
    while (1):


        ##test-begin
##        SOCKET.sendto("button1", ('127.0.0.1', BROADCAST_PORT))
##        time.sleep(0.4)
##        SOCKET.sendto("button2", ('127.0.0.1', BROADCAST_PORT))
##        time.sleep(0.4)
##        SOCKET.sendto("smile", ('127.0.0.1', BROADCAST_PORT))
##        time.sleep(0.4)
##        SOCKET.sendto("clench", ('127.0.0.1', BROADCAST_PORT))
##        time.sleep(0.4)
##        SOCKET.sendto("furrow", ('127.0.0.1', BROADCAST_PORT))
##        time.sleep(0.4)
##        SOCKET.sendto("blink", ('127.0.0.1', BROADCAST_PORT))
##        time.sleep(0.4)
##        SOCKET.sendto("raise-brow", ('127.0.0.1', BROADCAST_PORT))
##        time.sleep(0.4)
##        print('sent expresions');
        ##test-end
        
        state = EngineGetNextEvent(eEvent)
        if state >= 0:
            eventType = EmoEngineEventGetType(eEvent)
            EmoEngineEventGetUserId(eEvent, user)
            if eventType == 64:  # libEDK.IEE_Event_enum.IEE_EmoStateUpdated
                EmoEngineEventGetEmoState(eEvent, eState)
    ##            timestamp = IS_GetTimeFromStart(eState)
    ##            print "%10.3f New EmoState from user %d ...\r" % (timestamp,userID.value)
                logEmoState(userID, eState)     
        elif state != 0x0600:
            print "%10.0f Internal error in Emotiv Engine ! " %(state)
        time.sleep(0.1)
    # -------------------------------------------------------------------------
    ##f.close()
    libEDK.IEE_EngineDisconnect()
    libEDK.IEE_EmoStateFree(eState)
    libEDK.IEE_EmoEngineEventFree(eEvent)


def on_press(key):
    try: k = key.char # single-char keys
    except: k = key.name # other keys
##    if key == keyboard.Key.esc: return False # stop listener
    if k in ['1', '2']: # keys interested
        # self.keys.append(k) # store it in global-like variable
        print('Key pressed: ' + k)
        if k == '1':
            SOCKET.sendto("left", ('127.0.0.1', BROADCAST_PORT))
        else:
            SOCKET.sendto("right", ('127.0.0.1', BROADCAST_PORT))

        #return False # remove this if want more keys

lis = keyboard.Listener(on_press=on_press)
lis.start() # start to listen on a separate thread
Thread(target = facialExp).start()
lis.join() # no this if main thread is polling self.keys

