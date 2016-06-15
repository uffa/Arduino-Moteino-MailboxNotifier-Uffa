// Moteino based MailboxNotifier - RFM69 TRANSMITTER
// This is the code running on the receiver side, located in the house
// Based on code from LowPowerLab.com:
// https://github.com/LowPowerLab/MailboxNotifier (felix@lowpowerlab.com)
// http://opensource.org/licenses/mit-license.php


//////////////////////
// COM5
//////////////////////


#include <RFM69.h>
#include <SPI.h>
#include <avr/sleep.h>
#include <avr/delay.h>
#include <LowPower.h> //get library from: https://github.com/rocketscream/Low-Power

#define NODEID            1                   // this node's ID, should be unique among nodes on this NETWORKID
#define NETWORKID         100                 // unique id for this unit  //what network this node is on
//#define GATEWAYID         1                   // central node to report data to
#define FREQUENCY         RF69_915MHZ         // Match Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY               "1843891831978911"  // 16 chars, same across all nodes
#define IS_RFM69HW                            // uncomment only for RFM69HW
#define ACK_TIME          30                  // ms to wait for an ack
#define SERIAL_BAUD       115200
#define LEDPIN            9

#define SERIAL_EN                             // uncomment this line to enable serial IO debug messages

#ifdef SERIAL_EN
  #define DEBUG(input)              { Serial.print(input);          delay(1); }
  #define DEBUGF(input,format)      { Serial.print(input,format);   delay(1); }
  #define DEBUGN(input)             { Serial.println(input);        delay(1); }
  #define DEBUGFN(input,format)     { Serial.println(input,format); delay(1); }
#else
  #define DEBUG(input);
  #define DEBUGF(input,format);
  #define DEBUGN(input);
  #define DEBUGFN(input,format);
#endif

// END DEFINITIONS
///////////////////////////////////////////////
// BEGIN GLOBALS

RFM69 radio;
unsigned long now = 0, temp = 0;
// END GLOBALS
///////////////////////////////////////////////
// SETUP
void setup()
{
  pinMode(9, OUTPUT);

  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.encrypt(KEY);
  radio.sleep();
  #ifdef IS_RFM69HW
    radio.setHighPower();
  #endif
  #ifdef SERIAL_EN
    Serial.begin(SERIAL_BAUD);
    DEBUGN("\nListening...");
  #endif

  Blink(LEDPIN,5);
  delay(100);
  Blink(LEDPIN,5);
  DEBUG("FINISHED INIT\n");
}

byte recvCount = 0;

///////////////////////////////////////////////
// LOOP /
void loop()
{
/*  DEBUG("HOUSE LOOP ... ");
  DEBUG(now);
  DEBUGN("");
*/
  temp = millis();

  // check for any received packets
  if (radio.receiveDone())
  {

    DEBUGN("receiveDone...");
    DEBUG(now);
    DEBUG('[');DEBUGF(radio.SENDERID, DEC);DEBUG("] ");
    for (byte i = 0; i < radio.DATALEN; i++)
      DEBUG((char)radio.DATA[i]);
    DEBUG("   [RX_RSSI:");DEBUG(radio.RSSI);DEBUG("]");


    if (radio.ACK_REQUESTED)
      {
        byte theNodeID = radio.SENDERID;
        radio.sendACK();
        DEBUG(" - ACK sent.");
      }

    if (radio.ACKRequested())
    {
      byte rsenderID = radio.SENDERID;
      radio.sendACK();

      DEBUG("ACK requested from NODEID: ");
      DEBUG(rsenderID);
      DEBUGN("");
      DEBUG("ACK sent in response");
      DEBUG(NODEID);
      DEBUG(" > ");
      DEBUG(rsenderID);
      DEBUGN("");

    }

    DEBUGN("");
  }
  now = now + 500 + 22 + (millis()-temp); //correct millis() drift. Add 22ms to compensate time lost in other peripheral code, may need to be tweaked to be accurate

}


void Blink(byte PIN, byte DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}


