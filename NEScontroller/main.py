import time
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

# Crie um objeto Keyboard
keyboard = Keyboard(usb_hid.devices)

# Emule a digitação da string "Hello, World!"
keyboard.press(Keycode.H)
keyboard.release_all()
time.sleep(0.1)
keyboard.press(Keycode.E)
keyboard.release_all()
# ... continue com outras teclas

# Espere um pouco antes de desconectar
time.sleep(2)
