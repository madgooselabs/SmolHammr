/*
 * Important note:
 *    "GCC" heretofore refers to "GameCube Controller", not "GNU C Compiler" !!
 */

#include "GCC.hpp"

// Analog headers
#include "joysticks/analog.hpp"
#include "joysticks/JLM.hpp"
#include "joysticks/U360.hpp"

// Error suppression
#ifndef PIN_ANALOG_X
#define PIN_ANALOG_X       NULL
#endif

#ifndef PIN_ANALOG_Y
#define PIN_ANALOG_Y       NULL
#endif

#ifndef PIN_ANALOG_BUTTON
#define PIN_ANALOG_BUTTON  NULL
#endif

// Output mode
typedef enum { USB, GCN, DBG } MODE;
MODE outputMode;

typedef enum { LEVER_JLM, LEVER_ULTRASTIK, LEVER_THUMBSTICK, LEVER_D2A } ANALOG_MODE;
ANALOG_MODE analogMode;

analogInput analog;

void setup()
{
  // Set up GC Data pins
  pinMode(GCC_DATA_OUT, OUTPUT);
  pinMode(GCC_DATA_IN, INPUT_PULLUP);

  GCC_setup();

  Serial.begin(9600);
  Serial.println("SmolHammr ready !");

  // Host mode detection
  Serial.print("Detecting host mode... ");
  outputMode = USB;
  uint16_t counter = millis();
  uint16_t counter2 = counter;
  while (counter2 < counter + 1500)
  {
    if (digitalRead(GCC_DATA_IN) == LOW)  // Attempt to detect the GC line pulled low
    {
      GCC_discoveryAck();

      // Wait for console to stop transmitting before sending origin
      delayMicroseconds(35);
      GCC_originProbeResponse();
      
      outputMode = GCN;    
      break;
    }
    counter2++;
  }

  if (outputMode == USB)
    Serial.println("Output mode has been set to USB");
  else if (outputMode == GCN)
    Serial.println("Output mode has been set to GCN");
  else if (outputMode == DBG)
    Serial.println("Output mode has been set to DEBUG");

  // Get analog mode
  analogMode = (ANALOG_MODE)getAnalogMode();
  if (analogMode == LEVER_JLM) analog = JLM();
  else if (analogMode == LEVER_ULTRASTIK) analog = U360();
  //else if (analogMode == LEVER_THUMBSTICK) analog = Thumbstick();

  analog.begin(ANALOG_SAMPLES_PER_CYCLE, PIN_ANALOG_X, PIN_ANALOG_Y, 5, 10, PIN_ANALOG_BUTTON);

  if ((outputMode == DBG) || (outputMode == GCN))
  {
    GCC_setup();
  }
}

void loop()
{
  analog.sample();

  if (outputMode == USB)
  {
    // TODO
  }
  else if (outputMode == GCN)
  {
    // Byte 0
    GCC_byte0 = 0;

    if (READ_START) GCC_byte0 &= GCC_START;
    else GCC_byte0 ^= GCC_START;
    
    if (READ_Y) GCC_byte0 &= GCC_Y;
    else GCC_byte0 ^= GCC_Y;

    if (READ_X) GCC_byte0 &= GCC_X;
    else GCC_byte0 ^= GCC_X;

    if (READ_B) GCC_byte0 &= GCC_B;
    else GCC_byte1 ^= GCC_B;
    
    if (READ_A) GCC_byte0 &= GCC_A;
    else GCC_byte0 ^= GCC_A;

    // Byte 1
    GCC_byte1 = GCC_MYSTERY_BIT;

    if (READ_L) GCC_byte1 &= GCC_L;
    else GCC_byte1 ^= GCC_L;

    if (READ_R) GCC_byte1 &= GCC_R;
    else GCC_byte1 ^= GCC_R;

    if (READ_Z)
    {
      if (GCC_Z_IS_MACRO)
      {
        GCC_byte1 &= GCC_R;
        GCC_byte0 &= GCC_A;
      }
      else
        GCC_byte1 &= GCC_Z;
    }
    else
    {
      if (GCC_Z_IS_MACRO)
      {
        GCC_byte1 ^= GCC_R;
        GCC_byte0 ^= GCC_A;
      }
      else
        GCC_byte1 ^= GCC_Z;
    }

    if (analogMode == LEVER_D2A) 
    {
      GCC_byte1 &= (~GCC_DPAD_UP & ~GCC_DPAD_DOWN & ~GCC_DPAD_LEFT & ~GCC_DPAD_RIGHT); // Nulls the Dpad
      
      // Cleaning SOCD
      if ((READ_DPAD_LEFT) && (!(READ_DPAD_RIGHT))) GCC_byte2 = 0;
      else if ((!(READ_DPAD_LEFT)) && (READ_DPAD_RIGHT)) GCC_byte2 = 255;
      else GCC_byte2 = 127;

      if ((READ_DPAD_UP) && (!(READ_DPAD_DOWN))) GCC_byte3 = 0;
      else if ((!(READ_DPAD_UP)) && (READ_DPAD_DOWN)) GCC_byte3 = 255;
      else if ((READ_DPAD_UP) && (READ_DPAD_DOWN)) GCC_byte3 = 0;
      else GCC_byte3 = 127;
    }
    else
    {
      if ((READ_DPAD_UP) && (!(READ_DPAD_DOWN))) GCC_byte1 &= (GCC_DPAD_UP & ~GCC_DPAD_DOWN);
      else if ((!(READ_DPAD_UP)) && (READ_DPAD_DOWN)) GCC_byte1 &= (~GCC_DPAD_UP & GCC_DPAD_DOWN);
      else GCC_byte1 ^= (GCC_DPAD_UP & GCC_DPAD_DOWN);
  
      if ((READ_DPAD_LEFT) && (!(READ_DPAD_RIGHT))) GCC_byte1 &= (GCC_DPAD_LEFT & ~GCC_DPAD_RIGHT);
      else if ((!(READ_DPAD_LEFT)) && (READ_DPAD_RIGHT)) GCC_byte1 &= (~GCC_DPAD_LEFT & GCC_DPAD_RIGHT);
      else GCC_byte1 ^= (GCC_DPAD_LEFT & GCC_DPAD_RIGHT);
  
      // Byte 2 and 3
      GCC_byte2 = (uint8_t)map(analog.x, 0, 1023, 0, 255);
      GCC_byte3 = (uint8_t)map(analog.y, 0, 1023, 0, 255);
    }

    // Byte 4
    if (((READ_C_LEFT)) && (!(READ_C_RIGHT))) GCC_byte4 = 0;
    else if ((!(READ_C_LEFT)) && ((READ_C_RIGHT))) GCC_byte4 = 255;
    else GCC_byte4 = 127;

    // Byte 5
    if (((READ_C_UP)) && (!(READ_C_DOWN))) GCC_byte5 = 0;
    else if ((!(READ_C_UP)) && ((READ_C_DOWN))) GCC_byte5 = 255;
    else GCC_byte5 = 127;

    // Byte 6 & 7
    if (GCC_byte1 & READ_L) GCC_byte6 = 255;
    else GCC_byte6 = 0;

    if (GCC_byte1 & READ_R) GCC_byte7 = 255;
    else GCC_byte7 = 0;

    // Macro button
    if (READ_MACRO) GCC_macroPress();
    else GCC_macroRelease();

    GCC_sendReport();
  }
  else if (outputMode == DBG)
  {
    //GCC_sendZero();
    //GCC_sendOne();
    //GCC_sendStop();
    GCC_sendReport();
  }
}
