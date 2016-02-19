// -----
// McpEncoder.cpp - Library for using rotary encoders.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// More information on: http://www.mathertel.de/Arduino
// -----
// 18.01.2014 created by Matthias Hertel
// -----

#include "Arduino.h"
#include "McpEncoder.h"
#include "Adafruit_MCP23017.h"

// The array holds the values –1 for the entries where a position was decremented,
// a 1 for the entries where the position was incremented
// and 0 in all the other (no change or not valid) cases.

const int8_t KNOBDIR[] = {
  0, -1,  1,  0,
  1,  0,  0, -1,
  -1,  0,  0,  1,
0,  1, -1,  0  };


// positions: [3] 1 0 2 [3] 1 0 2 [3]
// [3] is the positions where my rotary switch detends
// ==> right, count up
// <== left,  count down


// ----- Initialization and Default Values -----

McpEncoder::McpEncoder(int pin1, int pin2, int mcp_num) {
  // Remember Hardware Setup
  _pin1 = pin1;
  _pin2 = pin2;
  _mcp_num = mcp_num;
  
  //Setup MCP23017
  _mcp.begin(_mcp_num);
  // Setup the input pins
  _mcp.pinMode(pin1, INPUT);
  _mcp.pullUp(pin1, HIGH);   // turn on pullup resistor

  _mcp.pinMode(pin2, INPUT);
  _mcp.pullUp(pin2, HIGH);   // turn on pullup resistor

  // when not started in motion, the current state of the encoder should be 3
  _oldState = 3;

  // start with position 0;
  _position = 0;
  _positionExt = 0;
} // McpEncoder()

int  McpEncoder::getPosition() {
  return _positionExt;
}

void McpEncoder::setPosition(int newPosition) {
  // only adjust the external part of the position.
  
  _position = ((newPosition<<2) | (_position & 0x03));
  _positionExt = newPosition;

}

void McpEncoder::tick(void)
{
  int sig1 = _mcp.digitalRead(_pin1);
  int sig2 = _mcp.digitalRead(_pin2);
  int8_t thisState = sig1 | (sig2 << 1);

  if (_oldState != thisState) {
    _position += KNOBDIR[thisState | (_oldState<<2)];
    
    if (thisState == LATCHSTATE)
      _positionExt = _position >> 2;
    
    _oldState = thisState;
  } // if
} // tick()

// End