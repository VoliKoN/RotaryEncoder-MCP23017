// -----
// MultipleRotator.ino - Example for the McpEncoder library.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// More information on: http://www.mathertel.de/Arduino
// -----
// 18.01.2014 created by Matthias Hertel
// -----

// This example checks the state of multiple rotary encoders in the loop() function.
// The current position is printed on output when changed.

// Hardware setup:
// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)
// Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)

// Attach a rotary encoder with output pins to Input #0 and Input #1.
// Attach another rotary encoder with output pins to Input #2 and Input #3.
// The common contact should be attached to ground.

#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <McpEncoder.h>

// Setup a RoraryEncoder for pins A2 and A3:
McpEncoder encoder1(0, 1, 0);
McpEncoder encoder2(2, 3, 0);

void setup()
{
  Serial.begin(57600);
  Serial.println("SimplePollRotator example for the McpEncoder library.");
  encoder1.init();
  encoder2.init();
} // setup()


// Read the current position of the encoder and print out when changed.
void loop()
{
  static int pos1 = 0;
  static int pos2 = 0;
  encoder1.tick();
  encoder2.tick();

  int newPos1 = encoder1.getPosition();
  int newPos2 = encoder2.getPosition();
  if (pos1 != newPos1) {
    Serial.print("1 :");
    Serial.print(newPos1);
    Serial.println();
    pos1 = newPos1;
  } // if
  if (pos2 != newPos2) {
    Serial.print("2 :");
    Serial.print(newPos2);
    Serial.println();
    pos2 = newPos2;
  } // if
} // loop ()

// The End
