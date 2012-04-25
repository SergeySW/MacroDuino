#define ARDUINO_MEM_ADDR 0

#define BUFFERSIZE 80
#define RETURNDATABUFFERSIZE 200


//PH_GAIN = 4000mv / (59.2 * 7) where 4000mv is the max output of the BNC sensor shield circuit
#define PH_GAIN 9.6525


#if PCF8574AENABLED == 1
const byte pcf8574a_addresses[] = {
    B0111000,
    B0111001,
    B0111010,
    B0111011,
    B0111100,
    B0111101,
    B0111110,
    B0111111,    
  };

byte pcf8574a_states[] = {
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  };  
#endif


const byte digital_pin_mem_start = 2;
const byte digital_pin_mem_end = 13;

const byte display_time_as = 16;
const byte i2clcd_time_display = 17;
const byte i2clcd_cursor_col = 18;
const byte i2clcd_cursor_row = 19;
const byte num_ds18b20_devices = 20;
const byte display_ds18b20_temp1 = 21;
const byte ds18b20_temp1_col = 22;
const byte ds18b20_temp1_row = 23;
const byte display_ds18b20_temp2 = 24;
const byte ds18b20_temp2_col = 25;
const byte ds18b20_temp2_row = 26;
const byte display_ds18b20_temp3 = 27;
const byte ds18b20_temp3_col = 28;
const byte ds18b20_temp3_row = 29;
const byte ds18b20_temp1_sensor = 30;
const byte ds18b20_temp2_sensor = 31;
const byte ds18b20_temp3_sensor = 32;
const byte display_ph = 33;
const byte display_ph_row = 34;
const byte display_ph_col = 35;

const byte display_ORP = 36;
const byte display_ORP_row = 37;
const byte display_ORP_col = 38;

const int onewire_addresses_memstart = 70;
const int onewire_addresses_memend = 110;
const byte onewire_addresses_bytes = 8;

extern const int macros_memstart = 111;
const int macros_memend = 511;
const byte macros_bytes = 20;

#if SENDTOPACHUBEENABLED == 1
  unsigned long pachube_last_connect;
  unsigned int pachube_successes = 0;
  unsigned int pachube_failures = 0;  
  boolean pachube_request_pause = false;
  boolean pachube_ready_to_update = true;
  unsigned int pachube_interval;  
  // to configure what data you send to pachube look in pachubeFunctions.h
#endif



uint8_t degree_symbol = 0xDF;
