# Genius
A Simon Says for Arduino, also known as Genius.

You can see the circuit simulation here: https://123d.circuits.io/circuits/918958-simon-says (no sound however)
See it running on a protoboard here: https://youtu.be/jRHjnw182f4 and here the enclosed version using arcade buttons: https://youtu.be/AFB2u_2nE7s

# Getting Started
You'll need the following:
* An Arduino, I've used Uno
* LEDs and resistors (at least 220 ohms)
* Pushbuttons
* a speaker or buzzer

You can set the led_pin, btn_pin and speaker_pin variables to their digital pins. Defaults pin positions are: Button positives on digital pins 3,4,5 and 6 (negative to ground), LED positives to digital pins 8,9,10 and 11 (negative to resistor and then ground) and speaker positive to digital pin 7 (negative to ground also).
 
