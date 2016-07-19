# RGBLamp
This is a arduino compatible library for controlling a RGB lamp wihout using delay functionality. It is best used with a timer library (such as https://github.com/JChristensen/Timer) but it also has its own built in timer functionality.

##Installation##
Just copy the `RGBLamp` folder to the `libraries` folder of your Arduino-IDE.

##Setup with built in timer##
```c++
#include "RGBLamp.h"

//Make sure pins are PWM-pins if you want to use fadeTo or blink fucntions.
int redPin = 3;
int greenPin = 5;
int bluePin = 6;
int mode = COMMON_ANODE;

RGBLamp myLamp;

void setup() {
  myLamp.begin(mode, redPin, greenPin, bluePin); 
}
  
void loop(){
  //Call the update function continuously
  myLamp.update();
} 
```

##Set a color
Calls to `setColor` can be placed anywhere in the code (also in a loop)
```c++
myLamp.setColor(255,0,0); //Red
```
or use the `Color` class included
```c++
myLamp.setColor(Color::Red); //Red
```

##Fade to a color
Calls to `fadeTo` can be placed anywhere in the code (also in a loop)
```c++
myLamp.fadeTo(0,255,255);
```
or use the `Color` class included
```c++
myLamp.fadeTo(Color::Cyan);
```

##Blink/pulse a color
Calls to `blink` can be placed anywhere in the code (also in a loop) and need only be called once
```c++
myLamp.blink(255,255,0);
```
or use the `Color` class included
```c++
myLamp.blink(Color::Orange);
```

##Setup using a timer library
Let the timer call `RGBLamp::rgbLampMain_10ms` every 10 ms instead of calling `RGBLamp::update`.
