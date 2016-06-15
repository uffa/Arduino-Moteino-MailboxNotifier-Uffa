// Moteino based MailboxNotifier - RFM69 TRANSMITTER
// This is the code running on the sensor side, located inside the mailbox
// Based on code from LowPowerLab.com:
// https://github.com/LowPowerLab/MailboxNotifier (felix@lowpowerlab.com)
// http://opensource.org/licenses/mit-license.php


//////////////////////
// COM4 > MAILBOX
//////////////////////


#include <RFM69.h>
#include <SPI.h>
#include <avr/sleep.h>
#include <avr/delay.h>
#include <LowPower.h> //get library from: https://github.com/rocketscream/Low-Power
                      //writeup here: http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/

#define NODEID            9                   // this node's ID, should be unique among nodes on this NETWORKID
#define NETWORKID         100                 // unique id for this unit  //what network this node is on
#define GATEWAYID         1                   // central node to report data to
#define FREQUENCY         RF69_915MHZ         // Match Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY               "1843891831978911"  // 16 chars, same across all nodes
#define IS_RFM69HW                            // uncomment only for RFM69HW
#define ACK_TIME          30                  // ms to wait for an ack
#define SERIAL_BAUD       115200
#define LEDPIN            9

#define SERIAL_EN                             // uncomment this line to enable serial IO debug messages will cause a magnitude higher current consumption

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

#define BLINK_EN                              // uncomment this to blink onboard LED every on every sensor reading
                                              // WARNING: even though onboard LED is only 2ma, blinking
#define SENSORREADPERIOD  SLEEP_500MS
#define SENDINTERVAL      5000               // interval for sending readings without ACK

// END DEFINITIONS
///////////////////////////////////////////////
// BEGIN GLOBALS

RFM69 radio;            // define radio and specify type/frequency
unsigned long now = 0, lastSend = 0, temp = 0;

// END GLOBALS
///////////////////////////////////////////////
// SETUP
void setup(void)
{
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.encrypt(KEY);
  radio.sleep();
  #ifdef IS_RFM69HW
    radio.setHighPower();
  #endif
  #ifdef SERIAL_EN
    Serial.begin(SERIAL_BAUD);
    DEBUGN("\nTransmitting...");
  #endif

  Blink(LEDPIN,5);
  delay(100);
  Blink(LEDPIN,5);
  DEBUG("FINISHED INIT\n");
}

///////////////////////////////////////////////
// LOOP
void loop()
{
  DEBUG("MAIL LOOP ... ");
  DEBUG(now);
  DEBUGN("");

  temp = millis();

  // send readings every SENDINTERVAL
  if (abs(now - lastSend) > SENDINTERVAL)
  {
    DEBUGN("SENDING NOTIFICATION...");
    if (radio.sendWithRetry(GATEWAYID, "TEST:DATA", 9))  {
      DEBUGN("RESPONSE: OK!!");
    }
    else {
      DEBUGN("RESPONSE: FAIL");
    }

    radio.sleep();
    lastSend = now;

    #ifdef BLINK_EN
      Blink(LEDPIN, 5);
    #endif
  }

  now = now + 500 + 22 + (millis()-temp); //correct millis() drift. Add 22ms to compensate time lost in other peripheral code, may need to be tweaked to be accurate
  LowPower.powerDown(SENSORREADPERIOD, ADC_OFF, BOD_ON);
}

void Blink(byte PIN, byte DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
