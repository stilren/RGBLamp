/*
* RGBLamp
* Version 1 July, 2016
* Copyright 2016 Sebastian Wassberg
*/

#ifndef _RGBLAMP_h
#define _RGBLAMP_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define COMMON_CATHODE 0
#define COMMON_ANODE 1

class RGBLamp {
public:
	RGBLamp();
	void rgbLampMain_10ms(uint8_t id);
	void begin(byte hardwareConfig, uint8_t red_pin, uint8_t green_pin, uint8_t blue_pinPin);
	void setColor(uint8_t red, uint8_t green, uint8_t blue);
	void setColor(uint32_t color);
	void fadeTo(uint8_t red, uint8_t green, uint8_t blue);
	void fadeTo(uint32_t color);
	void blink(uint32_t color);
	void blink(uint8_t red, uint8_t green, uint8_t blue);
	void off();
	void update();

private:
	const int fadeDuration_ms = 500;
	bool equalToTarget(uint8_t red, uint8_t green, uint8_t blue);
	bool equalToBlink(uint8_t red, uint8_t green, uint8_t blue);
	void setNewTarget(uint8_t red, uint8_t green, uint8_t blue);
	void setColorPriv(uint8_t red, uint8_t green, uint8_t blue);
	bool commonCathode = true;
	bool isBlinking = false;
	uint8_t pin_r, pin_g, pin_b, curr_r, curr_g, curr_b, target_r, target_g, target_b, blink_r, blink_g, blink_b;
	int16_t step_r, step_g, step_b;
	long timeForNextIteration = 0;
};

class Color {
public:
	static const uint32_t Red = 0xFF0000;
	static const uint32_t Green = 0x00FF00;
	static const uint32_t Blue = 0x0000FF;
	static const uint32_t White = 0xFFFFFF;
	static const uint32_t Yellow = 0xFFFF00;
	static const uint32_t Cyan = 0x00FFFF;
	static const uint32_t Purple = 0xFF00FF;
	static const uint32_t Off = 0x000000;
};

#endif

