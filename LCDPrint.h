#ifdef I2CLCD_h
void printToLCD() {
  I2CLCD lcd = I2CLCD(0x12, 20, 4);
  lcd.backlight(1);
  int temp;
  int ph;
  int orp;
  int hour = RTC.get(DS1307_HR,true);
  int minute = RTC.get(DS1307_MIN,false);
  int second = RTC.get(DS1307_SEC,false);
  int day = RTC.get(DS1307_DATE,false);
  int dayofweek = RTC.get(DS1307_DOW,false);
  int month = RTC.get(DS1307_MTH,false);
  int year = RTC.get(DS1307_YR,false);

  #if DS1307_h && I2CLCDENABLED == 1
    if(EEPROM.read(i2clcd_time_display) == 1) {    
      if(EEPROM.read(display_time_as) == 0) {
        lcd.setCursor(EEPROM.read(i2clcd_cursor_col), EEPROM.read(i2clcd_cursor_row));
        if(hour < 10) {
          lcd.write(" ");
          lcd.write(hour);
        } else {         
          lcd.write(hour);          
        }
        lcd.write(":");
        if(minute < 10){
          lcd.write("0");
          lcd.write(minute);
        } else {
          lcd.write(minute);
        }
        lcd.write(":");
        if(second < 10){
          lcd.write("0");
          lcd.write(second);
        } else {
          lcd.write(second);
        }
      } else if(EEPROM.read(display_time_as) == 1) {
        lcd.setCursor(EEPROM.read(i2clcd_cursor_col), EEPROM.read(i2clcd_cursor_row) - 2);
        if(hour < 10){
          lcd.write(" ");
          lcd.write(hour);
        } else if (hour >= 10 && hour <= 12) {
          lcd.write(hour);
        } else if(hour > 12) {
          hour = hour - 12;
          if(hour < 10) {
            lcd.write(" ");
          }
          lcd.write(hour);
        }
        lcd.write(":");
        if(minute < 10) {
          lcd.write("0");
          lcd.write(minute);
        } else {
          lcd.write(minute);
        }
        lcd.write(":");
        if(second < 10) {
          lcd.write("0");
          lcd.write(second);
        } else {
          lcd.write(second);
        }
        if(hour < 12) {
          lcd.write("AM");
        } else if(hour >= 12 && hour <= 23) {
          lcd.write("PM");
        }
      }
    }
  #endif
	
  #ifdef DS18B20ENABLED && I2CLCD_h
    if(EEPROM.read(display_ds18b20_temp1) == 1) {
      lcd.setCursor(EEPROM.read(ds18b20_temp1_col), EEPROM.read(ds18b20_temp1_row));
      temp = getDS18B20Temp(EEPROM.read(ds18b20_temp1_sensor));
      lcd.write("T1=");
      lcd.write((temp / 100));
      lcd.write(".");
      if((temp % 100) < 10) {
        lcd.write("0");
      }    
      lcd.write((temp % 100));
      lcd.write(degree_symbol);
      #if CELSIUS == 1 
        lcd.write("C");
      #else
        lcd.write("F");
      #endif                      
    }
    
    if(EEPROM.read(display_ds18b20_temp2) == 1) {
      lcd.setCursor(EEPROM.read(ds18b20_temp2_col), EEPROM.read(ds18b20_temp2_row));
      temp = getDS18B20Temp(EEPROM.read(ds18b20_temp2_sensor));
      lcd.write("T2=");    
      lcd.write((temp / 100));
      lcd.write(".");
      if((temp % 100) < 10) {
        lcd.write("0");
      }    
      lcd.write((temp % 100));
      lcd.write(degree_symbol);
      #if CELSIUS == 1 
        lcd.write("C");
      #else
        lcd.write("F");
      #endif  
    }  

    if(EEPROM.read(display_ds18b20_temp3) == 1) {
      lcd.setCursor(EEPROM.read(ds18b20_temp3_col), EEPROM.read(ds18b20_temp3_row));
      temp = getDS18B20Temp(EEPROM.read(ds18b20_temp3_sensor));
      lcd.write("T3=");    
      lcd.write((temp / 100));
      lcd.write(".");
      if((temp % 100) < 10){
        lcd.write("0");
      }
      lcd.write((temp % 100)); 
      lcd.write(degree_symbol);
      #if CELSIUS == 1 
        lcd.write("C");
      #else
        lcd.write("F");
      #endif   
    }
  #endif

  #ifdef PHENABLED && I2CLCD_h
    if(EEPROM.read(display_ph) == 1) {
      lcd.setCursor(EEPROM.read(display_ph_col), EEPROM.read(display_ph_row));
      lcd.write("PH:");
      ph = getPHValue(PH_PIN) * 100;
      lcd.write(ph / 100);
      lcd.write(".");
      lcd.write(ph % 100);
    }
  #endif
  
    #if ORPENABLED && I2CLCDENABLED == 1
    if(EEPROM.read(display_ORP) == 1) {
      lcd.setCursor(EEPROM.read(display_ORP_col), EEPROM.read(display_ORP_row));
      lcd.write("ORP:");
      lcd.write(getORPValue(ORP_PIN));
      lcd.write("mV");
    }
  #endif
}
#endif
