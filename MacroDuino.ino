/*
Andrew Oke - andrew@practicalmaker.com
 */
//debugging stuff. if you add serial.prints try and wrap them in #if DEBUG == 1 that way they can be turned off in production code
#define DEBUG 1
#define DEBUGFREEMEMORY 0
#define DEBUGETHERNETQUERYSTRING 1
#define DEBUGETHERNETRETURNDATA 1

//enable digitalRead and digitalWrite and analogWrite using the control functions
#define DIGITALPINSENABLED 1 
//enable reading analog pins (doesn't need to be enabled to read pH)
#define ANALOGENABLED 1
//enable reading ds18b20 temp sensors
#define DS18B20ENABLED 1 
//Not Defined in orginal code
#define I2CLCDENABLED 1
//Not Defined in orginal code
#define DS1307ENABLED 1 

#define PHENABLED 1 //enable ph readings
#define ORPENABLED 1 //enable ORP readings
#define PCF8574AENABLED 1 // enable use of pcf8574a i2c port expander. PCF8574A has a different address than PCF8574. Port expander shield uses PCF8574A
#define MACROSENABLED 1 // if you want to use macros enable this

#define CELSIUS 1 //change celsius to 1 to change readings to celsius
#define SENDTOPACHUBEENABLED 0 //enable sending data to pachube. You'll need to change the PACHUBE_ variables below and do some configuring in pachubeFunctions.h
#define ONEWIRE_PIN 2 //which pin to connect the onewire pin to.
#define ARDUINO_VOLTAGE 4.484 //to ensure better pH readings take a measurement of the voltage on your arduino and put that in here.
#define PH_PIN 2 //which analog pin to use for measuring ph that displayed on the LCD display.

#define ORP_PIN 3 // New Addition, show ORP on screen. 

#define ONEWIRE_PARASITIC_POWER_MODE 0 // change to 1 to use parasitc power mode

#if SENDTOPACHUBEENABLED == 0
#define PACHUBE_API_KEY            "YOUR_API_KEY" // fill in your API key
#define PACHUBE_SHARE_FEED_ID              29141     // this is your Pachube feed ID that you want to share to
#define PACHUBE_REMOTE_FEED_ID             0      // this is the ID of the remote Pachube feed that you want to connect to
#define PACHUBE_REMOTE_FEED_DATASTREAMS    4        // make sure that remoteSensor array is big enough to fit all the remote data streams
#define PACHUBE_UPDATE_INTERVAL            30000    // if the connection is good wait 30 seconds before updating again - should not be less than 5
#define PACHUBE_RESET_INTERVAL             30000    // if connection fails/resets wait 30 seconds before trying again - should not be less than 5  
#endif

#include <Arduino.h> // needs to be enabled
#include <EEPROM.h> // needs to be enabled
//#include <Wire.h>
//#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>
//#include <Tlc5940.h>
//#include <tlc_animations.h>
//#include <tlc_config.h>
//#include <tlc_fades.h>
//#include <tlc_progmem_utils.h>
//#include <tlc_servos.h>
//#include <tlc_shifts.h>
//#include <OneWire.h>
//#include <I2CLCD.h>
//#include <DS1307.h>
#include "variables.h"
//#include "freemem.h"
#include "supportFunctions.h"
#include "control.h"
#include "ethernetInterface.h"
#include "serialInterface.h"
//#include "LCDPrint.h"
//#include "pachubeFunctions.h"

//change these ethernet settings to whatever fits your home network. No need to change mac
#ifdef ethernet_h
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { EEPROM.read(IP_FIRST_OCTET), EEPROM.read(IP_SECOND_OCTET), EEPROM.read(IP_THIRD_OCTET), EEPROM.read(IP_FOURTH_OCTET) };
byte gateway[] = { EEPROM.read(GATEWAY_FIRST_OCTET), EEPROM.read(GATEWAY_SECOND_OCTET), EEPROM.read(GATEWAY_THIRD_OCTET), EEPROM.read(GATEWAY_FOURTH_OCTET) };
byte subnet[] = { EEPROM.read(SUBNET_FIRST_OCTET), EEPROM.read(SUBNET_SECOND_OCTET), EEPROM.read(SUBNET_THIRD_OCTET), EEPROM.read(SUBNET_FOURTH_OCTET) };
#endif

#ifdef ethernet_h
EthernetServer server(80);
#endif

#ifdef I2CLCD_h
I2CLCD lcd = I2CLCD(0x12, 20, 4);
#endif

#ifdef OneWire_h
OneWire ds(ONEWIRE_PIN);
#endif

long previousMillis = 0;
long interval = 1000;

void setup() {
  for(int i = digital_pin_mem_start; i <= digital_pin_mem_end; i++){
    pinMode(i, EEPROM.read(i));
  }
  Serial.begin(9600);
  Serial.println("Starting Up...");
  
  #ifdef __SD_H__
  SD.begin();
  #endif
  
  #ifdef TwoWire_h
  Wire.begin();
  #endif
  
  #ifdef ethernet_h
  Ethernet.begin(mac, ip);
  server.begin();
  #endif  
  
  #ifdef I2CLCD_h
  lcd.init();
  lcd.backlight(0);
  lcd.cursorOff();
  lcd.clear();
  #endif
  
  #ifdef TLC5940_H
  Tlc.init();
  #endif
}


void loop() {
  if(Serial.available() > 0) {
    serialInterface();
  }
  
  #ifdef ethernet_h
  EthernetClient client = server.available();
  if (client) {
    Serial.print("cond: ");
    Serial.println(client);
    ethernetWiznetW5100Interface();
  }
  #endif

  #ifdef I2CLCD_h
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    printToLCD();
  }
  #endif

  #if MACROSENABLED == 1
  runMacros();
  #endif

  #if SENDTOPACHUBEENABLED == 1
  //sendPachubeData();
  #endif  

  #if DEBUG == 1 && DEBUGFREEMEMORY == 1
  Serial.print("Free Memory: ");
  Serial.println(availableMemory());
  #endif
}

