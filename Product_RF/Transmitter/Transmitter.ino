/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT11

RF24 radio(7, 8); // CE, CSN
DHT dht(DHTPIN, DHTTYPE);

const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  dht.begin();
}
void loop() {
  float t = dht.readTemperature();
  Serial.println(t);
  
  //const char text[] = "Hello World";
  radio.write(&t, sizeof(t));
  delay(1000);
}
