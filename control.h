char *control(char *commandString) {
  //TODO figure out scope so I don't need to redeclare heres
  #ifdef I2CLCD_h
  I2CLCD lcd = I2CLCD(0x12, 20, 4);
  #endif

  /******* NOTES  
   * for control functions with an eeprom.write a delay before returning is needed otherwise no data is returned
   * returnData needs to be setup as follows
   * int counter = 0;
   * returnData[counter] = value;
   * counter++
   * the reason being it makes it easier to change
   */

  char returnData[RETURNDATABUFFERSIZE];
  char itoa_buffer[6];
  byte counter = 0;
  boolean check = false;

  memset(returnData, 0, sizeof returnData);  

  byte commandToken = atoi(strtok(commandString, "/"));
  //PRINT Arduino CONFIG BACK
  if(commandToken == 255) {
    counter = 0;
    
    memset(itoa_buffer, 0, sizeof itoa_buffer);
    itoa(EEPROM.read(ARDUINO_MEM_ADDR), itoa_buffer, 10);
    
    //DISPLAY ARDUINOS ADDRESS
    returnData[counter] = '{';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = ':';
    counter++;
    returnData[counter] = '"';
    counter++;    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '"';
    counter++;    

    #ifdef ethernet_h
    //DISPLAY ARDUINO IP
    returnData[counter] = ',';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = ':';
    counter++;
    returnData[counter] = '"';
    counter++;    
    
    memset(itoa_buffer, 0, sizeof itoa_buffer);
    itoa(EEPROM.read(IP_FIRST_OCTET), itoa_buffer, 10);    
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++;

    memset(itoa_buffer, 0, sizeof itoa_buffer);
    itoa(EEPROM.read(IP_SECOND_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++; 
 
    memset(itoa_buffer, 0, sizeof itoa_buffer); 
    itoa(EEPROM.read(IP_THIRD_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++;     
    
    memset(itoa_buffer, 0, sizeof itoa_buffer);    
    itoa(EEPROM.read(IP_FOURTH_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }    
    
    returnData[counter] = '"';
    counter++;    
    
    //DISPLAY SUBNET INFO
    returnData[counter] = ',';
    counter++;     
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'S';
    counter++;    
    returnData[counter] = 'U';
    counter++;    
    returnData[counter] = 'B';
    counter++;    
    returnData[counter] = 'N';
    counter++;    
    returnData[counter] = 'E';
    counter++;    
    returnData[counter] = 'T';
    counter++;    
    returnData[counter] = '"';
    counter++;     
    returnData[counter] = ':';
    counter++;        
    returnData[counter] = '"';
    counter++;     
    
    memset(itoa_buffer, 0, sizeof itoa_buffer);
    itoa(EEPROM.read(SUBNET_FIRST_OCTET), itoa_buffer, 10);    
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++;

    memset(itoa_buffer, 0, sizeof itoa_buffer);
    itoa(EEPROM.read(SUBNET_SECOND_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++; 
 
    memset(itoa_buffer, 0, sizeof itoa_buffer); 
    itoa(EEPROM.read(SUBNET_THIRD_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++;     
    
    memset(itoa_buffer, 0, sizeof itoa_buffer);    
    itoa(EEPROM.read(SUBNET_FOURTH_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }  
    returnData[counter] = '"';
    counter++;     
  
   //DISPLAY GATEWAY INFO
    returnData[counter] = ',';
    counter++;     
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'G';
    counter++;    
    returnData[counter] = 'A';
    counter++;    
    returnData[counter] = 'T';
    counter++;    
    returnData[counter] = 'E';
    counter++;    
    returnData[counter] = 'W';
    counter++;    
    returnData[counter] = 'A';
    counter++;    
    returnData[counter] = 'Y';
    counter++;        
    returnData[counter] = '"';
    counter++;     
    returnData[counter] = ':';
    counter++;        
    returnData[counter] = '"';
    counter++;     
    
    memset(itoa_buffer, 0, sizeof itoa_buffer);
    itoa(EEPROM.read(GATEWAY_FIRST_OCTET), itoa_buffer, 10);    
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++;

    memset(itoa_buffer, 0, sizeof itoa_buffer);
    itoa(EEPROM.read(GATEWAY_SECOND_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++; 
 
    memset(itoa_buffer, 0, sizeof itoa_buffer); 
    itoa(EEPROM.read(GATEWAY_THIRD_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '.';
    counter++;     
    
    memset(itoa_buffer, 0, sizeof itoa_buffer);    
    itoa(EEPROM.read(GATEWAY_FOURTH_OCTET), itoa_buffer, 10);
    
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    #endif    
    
    returnData[counter] = '"';
    counter++;       
    
    
    returnData[counter] = '}';
    counter++;
    
    delay(1);

    return returnData;
  }

  if(commandToken == 1) {
    byte address = atoi(strtok(NULL, "/"));

    EEPROM.write(ARDUINO_MEM_ADDR, address);

    itoa(address, itoa_buffer, 10);

    counter = 0;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    }
    if(itoa_buffer[1] != NULL) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    }
    if(itoa_buffer[2] != NULL) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    }
    returnData[counter] = '}';
    delay(1);    

    return returnData;
  }

  if(commandToken == 2) {
    resetMacros();

    counter = 0;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = ':';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = '}';
    counter++;    
    delay(1);    

    return returnData;
  }	

#if DIGITALPINSENABLED == 1
  if(commandToken == 3) {
    char *charpin = strtok(NULL, "/");
    char *charmode = strtok(NULL, "/");
    byte pin = atoi(charpin);
    byte mode = atoi(charmode);

    pinModeSet(pin, mode);

    counter = 0;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(charpin[0] != NULL) {
      returnData[counter] = charpin[0];
      counter++;
    }
    if(charpin[1] != NULL) {
      returnData[counter] = charpin[1];
      counter++;
    }    
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = ':';
    counter++;
    returnData[counter] = *charmode;
    counter++;
    returnData[counter] = '}';
    counter++;
    returnData[counter] = '\0';
    counter++;
    delay(1);    

    return returnData;
  }
#endif

#if DIGITALPINSENABLED == 1
  if(commandToken == 4) {
    char *charpin = strtok(NULL, "/");
    char *charpinstatus = strtok(NULL, "/");
    byte pin = atoi(charpin);
    byte pinstatus = atoi(charpinstatus);

    setPinStatus(pin, pinstatus);

    counter = 0;
    check = false;	

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(charpin[0] != NULL) {
      returnData[counter] = charpin[0];
      counter++;
    }
    if(charpin[1] != NULL) {
      returnData[counter] = charpin[1];
      counter++;
    }    
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'U';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(charpinstatus[0] != NULL) {
      returnData[counter] = charpinstatus[0];
      counter++;
    }
    if(charpinstatus[1] != NULL) {
      returnData[counter] = charpinstatus[1];
      counter++;
    } 
    else {
      check = true;
    }
    if(charpinstatus[2] != NULL && check != true) {
      returnData[counter] = charpinstatus[2];
      counter++;
    }    
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
#endif

#if MACROSENABLED == 1
  if(commandToken == 5) {
    char *macro_name = strtok(NULL, "/");
    int arg1 = atoi(strtok(NULL, "/"));
    int arg2 = atoi(strtok(NULL, "/"));
    int arg3 = atoi(strtok(NULL, "/"));
    int arg4 = atoi(strtok(NULL, "/"));
    int arg5 = atoi(strtok(NULL, "/"));
    int arg6 = atoi(strtok(NULL, "/"));
    int arg7 = atoi(strtok(NULL, "/"));
    int arg8 = atoi(strtok(NULL, "/"));
    int arg9 = atoi(strtok(NULL, "/"));
    int arg10 = atoi(strtok(NULL, "/"));     

    macroSet(macro_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);

    counter = 0;

    returnData[counter] = '"';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = '"';
    counter++;     
    delay(1);

    return returnData;
  }
#endif

#if PCF8574AENABLED == 1 
#ifdef TwoWire_h
  if(commandToken == 6) {
    byte device = atoi(strtok(NULL, "/"));
    byte pin = atoi(strtok(NULL, "/"));
    byte action = atoi(strtok(NULL, "/"));

    //void controlPCF8574AA(byte device, byte pin_status, byte pin) {

    controlPCF8574A(device, action, pin);

    counter = 0;

    returnData[counter] = '"';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'F';
    counter++;
    returnData[counter] = '8';
    counter++;
    returnData[counter] = '5';
    counter++;
    returnData[counter] = '7';
    counter++;     
    returnData[counter] = '4';
    counter++;          
    returnData[counter] = '"';
    counter++;          
    delay(1);

    return returnData;
  }   
#endif
#endif

#if DIGITALPINSENABLED == 1
  //TODO - not returning an address and won't return correct pin for values over 9
  if(commandToken == 7){
    char *charwatch_pin = strtok(NULL, "/");
    byte watch_pin = atoi(charwatch_pin);

    itoa(digitalRead(watch_pin), itoa_buffer, 10);

    counter = 0;

    returnData[counter] = '{';   
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = ':';
    counter++;
    returnData[counter] = *charwatch_pin;
    counter++;
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'V';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'U';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = ':';
    counter++;
    returnData[counter] = itoa_buffer[0]; 
    counter++;
    returnData[counter] = '}';   
    counter++;
    delay(1);   

    return returnData;
  }
#endif		


#if ANALOGENABLED == 1
  if(commandToken == 8){
    char *charwatch_pin = strtok(NULL, "/");
    int watch_pin = atoi(charwatch_pin);

    itoa(analogRead(watch_pin), itoa_buffer, 10);

    int counter = 0;
    boolean check = false;

    returnData[counter] = '{';   
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = ':';
    counter++;
    returnData[counter] = *charwatch_pin;
    counter++;
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'V';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'U';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0]; 
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check = true;
    }
    if(itoa_buffer[1] != NULL && check != true) {
      returnData[counter] = itoa_buffer[1]; 
      counter++;
    } 
    else {
      check = true;
    }
    if(itoa_buffer[2] != NULL && check != true) {
      returnData[counter] = itoa_buffer[2]; 
      counter++;
    } 
    else {
      check = true;
    }
    if(itoa_buffer[3] != NULL && check != true) {
      returnData[counter] = itoa_buffer[3]; 
      counter++;
    } 
    else {
      check = true;
    }
    returnData[counter] = '}'; 
    counter++;
    delay(1);   

    return returnData;
  }
#endif	

#ifdef DS1307_h
  if(commandToken == 9){	
    char *charhour = strtok(NULL, "/");
    char *charminute = strtok(NULL, "/");
    char *charsecond = strtok(NULL, "/");
    char *charday = strtok(NULL, "/");
    char *chardayofweek = strtok(NULL, "/");
    char *charmonth = strtok(NULL, "/");
    char *charyear = strtok(NULL, "/");
    byte hour = atoi(charhour);
    byte minute = atoi(charminute);
    byte second = atoi(charsecond);
    byte day = atoi(charday);
    byte dayofweek = atoi(chardayofweek);
    byte month = atoi(charmonth);
    byte year = atoi(charyear);

    DS1307SetTime(hour, minute, second, day, dayofweek, month, year);

    int counter = 0;
    boolean check_hour = false;
    boolean check_minute = false;
    boolean check_second = false;
    boolean check_day = false;
    boolean check_dow = false;
    boolean check_month = false;
    boolean check_year = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'H';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(charhour[0] != NULL) {
      returnData[counter] = charhour[0];   
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_hour = true;
    }
    if(charhour[1] != NULL && check_hour != true) {
      returnData[counter] = charhour[1];
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(charminute[0] != NULL) {
      returnData[counter] = charminute[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_minute = true;
    }
    if(charminute[1] != NULL && check_minute != true) {
      returnData[counter] = charminute[1];
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(charsecond[0] != NULL) {
      returnData[counter] = charsecond[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_second = true;
    }
    if(charsecond[1] != NULL && check_second != true) {
      returnData[counter] = charsecond[1];
      counter++;
    }
    returnData[counter] = ',';   
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(charday[0] != NULL) {
      returnData[counter] = charday[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_day = true;
    }
    if(charday[1] != NULL && check_day != true) {
      returnData[counter] = charday[1];
      counter++;
    }
    returnData[counter] = ',';   
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(chardayofweek[0] != NULL) {
      returnData[counter] = chardayofweek[0];
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'H';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(charmonth[0] != NULL) {
      returnData[counter] = charmonth[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_month = true; 
    }
    if(charmonth[1] != NULL && check_month != true) {
      returnData[counter] = charmonth[1];
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = ':';   
    counter++;
    if(charyear[0] != NULL) {
      returnData[counter] = charyear[0];   
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_year = true;
    }
    if(charyear[1] != NULL && check_year != true) {
      returnData[counter] = charyear[1];   
      counter++;
    }
    returnData[counter] = '}'; 
    counter++;
    delay(1);   

    return returnData;
  }	
#endif

#ifdef DS1307_h
  if(commandToken == 10){
    char hour[3];
    char minute[3];
    char second[3];
    char day[3];
    char dayofweek[2];
    char month[3];
    char year[5];

    itoa(RTC.get(DS1307_HR,true), hour, 10);
    itoa(RTC.get(DS1307_MIN,false), minute, 10);
    itoa(RTC.get(DS1307_SEC,false), second, 10);
    itoa(RTC.get(DS1307_DATE,false), day, 10);
    itoa(RTC.get(DS1307_DOW,false), dayofweek, 10);
    itoa(RTC.get(DS1307_MTH,false), month, 10);
    itoa(RTC.get(DS1307_YR,false), year, 10);

    int counter = 0;
    boolean check_hour = false;
    boolean check_minute = false;
    boolean check_second = false;
    boolean check_day = false;
    boolean check_dow = false;
    boolean check_month = false;
    boolean check_year = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'H';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(hour[0] != NULL) {
      returnData[counter] = hour[0];   
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_hour = true;
    }
    if(hour[1] != NULL && check_hour != true) {
      returnData[counter] = hour[1];
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(minute[0] != NULL) {
      returnData[counter] = minute[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_minute = true;
    }
    if(minute[1] != NULL && check_minute != true) {
      returnData[counter] = minute[1];
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(second[0] != NULL) {
      returnData[counter] = second[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_second = true;
    }
    if(second[1] != NULL && check_second != true) {
      returnData[counter] = second[1];
      counter++;
    }
    returnData[counter] = ',';   
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(day[0] != NULL) {
      returnData[counter] = day[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_day = true;
    }
    if(day[1] != NULL && check_day != true) {
      returnData[counter] = day[1];
      counter++;
    }
    returnData[counter] = ',';   
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(dayofweek[0] != NULL) {
      returnData[counter] = dayofweek[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'H';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(month[0] != NULL) {
      returnData[counter] = month[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_month = true; 
    }
    if(month[1] != NULL && check_month != true) {
      returnData[counter] = month[1];
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = ':';   
    counter++;
    if(year[0] != NULL) {
      returnData[counter] = year[0];   
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_year = true;
    }
    if(year[1] != NULL && check_year != true) {
      returnData[counter] = year[1];   
      counter++;
    } 
    else {
      check_year = true;
    }
    if(year[2] != NULL && check_year != true) {
      returnData[counter] = year[2];   
      counter++;
    } 
    else {
      check_year = true;
    }
    if(year[3] != NULL && check_year != true) {
      returnData[counter] = year[3];   
      counter++;
    } 
    else {
      check_year = true;
    }       
    returnData[counter] = '}'; 
    counter++;
    delay(1);   
    
    return returnData;
  }
#endif

#ifdef TLC5940_H
  if(commandToken == 11) {
    int tlc_pin_num = atoi(strtok(NULL, "/"));
    int tlc_action = atoi(strtok(NULL, "/"));
    
    #if DEBUG == 1
      Serial.print("tlc_pin_num ");
      Serial.println(tlc_pin_num);
      Serial.print("tlc_action ");
      Serial.println(tlc_action);
    #endif
   
    controlTLC5940(tlc_pin_num, tlc_action); 
    
    counter = 0;

    returnData[counter] = '{';
    counter++;    
    returnData[counter] = 'S';
    counter++;    
    returnData[counter] = 'E';
    counter++;    
    returnData[counter] = 'T';
    counter++;    
    returnData[counter] = 'T';
    counter++;    
    returnData[counter] = 'L';
    counter++;    
    returnData[counter] = 'C';
    counter++;    
    returnData[counter] = '5';
    counter++;    
    returnData[counter] = '9';
    counter++;    
    returnData[counter] = '4';
    counter++;    
    returnData[counter] = '0';
    counter++;    
    returnData[counter] = '}';
    counter++;       
    delay(1); 

    return returnData;    
  }
#endif

#ifdef I2CLCD_h
#ifdef DS1307_h
  if(commandToken == 12){
    char *chardisplay_time_as_value = strtok(NULL, "/");
    int display_time_as_value = atoi(chardisplay_time_as_value);

    EEPROM.write(display_time_as, display_time_as_value);

    lcd.clear();

    char type[5];
    if(display_time_as_value == 0) {
      type[0] = '2';
      type[1] = '4';
      type[2] = 'H';
    } 
    else if(display_time_as_value == 1){
      type[0] = '1';
      type[1] = '2';
      type[2] = 'H';
    }

    int counter = 0;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'P';
    counter++;       
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = ':';
    counter++;
    returnData[counter] = '"';
    counter++;       
    returnData[counter] = type[0];
    counter++;
    returnData[counter] = type[1];
    counter++;
    returnData[counter] = type[2];
    counter++;
    returnData[counter] = '"';
    counter++;       
    returnData[counter] = '}';
    counter++;
    delay(1);    

    return returnData;       
  }
#endif
#endif

#ifdef OneWire_h
  if(commandToken == 13){		
    int devices_found = discoverOneWireDevices();

    itoa(devices_found, itoa_buffer, 10);

    int counter = 0;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'V';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = ':';
    counter++;
    returnData[counter] = itoa_buffer[0];
    counter++;
    returnData[counter] = '}';
    counter++;

    return returnData;
  }
#endif

#ifdef OneWire_h
  if(commandToken == 14){	
    int mem_addresses = (onewire_addresses_memend - onewire_addresses_memstart) / onewire_addresses_bytes;  
    int counter = 0;
    int device_num = 0;
    returnData[counter] = '[';
    counter++;
    for(int i = 0; i < mem_addresses; i++){
      returnData[counter] = '{';
      counter++;
      returnData[counter] = 'D';
      counter++;         
      returnData[counter] = 'E';
      counter++;         
      returnData[counter] = 'V';
      counter++;
      returnData[counter] = 'I';
      counter++;
      returnData[counter] = 'C';
      counter++;
      returnData[counter] = 'E';
      counter++;
      returnData[counter] = ':';
      counter++;
      returnData[counter] = device_num + '0';
      counter++;
      returnData[counter] = ',';
      counter++;
      returnData[counter] = 'V';
      counter++;
      returnData[counter] = 'A';
      counter++;
      returnData[counter] = 'L';
      counter++;
      returnData[counter] = 'U';         
      counter++;
      returnData[counter] = 'E';         
      counter++;
      returnData[counter] = ':';                  
      counter++;
      returnData[counter] = '"';
      counter++;         
      for(int j = 0; j < 8; j++){
        char itoa_buffer[5];
        itoa(EEPROM.read((onewire_addresses_memstart + (i * onewire_addresses_bytes) + j)), itoa_buffer, 10);
        returnData[counter] = itoa_buffer[0];
        if(itoa_buffer[1] != NULL) {
          counter++;
          returnData[counter] = itoa_buffer[1]; 
        }
        counter++;
        returnData[counter] = '-';
        counter++;
      }
      counter--;
      returnData[counter] = '"';
      counter++;         
      returnData[counter] = '}';
      counter++;
      returnData[counter] = ',';
      counter++;
      returnData[counter] = '\r\n';
      counter++;
      device_num++;
    }
    returnData[counter] = ']';
    counter++;
    delay(1);

    return returnData;
  }
#endif 

#if OneWire_h
#if DS18B20ENABLED == 1
  if(commandToken == 15){
    char *chartemp_sensor_num = strtok(NULL, "/");
    int temp_sensor_num = atoi(chartemp_sensor_num);
    int temp_reading = getDS18B20Temp(temp_sensor_num);

    itoa(temp_reading, itoa_buffer, 10);

    int counter = 0;
    boolean check_temp_sensor_num = false;
    boolean check_itoa_buffer = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(chartemp_sensor_num[0] != NULL) {
      returnData[counter] = chartemp_sensor_num[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_temp_sensor_num = true;
    }
    if(chartemp_sensor_num[1] != NULL && check_temp_sensor_num != true) {
      returnData[counter] = chartemp_sensor_num[1];
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'V';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'L';     
    counter++;
    returnData[counter] = 'U';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(itoa_buffer[0] != NULL) {
      returnData[counter] = itoa_buffer[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_itoa_buffer = true;
    }
    if(itoa_buffer[1] != NULL && check_itoa_buffer != true) {
      returnData[counter] = itoa_buffer[1];
      counter++;
    } 
    else {
      check_itoa_buffer = true;
    }
    if(itoa_buffer[2] != NULL && check_itoa_buffer != true) {
      returnData[counter] = itoa_buffer[2];
      counter++;
    } 
    else {
      check_itoa_buffer = true;
    }
    if(itoa_buffer[3] != NULL && check_itoa_buffer != true) {
      returnData[counter] = itoa_buffer[3];
      counter++;
    } 
    else {
      check_itoa_buffer = true;
    }
    if(itoa_buffer[4] != NULL && check_itoa_buffer != true) {
      returnData[counter] = itoa_buffer[4];
      counter++;
    } 
    else {
      check_itoa_buffer = true;
    }
    returnData[counter] = '}';
    counter++;

    Serial.println(returnData);
    return returnData;		
  }
#endif 
#endif

#ifdef I2CLCD_h
#ifdef DS1307_h
  if(commandToken == 16){
    char *chari2clcd_time_display_value = strtok(NULL, "/");
    EEPROM.write(i2clcd_time_display, atoi(chari2clcd_time_display_value));

    lcd.clear();

    int counter = 0;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(chari2clcd_time_display_value[0] != NULL) {
      returnData[counter] = chari2clcd_time_display_value[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;		
  }
#endif
#endif

#ifdef I2CLCD_h
#ifdef DS1307_h
  if(commandToken == 17){
    char *char_row = strtok(NULL, "/");
    char *char_col = strtok(NULL, "/");
    byte row = atoi(char_row);
    byte col = atoi(char_col);

    EEPROM.write(i2clcd_cursor_col, col);
    EEPROM.write(i2clcd_cursor_row, row);

    lcd.clear();

    int counter = 0;
    boolean check_char_row = false;
    boolean check_char_col = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_row[0] != NULL) {
      returnData[counter] = char_row[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_col[0] != NULL) {
      returnData[counter] = char_col[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_col = true;
    }
    if(char_col[1] != NULL && check_char_col != true) {
      returnData[counter] = char_col[1];
      counter++;
    } 
    else {
      check_char_col = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1); 

    return returnData;
  }
#endif
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h
  if(commandToken == 18){
    char *char_row = strtok(NULL, "/");
    char *char_col = strtok(NULL, "/");
    byte row = atoi(char_row);
    byte col = atoi(char_col);	

    EEPROM.write(ds18b20_temp1_col, col);
    EEPROM.write(ds18b20_temp1_row, row);

    lcd.clear();

    int counter = 0;
    boolean check_char_row = false;
    boolean check_char_col = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_row[0] != NULL) {
      returnData[counter] = char_row[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_row = true;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_col[0] != NULL) {
      returnData[counter] = char_col[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_col = true;
    }
    if(char_col[1] != NULL && check_char_col != true) {
      returnData[counter] = char_col[1];
      counter++;
    } 
    else {
      check_char_col = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
#endif
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h   	
  if(commandToken == 19){
    char *char_sensor_num = strtok(NULL, "/");
    byte sensor_num = atoi(char_sensor_num);

    EEPROM.write(ds18b20_temp1_sensor, sensor_num);

    lcd.clear();

    int counter = 0;
    boolean check_char_sensor_num = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';       
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'U';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_sensor_num != NULL) {
      returnData[counter] = char_sensor_num[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_sensor_num = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
#endif     
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h   
  if(commandToken == 20){
    char *char_display_temp = strtok(NULL, "/");
    bool display_temp = atoi(char_display_temp);

    EEPROM.write(display_ds18b20_temp1, display_temp);

    lcd.clear();

    int counter = 0;
    boolean check_char_display_temp = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = '1';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_display_temp[0] != NULL) {
      returnData[counter] = char_display_temp[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_display_temp = true;
    }
    returnData[counter] = '}';       
    counter++;
    delay(1);

    return returnData;
  }
#endif
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h   
  if(commandToken == 21){
    char *char_row = strtok(NULL, "/");
    char *char_col = strtok(NULL, "/");
    byte row = atoi(char_row);
    byte col = atoi(char_col);

    EEPROM.write(ds18b20_temp2_col, col);
    EEPROM.write(ds18b20_temp2_row, row);

    lcd.clear();

    int counter = 0;
    boolean check_char_row = false;
    boolean check_char_col = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_row[0] != NULL) {
      returnData[counter] = char_row[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_row = true;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_col[0] != NULL) {
      returnData[counter] = char_col[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_col = true;
    }
    if(char_col[1] != NULL && check_char_col != true) {
      returnData[counter] = char_col[1];
      counter++;
    } 
    else {
      check_char_col = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
#endif     
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h   	
  if(commandToken == 22){
    char *char_sensor_num = strtok(NULL, "/");
    byte sensor_num = atoi(char_sensor_num);

    EEPROM.write(ds18b20_temp2_sensor, sensor_num);

    lcd.clear();

    int counter = 0;
    boolean check_char_sensor_num = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';       
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'U';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_sensor_num != NULL) {
      returnData[counter] = char_sensor_num[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_sensor_num = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
#endif     
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h   
  if(commandToken == 23){
    char *char_display_temp = strtok(NULL, "/");
    bool display_temp = atoi(char_display_temp);

    EEPROM.write(display_ds18b20_temp2, display_temp);

    lcd.clear();

    int counter = 0;
    boolean check_char_display_temp = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = '1';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_display_temp[0] != NULL) {
      returnData[counter] = char_display_temp[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_display_temp = true;
    }
    returnData[counter] = '}';       
    counter++;
    delay(1);

    return returnData;
  }
#endif
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h   
  if(commandToken == 24){
    char *char_row = strtok(NULL, "/");
    char *char_col = strtok(NULL, "/");
    byte row = atoi(char_row);
    byte col = atoi(char_col);

    EEPROM.write(ds18b20_temp3_col, col);
    EEPROM.write(ds18b20_temp3_row, row);

    lcd.clear();

    int counter = 0;
    boolean check_char_row = false;
    boolean check_char_col = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_row[0] != NULL) {
      returnData[counter] = char_row[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_row = true;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_col[0] != NULL) {
      returnData[counter] = char_col[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_col = true;
    }
    if(char_col[1] != NULL && check_char_col != true) {
      returnData[counter] = char_col[1];
      counter++;
    } 
    else {
      check_char_col = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
#endif
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h   	
  if(commandToken == 25){
    char *char_sensor_num = strtok(NULL, "/");
    byte sensor_num = atoi(char_sensor_num);

    EEPROM.write(ds18b20_temp3_sensor, sensor_num);

    lcd.clear();

    int counter = 0;
    boolean check_char_sensor_num = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';       
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'U';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_sensor_num != NULL) {
      returnData[counter] = char_sensor_num[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_sensor_num = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
#endif
#endif

#if DS18B20ENABLED == 1
#ifdef I2CLCD_h   
  if(commandToken == 26){
    char *char_display_temp = strtok(NULL, "/");
    bool display_temp = atoi(char_display_temp);

    EEPROM.write(display_ds18b20_temp3, display_temp);

    lcd.clear();

    int counter = 0;
    boolean check_char_display_temp = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = '1';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_display_temp[0] != NULL) {
      returnData[counter] = char_display_temp[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_display_temp = true;
    }
    returnData[counter] = '}';       
    counter++;
    delay(1);

    return returnData;
  }
#endif
#endif

#if PHENABLED == 1
  if(commandToken == 28){
    char *char_watch_pin = strtok(NULL, "/");
    int watch_pin = atoi(char_watch_pin);

    float pHReturned = getPHValue(watch_pin) * 100;
    char pHChar[5];

    itoa (pHReturned, pHChar, 10);

    return pHChar;
  }
#endif

#if PHENABLED == 1
#ifdef I2CLCD_h
  if(commandToken == 29){
    char *char_row = strtok(NULL, "/");
    char *char_col = strtok(NULL, "/");
    int row = atoi(char_row);
    int col = atoi(char_col);

    EEPROM.write(display_ph_col, col);
    EEPROM.write(display_ph_row, row);

    lcd.clear();

    int counter = 0;
    boolean check_char_col = false;
    boolean check_char_row = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_row[0] != NULL) {
      returnData[counter] = char_row[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_row = true;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_col[0] != NULL) {
      returnData[counter] = char_col[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_col = true;
    }
    if(char_col[1] != NULL && check_char_col != true) {
      returnData[counter] = char_col[1];
      counter++;
    } 
    else {
      check_char_col = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
  #endif
#endif

#if PHENABLED == 1
   #ifdef I2CLCD_h
  if(commandToken == 30){
    char *char_display_ph = strtok(NULL, "/");
    int display_ph_value = atoi(char_display_ph);

    EEPROM.write(display_ph, display_ph_value);

    lcd.clear();

    int counter = 0;
    boolean check_char_display_ph = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'H';
    counter++;
    returnData[counter] = '1';
    counter++;       
    returnData[counter] = ':';
    counter++;
    if(char_display_ph[0] != NULL) {
      returnData[counter] = char_display_ph[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_display_ph = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
  #endif
#endif

#if MACROSENABLED == 1
  if(commandToken == 31) {
    char *char_macro_number = strtok(NULL, "/");
    int macro_number = atoi(char_macro_number);

    int max_macros = ((macros_memend - macros_memstart) / macros_bytes) - 1;

    if(macro_number > max_macros) {
      int counter = 0;

      returnData[counter] = '"';
      counter++;      
      returnData[counter] = 'O';
      counter++;
      returnData[counter] = 'U';
      counter++;
      returnData[counter] = 'T';
      counter++;
      returnData[counter] = 'O';
      counter++;
      returnData[counter] = 'F';
      counter++;
      returnData[counter] = 'B';
      counter++;
      returnData[counter] = 'O';
      counter++;
      returnData[counter] = 'U';
      counter++;
      returnData[counter] = 'N';
      counter++;
      returnData[counter] = 'D';
      counter++;
      returnData[counter] = 'S';
      counter++;
      returnData[counter] = '"';
      counter++;      
    } 
    else {
      int counter = 0;
      boolean check_macro_number = false;
      int address_start = macros_memstart + (macros_bytes * macro_number);
      returnData[counter] = '"';
      counter++;
      if(char_macro_number[0] != NULL) {
        returnData[counter] = char_macro_number[0];
        counter++;
      } 
      else {
        returnData[counter] = 48;
        counter++;
        check_macro_number = true;
      }
      if(char_macro_number[1] != NULL && check_macro_number != true) {
        returnData[counter] = char_macro_number[1];
        counter++;
      } 
      else {
        check_macro_number = true;
      }
      returnData[counter] = ',';
      counter++;
      for(int i=0; i<macros_bytes; i++) {
        int address = address_start + i;
        int eeprom_value = EEPROM.read(address);

        if(i < 15) {
          char itoa_buffer[5];
          itoa(eeprom_value, itoa_buffer, 10);
          boolean check_itoa_buffer = false;

          if(itoa_buffer[0] != NULL) {
            returnData[counter] = itoa_buffer[0];
            counter++;
          } 
          else {
            returnData[counter] = 48;
            counter++;
            check_itoa_buffer = true;
          }
          if(itoa_buffer[1] != NULL && check_itoa_buffer != true) {
            returnData[counter] = itoa_buffer[1];
            counter++;  
          } 
          else {
            check_itoa_buffer = true;
          }
          if(itoa_buffer[2] != NULL && check_itoa_buffer != true) {
            returnData[counter] = itoa_buffer[2];
            counter++;  
          } 
          else {
            check_itoa_buffer = true;
          }
          returnData[counter] = ',';
          counter++;          
        } 
        else {
          if(eeprom_value != 0) {
            returnData[counter] = eeprom_value;
            counter++;
          }
        }
      }
      returnData[counter] = '"';
      counter++;      
    }  
    delay(1);

    return returnData;
  }
#endif

#if MACROSENABLED == 1
  if(commandToken == 32) {
    char *char_macro_number = strtok(NULL, "/");
    int macro_number = atoi(char_macro_number);

    int address = macros_memstart + (macros_bytes * macro_number);

    EEPROM.write(address, 0);

    int counter = 0;

    returnData[counter] = '"';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'M';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = '"';
    counter++;    
    delay(1);

    return returnData;
  }  
#endif

#if PHENABLED == 1
#ifdef I2CLCD_h
  if(commandToken == 33){
    char *char_row = strtok(NULL, "/");
    char *char_col = strtok(NULL, "/");
    int row = atoi(char_row);
    int col = atoi(char_col);

    EEPROM.write(display_ORP_col, col);
    EEPROM.write(display_ORP_row, row);

    lcd.clear();

    int counter = 0;
    boolean check_char_col = false;
    boolean check_char_row = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'R';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_row[0] != NULL) {
      returnData[counter] = char_row[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_row = true;
    }
    returnData[counter] = ',';
    counter++;
    returnData[counter] = 'C';
    counter++;
    returnData[counter] = 'O';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = ':';
    counter++;
    if(char_col[0] != NULL) {
      returnData[counter] = char_col[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_col = true;
    }
    if(char_col[1] != NULL && check_char_col != true) {
      returnData[counter] = char_col[1];
      counter++;
    } 
    else {
      check_char_col = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
  #endif
#endif

#if PHENABLED == 1
   #ifdef I2CLCD_h
  if(commandToken == 34){
    char *char_display_ph = strtok(NULL, "/");
    int display_ORP_value = atoi(char_display_ph);

    EEPROM.write(display_ORP, display_ORP_value);

    lcd.clear();

    int counter = 0;
    boolean check_char_display_ph = false;

    returnData[counter] = '{';
    counter++;
    returnData[counter] = 'D';
    counter++;
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'L';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'Y';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = 'H';
    counter++;
    returnData[counter] = '1';
    counter++;       
    returnData[counter] = ':';
    counter++;
    if(char_display_ph[0] != NULL) {
      returnData[counter] = char_display_ph[0];
      counter++;
    } 
    else {
      returnData[counter] = 48;
      counter++;
      check_char_display_ph = true;
    }
    returnData[counter] = '}';
    counter++;
    delay(1);

    return returnData;
  }
  #endif
#endif

//SET ARDUINO IP ADDRESS TO EEPROM
#ifdef ethernet_h
  if(commandToken == 35) {
    byte ip_first = atoi(strtok(NULL, "/"));
    byte ip_second = atoi(strtok(NULL, "/"));
    byte ip_third = atoi(strtok(NULL, "/"));
    byte ip_fourth = atoi(strtok(NULL, "/"));
 
    EEPROM.write(IP_FIRST_OCTET, ip_first);
    EEPROM.write(IP_SECOND_OCTET, ip_second);
    EEPROM.write(IP_THIRD_OCTET, ip_third);
    EEPROM.write(IP_FOURTH_OCTET, ip_fourth);    
    
    returnData[counter] = '{';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = ':';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'I';
    counter++;
    returnData[counter] = 'P';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = '}';
    counter++;    
    delay(1);

    return returnData;
  }    
#endif

//SET ARDUINO SUBNET ADDRESS TO EEPROM
#ifdef ethernet_h
  if(commandToken == 36) {
    byte ip_first = atoi(strtok(NULL, "/"));
    byte ip_second = atoi(strtok(NULL, "/"));
    byte ip_third = atoi(strtok(NULL, "/"));
    byte ip_fourth = atoi(strtok(NULL, "/"));
 
    EEPROM.write(SUBNET_FIRST_OCTET, ip_first);
    EEPROM.write(SUBNET_SECOND_OCTET, ip_second);
    EEPROM.write(SUBNET_THIRD_OCTET, ip_third);
    EEPROM.write(SUBNET_FOURTH_OCTET, ip_fourth);    
    
    returnData[counter] = '{';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = ':';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'U';
    counter++;
    returnData[counter] = 'B';
    counter++;
    returnData[counter] = 'N';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;    
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = '}';
    counter++;    
    delay(1);

    return returnData;
  }    
#endif

//SET ARDUINO GATEWAY ADDRESS TO EEPROM
#ifdef ethernet_h
  if(commandToken == 37) {
    byte ip_first = atoi(strtok(NULL, "/"));
    byte ip_second = atoi(strtok(NULL, "/"));
    byte ip_third = atoi(strtok(NULL, "/"));
    byte ip_fourth = atoi(strtok(NULL, "/"));
 
    EEPROM.write(GATEWAY_FIRST_OCTET, ip_first);
    EEPROM.write(GATEWAY_SECOND_OCTET, ip_second);
    EEPROM.write(GATEWAY_THIRD_OCTET, ip_third);
    EEPROM.write(GATEWAY_FOURTH_OCTET, ip_fourth);    
    
    returnData[counter] = '{';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'S';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = ':';
    counter++;
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = 'G';
    counter++;
    returnData[counter] = 'A';
    counter++;
    returnData[counter] = 'T';
    counter++;
    returnData[counter] = 'E';
    counter++;
    returnData[counter] = 'W';
    counter++;
    returnData[counter] = 'A';
    counter++;    
    returnData[counter] = 'Y';
    counter++;        
    returnData[counter] = '"';
    counter++;    
    returnData[counter] = '}';
    counter++;    
    delay(1);

    return returnData;
  }    
#endif

  memset(commandString, 0, sizeof commandString);
}



