#include "rp2040.hpp"

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
	pinMode(9, INPUT_PULLUP);      // START

	pinMode(10, INPUT_PULLUP);     // C-Up
	pinMode(11, INPUT_PULLUP);     // C-Down
	pinMode(12, INPUT_PULLUP);     // C-Left
	pinMode(13, INPUT_PULLUP);     // C-Right

	pinMode(14, INPUT_PULLUP);     // MACRO
	pinMode(15, INPUT_PULLUP);     // TILT

	pinMode(21, INPUT_PULLUP);     // Dpad-Up
	pinMode(20, INPUT_PULLUP);     // Dpad-Down
	pinMode(19, INPUT_PULLUP);     // Dpad-Left
	pinMode(18, INPUT_PULLUP);     // Dpad-Right
}

// Manual delay functions
void GCC_delay1ms()
{
  volatile uint16_t count = 6;
  while (count--);
}

void GCC_delay2ms()
{
  volatile uint16_t count = 12;
  while (count--);
}

void GCC_delay3ms()
{
  volatile uint16_t count = 19;
  while (count--);
}

uint8_t getAnalogMode()
{
	// The Pico doesn't have enough pins to take a 3pin DIP switch
	// So we return 0, which in SmolHammr parlance is a JLM
	// Feel free to override as needed !
	return 0;
}