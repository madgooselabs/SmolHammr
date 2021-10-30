#include "JLM.hpp"

JLM::JLM()
{
}

void JLM::begin(uint8_t _samples, uint8_t _pinx, uint8_t _piny, uint16_t _dz, uint16_t _rdz, uint8_t _pinBtn)
{
}


uint16_t JLM::button()
{
	return analogRead(pinButton) > 512 ? 1 : 0;
}
