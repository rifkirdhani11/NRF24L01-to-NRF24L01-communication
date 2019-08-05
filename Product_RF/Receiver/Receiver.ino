/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
}
void loop() {
  if (radio.available()) {
    char text[32] = "";
    float temp;
    radio.read(&temp, sizeof(temp));
    Serial.println(temp);
  
    lcd.setCursor(0,0);
    lcd.print(String("Temp(C) =")+String(temp));  
  }
}
