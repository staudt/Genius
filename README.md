# Genius
A Simon Says for Arduino, also known as Genius.

You can see the circuit simulation here (but no sound): https://123d.circuits.io/circuits/918958-simon-says

There's also videos of it running on a protoboard here: https://youtu.be/jRHjnw182f4 and a enclosed version using blinking arcade buttons: https://youtu.be/AFB2u_2nE7s

# Getting Started
You'll need the following:
* Arduino, I've used Uno
* 4 LEDs and 4 resistors (at least 22OΩ)
* 4 Pushbuttons
* A speaker, buzzer or piezo
* You might also want a protoboard and jumper wires

You can set the led_pin, btn_pin and speaker_pin variables according to your setup (just avoid digital pins 1 and 2 for buttons). By default the pin positions are: Button positives to digital pins 3,4,5 and 6 (negatives to ground), LED positives to digital pins 8,9,10 and 11 (negative to resistor and then ground) and speaker positive to digital pin 7 (negative also to ground).
 
