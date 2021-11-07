#ifndef ANALOG_HPP
#define ANALOG_HPP
#pragma once

#include <Arduino.h>

#define ANALOG_SAMPLES_PER_CYCLE    5
#define ANALOG_DEADZONE				10
#define ANALOG_REVERSE_DEADZONE		10

class analogInput
{
	protected:
		char name[16];
		uint8_t numberOfSamples;		// Self explanatory

		uint8_t pinX;					// Analog pin to read for X axis
		uint16_t centerX;				// Self explanatory
		uint16_t minX;
		uint16_t maxX;
		uint16_t* rawX;					// Array of samples, X axis

		uint8_t pinY;					// Analog pin to read for Y axis
		uint16_t centerY;				// Self explanatory
		uint16_t minY;
		uint16_t maxY;
		uint16_t* rawY;					// Array of samples, Y axis

		uint8_t pinButton;				// Analog pin to read for button press

        uint8_t deadzone;               // Deadzone in % away from center
        uint16_t dzNegativeValue;        // DZ to the left and down
        uint16_t dzPositiveValue;        // DZ to the right and up

        uint8_t reverseDeadzone;        // Deadzone in % away from edge
        uint16_t rdzNegativeValue;       // RDZ to the left and down
        uint16_t rdzPositiveValue;       // RDZ to the right and up
    
        uint16_t xDeltaPositive, xDeltaNegative, yDeltaPositive, yDeltaNegative;
	public:
		analogInput();
		void init(const char* _name, uint8_t _samples, uint8_t _pinx, uint8_t _piny, uint8_t _pinBtn, uint16_t _dz, uint16_t _rdz, uint16_t _xdp,  uint16_t _xdn, uint16_t _ydp, uint16_t _ydn);
		void sample(int outputMode);
		char* getLeverInfo(char *buf);
		uint16_t x;						// Average of samples on X axis
		uint16_t y;						// Average of samples on Y axis
		uint16_t button();				// Button (represented as a boolean because it doesn't give depth anyway)
};
#endif