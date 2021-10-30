#ifndef ANALOG_HPP
#define ANALOG_HPP
#pragma once

#include <Arduino.h>
#include "analog.hpp"

#define ANALOG_SAMPLES_PER_CYCLE    5

class analogInput
{
	private:
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

        uint8_t deadzone;               // Deadzone in % away from center
        uint8_t dzNegativeValue;        // DZ to the left and down
        uint8_t dzPositiveValue;        // DZ to the right and up

        uint8_t reverseDeadzone;        // Deadzone in % away from edge
        uint8_t rdzNegativeValue;       // RDZ to the left and down
        uint8_t rdzPositiveValue;       // RDZ to the right and up
    protected:
		uint8_t pinButton;				// Analog pin to read for button press
        uint16_t xDeltaPositive, xDeltaNegative, yDeltaPositive, yDeltaNegative;
	public:
		analogInput();
		void begin(uint8_t _samples, uint8_t _pinx, uint8_t _piny, uint16_t _dz, uint16_t _rdz, uint8_t _pinBtn);
		void sample();
		uint16_t x;						// Average of samples on X axis
		uint16_t y;						// Average of samples on Y axis
		uint16_t button();				// Button (represented as a boolean because it doesn't give depth anyway)
};
#endif