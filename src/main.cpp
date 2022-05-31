#include <Arduino.h>

// kode untuk gps
#include <TinyGPSPlus.h>
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

// kode untuk i2c lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// kode untuk buzzer
#include "pitch.h"

void setup()
{
  Serial.begin(9600);
  Serial2.begin(GPSBaud);
  // mulai lcd
  lcd.init(); // initialize the lcd
  lcd.backlight();

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
  Serial.print(F("Testing TinyGPSPlus library v. "));
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();

  lcd.setCursor(0, 0);
  lcd.print("hai dunia");
  lcd.setCursor(0, 1);
  lcd.print("apa kabarnya?");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("gps starting...");
  delay(2000);
}

void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    lcd.setCursor(0, 0);
    lcd.print(gps.location.lat(), 6);
    lcd.print("          ");
    lcd.setCursor(0, 1);
    lcd.print(gps.location.lng(), 6);
    lcd.print("          ");
    if (gps.location.lat() < -5.361300 || gps.location.lat() > -5.361100)
      tone(8, NOTE_G3);
    else
      noTone(8);
  }
  else
  {
    Serial.print(F("INVALID"));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("gps invalid");
    lcd.print("     ");
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

void loop()
{

  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true)
      ;
  }
}
