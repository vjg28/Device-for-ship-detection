#include<Wire.h>
#include <SPI.h>
#include "RF24.h"

RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F000LL;
uint8_t k,RPD;
int i=0,d=0,j=0,total=0,fin,o=5;
char msg[1];
bool l;
rf24_pa_dbm_e power,level;

void setup()
{
Serial.begin(9600);
radio.begin();
radio.setChannel(0x0A);
radio.openReadingPipe(1,pipe);
radio.startListening();
pinMode(o,OUTPUT);
}

void loop()
{
  radio.setChannel(0x0A);
  if (radio.available())
  {
    bool done = false;
    while (!done)
    {
      done = radio.read(msg, 1);
      Serial.println(msg[0]);                         // sends x 
      level=RF24_PA_LOW;
      radio.setPALevel(level) ;
      power= radio.getPALevel();
      l=radio.testRPD();
      if(l)
      {
            //fin=1;
            Serial.println("Small ship nearby: careful");
            digitalWrite(o,HIGH);
      }
      else 
      {
             //fin=0;
             Serial.println("0");
             digitalWrite(o,LOW);
      }
    }
  }
}  
