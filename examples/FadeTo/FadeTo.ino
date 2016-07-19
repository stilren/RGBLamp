#include "RGBLamp.h"

RGBLamp myLamp;
int redPin = 3;
int greenPin = 5;
int bluePin = 6;
int mode = COMMON_ANODE;

void setup() {
  myLamp.begin(mode, redPin, greenPin, bluePin); //Make sure pins are PWM-pins if you want to use fadeTo or blink fucntions.
  myLamp.off();
  myLamp.fadeTo(Color::Red);
}

void loop() {
  myLamp.update(); //Run continuously
}
