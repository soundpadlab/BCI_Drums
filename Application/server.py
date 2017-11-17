#on cmd run: python -m pip install pynput

from pynput import keyboard
from socket import *

BROADCAST_PORT = 8889
SOCKET = socket(AF_INET, SOCK_DGRAM)
SOCKET.bind(('', 0))
SOCKET.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)

def on_press(key):
    try: k = key.char # single-char keys
    except: k = key.name # other keys
    if key == keyboard.Key.esc: return False # stop listener
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
lis.join() # no this if main thread is polling self.keys
