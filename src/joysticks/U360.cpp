#include "U360.hpp"

U360::U360()
{
}

void U360::begin(uint8_t _samples, uint8_t _pinx, uint8_t _piny, uint16_t _dz, uint16_t _rdz, uint8_t _pinBtn)
{
	xDeltaPositive = 200;
	xDeltaNegative = 200;
	yDeltaPositive = 200;
	yDeltaNegative = 200;
	analogInput::begin(_samples, _pinx, _piny, _dz, _rdz, _pinBtn);
}

uint16_t U360::button()
{
	return 0;	// U360 doesn't have a button
}
