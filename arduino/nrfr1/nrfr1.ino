//#include <Servo.h>
#include<Wire.h>
#include <SPI.h>

#include "RF24.h"
//#define RPD 0x09;
//Servo myservo;

//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8

RF24 radio(8,7);

const uint64_t pipe = 0xE8E8F0F0E1LL;
uint8_t k,RPD;

int msg[1],i=0,d=0,j=0,total=0,fin;
bool l;

rf24_pa_dbm_e power,level;

void setup()

{

Serial.begin(9600);
Wire.begin();
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
      //RPD=0x09;
      done = radio.read(msg, 1);
      //Serial.println(msg[0]);
      //Serial.print(" ");
      Wire.beginTransmission(9); // transmit to device #9
                                 // sends x 
      level=RF24_PA_LOW;
      radio.setPALevel(level) ;
      power= radio.getPALevel();
      //Serial.print(power);
      l=radio.testRPD();
      //Serial.print(" ");
      //Serial.print(i);
      //Serial.print(" ");
      //Serial.println(l);
      //Wire.write(l);
      //Wire.endTransmission(); 
      //Serial.println(" ");
      //delay(100);
      d=d+l;
      i++;
      if(i==50)
      {
        //Serial.print(total);
        //Serial.println(d);
        if(d>=40)
        {
          total=total+1;
        }
        if(j==3)
        {
            j=0;
            if(total>=2)
            {
                fin=1;//Serial.println(" ");
                Serial.println("1");
                Wire.write(fin);
                Wire.endTransmission();
                //Serial.println("*  ");
            }
            else
            {
                fin=0;
                //Serial.println(" ");
                Serial.println("0");
                Wire.write(fin);
                Wire.endTransmission();
                //Serial.println("*  ");
            }
            total=0;
        }
        i=0;
        d=0;
        j++;
      }
      else 
      {
          //Serial.println("0");
      }

  }

 }
}

