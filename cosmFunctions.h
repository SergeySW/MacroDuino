#ifdef SENDTOCOSMENABLED
void sendCosmData(){
  
  CosmClient client = CosmClient(COSM_APIKEY);
  
  /*
  for each datastream you want to update just add a line
  client.updateFeed(COSM_FEED_ID, dataStreamName, sensorReading);
  
  available functions:
  analogRead(pin#);
  digitalRead(pin#);
  (double)(getDS18B20Temp(device_num)/100)    note that in MacroDuino ds18b20 devices get assigned by device number. 0-4 are valid values. remember to run command discover 1wire devices
  (double)getPHValue(pin#)
  (double)getORPValue(pin#)
  */
  
  client.connectViaGateway(mac, ip, gateway, gateway, subnet);  
  client.updateFeed(COSM_FEED_ID, "TEMP", ((double)getDS18B20Temp(0)/100.00));

  client.connectViaGateway(mac, ip, gateway, gateway, subnet);  
  client.updateFeed(COSM_FEED_ID, "APIN0", (double)analogRead(2));
  
}
#endif

