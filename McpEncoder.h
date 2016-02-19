// -----
// McpEncoder.h - Library for using rotary encoders.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// More information on: http://www.mathertel.de/Arduino
// -----
// 18.01.2014 created by Matthias Hertel
// -----

#ifndef McpEncoder_h
#define McpEncoder_h

#include "Arduino.h"
#include "Adafruit_MCP23017.h"
#define LATCHSTATE 3

class McpEncoder
{
public:
  // ----- Constructor -----
  McpEncoder(int pin1, int pin2, int mcp_num);
  
  // retrieve the current position
  int  getPosition();

  // adjust the current position
  void setPosition(int newPosition);

  // call this function every some milliseconds or by using an interrupt for handling state changes of the rotary encoder.
  void tick(void);

private:
  int _pin1, _pin2, _mcp_num; // Arduino pins used for the encoder. 
  
  Adafruit_MCP23017 _mcp;
  
  int8_t _oldState;
  
  int _position;     // Internal position (4 times _positionExt)
  int _positionExt;  // External position
};

#endif

// End