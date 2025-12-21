//
//    FILE: LC7822_two_device.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/LC7822
//
//  Two devices with fixed wires on the sPin
//  so the address need to be set in the begin() function.


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7822 LC1(4, 5, 6);  //  no sPin, no resetPin.
LC7822 LC2(4, 5, 6);  //  no sPin, no resetPin.


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LC7822_LIB_VERSION: ");
  Serial.println(LC7822_LIB_VERSION);
  Serial.println();

  LC1.begin(0x03);
  LC2.begin(0x0B);
  Serial.println(LC1.getAddress());
  Serial.println(LC2.getAddress());
  Serial.println();

  //  start explicitly all off.
  LC1.setAll(0);
  LC2.setAll(0);

  //  should print 255 0
  LC1.setAll(255);
  Serial.println(LC1.getAll());
  Serial.println(LC2.getAll());
  Serial.println();

  //  should print 255 255
  LC2.setAll(255);
  Serial.println(LC1.getAll());
  Serial.println(LC2.getAll());
  Serial.println();

  //  should print 0 255
  LC1.setAll(0);
  Serial.println(LC1.getAll());
  Serial.println(LC2.getAll());
  Serial.println();

  //  should print 0 0
  LC2.setAll(0);
  Serial.println(LC1.getAll());
  Serial.println(LC2.getAll());
  Serial.println();

}


void loop()
{
}


//  -- END OF FILE --
