#include <SPI.h>

#include "RF24.h"

int msg[1];                               //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8 //declaring variable array msg

RF24 radio(8,7);                          //radio is a struct variable of data type RF24

const uint64_t pipe = 0xE8E8F0F0E1LL;     //uint8_t, uint16_t, uint32_t, uint64_t == unsigned char, unsigned short, unsigned int and unsigned long long respectively.

rf24_pa_dbm_e level,power;
//int potpin = 0;                           //input variable (in this case potentiometer pin) need to change that
rf24_pa_dbm_e RF24_PA_MED;
int val;

void setup(void)

{
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(pipe);
}

void loop(void)

{

//val = analogRead(potpin);

val = 5;
msg[0] = val;
Serial.println("a");
power= radio.getPALevel();

/*for(int i=0;;i++)
{
  if(i%40<=10)
  {
      level=RF24_PA_MIN;
      radio.setPALevel(level) ;
      power= radio.getPALevel();
      Serial.println(power);
      //Serial.print(" ");
      //Serial.print(msg[0]);
      //Serial.print(" ");
      //Serial.print(i);
      radio.write(msg, 1);
  }
  if(i%40<20 & i%40>=10)
  {
      level=RF24_PA_MIN;
      radio.setPALevel(level) ;
      power= radio.getPALevel();
      Serial.println(power);
      Serial.print(" ");
      Serial.print(msg[0]);
      Serial.print(" ");
      Serial.println(i);
      radio.write(msg, 1);
  }
  if(i%40<30 & i%40>=20)
  {
      level=RF24_PA_LOW;
      radio.setPALevel(level) ;
      power= radio.getPALevel();
      Serial.println(power);
      Serial.print(" ");
      Serial.print(msg[0]);
      Serial.print(" ");
      Serial.println(i);
      radio.write(msg, 1);
  }
  if(i%40<40 & i%40>=30)
  {
      */
      level=RF24_PA_MAX;
      radio.setPALevel(level) ;
      power= radio.getPALevel();
      Serial.print(power);
      Serial.print(" ");
      Serial.println(msg[0]);
      radio.write(msg, 1);
  //}
}


