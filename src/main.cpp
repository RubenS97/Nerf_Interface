/*
Nerf Gun Interface
Show Ammo Capacity and Battery Voltage
on 4 digit 7-Segment Display
*/

#include <Arduino.h>
#include "seven_segment.h"
#include <IRremote.hpp>

static constexpr auto PIN_MAGAZIN = A0;
static constexpr auto IR_RECEIVE_PIN = 13;

static constexpr auto MAGAZIN_SIZE = 15;
static constexpr auto BATTERY_VOLTAGE = 3;

int ammo = MAGAZIN_SIZE;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  seven_segment_setup();

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  // Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void loop()
{
  // put your main code here, to run repeatedly:
  seven_segment_write_int(ammo);

  if (digitalRead(PIN_MAGAZIN) == HIGH && ammo > 0)
    --ammo;

  if (IrReceiver.decode())
  {

    // Print a short summary of received data
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    /*
     * !!!Important!!! Enable receiving of the next value,
     * since receiving has stopped after the end of the current received data packet.
     */
    IrReceiver.resume(); // Enable receiving of the next value

    /*
     * Finally, check the received data and perform actions according to the received command
     */
    if (IrReceiver.decodedIRData.command == 0x10)
    {
      // do something
    }
    else if (IrReceiver.decodedIRData.command == 0x11)
    {
      // do something else
    }
  }
}