#include <SPI.h>
#include <Wire.h>
#include "RF24.h"

char msg[1];                               //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8 //declaring variable array msg

RF24 radio(8,7);                          //radio is a struct variable of data type RF24

const uint64_t pipe = 0xE8E8F0F000LL;     //uint8_t, uint16_t, uint32_t, uint64_t == unsigned char, unsigned short, unsigned int and unsigned long long respectively.

rf24_pa_dbm_e level,power;
//int potpin = 0;                           //input variable (in this case potentiometer pin) need to change that
rf24_pa_dbm_e RF24_PA_MED;
int val,i=0;
char data[7]={'2','3','e',' ','4','5','n'};
char incomingByte;
void setup(void)

{
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(pipe);
Wire.begin(9); 
  // Attach a function to trigger when something is received.
Wire.onReceive(receiveEvent);
}

void receiveEvent (int bytes) {
  incomingByte = Wire.read();    // read one character from the I2C
}

void loop(void)
{

level=RF24_PA_MAX;              //maximum power signal that can be emmited
radio.setPALevel(level);        //set power level==value(level)      
power= radio.getPALevel();      //saving value of power of signal in variable power
  if(incomingByte==1)           //bit coming from i2c communication Pins a4-a5-gnd
  {
    if(i<7)
    {
      msg[0] = data[i];
      Serial.print(msg[0]);
      i++;
    }
    else
    {
      i=0;
      msg[0]='*';
      Serial.print(msg[0]);
      Serial.print(" Power=");
      Serial.println(power);
      delay(500);
    }
    radio.write(msg, 1);
  }
}
   


