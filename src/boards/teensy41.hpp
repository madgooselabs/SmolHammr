#ifndef TEENSY41_HPP
#define TEENSY41_HPP

#include <Arduino.h>

#pragma message "Compiling for board Teensy 4.1 !"

// GCC data line manipulation
#define GCC_LOW           GPIO9_DR_CLEAR = (1 << 7)
#define GCC_HIGH          GPIO9_DR_SET = (1 << 7)
#define GCC_READ          GPIO7_DR & (1 << 29)
#define GCC_DATA_IN       34
#define GCC_DATA_OUT      33

// Anti-magic fields
#define READ_A            GPIO9_DR & (1 << 4)
#define READ_B            GPIO9_DR & (1 << 5)
#define READ_X            GPIO9_DR & (1 << 6)
#define READ_Y            GPIO9_DR & (1 << 8)

#define READ_L            GPIO6_DR & (1 << 25)
#define READ_R            GPIO6_DR & (1 << 24)
#define READ_Z            GPIO6_DR & (1 << 27)
#define READ_START        GPIO6_DR & (1 << 26)

#define READ_C_UP         GPIO7_DR & (1 << 17)
#define READ_C_DOWN       GPIO7_DR & (1 << 16)
#define READ_C_LEFT       GPIO7_DR & (1 << 11)
#define READ_C_RIGHT      GPIO8_DR & (1 << 12)

#define READ_DPAD_UP      GPIO6_DR & (1 << 17)
#define READ_DPAD_DOWN    GPIO6_DR & (1 << 22)
#define READ_DPAD_LEFT    GPIO6_DR & (1 << 23)
#define READ_DPAD_RIGHT   GPIO6_DR & (1 << 19)

#define READ_MACRO        GPIO6_DR & 1
#define READ_TILT         GPIO6_DR & 1

// Analog shenanigans
#define PIN_ANALOG_X      14
#define PIN_ANALOG_Y      15
#define PIN_ANALOG_BTN    16

void GCC_setup();
void GCC_delay1ms();
void GCC_delay2ms();
void GCC_delay3ms();

uint8_t getAnalogMode();

#endif