#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

RF24 radio(10, 8); // CE, CSN
const byte address[6] = "00002";

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int buzzer = 4;
int i=0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(1);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_DISABLED);
  radio.startListening();
  radio.powerUp();

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);

  pinMode(buzzer,OUTPUT);
}

struct MessageData
{   float temp;
    unsigned char button;
};


void loop() {
  MessageData pmr;
  lcd.clear();
  if (radio.available()) {
    radio.read(&pmr, sizeof(pmr));
    Serial.println(pmr.temp);
    Serial.println(pmr.button);
  
    lcd.setCursor(0,0);
    lcd.print(String("Temp(C) =")+String(pmr.temp));  
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Disconnected");
    Serial.println("Disconnected");
  }

  if (pmr.temp>=30 and i==0) {
    digitalWrite(buzzer,HIGH);
    delay(700);
    digitalWrite(buzzer,LOW);
    delay(100);
    
    lcd.setCursor(0,1);
    lcd.print("Pindahkan wadah");
    
    if (pmr.button==0){
      digitalWrite(buzzer,LOW);
      i = 1;
    }
  }
  else if (pmr.temp<30) {
    digitalWrite(buzzer,LOW);
    i = 0;
  }
  
  delay(500);
}
