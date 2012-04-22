#ifdef client_h
void ethernetWiznetW5100Interface() {
  Server server(80);
  char ethernetCommandString[BUFFERSIZE];
  int index = 0;
  char *ethernetReturnData;

  // listen for incoming clients
  Client client = server.available();
  if (client) {
    //  reset input buffer
    index = 0;
   Serial.println(client);
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //  fill url the buffer
        if(c != '\n' && c != '\r'){
          ethernetCommandString[index] = c;
          index++;

          //  if we run out of buffer, overwrite the end
          if(index >= BUFFERSIZE)
            index = BUFFERSIZE -1;

          continue;
        }         

        char *commandString;
        char *jsonpCallback;
        int num_spaces = 0;
        int counter = 0;

        commandString = strtok(ethernetCommandString, " ");
        commandString = strtok(NULL, "?");
        jsonpCallback = strtok(NULL, "=");     
        jsonpCallback = strtok(NULL, " ");

        String jsonpCallbackString = String(jsonpCallback);
        

        #if DEBUGETHERNETQUERYSTRING == 1
                Serial.println(ethernetCommandString);
                Serial.println(commandString);
                Serial.println(jsonpCallbackString);
        #endif        
        
        delay(1);
          client.println("HTTP/1.1 200 OK");
          //client.println("Content-type: text/json");
          //client.println("Content-type: application/json");
          client.println("Content-Type: text/javascript");          
          client.println();

        ethernetReturnData = control(commandString);
        
        #if DEBUGETHERNETRETURNDATA == 1
          Serial.print(jsonpCallbackString);
          Serial.print("({VALUE:");
          Serial.print(ethernetReturnData);
          Serial.println("})");          
        #endif

        client.print(jsonpCallbackString);
        client.print("({VALUE:");
        client.print(ethernetReturnData);
        client.println("})");
       
        break;

      }
    }

    // close the connection:
    client.stop();
  }
}
#endif
