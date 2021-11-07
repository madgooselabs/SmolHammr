#ifndef GCC_HPP
#define GCC_HPP

#include <Arduino.h>

#ifdef TARGET_RPI_PICO
  #include "boards/rp2040.hpp"
#endif

#ifdef TARGET_TEENSY_4_1
  #include "boards/teensy41.hpp"
#endif

// Gamecube data structure, bit order listed left to right, in order of transmission
// Byte 0 - 0, 0, 0, Start, Y, X, B, A
extern uint8_t GCC_byte0; 
//                        1
//                        2
//                        4
#define GCC_START         8
#define GCC_Y             16
#define GCC_X             32
#define GCC_B             64
#define GCC_A             128
// Byte 1 - 1, L, R, Z, DPad
extern uint8_t GCC_byte1;
#define GCC_MYSTERY_BIT   1
#define GCC_L             2
#define GCC_R             4
#define GCC_Z             8
#define GCC_DPAD_UP       16
#define GCC_DPAD_DOWN     32
#define GCC_DPAD_LEFT     64
#define GCC_DPAD_RIGHT    128
// Byte 2 - Left joystick X value
extern uint8_t GCC_byte2;
// Byte 3 - Left joystick Y value
extern uint8_t GCC_byte3;
// Byte 4 - C-Stick X value
extern uint8_t GCC_byte4;
// Byte 5 - C-Stick Y value
extern uint8_t GCC_byte5;
// Byte 6 - L analog value
extern uint8_t GCC_byte6;
// Byte 7 - R analog value
extern uint8_t GCC_byte7;

// In Melee Z is treated as R+A.
// The game's implementation of this is... less than ideal and tends to drop either of the inputs
// So we can choose to treat it as a raw R+A or as Z
#define GCC_Z_IS_MACRO 0

// The entire packet to be sent to the console
#define GCC_PACKET GCC_sendZero();\
  GCC_sendZero();\
  GCC_sendZero();\
  if (GCC_byte0 & 8) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte0 & 16) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte0 & 32) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte0 & 64) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte0 & 128) GCC_sendOne();\
  else GCC_sendZero();\
  GCC_sendOne();\
  if (GCC_byte1 & 2) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte1 & 4) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte1 & 8) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte1 & 16) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte1 & 32) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte1 & 64) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte1 & 128) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte2 & 1) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte2 & 2) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte2 & 4) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte2 & 8) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte2 & 16) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte2 & 32) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte2 & 64) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte2 & 128) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte3 & 1) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte3 & 2) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte3 & 4) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte3 & 8) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte3 & 16) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte3 & 32) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte3 & 64) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte3 & 128) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte4 & 1) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte4 & 2) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte4 & 4) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte4 & 8) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte4 & 16) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte4 & 32) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte4 & 64) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte4 & 128) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte5 & 1) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte5 & 2) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte5 & 4) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte5 & 8) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte5 & 16) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte5 & 32) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte5 & 64) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte5 & 128) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte6 & 1) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte6 & 2) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte6 & 4) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte6 & 8) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte6 & 16) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte6 & 32) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte6 & 64) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte6 & 128) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte7 & 1) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte7 & 2) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte7 & 4) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte7 & 8) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte7 & 16) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte7 & 32) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte7 & 64) GCC_sendOne();\
  else GCC_sendZero();\
  if (GCC_byte7 & 128) GCC_sendOne();\
  else GCC_sendZero();

void GCC_macroPress();
void GCC_macroRelease();

void GCC_sendZero();
void GCC_sendOne();
void GCC_sendStop();

void GCC_discoveryAck();
void GCC_originProbeResponse();
void GCC_sendReport();

#endif
