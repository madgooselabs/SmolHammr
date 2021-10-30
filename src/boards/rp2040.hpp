#ifndef RP2040_HPP
#define RP2040_HPP

#include <Arduino.h>

#pragma message "Compiling for board Raspberry Pi Pico !"

// GCC data line manipulation
#define GCC_LOW           gpio_clr_mask(1 << 16)
#define GCC_HIGH          gpio_set_mask(1 << 16)
#define GCC_READ          NULL
#define GCC_DATA_IN       17
#define GCC_DATA_OUT      16

// Anti-magic fields
#define READ_A            gpio_get(2)
#define READ_B            gpio_get(3)
#define READ_X            gpio_get(4)
#define READ_Y            gpio_get(5)

#define READ_L            gpio_get(6)
#define READ_R            gpio_get(7)
#define READ_Z            gpio_get(8)
#define READ_START        gpio_get(9)

#define READ_C_UP         gpio_get(10)
#define READ_C_DOWN       gpio_get(11)
#define READ_C_LEFT       gpio_get(12)
#define READ_C_RIGHT      gpio_get(13)

#define READ_DPAD_UP      gpio_get(21)
#define READ_DPAD_DOWN    gpio_get(20)
#define READ_DPAD_LEFT    gpio_get(19)
#define READ_DPAD_RIGHT   gpio_get(18)

#define READ_MACRO        gpio_get(14)
#define READ_TILT         gpio_get(15)

void GCC_setup();
void GCC_delay1ms();
void GCC_delay2ms();
void GCC_delay3ms();

uint8_t getAnalogMode();

#endif