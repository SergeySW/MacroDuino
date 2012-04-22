void serialInterface() {
  char serialCommandString[BUFFERSIZE];
  char *serialReturnData;
  byte inByte;
  byte index = 0;
  
  while(Serial.available() > 0) {	
    inByte = Serial.read();
    if(inByte != '\n') {
      serialCommandString[index] = inByte;
      #if DEBUG == 1
        Serial.print("Received: ");
        Serial.println(serialCommandString[index]);
      #endif
      delay(2);
      index++;
      serialCommandString[index] = '\0';
    } else { 
      serialReturnData = control(serialCommandString);

      Serial.print("{ Value : ");        
      Serial.print(serialReturnData);
      Serial.println(" }");
      break;
    }
  }
  return;
}


