// kode ini saya tujukan untuk arduino mega
// koneksi arduino mega ke internet menggunakan esp01
// alasan saya menggunakan mega karena saya ingin banyak konektornya
// dan alasan menggunakan esp01 karena murah dan bisa digunakan untuk wifi

// masukkkan semua liblarry ke arduino mega
#include <Arduino.h>
// #include <Wire.h>
#include <LiquidCrystal_I2C.h>

// setting untuk motor
const int EnableA = 2;
const int IN1 = 3;
const int IN2 = 4;
const int IN3 = 5;
const int IN4 = 6;
const int EnableB = 7;

// setting untuk rgb led
const int ledR = 6;
const int ledG = 5;
const int ledB = 3;

// pin sensor cahaya
const int sensorSampah = 13;

// nilai counter untuk main2
int nilai_counter = 0;

// setting awal untuk lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

// buat variabel bool untuk parsing data.
bool parsing = false;
String sData, data[10];
int isReady = 0, sensorReady = 0, warnaR = 0, warnaG = 0, warnaB = 0;
String emailUser;
int NilaiSensorSampah = 0;
int kirimNilaiSensorSampah = 0;

void setup()
{
  // start komunikasi dengan esp01 pada serial 01-nya mega
  Serial.begin(9600);
  // pinmode untuk motor
  for (int i = 2; i <= 7; i++)
  {
    pinMode(i, OUTPUT);
  }
  // pinmode untuk led rgb
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  // pinmode untuk sensor sampah
  pinMode(sensorSampah, INPUT);

  // mulai lcd
  lcd.init();
  lcd.backlight();
}

void loop()
{
  // baca nilai sensor cahaya setiap pertama kali
  NilaiSensorSampah = digitalRead(sensorSampah);
  // kode untuk mendapatkan nilai dari esp01.
  // dan tampilkan hasilnya di layar lcd
  while (Serial.available())
  {
    // buat variabel nilaiinput, dan masukkan nilai serial.readString kesana
    // String nilaiInput = Serial.readString();
    // print/tampilkan nilai input tadi di serial monitor
    char inChar = Serial.read();
    sData += inChar;
    if (inChar == '$')
      parsing = true;
    if (parsing)
    {
      int q = 0;
      for (int i = 0; i < sData.length(); i++)
      {
        if (sData[i] == '#')
        {
          q++;
          data[q] = "";
        }
        else
          data[q] += sData[i];
      }
      // setelah semua data didapatkan, kita akan print datanya ke serial satu persatu
      isReady = data[1].toInt();
      sensorReady = data[2].toInt();
      emailUser = data[3].c_str();
      warnaR = data[4].toInt();
      warnaG = data[5].toInt();
      warnaB = data[6].toInt();
      parsing = false;
      sData = "";
    }
  }

  // // tampilan pada layar lcd dan perintah pada setiap kondisinya
  if (isReady == 1 && sensorReady == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(emailUser);
    lcd.print("               ");
    lcd.setCursor(0, 1);
    lcd.print("brhsl login");
    lcd.print(NilaiSensorSampah);
    lcd.print(kirimNilaiSensorSampah);
    lcd.print("               ");
    analogWrite(ledR, warnaR);
    analogWrite(ledG, warnaG);
    analogWrite(ledB, warnaB);
    kirimNilaiSensorSampah = 0;
  }
  else if (isReady == 1 && sensorReady == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("sampah terscan");
    lcd.print("               ");
    lcd.setCursor(0, 1);
    lcd.print("mskn sampah");
    lcd.print(NilaiSensorSampah);
    lcd.print(kirimNilaiSensorSampah);
    lcd.print("               ");
    analogWrite(ledR, 225 - warnaR);
    analogWrite(ledG, 225 - warnaG);
    analogWrite(ledB, 225 - warnaB);
    if (NilaiSensorSampah == 0)
      kirimNilaiSensorSampah = 1;
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("welove 001");
    lcd.print("               ");
    lcd.setCursor(0, 1);
    lcd.print("be a savior");
    lcd.print(NilaiSensorSampah);
    lcd.print(kirimNilaiSensorSampah);
    lcd.print("               ");
    lcd.print(sensorReady);
    analogWrite(ledR, 0);
    analogWrite(ledG, 0);
    analogWrite(ledB, 0);
    kirimNilaiSensorSampah = 0;
  }

  // kirim nilai sensor sampah ke esp01
  Serial.print("#");
  Serial.print(kirimNilaiSensorSampah);
  Serial.println("#$");
}
