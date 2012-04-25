float c2f(float cel) {
  return (cel * (9.0/5.0)) + (float)3200;
}

int highValue(int value) {
  return value / 256;
}

int lowValue(int value) {
  return value % 256; 
}

int combineValue(unsigned int lb, unsigned int hb) {
  return ((hb * 256) + lb);
}


void resetMacros(){
  for(int i = macros_memstart; i <= macros_memend; i++){
    EEPROM.write(i, 0);
  }
}

#if DIGITALPINSENABLED == 1
void pinModeSet(byte pin, byte mode){
  EEPROM.write(pin, mode);
  pinMode(pin, mode);
}
#endif

#if DIGITALPINSENABLED == 1
void setPinStatus(byte pin, byte Status) {
  if(Status <= 1) {
    digitalWrite(pin, Status);
  }
  else if(Status > 1) {
    analogWrite(pin, Status);
  }
}
#endif

#if PCF8574AENABLED == 1
#ifdef TwoWire_h
void controlPCF8574A(byte device, byte pin_status, byte pin) {
  if(pin_status == 0) {
    pcf8574a_states[device] |= (1 << pin);
    Wire.beginTransmission(pcf8574a_addresses[device]);
    Wire.write(pcf8574a_states[device]);
    Wire.endTransmission();
  }
  else if(pin_status == 1) {
    pcf8574a_states[device] &= ~(1 << pin);
    Wire.beginTransmission(pcf8574a_addresses[device]);
    Wire.write(pcf8574a_states[device]);
    Wire.endTransmission();    
  }
}
#endif
#endif

//TODO - intelligently handle numbers > 255 and store them.
#if MACROSENABLED == 1
void macroSet(char *macro_name,  int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10){
  int arg11;
  int arg12;
  int arg13;
  int arg14;
  int memstart;
  for(int i=0; i<((macros_memend - macros_memstart)/macros_bytes); i++) {
    if(EEPROM.read((macros_memstart + (i * macros_bytes))) == 0) {
      memstart = macros_memstart + (i * macros_bytes);
      break;
    }
  }

  if(arg1 > 255) {
    arg14 = highValue(arg1);    
    arg1 = lowValue(arg1);
  }
  else if(arg2 > 255) {
    arg14 = highValue(arg2);    
    arg2 = lowValue(arg2);    
  }
  else if(arg3 > 255) {
    arg14 = highValue(arg3);    
    arg3 = lowValue(arg3);    
  }
  else if(arg4 > 255) {
    arg14 = highValue(arg4);    
    arg4 = lowValue(arg4);    
  }
  else if(arg5 > 255) {
    arg14 = highValue(arg5);    
    arg5 = lowValue(arg5);
  }
  else if(arg6 > 255) {
    arg14 = highValue(arg6);    
    arg6 = lowValue(arg6);    
  }
  else if(arg7 > 255) {
    arg14 = highValue(arg7);    
    arg7 = lowValue(arg7);    
  }
  else if(arg8 > 255) {
    arg14 = highValue(arg8);    
    arg8 = lowValue(arg8);
  }    

  EEPROM.write(memstart, 1);
  EEPROM.write(memstart + 1, arg1);  
  EEPROM.write(memstart + 2, arg2);
  EEPROM.write(memstart + 3, arg3);
  EEPROM.write(memstart + 4, arg4);
  EEPROM.write(memstart + 5, arg5);
  EEPROM.write(memstart + 6, arg6);
  EEPROM.write(memstart + 7, arg7);
  EEPROM.write(memstart + 8, arg8);
  EEPROM.write(memstart + 9, arg9);
  EEPROM.write(memstart + 10, arg10);
  EEPROM.write(memstart + 11, arg11);
  EEPROM.write(memstart + 12, arg12);
  EEPROM.write(memstart + 13, arg13);
  EEPROM.write(memstart + 14, arg14);  

  int counter = 0;
  boolean check = false;
  for(int i=15; i<= 19; i++) {
    if(macro_name[counter] != NULL && check != true) {
      EEPROM.write(memstart + i, macro_name[counter]);
      counter++;
    } 
    else if(macro_name[counter] == NULL && check == false) {
      EEPROM.write(memstart + i, 0);      
      check = true;
    }
  } 
}
#endif

#if DIGITALPINSENABLED == 1
void runDigitalMacro(unsigned int mem_address){
  if(digitalRead(EEPROM.read(mem_address + 2)) == EEPROM.read(mem_address + 3)) {
    if(EEPROM.read(mem_address + 5) <= 1) {
      if(EEPROM.read(mem_address + 4) <= 13) {  
        digitalWrite(EEPROM.read(mem_address + 4), EEPROM.read(mem_address + 5));
      } 
      else if(EEPROM.read(mem_address + 4) == 254) { //pcf8574
#if PCF8574AENABLED == 1
        controlPCF8574A(EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 5), EEPROM.read(mem_address + 7));
#endif
      }
    }
    else{
      analogWrite(EEPROM.read(mem_address + 4), EEPROM.read(mem_address + 5));		
    }
  }
}
#endif

#if ANALOGENABLED == 1
void runAnalogMacro(unsigned int mem_address){
  if(EEPROM.read(mem_address + 4) == 1) {
    if(analogRead(EEPROM.read(mem_address + 2)) < combineValue(EEPROM.read(mem_address + 3), EEPROM.read(mem_address + 14))) {
      if(EEPROM.read(mem_address + 6) <= 1) {
        if(EEPROM.read(mem_address + 5) <= 13) {
          digitalWrite(EEPROM.read(mem_address + 5), EEPROM.read(mem_address + 6));
        }
        else if(EEPROM.read(mem_address + 5) == 254) { //pcf8574
#if PCF8574AENABLED == 1
          controlPCF8574A(EEPROM.read(mem_address + 7), EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 8));
#endif
        }
      }
      else if(EEPROM.read(mem_address + 6) > 1) {
        analogWrite(EEPROM.read(mem_address + 5), EEPROM.read(mem_address + 6));
      }
    }
  }
  else if(EEPROM.read(mem_address + 4) == 2) {
    if(analogRead(EEPROM.read(mem_address + 2)) > combineValue(EEPROM.read(mem_address + 3), EEPROM.read(mem_address + 14))) {
      if(EEPROM.read(mem_address + 6) <= 1) {
        if(EEPROM.read(mem_address + 5) <= 13) {
          digitalWrite(EEPROM.read(mem_address + 5), EEPROM.read(mem_address + 6));
        }
        else if(EEPROM.read(mem_address + 5) == 254) { //pcf8574
#if PCF8574AENABLED == 1
          controlPCF8574A(EEPROM.read(mem_address + 7), EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 8));
#endif
        }
      }
      else if(EEPROM.read(mem_address + 6) > 1) {
        analogWrite(EEPROM.read(mem_address + 5), EEPROM.read(mem_address + 6));
      }
    }	
  }
  else if(EEPROM.read(mem_address + 4) == 3) {
    if(analogRead(EEPROM.read(mem_address + 2)) == combineValue(EEPROM.read(mem_address + 3), EEPROM.read(mem_address + 14))) {
      if(EEPROM.read(mem_address + 6) <= 1) {
        if(EEPROM.read(mem_address + 5) <= 13) {
          digitalWrite(EEPROM.read(mem_address + 5), EEPROM.read(mem_address + 6));
        }
        else if(EEPROM.read(mem_address + 5) == 254) { //pcf8574
#if PCF8574AENABLED == 1
          controlPCF8574A(EEPROM.read(mem_address + 7), EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 8));
#endif
        }
      }
      else if(EEPROM.read(mem_address + 6) > 1) {
        analogWrite(EEPROM.read(mem_address + 5), EEPROM.read(mem_address + 6));
      }
    }
  }
}
#endif

#ifdef DS1307_h
void DS1307SetTime(byte hour, byte minute, byte second, byte day, byte dow, byte month, byte year){
  RTC.stop();
  RTC.set(DS1307_SEC, second);        //set the seconds
  RTC.set(DS1307_MIN, minute);     //set the minutes
  RTC.set(DS1307_HR, hour);       //set the hours
  RTC.set(DS1307_DOW, dow);       //set the day of the week
  RTC.set(DS1307_DATE, day);       //set the date
  RTC.set(DS1307_MTH, month);        //set the month
  RTC.set(DS1307_YR, year);         //set the year
  RTC.start();
}
#endif

#ifdef DS1307_h
void runDS1307Macro(unsigned int mem_address){
  unsigned int time_start;
  unsigned int time_stop;
  unsigned int rtc_time;		

  rtc_time = (RTC.get(DS1307_HR,true) * 60) + RTC.get(DS1307_MIN,true);
  time_start = (EEPROM.read(mem_address + 2) * 60) + EEPROM.read(mem_address + 3);
  time_stop = (EEPROM.read(mem_address + 4) * 60) + EEPROM.read(mem_address + 5);

  if(RTC.get(DS1307_DOW, false) == EEPROM.read(mem_address + 6) || EEPROM.read(mem_address + 6) == 0) {	
    if(rtc_time >= time_start && rtc_time <= time_stop) {
      if(EEPROM.read(mem_address + 8) <= 1) {
        if(EEPROM.read(mem_address + 7) <= 13) {
          digitalWrite(EEPROM.read(mem_address + 7), EEPROM.read(mem_address + 8));
        } 
        else if(EEPROM.read(mem_address + 7) == 254) { //pcf8574
#if PCF8574AENABLED == 1
          controlPCF8574A(EEPROM.read(mem_address + 10), EEPROM.read(mem_address + 8), EEPROM.read(mem_address + 11));
#endif
        }
      } 
      else {
        if(rtc_time < (time_start + EEPROM.read(mem_address + 9))) { //fade in
          if(EEPROM.read(mem_address + 7) <= 13) {
            int pwm_value = (rtc_time - time_start) * (EEPROM.read(mem_address + 8) / EEPROM.read(mem_address + 9));
#if DEBUG == 1
            Serial.print("PWM Fade In: ");
            Serial.println(pwm_value);
#endif
            analogWrite(EEPROM.read(mem_address + 7), pwm_value);
          }
        }
        else if(rtc_time > (time_stop - EEPROM.read(mem_address + 9))) { //fade out
          int pwm_value = (time_stop - rtc_time) * (EEPROM.read(mem_address + 8) / EEPROM.read(mem_address + 9));
#if DEBUG == 1
          Serial.print("PWM Fade Out: ");        
          Serial.println(pwm_value);
#endif        
          analogWrite(EEPROM.read(mem_address + 7), pwm_value);
        } 
        else {
#if DEBUG == 1
          Serial.print("PWM On at: ");
          Serial.println(EEPROM.read(mem_address + 8));
#endif
          analogWrite(EEPROM.read(mem_address + 7), EEPROM.read(mem_address + 8));
        }

      }
    }
    else if(rtc_time > time_stop) {
      digitalWrite(EEPROM.read(mem_address + 7), 0);
#if PCF8574AENABLED == 1
      controlPCF8574A(EEPROM.read(mem_address + 10), 0, EEPROM.read(mem_address + 11));    
#endif
    }
  }
}
#endif

#ifdef OneWire_h
int discoverOneWireDevices() {
  OneWire ds(ONEWIRE_PIN);

  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  unsigned int d = 0;
  unsigned int e;

  while(ds.search(addr)) {

    e = onewire_addresses_memstart + (d * onewire_addresses_bytes);
    
    for( i = 0; i < 8; i++) {

      EEPROM.write((e + i), addr[i]);
      Serial.println(addr[i]);
    }

    if ( OneWire::crc8( addr, 7) != addr[7]) {
      return 0;
    }
    d++;
  }
  EEPROM.write(num_ds18b20_devices, d);

  ds.reset_search();
  return d;
}
#endif

#if DS18B20ENABLED
int getDS18B20Temp(int device_num) {
  OneWire ds(ONEWIRE_PIN);

  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;

  for(i = 0; i < 8; i++){
    addr[i] = EEPROM.read((onewire_addresses_memstart + (onewire_addresses_bytes * device_num) + i)); 
  }

#if DEBUG == 1
  if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.print("CRC is not valid!\n");
  }
#endif

#if DEBUG == 1
  if ( addr[0] != 0x28) {
    Serial.print("Device is not a DS18S20 family device.\n");
  }
#endif

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);

#if ONEWIRE_PARASITIC_POWER_MODE == 1	
  delay(1000);
#endif

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);

  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit
  if (SignBit) {
    TReading = (TReading ^ 0xffff) + 1; // 2's comp
  }
  Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25

#if CELSIUS == 0
  Tc_100 = c2f(Tc_100);
#endif 

  return Tc_100;
}
#endif

#if PHENABLED == 1
float getPHValue(unsigned int pin) {
  int analogreadings;
  unsigned int millivolts;
  float ph;
  unsigned int i;

  analogreadings = 0;
  for(i = 1; i < 50; i++){
    analogreadings += analogRead(pin);
    // give analog pin time to recover
    delay(10);
  }
  analogreadings /= i;

  millivolts = ((analogreadings * ARDUINO_VOLTAGE) / 1024) * 1000;

  ph = ((millivolts / PH_GAIN) / 59.2) + 7;

  return ph; 
}
#endif

#if ORPENABLED == 1
int getORPValue(unsigned int pin) {
  int analogreadings;
  int millivolts;
  unsigned int i;

  analogreadings = 0;
  for(i = 1; i < 50; i++){
    analogreadings += analogRead(pin);
    // give analog pin time to recover
    delay(10);
  }
  analogreadings /= i;

  millivolts = ((analogreadings * ARDUINO_VOLTAGE) / 1024) * 1000;
  return millivolts; 
}
#endif

#ifdef OneWire_h
#ifdef EEPROM_h
void runDS18B20Macro(int mem_address) {
  int temp;

  temp = getDS18B20Temp(EEPROM.read(mem_address + 2));

  if(EEPROM.read(mem_address + 3) == 1) {
    if(temp < ((EEPROM.read(mem_address + 4) * 100) + EEPROM.read(mem_address + 5))) {
      if(EEPROM.read(mem_address + 7) <= 1) {
        if(EEPROM.read(mem_address + 6) <= 13) {
          digitalWrite(EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 7));
        }
        else if(EEPROM.read(mem_address + 6) == 254) { //pcf8574
          controlPCF8574A(EEPROM.read(mem_address + 8), EEPROM.read(mem_address + 7), EEPROM.read(mem_address + 9));
        }
      } 
      else {
        analogWrite(EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 7));			
      }
    }
  } 
  else if(EEPROM.read(mem_address + 3) == 2) {
    if(temp > ((EEPROM.read(mem_address + 4) * 100) + EEPROM.read(mem_address + 5))) {
      if(EEPROM.read(mem_address + 7) <= 1) {
        if(EEPROM.read(mem_address + 6) <= 13) {
          digitalWrite(EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 7));
        }
        else if(EEPROM.read(mem_address + 6) == 254) { //pcf8574
          controlPCF8574A(EEPROM.read(mem_address + 8), EEPROM.read(mem_address + 7), EEPROM.read(mem_address + 9));
        }
      } 
      else {
        analogWrite(EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 7));			
      }
    }	
  } 
  else if(EEPROM.read(mem_address + 3) == 3) {
    if(temp == ((EEPROM.read(mem_address + 4) * 100) + EEPROM.read(mem_address + 5))) {
      if(EEPROM.read(mem_address + 7) <= 1) {
        if(EEPROM.read(mem_address + 6) <= 13) {
          digitalWrite(EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 7));
        }
        else if(EEPROM.read(mem_address + 6) == 254) { //pcf8574
          controlPCF8574A(EEPROM.read(mem_address + 8), EEPROM.read(mem_address + 7), EEPROM.read(mem_address + 9));
        }
      } 
      else {
        analogWrite(EEPROM.read(mem_address + 6), EEPROM.read(mem_address + 7));			
      }
    }	
  }
}
#endif  
#endif

#ifdef TLC5940_H
void controlTLC5940(int tlc_pin_num, int tlc_action) {
  Tlc.set(tlc_pin_num, tlc_action);
  Tlc.update();
  delay(100);
}
#endif

void runMacros() {
  int macro_mem_address_start;
  for(unsigned int i = 0; i < ((macros_memend - macros_memstart) / macros_bytes); i++) {
    macro_mem_address_start = macros_memstart + (i * macros_bytes);
    if(EEPROM.read(macro_mem_address_start) == 1) {    
      if(EEPROM.read(macro_mem_address_start + 1) == 1) {
#if DIGITALPINSENABLED == 1
        runDigitalMacro(macro_mem_address_start);
#endif
      }
      else if(EEPROM.read(macro_mem_address_start + 1) == 2) {
#if ANALOGENABLED == 1
        runAnalogMacro(macro_mem_address_start);
#endif
      }
      else if(EEPROM.read(macro_mem_address_start + 1) == 3) {
#ifdef DS1307_h
        runDS1307Macro(macro_mem_address_start);
#endif
      }
      else if(EEPROM.read(macro_mem_address_start + 1) == 4) {
#if DS18B20ENABLED == 1
        runDS18B20Macro(macro_mem_address_start);
#endif
      }
    }
  }
}


