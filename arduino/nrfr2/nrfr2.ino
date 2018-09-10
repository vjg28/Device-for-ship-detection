#include<Servo.h>
#include <SPI.h>
#include "RF24.h"

//#define RPD 0x09;
//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8

RF24 radio(8,7);
Servo myservo;
const uint64_t pipe = 0xE8E8F0F0E1LL;
int msg[1],i=1,j=0,approx_radius=25,distanceFromBuoy=30;
bool l;
int no_of_readings=0;
int positionDistance=0;
int angleValue;
int k=1;
rf24_pa_dbm_e power,level;

void setup()

{
myservo.attach(9);
Serial.begin(9600);

radio.begin();

radio.openReadingPipe(1,pipe);

radio.startListening();

}

void loop()

{
    Serial.println(i);
    int repeatloop=0;
    myservo.write(i);
    i=i+k;
    if(i==180||i==0)
    {
      k=-k;
      //repeatloop++;
    }
    
    if (radio.available())
    { 
      no_of_readings++;
      angleValue=i;
      bool done = false;
      while (!done & j>1000)
      {
        j++;
        done = radio.read(msg, 1);
        //power= radio.getPALevel();
        l=radio.testRPD();
        Serial.print(msg[0]);
        Serial.print("**");
        Serial.print(l);
      }
      Serial.println("");
      Serial.print("**angleValue=");
      Serial.print(angleValue);
      Serial.print("*PositionDistance=");
      positionDistance= approx_radius+distanceFromBuoy;
      Serial.println(positionDistance);
    }
    
}
    
    
    
/*    //i=i+k;
    //d=d+l;
    //i++;
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
      //Serial.println(" ");
      Serial.println("1");
      //Serial.println("*  ");
    }
    else
    {
      //Serial.println(" ");
      Serial.println("0");
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
*/

