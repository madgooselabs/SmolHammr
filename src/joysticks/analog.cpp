#include "joysticks/analog.hpp"

analogInput::analogInput()
{
}

void analogInput::init(const char* _name, uint8_t _samples, uint8_t _pinx, uint8_t _piny, uint8_t _pinBtn, uint16_t _dz, uint16_t _rdz, uint16_t _xdp,  uint16_t _xdn, uint16_t _ydp, uint16_t _ydn)
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

	// Set name
	strcpy(name, _name);

	// Set axes
	pinX = _pinx;
	pinY = _piny;
	pinButton = _pinBtn;
	
	// Read initial values and pray for the lever to not be tilted someway already
	centerX = analogRead(pinX);
	centerY = analogRead(pinY);

	// Set deltas
	xDeltaPositive = _xdp;
	xDeltaNegative = _xdn;
	yDeltaPositive = _ydp;
	yDeltaNegative = _ydn;

	// Infer min and max axial values; empirical tests showed a range of +/- 200 so we're using that as a base
	minX = centerX - xDeltaNegative;
	maxX = centerX + xDeltaPositive;
	minY = centerY - yDeltaNegative;
	maxY = centerY + yDeltaPositive;

    // Compute raw deadzones
    deadzone = _dz;
    reverseDeadzone = _rdz;
    dzNegativeValue = centerX - ((centerX * deadzone) / 100);
    dzPositiveValue = centerX + ((centerX * deadzone) / 100);
    rdzNegativeValue = ((centerX * reverseDeadzone) / 100);
    rdzPositiveValue = maxX - ((centerX * reverseDeadzone) / 100);

	// Allocate memory for the sample arrays
	rawX = (uint16_t*)calloc(numberOfSamples, sizeof(uint16_t));
	rawY = (uint16_t*)calloc(numberOfSamples, sizeof(uint16_t));
}

void analogInput::sample(int outputMode)
{
	// Run it every cycle
	static uint8_t counter = 0;
    static bool reverseDirection = false;

	if (counter < numberOfSamples)
	{
		rawX[counter] = analogRead(pinX);
		rawY[counter] = analogRead(pinY);

		if (counter > 0)
		{
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

			if (rawY[counter-1] < centerY)
			{
				if (rawY[counter] > centerY)
				{
					reverseDirection = true;
				}
			}
			else if (rawY[counter-1] > centerY)
			{
				if (rawY[counter] < centerY)
				{
					reverseDirection = true;
				}
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
		if ((x >= dzNegativeValue) && (x <= dzPositiveValue))
			x = centerX;
		if ((y >= dzNegativeValue) && (y <= dzPositiveValue))
			y = centerY;
		// Reverse deadzone handling
		if (x <= minX + rdzNegativeValue + (rdzPositiveValue / 100))	// Add 1% of extra margin
			x = minX;
		else if (x >= rdzPositiveValue - (rdzPositiveValue / 100))
			x = maxX;
		if (y <= minY + rdzNegativeValue + (rdzPositiveValue / 100))
			y = minY;
		else if (y >= rdzPositiveValue - (rdzPositiveValue / 100))
			y = maxY;

		switch (outputMode)
		{
			case 0:		// USB
				x = map(x, minX, maxX, 0, 1023);
				y = map(y, minY, maxY, 1023, 0);	// Y-axis needs reversing
				break;
			case 1:		// Gamecube
				x = map(x, minX, maxX, 0, 255);
				y = map(y, minY, maxY, 255, 0);
				break;
			default:	// What in tarnation are you doing
				x = map(x, minX, maxX, 0, 1023);
				y = map(y, minY, maxY, 1023, 0);
				break;
		}

		counter = 0;
	}
}

char* analogInput::getLeverInfo(char *buf)
{
	sprintf(buf, "Lever name: %s\nAnalog X pin: %d\nAnalog Y pin: %d\nCenter X value: %d\nCenter Y value: %d\nXmin: %d\nXmax: %d\nYmin: %d\nYmax: %d\nDeadzone interval: [%d, %d]\nReverse deadzone interval: [%d, %d] U [%d, %d]",\
					name, pinX, pinY, centerX, centerY, minX, maxX, minY, maxY, dzNegativeValue, dzPositiveValue, minX, minX + rdzNegativeValue, rdzPositiveValue, maxX);
	return buf;
}
uint16_t analogInput::button()
{
	// Override as needed
	return 0;
}
