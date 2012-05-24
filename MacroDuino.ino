/*
Andrew Oke - andrew@practicalmaker.com
 */

//debugging stuff. if you add serial.prints try and wrap them in #if DEBUG == 1 that way they can be turned off in production code
#define DEBUG 0
#define DEBUGFREEMEMORY 0
#define DEBUGETHERNETQUERYSTRING 0
#define DEBUGETHERNETRETURNDATA 0

//#define SERIALON
//uncomment to enable things like digitalRead, digitalWrite and analogWrite
#define DIGITALPINSENABLED
//uncomment to enable analogRead
#define ANALOGENABLED
//uncomment to use ds18b20 sensors
#define DS18B20ENABLED
//uncomment to enable pH readings
//#define PHENABLED
//uncomment to enable ORP readings
//#define ORPENABLED
//uncomment to enable pcf8574a
#define PCF8574AENABLED
//uncomment if you want to enable macros
#define MACROSENABLED

#define CELSIUS 0 //change celsius to 1 to change readings to celsius
//uncomment to enable sending data to COSM
#define SENDTOCOSMENABLED
#define ONEWIRE_PIN 2 //which pin to connect the onewire pin to.
#define ARDUINO_VOLTAGE 4.484 //to ensure better pH readings take a measurement of the voltage on your arduino and put that in here.
#define PH_PIN 2 //which analog pin to use for measuring ph that displayed on the LCD display.

#define ORP_PIN 3 // New Addition, show ORP on screen. 

#define ONEWIRE_PARASITIC_POWER_MODE 0 // change to 1 to use parasitc power mode

#ifdef SENDTOCOSMENABLED
#define COSM_APIKEY "" // fill in your API key
#define COSM_FEED_ID 60964     // this is your Pachube feed ID that you want to share to
#define COSM_UPDATE_INTERVAL 30000    // if the connection is good wait 30 seconds before updating again - should not be less than 5
#endif

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


#include <Arduino.h> // needs to be enabled
#include <EEPROM.h> // needs to be enabled
#include <Wire.h>
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
#include <OneWire.h>
//#include <I2CLCD.h>
//#include <DS1307.h>
#include <Pachube.h>
#include "variables.h"
//#include "freemem.h"
#include "supportFunctions.h"
#include "control.h"
#include "ethernetInterface.h"
//#include "serialInterface.h"
//#include "LCDPrint.h"
#include "cosmFunctions.h"

#ifdef ethernet_h
EthernetServer server(80);
#endif

#ifdef I2CLCD_h
I2CLCD lcd = I2CLCD(0x12, 20, 4);
#endif

#ifdef OneWire_h
OneWire ds(ONEWIRE_PIN);
#endif

void setup() {
  for(int i = digital_pin_mem_start; i <= digital_pin_mem_end; i++){
    pinMode(i, EEPROM.read(i));
  }
  
  #ifdef SERIALON
    Serial.begin(9600);
  #endif 
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
  #ifdef SERIALON
    if(Serial.available() > 0) {
      serialInterface();
    }
  #endif
  
  #ifdef ethernet_h
    ethernetWiznetW5100Interface();
  #endif

  #ifdef I2CLCD_h
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    printToLCD();
  }
  #endif

  #ifdef MACROSENABLED
  runMacros();
  #endif

  #ifdef SENDTOCOSMENABLED
    if((currentMillis - COSM_LAST_UPDATE)  > COSM_UPDATE_INTERVAL) {  
      COSM_LAST_UPDATE = currentMillis;
      sendCosmData();
    }
  #endif  

  #if DEBUG == 1 && DEBUGFREEMEMORY == 1
  Serial.print("Free Memory: ");
  Serial.println(availableMemory());
  #endif
 
  currentMillis = millis();
}

