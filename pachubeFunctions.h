#if SENDTOPACHUBEENABLED == 1
void sendPachubeData(){
  char pachube_data[70];

  boolean found_status_200 = false;
  boolean found_session_id = false;
  boolean found_CSV = false;
  char *found;

  int content_length;

  byte pachubeServer[] = { 173, 203, 98, 29 };            // pachube.com

  Client localClient(pachubeServer, 80);
  int pointer = 0;


  if (millis() < pachube_last_connect) pachube_last_connect = millis();

  if (pachube_request_pause){
    if ((millis() - pachube_last_connect) > pachube_interval){
      pachube_ready_to_update = true;
      pachube_request_pause = false;
      found_status_200 = false;
      found_session_id = false;
      found_CSV = false;
    }
  }

  if (pachube_ready_to_update){
    #if DEBUG == 1
      Serial.println("Connecting...");
    #endif
    if (localClient.connect()) {

      /* you can send pachube 4 values for now:
      
      digitalRead(pin): requires %d and digitalRead(pin)
      
      analogRead(pin): requires %d and analogRead(pin)
      
      getPHValue(analog_pin): requires
      
      float ph1 = getPHValue(2);
      int int_ph1 = (ph1 - (int)ph1) * 100;
      in sprintf: sprintf(pachube_data, "%0d.%d", (int)ph1, int_ph1) basically replace %d with %0d.%d and add TWO arguments (int)ph1 and int_ph1
            

      getDS18B20Temp(temp_sensor_num): requires
      
      float temp1 = (float)getDS18B20Temp(0) / 100;
      int int_temp1 = (temp1 - (int)temp1) * 100;
      in sprintf: sprintf(pactube_data, "%0d.%d,", (int)temp1, int_temp1) basicall replace %d with %0d.%d and add TWO arguments (int)temp1 and int_temp1
      */
       /* 
        the example below shows how each of the four should be setup. I add in successes and failures at the end
        because it can show problems
       */
       
      float temp1 = (float)getDS18B20Temp(0) / 100;
      int int_temp1 = (temp1 - (int)temp1) * 100;
      
      float ph1 = getPHValue(2);
      int int_ph1 = (ph1 - (int)ph1) * 100;

      //sprintf(pachube_data, "%0d.%d, %0d.%d, %d, %d, %d", (int)ph1, int_ph1, (int)temp1, int_temp1, analogRead(0), pachube_successes++, pachube_failures);
      
      sprintf(pachube_data, "%0d.%d, %d, %d, %0d.%d, %d", (int)temp1, int_temp1, analogRead(2), digitalRead(5), (int)ph1, int_ph1, pachube_successes++);
      
      content_length = strlen(pachube_data);

      #if DEBUG == 1
        Serial.print("pachube data: ");
        Serial.println(pachube_data);
      #endif
      
      localClient.print("GET /api/");
      localClient.print(PACHUBE_REMOTE_FEED_ID);
      localClient.print(".csv HTTP/1.1\nHost: pachube.com\nX-PachubeApiKey: ");
      localClient.print(PACHUBE_API_KEY);
      localClient.print("\nUser-Agent: Arduino (Pachube In Out v1.1)");
      localClient.println("\n");

      localClient.print("PUT /api/");
      localClient.print(PACHUBE_SHARE_FEED_ID);
      localClient.print(".csv HTTP/1.1\nHost: pachube.com\nX-PachubeApiKey: ");
      localClient.print(PACHUBE_API_KEY);

      localClient.print("\nUser-Agent: Arduino (Pachube In Out v1.1)");
      localClient.print("\nContent-Type: text/csv\nContent-Length: ");
      localClient.print(content_length);
      localClient.print("\nConnection: close\n\n");
      localClient.print(pachube_data);



      localClient.print("\n");

      pachube_ready_to_update = false;
      pachube_request_pause = true;
      pachube_interval = PACHUBE_UPDATE_INTERVAL;
      pachube_last_connect = millis();
    } 
    else {
      pachube_failures++;
      #if DEBUG == 1
        Serial.print("connection failed!");
        Serial.println(pachube_failures);
      #endif
      found_status_200 = false;
      found_session_id = false;
      found_CSV = false;
      pachube_ready_to_update = false;
      pachube_request_pause = true;
      pachube_last_connect = millis();
      pachube_interval = PACHUBE_RESET_INTERVAL;

      #if DEBUG == 1
        Serial.println("reset ethernet");
      #endif
      Ethernet.begin(mac, ip);
      Client remoteClient(255);
      delay(500);
      pachube_interval = PACHUBE_UPDATE_INTERVAL;
      #if DEBUG == 1
        Serial.println("setup complete");
      #endif
    }
  } 
}
#endif

