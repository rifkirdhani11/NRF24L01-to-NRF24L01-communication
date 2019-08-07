#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 
#define DHTTYPE DHT11

RF24 radio(10, 8); // CE, CSN
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

const byte address[6] = "00002";
const int button = 6;

int butState;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  dht.begin();
  
  radio.begin();
  radio.setChannel(1);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_DISABLED);
  radio.stopListening();
  radio.powerUp();

  pinMode(button, INPUT_PULLUP);
}

struct MessageData
{   float temp;
    unsigned char button;
};

void loop() {
  MessageData pm;
  pm.temp = dht.readTemperature();
  pm.button = (unsigned char) digitalRead(button);

  Serial.println(pm.temp);
  Serial.println(pm.button);
    
  lcd.setCursor(0,0);
  lcd.print(String("Temp(C) =")+String(pm.temp));

  if (pm.temp>=30) {
    lcd.setCursor(0,1);
    lcd.print("Tekan 3 detik");
 
    if (pm.button==0){
      lcd.clear();
    }
  }
    
  radio.write(&pm, sizeof(pm));
  delay(100);
  lcd.clear();
}
