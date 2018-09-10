#include <SPI.h>
#include "RF24.h"

//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8
RF24 radio(8,7);

const uint64_t pipe = 0xE8E8F0F0E1LL;
uint8_t k,RPD;

int msg[1];
bool l;
rf24_pa_dbm_e level;
void setup()

{

Serial.begin(9600);
radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();

}

void loop()
{
if (radio.available())
  {
  bool done = false;
  while (!done)
   {
      level=RF24_PA_MAX;
      radio.setPALevel(level) ;
      done = radio.read(msg, 1);
      Serial.println(msg[0]);
    }
  }
}

