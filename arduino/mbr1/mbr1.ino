#include<Wire.h>
#include <SPI.h>
#include "RF24.h"

RF24 radio(8,4);
const uint64_t pipe = 0xE8E8F0F0E1LL;             //(shipdistance address) channel A  address are 40 bit . LL means long long
const uint64_t pipe1 = 0xE8E8F0F0A1LL;             //(Distress address) channel B : to set channel use radio.setChannel(0-127)
uint8_t k,RPD;
int msg[1],i;
char fin;
bool l;
int d=0;
rf24_pa_dbm_e power,level;
//int resetPin = 4;

void setup()
{
  //digitalWrite(resetPin, HIGH);
  //delay(400);
//  pinMode(resetPin, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  radio.begin();
  radio.setChannel(0x0A);
  radio.openReadingPipe(1,pipe);  //opens up the channel from which it will read
  //can open more than one reading pipes Just the last byte of their address must be unique
  //pipe 0 is used by writing.So,don't use that.
  radio.openReadingPipe(2,pipe1) ;
  radio.startListening();
}


int distress(void)
{
  radio.setChannel(0x78);
  delay(1000);
  if (radio.available())
  {
    bool done = false;
    while (!done)
    {
      done = radio.read(msg, 1);   //gives true if signal payload is recieved sucessfully
      Wire.beginTransmission(9); // transmit to device                            // sends x 
      level=RF24_PA_MAX;
      radio.setPALevel(level) ;
      power= radio.getPALevel();
      l=radio.testRPD();
      if(l)
      {
            fin='n';
            Serial.println("Please HELP : near moored buoy1 *address*");
            Wire.write(fin);
            Wire.endTransmission();
      }
      else 
      {
             fin='f';
             Serial.println("Please Help: far from moored buoy1 *address*");
             Wire.write(fin);
             Wire.endTransmission();
      }
    }
  }
  Serial.println("Tu chutiya hai"); 
  return 1;
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0






void loop()

{
  k=0;d=0;
  i++;
  radio.setChannel(0x0A);
  if (radio.available())
  {
    bool done = false;
    while (!done)
    {
      done = radio.read(msg, 1);   //gives true if signal payload is recieved sucessfully
      //Serial.println(msg[0]);
      if(msg[0]=='#')              //distress signal bit
      {
         while(k<=10)
         {
            d=distress();
            k=k+d;
         }
         //digitalWrite(resetPin, LOW);
         Serial.println("resetting");
         resetFunc();  //call reset
      }
      
      Wire.beginTransmission(9); // transmit to device #9
      level=RF24_PA_MAX;
      radio.setPALevel(level) ;
      power= radio.getPALevel();
      l=radio.testRPD();
      if(l)
      {
            fin='a';//Serial.println(" ");
            Serial.println("1");
            Wire.write(fin);
            Wire.endTransmission();
      }
      else 
      {
             fin='b';
             //Serial.println(" ");
             Serial.println("0");
             Wire.write(fin);
             Wire.endTransmission();
             //Serial.println("*  ");
      }
    }
  } 
} 


  //if((i%1000)==0)
  //{
    //weather code
  //}


