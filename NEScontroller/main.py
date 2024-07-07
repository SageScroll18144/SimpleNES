import time
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

# Inicializar o teclado
keyboard = Keyboard(usb_hid.devices)

while True:
    # Digitar "felipe"
    keyboard.send(Keycode.F)
    keyboard.send(Keycode.E)
    keyboard.send(Keycode.L)
    keyboard.send(Keycode.I)
    keyboard.send(Keycode.P)
    keyboard.send(Keycode.E)

    # Adicionar um espaço após "felipe" ou pular linha se desejar
    keyboard.send(Keycode.SPACE)

    # Aguardar um tempo antes de repetir
    time.sleep(0.1)