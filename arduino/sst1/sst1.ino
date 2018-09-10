#include <SPI.h>
#include "RF24.h"
#include<Wire.h>
#define SLAVE_ADDRESS 0x04

int msg[1];                               //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8 //declaring variable array msg
int number = 0;
int state = 0;
RF24 radio(8,7);                          //radio is a struct variable of data type RF24
const uint64_t pipe = 0xE8E8F0F0E1LL;             //(shipdistance address) channel A  address are 40 bit . LL means long long
const uint64_t pipe1 = 0xE8E8F0F0A1LL;             //(Distress address) channel B : to set channel use radio.setChannel(0-127
rf24_pa_dbm_e level,power;                       //input variable (in this case potentiometer pin) need to change that
rf24_pa_dbm_e RF24_PA_MED;
int val;

void setup(void)
{
Serial.begin(115200);
radio.begin();
radio.setChannel(0x0A);
radio.openWritingPipe(pipe);
Wire.begin(SLAVE_ADDRESS);
Wire.onReceive(receiveData);
Serial.println("tatti");
//Wire.onRequest(sendData);
pinMode(9,INPUT);
}

void loop(void)
{
delay(1);

if(0)
{
  radio.setChannel(0x78);
  radio.openWritingPipe(pipe1);
  val = 5;
  msg[0] = val; 
  level=RF24_PA_MAX;
  radio.setPALevel(level) ;
  power= radio.getPALevel();
  Serial.println(msg[0]);
  radio.write(msg, 1);
}

}

void receiveData(int byteCount){

while(Wire.available()) 
{
  number = Wire.read();
  //Serial.print("data received: ");
  Serial.println(number);
  if(number==1)
  {
    //Serial.println("d");
    radio.setChannel(0x0A);
    //Serial.println("b");
    val = 8;
    msg[0] = val;  
    //Serial.println("a");
    level=RF24_PA_MAX;
    radio.setPALevel(level) ;
    //Serial.println("f");
    power= radio.getPALevel();
    //Serial.println(msg[0]);
    radio.write(msg, 1);
    //Serial.println("e");
  }
}
}

void sendData(){
Wire.write(number);
Serial.println("g");
}
