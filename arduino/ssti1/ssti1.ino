#include <SPI.h>
#include "RF24.h"

char msg[1];                               //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8 //declaring variable array msg
RF24 radio(8,7);                          //radio is a struct variable of data type RF24
const uint64_t pipe = 0xE8E8F0F0E1LL;             //(shipdistance address) channel A  address are 40 bit . LL means long long
const uint64_t pipe1 = 0xE8E8F0F0A1LL;             //(Distress address) channel B : to set channel use radio.setChannel(0-127
rf24_pa_dbm_e level,power;                       //input variable (in this case potentiometer pin) need to change that
rf24_pa_dbm_e RF24_PA_MED;
char val;
int an=4,number,j=0;
//int resetPin=9;
int l=0;

void setup(void)
{
//digitalWrite(resetPin, HIGH);
//delay(200);  
//pinMode(resetPin, OUTPUT);
Serial.begin(9600);
radio.begin();
radio.setChannel(0x0A);
radio.openWritingPipe(pipe);
pinMode(5,INPUT);
pinMode(4,INPUT);
pinMode(2,OUTPUT);
pinMode(6,OUTPUT);
}

void loop(void)
{ 
  digitalWrite(6,LOW);
  digitalWrite(2,LOW);
  l=0;
  j=0;
  level=RF24_PA_MAX;
  radio.setPALevel(level) ;
  number = analogRead(an);
  Serial.println(number);
  if(number>=550 && digitalRead(5)==LOW)
  {
    digitalWrite(6,HIGH);
    radio.setChannel(0x0A);
    val = '8';
    msg[0] = val;  
    power= radio.getPALevel();
    Serial.println(msg[0]);
    radio.write(msg, 1);
  }

//distress code
  while(digitalRead(5)==HIGH)
  {
    digitalWrite(2,HIGH);
    digitalWrite(6,LOW);
    while(j<=20)
    {
      msg[0] = '#'; 
      power= radio.getPALevel();
      Serial.println(msg[0]);
      radio.write(msg, 1);
      j++; 
    }
    
    radio.setChannel(0x78);       //distress channel
    if(l==0)
    {
      delay(1000);
      l++;
    }
    radio.openWritingPipe(pipe1);   //pipe1=distress pipe
    val = '5';                        //arbitary
    msg[0] = val; 
    level=RF24_PA_MAX;
    radio.setPALevel(level) ;
    power= radio.getPALevel();
    Serial.println(msg[0]);
    radio.write(msg, 1);
  }

}



