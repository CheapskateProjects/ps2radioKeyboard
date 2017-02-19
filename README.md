# ps2radioKeyboard
This project converts normal PS/2 keyboard into wireless radio keyboard. 

Transmitter transmits keyboard presses as characters over radio link ( nRF24L01 ).
Receiver listens to those radio commands and then inputs them as keyboard emulation calls over the USB.
  
Dependecies: <https://github.com/maniacbug/RF24> <https://www.pjrc.com/teensy/td_libs_PS2Keyboard.html>
