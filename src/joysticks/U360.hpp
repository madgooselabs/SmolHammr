#ifndef U360_HPP
#define U360_HPP
#pragma once

#include <Arduino.h>
#include "analog.hpp"

class U360 : public analogInput
{
	public:
		U360();
		void begin(uint8_t _samples, uint8_t _pinx, uint8_t _piny, uint16_t _dz, uint16_t _rdz, uint8_t _pinBtn);
		void sample();
		uint16_t x;
		uint16_t y;
		uint16_t button();
};

#endif