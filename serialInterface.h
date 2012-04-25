void serialInterface() {
  char serialCommandString[BUFFERSIZE];
  char *serialReturnData;
  byte inByte;
  byte index = 0;
  
  while(Serial.available() > 0) {	
    inByte = Serial.read();
    serialCommandString[index] = inByte;
    #if DEBUG == 1
      Serial.print("Received: ");
      Serial.println(serialCommandString[index]);
    #endif
    delay(2);
    index++;
    serialCommandString[index] = '\0';
  }

  serialReturnData = control(serialCommandString);
     
  Serial.println(serialReturnData);

  return;
}


