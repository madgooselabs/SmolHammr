#include "GCC.hpp"

uint8_t GCC_byte0 = 0;
uint8_t GCC_byte1 = 128;
uint8_t GCC_byte2 = 128;
uint8_t GCC_byte3 = 128;
uint8_t GCC_byte4 = 128;
uint8_t GCC_byte5 = 128;
uint8_t GCC_byte6 = 128;
uint8_t GCC_byte7 = 128;

// What does the Macro button do ?
// This one does L+R+A:
void GCC_macroPress()
{
  GCC_byte0 &= GCC_A;
  GCC_byte1 &= (GCC_L & GCC_R);
}
void GCC_macroRelease()
{
  GCC_byte0 ^= GCC_A;
  GCC_byte1 ^= (GCC_L & GCC_R);
}

void GCC_sendZero()
{
  // Sends what the GameCube recognizes as a zero
  GCC_LOW;
  GCC_delay3ms();
  GCC_HIGH;
  GCC_delay1ms();
}

void GCC_sendOne()
{
  // Sends what the GameCube recognizes as a one

  GCC_LOW;
  GCC_delay1ms();
  GCC_HIGH;
  GCC_delay3ms();
}

void GCC_sendStop()
{
  // Sends what the GameCube recognizes as a stop bit

  GCC_LOW;
  GCC_delay1ms();
  GCC_HIGH;
  GCC_delay2ms();
}

void GCC_discoveryAck()
{
  // Used once to tell the console there is a controller on the line
  noInterrupts();

  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendOne();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendOne();

  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();

  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendOne();
  GCC_sendOne();

  GCC_sendStop();

  interrupts();
}

void GCC_originProbeResponse()
{
// Disable interrupts
  noInterrupts();
  
  GCC_PACKET;

  // Send two extras null bytes for some reason ?
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();

  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();
  GCC_sendZero();

  // Send stop bit
  GCC_sendStop();

  // Enable interrupts again
  interrupts();
}

void GCC_sendReport()
{
  // Disable interrupts
  noInterrupts();
  
  GCC_PACKET;

  // Send stop bit
  GCC_sendStop();

  // Enable interrupts again
  interrupts();
}
