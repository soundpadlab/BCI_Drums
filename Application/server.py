import sys
import os
import platform
import time
import ctypes
import ConfigParser


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

##IS_FacialExpressionGetUpperFaceAction =  \
##    libEDK.IS_FacialExpressionGetUpperFaceAction
##IS_FacialExpressionGetUpperFaceAction.restype = c_int
##IS_FacialExpressionGetUpperFaceAction.argtypes = [c_void_p]
##
##IS_FacialExpressionGetUpperFaceActionPower = \
##    libEDK.IS_FacialExpressionGetUpperFaceActionPower
##IS_FacialExpressionGetUpperFaceActionPower.restype = c_float
##IS_FacialExpressionGetUpperFaceActionPower.argtypes = [c_void_p]
##
##IS_FacialExpressionGetLowerFaceAction = \
##    libEDK.IS_FacialExpressionGetLowerFaceAction
##IS_FacialExpressionGetLowerFaceAction.restype = c_int
##IS_FacialExpressionGetLowerFaceAction.argtypes = [c_void_p]
##
##IS_FacialExpressionGetLowerFaceActionPower = \
##    libEDK.IS_FacialExpressionGetLowerFaceActionPower
##IS_FacialExpressionGetLowerFaceActionPower.restype = c_float
##IS_FacialExpressionGetLowerFaceActionPower.argtypes = [c_void_p]
##
##IS_FacialExpressionGetEyeLocation = libEDK.IS_FacialExpressionGetEyeLocation
##IS_FacialExpressionGetEyeLocation.restype = c_float
##IS_FacialExpressionGetEyeLocation.argtype = [c_void_p]
##
##IS_FacialExpressionGetEyelidState = libEDK.IS_FacialExpressionGetEyelidState
##IS_FacialExpressionGetEyelidState.restype = c_float
##IS_FacialExpressionGetEyelidState.argtype = [c_void_p]
##
##EyeX = c_float(0)
##EyeY = c_float(0)
##EyeLidLeft = c_float(0)
##EyeLidRight = c_float(0)
##
##X = pointer(EyeX)
##Y = pointer(EyeY)
##Left = pointer(EyeLidLeft)
##Right = pointer(EyeLidRight)
##
###Perfomance metrics Model Parameters /long term excitement not present
##
##RawScore = c_double(0)
##MinScale = c_double(0)
##MaxScale = c_double(0)
##
##Raw = pointer(RawScore)
##Min = pointer(MinScale)
##Max = pointer(MaxScale)
##

# short term excitement
#IS_PerformanceMetricGetInstantaneousExcitementModelParams = libEDK.#IS_PerformanceMetricGetInstantaneousExcitementModelParams
#IS_PerformanceMetricGetInstantaneousExcitementModelParams.restype = c_void_p
#IS_PerformanceMetricGetInstantaneousExcitementModelParams.argtypes = [c_void_p]
##
### relaxation
##IS_PerformanceMetricGetRelaxationModelParams = libEDK.IS_PerformanceMetricGetRelaxationModelParams
##IS_PerformanceMetricGetRelaxationModelParams.restype = c_void_p
##IS_PerformanceMetricGetRelaxationModelParams.argtypes = [c_void_p]
##
### stress
##IS_PerformanceMetricGetStressModelParams = libEDK.IS_PerformanceMetricGetStressModelParams
##IS_PerformanceMetricGetStressModelParams.restype = c_void_p
##IS_PerformanceMetricGetStressModelParams.argtypes = [c_void_p]
##
### boredom/engagement
##IS_PerformanceMetricGetEngagementBoredomModelParams = libEDK.IS_PerformanceMetricGetEngagementBoredomModelParams
##IS_PerformanceMetricGetEngagementBoredomModelParams.restype = c_void_p
##IS_PerformanceMetricGetEngagementBoredomModelParams.argtypes = [c_void_p]
##
### interest
##IS_PerformanceMetricGetInterestModelParams = libEDK.IS_PerformanceMetricGetInterestModelParams
##IS_PerformanceMetricGetInterestModelParams.restype = c_void_p
##IS_PerformanceMetricGetInterestModelParams.argtypes = [c_void_p]
##
### focus
##IS_PerformanceMetricGetFocusModelParams = libEDK.IS_PerformanceMetricGetFocusModelParams
##IS_PerformanceMetricGetFocusModelParams.restype = c_void_p
##IS_PerformanceMetricGetFocusModelParams.argtypes = [c_void_p]
##
###Perfomance metrics Normalized Scores
##
### long term excitement
##IS_PerformanceMetricGetExcitementLongTermScore = libEDK.IS_PerformanceMetricGetExcitementLongTermScore
##IS_PerformanceMetricGetExcitementLongTermScore.restype = c_float
##IS_PerformanceMetricGetExcitementLongTermScore.argtypes = [c_void_p]
##
### short term excitement
##IS_PerformanceMetricGetInstantaneousExcitementScore = libEDK.IS_PerformanceMetricGetInstantaneousExcitementScore
##IS_PerformanceMetricGetInstantaneousExcitementScore.restype = c_float
##IS_PerformanceMetricGetInstantaneousExcitementScore.argtypes = [c_void_p]
##
### relaxation
##IS_PerformanceMetricGetRelaxationScore = libEDK.IS_PerformanceMetricGetRelaxationScore
##IS_PerformanceMetricGetRelaxationScore.restype = c_float
##IS_PerformanceMetricGetRelaxationScore.argtypes = [c_void_p]
##
### stress
##IS_PerformanceMetricGetStressScore = libEDK.IS_PerformanceMetricGetStressScore
##IS_PerformanceMetricGetStressScore.restype = c_float
##IS_PerformanceMetricGetStressScore.argtypes = [c_void_p]
##
### boredom/engagement
##IS_PerformanceMetricGetEngagementBoredomScore = libEDK.IS_PerformanceMetricGetEngagementBoredomScore
##IS_PerformanceMetricGetEngagementBoredomScore.restype = c_float
##IS_PerformanceMetricGetEngagementBoredomScore.argtypes = [c_void_p]
##
### interest
##IS_PerformanceMetricGetInterestScore = libEDK.IS_PerformanceMetricGetInterestScore
##IS_PerformanceMetricGetInterestScore.restype = c_float
##IS_PerformanceMetricGetInterestScore.argtypes = [c_void_p]
##
### focus
##IS_PerformanceMetricGetFocusScore = libEDK.IS_PerformanceMetricGetFocusScore
##IS_PerformanceMetricGetFocusScore.restype = c_float
##IS_PerformanceMetricGetFocusScore.argtypes = [c_void_p]

# -------------------------------------------------------------------------

def logEmoState(userID, eState):
##    print >>f, IS_GetTimeFromStart(eState), ",",
##    print >>f, userID.value, ",",
##    print >>f, IS_GetWirelessSignalStatus(eState), ",",
##    print >>f, IS_FacialExpressionIsBlink(eState), ",",
##    print >>f, IS_FacialExpressionIsLeftWink(eState), ",",
##    print >>f, IS_FacialExpressionIsRightWink(eState), ",",
    global count_b, count_lw, count_rw, count_fr, count_sm, count_cl, count_eb, count_limit_b, count_limit_lw, count_limit_rw, count_limit_fr, count_limit_sm, count_limit_cl, count_limit_eb, s_blink, s_smile, s_raisebr, s_clench, s_frown, s_lwink, s_rwink

    FacialExpressionStates = {}
##    FacialExpressionStates[FE_SUPPRISE] = 0
    FacialExpressionStates[FE_FROWN] = 0
    FacialExpressionStates[FE_SMILE] = IS_FacialExpressionGetSmileExtent(eState)
    FacialExpressionStates[FE_CLENCH] = IS_FacialExpressionGetClenchExtent(eState)

##    upperFaceAction = IS_FacialExpressionGetUpperFaceAction(eState)
##    upperFacePower = IS_FacialExpressionGetUpperFaceActionPower(eState)
##    lowerFaceAction = IS_FacialExpressionGetLowerFaceAction(eState)
##    lowerFacePower = IS_FacialExpressionGetLowerFaceActionPower(eState)
##    FacialExpressionStates[upperFaceAction] = upperFacePower
##    FacialExpressionStates[lowerFaceAction] = lowerFacePower

##    print >>f, FacialExpressionStates[FE_SUPPRISE], ",",
##    print >>f, FacialExpressionStates[FE_FROWN], ",",
##    print >>f, FacialExpressionStates[FE_SMILE], ",",
##    print >>f, FacialExpressionStates[FE_CLENCH], ",",
    print "BLINK: %.6f | SMILE: %.6f | RAISE-BROWS: %.6f | %.6f, %.6f, %.6f %.6f\n" % (IS_FacialExpressionIsBlink(eState), FacialExpressionStates[FE_SMILE], IS_FacialExpressionGetEyebrowExtent(eState), IS_FacialExpressionIsLeftWink(eState), IS_FacialExpressionIsRightWink(eState), FacialExpressionStates[FE_FROWN], FacialExpressionStates[FE_CLENCH])
    
    sum = IS_FacialExpressionIsBlink(eState) + IS_FacialExpressionIsLeftWink(eState) + IS_FacialExpressionIsRightWink(eState) + FacialExpressionStates[FE_FROWN] + FacialExpressionStates[FE_SMILE] + FacialExpressionStates[FE_CLENCH] + IS_FacialExpressionGetEyebrowExtent(eState)
    if (sum>0):    
##        SOCKET.sendto("%.6f, %.6f, %.6f, %.6f, %.6f, %.6f \n" % (IS_FacialExpressionIsBlink(eState), IS_FacialExpressionIsLeftWink(eState), IS_FacialExpressionIsRightWink(eState), FacialExpressionStates[FE_FROWN], FacialExpressionStates[FE_SMILE], FacialExpressionStates[FE_CLENCH]), ('127.0.0.1', BROADCAST_PORT))
        if (IS_FacialExpressionIsBlink(eState)>=s_blink):
            count_b += 1
            if (count_b >= count_limit_b):
                SOCKET.sendto("blink", ('127.0.0.1', BROADCAST_PORT))
                count_b = 0
        elif (IS_FacialExpressionIsLeftWink(eState)>=s_lwink):
            count_lw += 1
            if (count_lw >= count_limit_lw):
                SOCKET.sendto("left-wink", ('127.0.0.1', BROADCAST_PORT))
                count_lw = 0
        elif (IS_FacialExpressionIsRightWink(eState)>=s_rwink):
            count_rw += 1
            if (count_rw >= count_limit_rw):
                SOCKET.sendto("right-wink", ('127.0.0.1', BROADCAST_PORT))
                count_rw = 0
        elif (FacialExpressionStates[FE_FROWN]>=s_frown):
            count_fr += 1
            if (count_fr >= count_limit_fr):
                SOCKET.sendto("furrow", ('127.0.0.1', BROADCAST_PORT))
                count_fr = 0
        elif (FacialExpressionStates[FE_SMILE]>=s_smile):
            count_sm += 1
            if (count_sm >= count_limit_sm):
                SOCKET.sendto("smile", ('127.0.0.1', BROADCAST_PORT))
                count_sm = 0
        elif (FacialExpressionStates[FE_CLENCH]>=s_clench):
            count_cl += 1
            if (count_cl >= count_limit_cl):
                SOCKET.sendto("clench", ('127.0.0.1', BROADCAST_PORT))
                count_cl = 0
        elif (IS_FacialExpressionGetEyebrowExtent(eState)>=s_raisebr):
            count_eb += 1
            if (count_eb >= count_limit_eb):
                SOCKET.sendto("raise-brow", ('127.0.0.1', BROADCAST_PORT))
                count_eb = 0

##    IS_FacialExpressionGetEyeLocation(eState,X,Y)
##    print >>f, EyeX.value, ",",
##    print >>f, EyeY.value, ",",
##    IS_FacialExpressionGetEyeLocation(eState,Left,Right)
##    print >>f, EyeLidLeft.value, ",",
##    print >>f, EyeLidRight.value, ",",
##
##    # Performance metrics Suite results
##    print >>f, IS_PerformanceMetricGetExcitementLongTermScore(eState), ",",
##    print >>f, IS_PerformanceMetricGetInstantaneousExcitementScore(eState), ",",    
##    #IS_PerformanceMetricGetInstantaneousExcitementModelParams(eState, Raw, Min, Max)
##    print >>f, RawScore.value, ",",
##    print >>f, MinScale.value, ",",
##    print >>f, MaxScale.value, ",",
##    print >>f, IS_PerformanceMetricGetStressScore(eState), ",",
##    IS_PerformanceMetricGetStressModelParams(eState, Raw, Min, Max)
##    print >>f, RawScore.value, ",",
##    print >>f, MinScale.value, ",",
##    print >>f, MaxScale.value, ",",
##    print >>f, IS_PerformanceMetricGetRelaxationScore(eState), ",",
##    IS_PerformanceMetricGetRelaxationModelParams(eState, Raw, Min, Max)
##    print >>f, RawScore.value, ",",
##    print >>f, MinScale.value, ",",
##    print >>f, MaxScale.value, ",",
##    print >>f, IS_PerformanceMetricGetEngagementBoredomScore(eState), ",",
##    IS_PerformanceMetricGetEngagementBoredomModelParams(eState, Raw, Min, Max)
##    print >>f, RawScore.value, ",",
##    print >>f, MinScale.value, ",",
##    print >>f, MaxScale.value, ",",
##    print >>f, IS_PerformanceMetricGetInterestScore(eState), ",",
##    IS_PerformanceMetricGetInterestModelParams(eState, Raw, Min, Max)
##    print >>f, RawScore.value, ",",
##    print >>f, MinScale.value, ",",
##    print >>f, MaxScale.value, ",",
##    print >>f, IS_PerformanceMetricGetFocusScore(eState), ",",
##    IS_PerformanceMetricGetFocusModelParams(eState, Raw, Min, Max)
##    print >>f, RawScore.value, ",",
##    print >>f, MinScale.value, ",",
##    print >>f, MaxScale.value, ",",
##    print >>f, '\n',
    
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


# -------------------------------------------------------------------------
##header = ['Time', 'UserID', 'Wireless Signal Status', 'Blink', 'Wink Left', 'Wink Right',
##          'Surprise', 'Furrow', 'Smile', 'Clench',
##          'EyeLocationHoriz', 'EyeLocationVert','EyelidStateLeft', 'EyelidStateRight', 'LongTermExcitementRawNorm', 
##          'ShortTermExcitementRawNorm','ShortTermExcitementRaw', 'ShortTermExcitementMin', 'ShortTermExcitementMax',
##          'RelaxationRawNorm','RelaxationRaw','RelaxationMin','RelaxationMax',
##          'StressRawNorm','StressRaw','StressMin','StressMax', 'EngagementRawNorm','EngagementRaw', 'EngagementMin','EngagementMax',
##          'InterestRawNorm','InterestRaw', 'InterestMin', 'InterestMax','FocusRawNorm','FocusRaw','FocusMin','FocusMax']
##
##input = ''
##print "==================================================================="
##print "Example to show how to log EmoState from EmoEngine/EmoComposer."
##print "==================================================================="
##print "Press '1' to start and connect to the EmoEngine                    "
##print "Press '2' to connect to the EmoComposer                            "
##print ">> "


# -------------------------------------------------------------------------

##option = int(raw_input())
##
##if option == 1:
##    if libEDK.IEE_EngineConnect("Emotiv Systems-5") != 0:
##        print "Emotiv Engine start up failed."
##elif option == 2:
##    if libEDK.IEE_EngineRemoteConnect("127.0.0.1", composerPort) != 0:
##        print "Cannot connect to EmoComposer on"
##else:
##    print "option = ?"


##print "Start receiving Emostate! Press any key to stop logging...\n"
##f = file('ES.csv', 'w')
##f = open('ES.csv', 'w')
##print >> f, header

if libEDK.IEE_EngineConnect("Emotiv Systems-5") != 0:
        print "Emotiv Engine start up failed."
        
while (1):
    
    if kbhit():
        break

    ##test-begin
    SOCKET.sendto("button1", ('127.0.0.1', BROADCAST_PORT))
    time.sleep(0.4)
    SOCKET.sendto("button2", ('127.0.0.1', BROADCAST_PORT))
    time.sleep(0.4)
    SOCKET.sendto("smile", ('127.0.0.1', BROADCAST_PORT))
    time.sleep(0.4)
    SOCKET.sendto("clench", ('127.0.0.1', BROADCAST_PORT))
    time.sleep(0.4)
    SOCKET.sendto("furrow", ('127.0.0.1', BROADCAST_PORT))
    time.sleep(0.4)
    SOCKET.sendto("blink", ('127.0.0.1', BROADCAST_PORT))
    time.sleep(0.4)
    SOCKET.sendto("raise-brow", ('127.0.0.1', BROADCAST_PORT))
    time.sleep(0.4)
    ##test-end
    
##    state = libEDK.IEE_EngineGetNextEvent(eEvent)
##    if state >= 0:
##        eventType = libEDK.IEE_EmoEngineEventGetType(eEvent)
##        libEDK.IEE_EmoEngineEventGetUserId(eEvent, user)
##        if eventType == 64:  # libEDK.IEE_Event_enum.IEE_EmoStateUpdated
##            libEDK.IEE_EmoEngineEventGetEmoState(eEvent, eState)
##            timestamp = IS_GetTimeFromStart(eState)
####            print "%10.3f New EmoState from user %d ...\r" % (timestamp,userID.value)
##            logEmoState(userID, eState)     
##    elif state != 0x0600:
##        print "%10.0f Internal error in Emotiv Engine ! " %(state)
    time.sleep(0.1)
# -------------------------------------------------------------------------
##f.close()
libEDK.IEE_EngineDisconnect()
libEDK.IEE_EmoStateFree(eState)
libEDK.IEE_EmoEngineEventFree(eEvent)
