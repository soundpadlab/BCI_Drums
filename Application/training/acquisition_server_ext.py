import sys
import os
import platform
import time
import ctypes

from array import *
from ctypes import *
from __builtin__ import exit
from socket import *

BROADCAST_PORT = 8888
SOCKET = socket(AF_INET, SOCK_DGRAM)
SOCKET.bind(('', 0))
SOCKET.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)


try:
	if sys.platform.startswith('win32'):
		libEDK = cdll.LoadLibrary("bin/win32/edk.dll")
	elif sys.platform.startswith('linux'):
		srcDir = os.getcwd()
		if platform.machine().startswith('arm'):
			libPath = srcDir + "/bin/armhf/libedk.so"
		else:
			libPath = srcDir + "/bin/linux64/libedk.so"
			libEDK = CDLL(libPath)
	else:
		raise Exception('System not supported.')
except Exception as e:
	print 'Error: cannot load EDK lib:', e
	exit()

IEE_EmoEngineEventCreate = libEDK.IEE_EmoEngineEventCreate
IEE_EmoEngineEventCreate.restype = c_void_p
eEvent = IEE_EmoEngineEventCreate()

IEE_EmoEngineEventGetEmoState = libEDK.IEE_EmoEngineEventGetEmoState
IEE_EmoEngineEventGetEmoState.argtypes = [c_void_p, c_void_p]
IEE_EmoEngineEventGetEmoState.restype = c_int

IEE_EmoStateCreate = libEDK.IEE_EmoStateCreate
IEE_EmoStateCreate.restype = c_void_p
eState = IEE_EmoStateCreate()

userID = c_uint(0)
user   = pointer(userID)
ready  = 0
state  = c_int(0)
result = c_int(0)

nSamples   = c_uint(0)
nSam       = c_uint(0)
nSamplesTaken  = pointer(nSamples)
data     = pointer(c_double(0))
secs      = c_float(1)
datarate        = c_uint(0)
readytocollect  = False
option    = c_int(0)

alphaValue       = c_double(0)
low_betaValue  = c_double(0)
high_betaValue = c_double(0)
gammaValue       = c_double(0)
thetaValue       = c_double(0)

ALPHA    = c_double(0)
LOW_BETA  = c_double(0)
HIGH_BETA = c_double(0)
GAMMA    = c_double(0)
THETA    = c_double(0)

alpha    = pointer(alphaValue)
low_beta  = pointer(low_betaValue)
high_beta = pointer(high_betaValue)
gamma    = pointer(gammaValue)
theta    = pointer(thetaValue)

IED_COUNTER = 0   
IED_TIMESTAMP = 19       
IED_ES_TIMESTAMP = 20 

channelList = array('I',[IED_COUNTER,IED_TIMESTAMP,IED_ES_TIMESTAMP, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16])   # IED_AF3, IED_AF4, IED_T7, IED_T8, IED_Pz
targetChannelList = [IED_COUNTER,IED_TIMESTAMP,IED_ES_TIMESTAMP,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]

if libEDK.IEE_EngineConnect("Emotiv Systems-5") != 0:
		print "Emotiv Engine start up failed."
		exit();

#print "Theta, Alpha, Low_beta, High_beta, Gamma \n"

##header = ['COUNTER','TIMESTAMP','ES_TIMESTAMP','AF3','F7','F3','FC5','T7','P7','Pz','O2','P8','T8','FC6','F4','F8','AF4']
##f = file('EEG.csv', 'w')
##f = open('EEG.csv', 'w')
##print >> f,header

hData = libEDK.IEE_DataCreate()
libEDK.IEE_DataSetBufferSizeInSec(secs)


while (1):
	state = libEDK.IEE_EngineGetNextEvent(eEvent)
	waveData = ()

	if state == 0:
		eventType = libEDK.IEE_EmoEngineEventGetType(eEvent)
		libEDK.IEE_EmoEngineEventGetUserId(eEvent, user)
		if eventType == 16:  # libEDK.IEE_Event_enum.IEE_UserAdded
			libEDK.IEE_FFTSetWindowingType(userID, 1);  # 1: libEDK.IEE_WindowingTypes_enum.IEE_HAMMING
			libEDK.IEE_DataAcquisitionEnable(userID,True)
			ready = 1
			readytocollect = True
			print "User added"

	if ready == 1 and readytocollect==True:
		libEDK.IEE_DataUpdateHandle(0, hData)
		libEDK.IEE_DataGetNumberOfSample(hData,nSamplesTaken)
		if nSamplesTaken[0] != 0:
			nSam=nSamplesTaken[0]
			arr=(ctypes.c_double*nSamplesTaken[0])()
			ctypes.cast(arr, ctypes.POINTER(ctypes.c_double))
			for sampleIdx in range(nSamplesTaken[0]): 
				for i in range(17):
					if i < 3:
						libEDK.IEE_DataGet(hData,channelList[i],byref(arr), nSam)
						#print i, '\n'
						waveData = waveData + (arr[sampleIdx],)
						#print >>f,arr[sampleIdx],",",
					else:
						result = c_int(0)
						result = libEDK.IEE_GetAverageBandPowers(userID, i, theta, alpha, low_beta, high_beta, gamma)
						#print i, '\n'
						libEDK.IEE_DataGet(hData,channelList[i],byref(arr), nSam)
						waveData = waveData + (arr[sampleIdx], alphaValue.value, low_betaValue.value, high_betaValue.value, gammaValue.value, thetaValue.value)
						#print>>f,arr[sampleIdx],",", alphaValue.value,",", low_betaValue.value,",", high_betaValue.value,",", gammaValue.value,",", thetaValue.value,",",
				#print>>f,'\n'
				dataToSend = ' '.join(format(f, '.3f') for f in waveData)
				SOCKET.sendto(dataToSend, ('<broadcast>', BROADCAST_PORT))
				waveData = ()
				#if result == 0: #EDK_OK
					#print>>f,'\n'
					#dataToSend = ' '.join(format(f, '.3f') for f in waveData)
					#print dataToSend, '\n---------------\n'
					#SOCKET.sendto(dataToSend, ('<broadcast>', BROADCAST_PORT))
					#waveData = ()
					#print waveData, '\n'
					#SOCKET.sendto(' '.join(format(f, '.3f') for f in waveData), ('<broadcast>', BROADCAST_PORT))
					#SOCKET.sendto((waveData), ('<broadcast>', BROADCAST_PORT))
					#print "%.6f, %.6f, %.6f, %.6f, %.6f \n" % (THETA, ALPHA, LOW_BETA, HIGH_BETA, GAMMA)
					#SOCKET.sendto("%.6f %.6f %.6f %.6f %.6f" % (THETA, ALPHA, LOW_BETA, HIGH_BETA, GAMMA), ('<broadcast>', BROADCAST_PORT))
				
	elif state != 0x0600:
		print "Internal error in Emotiv Engine ! "
	time.sleep(0.1)
libEDK.IEE_DataFree(hData)
# -------------------------------------------------------------------------
libEDK.IEE_EngineDisconnect()
libEDK.IEE_EmoStateFree(eState)
libEDK.IEE_EmoEngineEventFree(eEvent)
