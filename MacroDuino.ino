/*
Andrew Oke - andrew@practicalmaker.com
 */
/*
BEGIN ENABLE VARIABLES. UNCOMMENT TO ENABLE, COMMENT TO DISABLE
*/
//debugging stuff. if you add serial.prints try and wrap them in #ifdef DEBUG ... #endif that way they can be turned off in production code
//#define DEBUG
//#define DEBUGFREEMEMORY
//#define DEBUGETHERNETQUERYSTRING
//#define DEBUGETHERNETRETURNDATA

#define SERIALON  // if uncommented also uncomment #include "control.h" AND #include "serialInterface.h"
//uncomment to enable things like digitalRead, digitalWrite and analogWrite
#define DIGITALPINSENABLED
//uncomment to enable analogRead
#define ANALOGENABLED
//uncomment to use ds18b20 sensorsz
#define DS18B20ENABLED  // if uncommented also uncomment #include <O
//uncomment to enable pH readings
#define PHENABLED
//uncomment to enable ORP readings
#define ORPENABLED
//uncomment to enable pcf8574a
#define PCF8574AENABLED
//uncomment if you want to enable macros
#define MACROSENABLED
//uncomment to enable sending data to COSM
//#define SENDTOCOSMENABLED
//uncomment to have readings in celsius
//#define CELSIUS
//uncomment to use 1wire parasitic power mode
//#define ONEWIRE_PARASITIC_POWER_MODE
/*
END ENABLE VARIABLES
*/

/*
BELOW ARE VARIABLES YOU CAN CHANGE
*/
//to ensure better pH readings take a measurement of the voltage on your arduino and put that in here.
#define ARDUINO_VOLTAGE 4.484

#define ONEWIRE_PIN 2

#ifdef SENDTOCOSMENABLED
#define COSM_APIKEY "" // fill in your API key
#define COSM_FEED_ID 60964     // this is your Pachube feed ID that you want to share to
#define COSM_UPDATE_INTERVAL 60000    // if the connection is good wait 30 seconds before updating again - should not be less than 5
#endif

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
/*
END VARIABLES YOU CAN CHANGE
*/

/*
BEGIN LIBRARIES. TO ENABLE FUNCTIONALITY, UNCOMMENT THE LIBRARY. TO DISABLE FUNCTIONALITY COMMENT LIBRARY
*Note: If you've enabled something in the ENABLE VARIABLES and it's not working double check to make sure that it's library is also uncommented.
ie. If you uncomment DS18B20ENABLED but don't uncomment #include <OneWire.h> it won't work because the code checks to make sure they're both available before enabling
*/
#include <Arduino.h> // needs to be enabled
#include <EEPROM.h> // needs to be enabled
#include <Wire.h>
//#include <SD.h>
#include <SPI.h>  //needs to be uncommented if #include <Ethernet.h> is uncommented
#include <Ethernet.h>  //if uncommented also uncomment #include "ethernetInterface.h"
//#include <Tlc5940.h>
//#include <tlc_animations.h>
//#include <tlc_config.h>
//#include <tlc_fades.h>
//#include <tlc_progmem_utils.h>
//#include <tlc_servos.h>
//#include <tlc_shifts.h>
#include <OneWire.h>
//#include <I2CLCD.h>
#include <DS1307.h>
#include <Cosm.h>
#include "variables.h" // needs to be enabled
//#include "freemem.h"
#include "supportFunctions.h"
#include "control.h"
#include "ethernetInterface.h" // if uncommented also uncomment #include "control.h"
#include "serialInterface.h" // if uncommented also uncomment #include "control.h"
//#include "LCDPrint.h"
#include "cosmFunctions.h"

/*
You shouldn't need to change anything below this line
*/

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
  
  #ifdef ethernet_h
    Ethernet.begin(mac, ip);
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

  #ifdef DEBUG && DEBUGFREEMEMORY
  Serial.print("Free Memory: ");
  Serial.println(availableMemory());
  #endif
 
  currentMillis = millis();
}

