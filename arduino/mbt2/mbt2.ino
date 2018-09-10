#include <SPI.h>
#include <Wire.h>
#include "RF24.h"

char msg[1];                               //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8 //declaring variable array msg
RF24 radio(8,7);                          //radio is a struct variable of data type RF24
const uint64_t pipe = 0xE8E8F0F000LL;     //uint8_t, uint16_t, uint32_t, uint64_t == unsigned char, unsigned short, unsigned int and unsigned long long respectively.
rf24_pa_dbm_e level,power;                       
rf24_pa_dbm_e RF24_PA_MED;
int val,i=0;
char data[8]={'S','S',' ','n',' ','M','B','1'};            //syntax for small ship signal
char data1[8]={'S','O','S','*','S','0','S','*'};          //syntax for sos near MB1
char data2[8]={'s','o','s','#','#','s','o','s'};          //syntax for sos far MB1
char data3[8]={'S','S',' ','f',' ','M','B','1'};
char incomingByte;

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(0x0A);
  radio.openWritingPipe(pipe);   //can only open one writing pipe at an instant
  Wire.begin(9);                 // Attach a function to trigger when something is received.
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
  
  if(incomingByte=='a')           //bit coming from i2c communication Pins a4-a5-gnd
  {
    radio.setChannel(0x0A);
    if(i<8)
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
    }
    radio.write(msg, 1);
  }
  
  if(incomingByte=='n')           //bit coming from i2c communication Pins a4-a5-gnd
  {
    radio.setChannel(0x78);
    if(i<8)
    {
      msg[0] = data1[i];
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
    }
    radio.write(msg, 1);
  }

  if(incomingByte=='f')           //bit coming from i2c communication Pins a4-a5-gnd
  {
    radio.setChannel(0x78);
    if(i<8)
    {
      msg[0] = data2[i];
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
    }
    radio.write(msg, 1);
  }
  incomingByte='0';
}

