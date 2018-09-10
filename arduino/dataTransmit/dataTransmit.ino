#include <SPI.h>
#include "RF24.h"

int msg[1];                               //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8 //declaring variable array msg

RF24 radio(8,7);                          //radio is a struct variable of data type RF24
const uint64_t pipe = 0xE8E8F0F0E1LL;     //uint8_t, uint16_t, uint32_t, uint64_t == unsigned char, unsigned short, unsigned int and unsigned long long respectively.
rf24_pa_dbm_e level;                        
int val;

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  //radio.setChannel(0x0A);
  radio.openWritingPipe(pipe);
}

void loop(void)

{
  level=RF24_PA_MAX;
  radio.setPALevel(level) ;
  
  val = 3;
  msg[0] = val; 
  Serial.println(msg[0]);
  radio.write(msg, 1);


}
