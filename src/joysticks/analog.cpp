#include "analog.hpp"

analogInput::analogInput()
{
}

void analogInput::begin(uint8_t _samples, uint8_t _pinx, uint8_t _piny, uint16_t _dz, uint16_t _rdz, uint8_t _pinBtn)
{
	// Set sample "rate"
	if (_samples > 0)
	{
		numberOfSamples = _samples;
	}
	else
	{
		// TODO: Figure a way to make this actually work
		//#pragma message ("WARNING: Number of samples set to a value inferior to 1; defaulting to 1")
		numberOfSamples = 1;
	}

	// Set axes
	pinX = _pinx;
	pinY = _piny;
	pinButton = _pinBtn;
	
	// Read initial values and pray for the lever to not be tilted someway already
	centerX = analogRead(pinX);
	centerY = analogRead(pinY);

	// Infer min and max axial values; empirical tests showed a range of +/- 200 so we're using that as a base
	minX = centerX - xDeltaNegative;
	maxX = centerX + xDeltaPositive;
	minY = centerY - yDeltaNegative;
	maxY = centerY + yDeltaPositive;

    // Compute raw deadzones
    deadzone = _dz;
    reverseDeadzone = _rdz;
    dzNegativeValue = centerX - (centerX * (deadzone / 100));
    dzPositiveValue = centerX + (centerX * (deadzone / 100));
    rdzNegativeValue = dzPositiveValue - centerX;
    rdzPositiveValue = dzNegativeValue + centerX;

	// Allocate memory for the sample arrays
	rawX = (uint16_t*)calloc(numberOfSamples, sizeof(uint16_t));
	rawY = (uint16_t*)calloc(numberOfSamples, sizeof(uint16_t));
}

void analogInput::sample()
{
	// Run it every cycle
	static uint8_t counter = 0;
    static bool reverseDirection = false;

	if (counter < numberOfSamples)
	{
		rawX[counter] = analogRead(pinX);
		rawY[counter] = analogRead(pinY);

        if (rawX[counter-1] < centerX)
        {
            if (rawX[counter] > centerX)
            {
                reverseDirection = true;
            }
        }
        else if (rawX[counter-1] > centerX)
        {
            if (rawX[counter] < centerX)
            {
                reverseDirection = true;
            }
        }

        if (reverseDirection == false)
        {
		    counter++;
        }
        else
        {
            counter = 0;
            reverseDirection = false;
        }
	}
	else
	{
		x = 0;
		y = 0;

		for (int i = 0; i < numberOfSamples; i++)
		{
			x += rawX[i];
			y += rawY[i];
		}
		x = x / numberOfSamples;
		y = y / numberOfSamples;

		// Deadzone handling
		if ((x >= centerX - dzNegativeValue) && (x <= centerX + dzPositiveValue))
			x = centerX;
		if ((y >= centerY - dzNegativeValue) && (y <= centerY + dzPositiveValue))
			y = centerY;
		// Reverse deadzone handling
		if (x <= minX + rdzNegativeValue)
			x = minX;
		else if (x >= maxX - rdzPositiveValue)
			x = maxX;
		if (y <= minY + rdzPositiveValue)
			y = minY;
		else if (y >= maxY - rdzNegativeValue)
			y = maxY;

		x = map(x, minX, maxX, 0, 1023);
		y = map(y, minY, maxY, 1023, 0);	// Y-axis needs reversing

		counter = 0;
	}
}

uint16_t analogInput::button()
{
	// Override as needed
}
