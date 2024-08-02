#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS A0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  sensors.begin();

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
}

void loop() { 
  Serial.print("Mengambil suhu...");
  sensors.requestTemperatures(); 
  Serial.println();

  float tempC = sensors.getTempCByIndex(0);

  if(tempC != DEVICE_DISCONNECTED_C) {
    Serial.print("SUHU: ");
    Serial.println(tempC);

    lcd.setCursor(6, 0); 
    lcd.print(tempC);
    lcd.print(" C  "); 

    lcd.setCursor(0, 1); 
    lcd.print("                "); // Clear the second line
    if (tempC < 35.5) {
      Serial.println();
      lcd.setCursor(4, 1); 
      lcd.print("      ");
    } 
    else if (tempC >= 35.5 && tempC <= 37.5) {
      Serial.println("Suhu: Normal");
      lcd.setCursor(5, 1); 
      lcd.print("Normal");
    } 
    else {
      Serial.println("Suhu: Sakit");
      lcd.setCursor(5, 1); 
      lcd.print("Sakit");
    }
  } else {
    Serial.println("Error: Tidak dapat membaca data suhu");

    lcd.setCursor(0, 1);
    lcd.print("Error membaca");
  }

  delay(1000); // 1000 milliseconds = 1 second
}