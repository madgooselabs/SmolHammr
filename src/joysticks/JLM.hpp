#ifndef JLM_HPP
#define JLM_HPP
#pragma once

#include <Arduino.h>
#include "analog.hpp"

class JLM : public analogInput
{
	public:
		JLM();
		void begin(uint8_t _samples, uint8_t _pinx, uint8_t _piny, uint16_t _dz, uint16_t _rdz, uint8_t _pinBtn);
		void sample();
		uint16_t x;
		uint16_t y;
		uint16_t button();
};

#endif