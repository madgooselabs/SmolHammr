#include "teensy41.hpp"

void GCC_setup()
{
	// Set up inputs
	pinMode(2, INPUT_PULLUP);      // A
	pinMode(3, INPUT_PULLUP);      // B
	pinMode(4, INPUT_PULLUP);      // X
	pinMode(5, INPUT_PULLUP);      // Y

	pinMode(6, INPUT_PULLUP);      // L
	pinMode(7, INPUT_PULLUP);      // R
	pinMode(8, INPUT_PULLUP);      // Z
	pinMode(30, INPUT_PULLUP);     // START

	pinMode(9, INPUT_PULLUP);      // C-Up
	pinMode(10, INPUT_PULLUP);     // C-Down
	pinMode(11, INPUT_PULLUP);     // C-Left
	pinMode(12, INPUT_PULLUP);     // C-Right

	pinMode(28, INPUT_PULLUP);     // MACRO
	pinMode(29, INPUT_PULLUP);     // TILT

	pinMode(24, INPUT_PULLUP);     // Dpad-Up
	pinMode(25, INPUT_PULLUP);     // Dpad-Down
	pinMode(26, INPUT_PULLUP);     // Dpad-Left
	pinMode(27, INPUT_PULLUP);     // Dpad-Right
}

// Manual delay functions
void GCC_delay1ms()
{
  volatile uint16_t count = 64;
  while (count--);
}

void GCC_delay2ms()
{
  volatile uint16_t count = 127;
  while (count--);
}

void GCC_delay3ms()
{
  volatile uint16_t count = 197;
  while (count--);
}

uint8_t getAnalogMode()
{
	return (digitalRead(35) & digitalRead(36) << 1 & digitalRead(37) << 2);
}