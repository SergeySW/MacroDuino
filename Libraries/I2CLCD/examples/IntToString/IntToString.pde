#include <Wire.h>
#include <I2CLCD.h>
 
//initialize the library. I2CLCD lcd = I2CLCD(address, columns, rows);
I2CLCD lcd = I2CLCD(0x12, 20, 4);
 
void setup(){
lcd.init();
lcd.backlight(1);
}
 
void loop(){
  
for(int x =0; x <=100; x++){
  char val[12];
  itoa(x, val, 10);
  lcd.write(val);
  delay(20);
}
lcd.clear();

}
