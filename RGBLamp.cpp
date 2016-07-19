/*
* RGBLamp
* Version 1 July, 2016
* Copyright 2016 Sebastian Wassberg
*/

#include "RGBLamp.h"

RGBLamp::RGBLamp() {

}

// Save the input pin numbers and hw config to library variables and turn lamp off
void RGBLamp::begin(byte hardwareConfig, uint8_t red_pin, uint8_t green_pin, uint8_t blue_pinPin )
{
	if (hardwareConfig == 1) {
		commonCathode = false;
	}
	
	pin_r = red_pin;
	pin_g = green_pin;
	pin_b = blue_pinPin;

	pinMode(pin_r, OUTPUT);
	pinMode(pin_g, OUTPUT);
	pinMode(pin_b, OUTPUT);

	setColor(0, 0, 0);
}

void RGBLamp::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
	isBlinking = false;
	setColorPriv(red, green, blue);
	setNewTarget(red, green, blue);
}

void RGBLamp::setColor(uint32_t color)
{
	setColor((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF);
}

void RGBLamp::off()
{
	setColor(0, 0, 0);
}

void RGBLamp::update()
{
	if (millis() >= timeForNextIteration) {
		rgbLampMain_10ms(0);
		timeForNextIteration = millis() + 10;
	}
}


bool RGBLamp::equalToTarget(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red == target_r && green == target_g && blue == target_b);
}

bool RGBLamp::equalToBlink(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red == RGBLamp::blink_r && green == RGBLamp::blink_g && blue == RGBLamp::blink_b);
}

void  RGBLamp::setNewTarget(uint8_t red, uint8_t green, uint8_t blue) {
	target_r = red;
	target_b = blue;
	target_g = green;


	int16_t diff_r = target_r - curr_r;
	int16_t diff_g = target_g - curr_g;
	int16_t diff_b = target_b - curr_b;

	// calculate the width of each step
	step_r = (diff_r / (fadeDuration_ms / 10));
	step_g = (diff_g / (fadeDuration_ms / 10));
	step_b = (diff_b / (fadeDuration_ms / 10));
}


void RGBLamp::fadeTo(uint8_t red, uint8_t green, uint8_t blue)
{
	isBlinking = false;

	if(equalToTarget(red, green, blue)) {
		return; //we are aleardy heading there!
	}

	setNewTarget(red, green, blue);
}



void RGBLamp::fadeTo(uint32_t color)
{
	fadeTo((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF);
}


void RGBLamp::blink(uint32_t color)
{
	blink((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF);
}

void RGBLamp::blink(uint8_t red, uint8_t green, uint8_t blue) {
	isBlinking = true;
	if (equalToBlink(red, green, blue)) {
		return;
	}
	blink_r = red;
	blink_g = green;
	blink_b = blue;
	setNewTarget(red, green, blue);
}

//Checks so we dont go past our target when moving towards it
uint8_t safeStep(uint8_t target, uint8_t color, int16_t step) {
	int16_t nextStep = color + step;
	if (step >= 0) {
		if (nextStep > target) {
			return target;
		}
	}

	if (step < 0) {
		if (nextStep < target) {
			return target;
		}
	}

	return nextStep;
}

//Sets color on lamp and update internal current color values
void RGBLamp::setColorPriv(uint8_t red, uint8_t green, uint8_t blue)
{
	if (commonCathode) {
		analogWrite(pin_r, red);
		analogWrite(pin_g, green);
		analogWrite(pin_b, blue);
	}
	else {
		analogWrite(pin_r, 255 - red);
		analogWrite(pin_g, 255 - green);
		analogWrite(pin_b, 255 - blue);
	}
	curr_r = red;
	curr_b = blue;
	curr_g = green;
}

//If we are not on target color we move towards it. If we are on target but is blinking we set a new target.
void RGBLamp::rgbLampMain_10ms(uint8_t id)
{
	
	if (!equalToTarget(curr_r, curr_g, curr_b)) {
		setColorPriv(safeStep(target_r, curr_r, step_r), safeStep(target_g, curr_g, step_g), safeStep(target_b, curr_b, step_b));
	}
	else
	{
		if (isBlinking) {
			uint8_t temp_r = (curr_r == 0) ? blink_r : 0;
			uint8_t temp_g = (curr_g == 0) ? blink_g : 0;
			uint8_t temp_b = (curr_b == 0) ? blink_b : 0;
			setNewTarget(temp_r, temp_g, temp_b);
		}
	}
}


