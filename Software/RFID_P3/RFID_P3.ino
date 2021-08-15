#include <EEPROM.h>     // We are going to read and write PICC's UIDs from/to EEPROM
#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices
#include <Adafruit_NeoPixel.h>
#include <MsTimer2.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "TM1637.h"

String UID = "F8U6V3";
#define sos 4
#define Buzz 6
#define wipeB 7
#define DIO 8
#define RST_PIN 9
#define SS_PIN 10
#define fin A0
#define fout A1
#define rout A2
#define rin A3
#define SDA A4
#define SCL A5
#define DIP1 A6
#define DIP2 A7
#define Audio 3
#define address 0X38

#define Master 10
#define Production 50
#define Maintenance 90
#define Quality 130

bool LT_Status = false, HT_Status = false, HT1_Status = false, Buzzer = false, Audio_Out = false, L_Test = false, Learn_Status = false, N_Status = false;
bool LT_Time = false, HT_Time = false, HT1_Time = false, Learn_State = false, Trig_State = false;
bool Rev_Mode = false, By_Pass1 = true, By_Pass2 = true, Rev_State = true;
bool Authorized = false, Direct_Authorized = false;
bool programMode = false;  // initialize programming mode to false
uint8_t successRead;    // Variable integer to keep if we have Successful Read from Reader
byte storedCard[4];   // Stores an ID read from EEPROM
byte readCard[4];   // Stores scanned ID read from RFID Module
byte masterCard[4];   // Stores master card's ID read from EEPROM
int Learn_Count = 0;
int SC_Counter, sc, Prev_SC_Counter;
long int  a, b;
int s_count = 0;
bool Master_Status = false, MQ = false, Clamp1_Status = false, Clamp2_Status = false, NG_Status = false;

MFRC522 mfrc522(SS_PIN, RST_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(4, 5, NEO_GRB + NEO_KHZ800);//Stage 1
LiquidCrystal_I2C lcd(0x39, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address
TM1637 tm1637(sos, DIO);

int Screw_Count ;
float HT;
float LT;
int bright;

int HT4;
int LT4;

void setup() {
  pinMode(DIP1, INPUT);
  pinMode(DIP2, INPUT);
  pinMode(Buzz, OUTPUT);
  pinMode(wipeB, INPUT_PULLUP);
  pinMode(fin, INPUT_PULLUP);
  pinMode(fout, OUTPUT);
  pinMode(rout, OUTPUT);
  pinMode(rin, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(Audio, OUTPUT);
  digitalWrite(fout, HIGH);
  digitalWrite(rout, HIGH);
  Serial.begin(9600);
//  if (EEPROM.read(0) != 100) {
//    EEPROM.write(0, 100);
//    EEPROM.write(2, 0);
//    EEPROM.write(4, 0);
//    EEPROM.write(6, 0);
//    EEPROM.write(8, 0);
//    EEPROM.write(411, 4);
//    EEPROM.write(412, 1);
//    EEPROM.write(413, 20);
//    EEPROM.write(414, 0);
//    EEPROM.write(415, 30);
//    EEPROM.write(416, 1);
//    EEPROM.write(418, 1);
//    EEPROM.write(419, 0);
//    EEPROM.write(420, 2);
//    EEPROM.write(421, 0);
//    EEPROM.write(422, 0);
//  }
  pixels.begin();
  Wire.begin();
  SPI.begin();
  mfrc522.PCD_Init();    // Initialize MFRC522 Hardware
  ShowReaderDetails();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("AIRPRO CO.  ,");//Text printed on LCD when system is ON
  lcd.setCursor(4, 1);
  lcd.print("LIMITED");//Text printed on LCD when system is ON
  Seg_begin();
  setrow(0, 3, 0x77);
  setrow(0, 2, 0x67);
  setrow(0, 1, 0x05);
  setrow(0, 0, 0x1D);
  Screw_Count = EEPROM.read(411);
  HT = EEPROM.read(412) + EEPROM.read(413) * 0.01;
  LT = EEPROM.read(414) + EEPROM.read(415) * 0.01;
  bright = EEPROM.read(420) % 4;

  HT4 = (HT - LT) * 1000;
  LT4 = LT * 1000;

  if (EEPROM.read(416) > 0)
    Buzzer = true;
  if (EEPROM.read(418) > 0)
    Rev_Mode = true;
  if (EEPROM.read(419) > 0)
    Rev_State = true;
  if (EEPROM.read(421) > 0)
    Clamp1_Status = true;
  if (EEPROM.read(422) > 0)
    Clamp1_Status = true;
  pixels.setPixelColor(0, pixels.Color(255, 255, 255));
  pixels.setPixelColor(1, pixels.Color(255, 255, 255));
  pixels.show();
  isMaster_Present();
  isProduction_Present();
  isMaintenance_Present();
  isQuality_Present();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("AIRPRO CO.  ,");//Text printed on LCD when system is ON
  lcd.setCursor(4, 1);
  lcd.print("LIMITED");//Text printed on LCD when system is
  pixels.setPixelColor(2, pixels.Color(255,255, 255));
  pixels.setPixelColor(3, pixels.Color(255, 255, 255));
  pixels.show();
  for (int i = 0; i < 2; i++) {
    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.setPixelColor(1, pixels.Color(255, 255, 255));
    pixels.show();
    delay(500);
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.setPixelColor(1, pixels.Color(0, 0, 255));
    pixels.show();
    delay(500);
  }
  lcd.clear();
  lcd.print("CURRENT / BATCH:");
  lcd.setCursor(0, 1);
  lcd.print(SC_Counter);
  lcd.print("/");
  lcd.print(Screw_Count);
}

void loop() {

  setrow(12, 3, 0X4e);
  setrow(12, 2, 0x01);
  setdigit(12, 1, SC_Counter / 10, false);
  setdigit(12, 0, SC_Counter % 10, false);
  pixels.setPixelColor(0, pixels.Color(255, 255, 255));
  pixels.setPixelColor(1, pixels.Color(255, 255, 255));
  pixels.show();

  if (!(ReadIo() & 0X02)) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Settings");//Text printed on LCD when system is ON
    setrow(0, 3, 0x5B);
    setrow(0, 2, 0x4f);
    setrow(0, 1, 0x01);
    setrow(0, 0, 0x0E);

    readCard[0] = 0;
    a = millis();
    while (!(ReadIo() & 0X02)) {
      b = millis();
      if (b < a)
        b = b + (2 ^ 32) - 1;
      if ((b - a) > 5000 && (b - a) < 6000)
        break;
      getID();
      if (isMaster(readCard)) {
        readCard[0] = 0;
        Authorized = true;
        Master_Status = true;
        Ring(300, 1);
        break;
      }
      if (isProduction(readCard)) {
        readCard[0] = 0;
        Authorized = true;
        Master_Status = false;
        Ring(300, 1);
        break;
      }
      if (isMaintenance(readCard)) {
        readCard[0] = 0;
        Screen3();
        Authorized = true;
        MQ = true;
        break;
      }
      if (isQuality(readCard)) {
        readCard[0] = 0;
        Screen4();
        Authorized = true;
        MQ = true;
        break;
      }
    }
    delay(5);
    while ((!(ReadIo() & 0X02) || (ReadIo() & 0X02)) && !Authorized)
    {
      b = millis();
      if (b < a)
        b = b + (2 ^ 32) - 1;
      if ((b - a) > 5000 && (b - a) < 6000)
        break;
      getID();
      if (isMaster(readCard))
      {
        readCard[0] = 0;
        Authorized = true;
        Master_Status = true;
        Ring(300, 1);
        break;
      }
      if (isProduction(readCard))
      {
        readCard[0] = 0;
        Authorized = true;
        Master_Status = false;
        Ring(300, 1);
        break;
      }
      if (isMaintenance(readCard)) {
        readCard[0] = 0;
        Screen3();
        Authorized = true;
        MQ = true;
        break;
      }
      if (isQuality(readCard)) {
        readCard[0] = 0;
        Screen4();
        Authorized = true;
        MQ = true;
        break;
      }
    }
    if (Authorized && !MQ) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Settings");
      lcd.setCursor(4, 1);
      lcd.print("Unlocked");
      setrow(0, 3, 0x5B);
      setrow(0, 2, 0x4f);
      setrow(0, 1, 0x01);
      setrow(0, 0, 0x3e);
      delay(300);
      s_count = 0;
      while (!(ReadIo() & 0X02) || (ReadIo() & 0X02)) {
        if (!(ReadIo() & 0X01))
          s_count = (s_count + 1) % 12;
        else if (!(ReadIo() & 0X04)) {
          if (s_count > 0)
            s_count--;
          else
            s_count = 11;
        }
        if (!Master_Status && s_count == 11)
          s_count = 0;
        settings(s_count);
        delay(100);
        getID();
        if (isProduction(readCard) || isMaster(readCard))
        {
          readCard[0] = 0;
          break;
        }
      }
    }
    pixels.setPixelColor(2, pixels.Color(255, 255, 255));
    pixels.setPixelColor(3, pixels.Color(255, 255, 255));
    pixels.show();
    Master_Status = false;
    Authorized = false;
    MQ = false;
    lcd.clear();
    lcd.print("CURRENT / BATCH:");
    lcd.setCursor(0, 1);
    lcd.print(SC_Counter);
    lcd.print("/");
    lcd.print(Screw_Count);
  }
  if (((ReadIo() & 0X08) || Clamp1_Status) && ((ReadIo() & 0X10) || Clamp2_Status))
  {
    By_Pass1 = true;
    By_Pass2 = true;
  }

  if (!(ReadIo() & 0X01) && !(ReadIo() & 0X02)) {
    SC_Counter = 0;
    WriteIo(B01011111);
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.setPixelColor(1, pixels.Color(0, 0, 255));
    pixels.show();
    if (Buzzer) {
      digitalWrite(Buzz, HIGH);
      delay(250);
      digitalWrite(Buzz, LOW);
    }
    pixels.setPixelColor(0, pixels.Color(0, 125, 0));
    pixels.setPixelColor(1, pixels.Color(0, 125, 0));
    pixels.show();
    delay(200);
    WriteIo(B00011111);
  }

  if (digitalRead(fin) == 0)// && By_Pass1 && By_Pass2)
    Forward();

  if (digitalRead(rin) == 0 && Rev_State && digitalRead(fin) == 0)
    Reverse();
}

void settings(int c)
{
  bool Save = false;
  switch (c) {

    case 0: //Screw Count
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Screw Count");
      lcd.setCursor(4, 1);
      lcd.print("Settings");
      SC_Set();
      break;

    case 1: //HT_Setting
      {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("HIGH Time");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        HT_Set();
      }
      break;

    case 2: //LT_Setting
      {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("LOW Time");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        LT_Set();
      }
      break;

    case 3: // Buzzer Settings (ON/OFF)
      {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Buzzer");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        Buzz_Set();
      }
      break;

    case 4: // Reverse Mode (ON/OFF)
      {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Reverse Mode");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        Rev_Set();
      }
      break;

    case 5: // Reverse Mode (ON/OFF)
      {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Reverse State");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        Rev_State_Set();
      }
      break;

    case 6://Clamp 1
      {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Clamp 1");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        Clamp1();
      }
      break;

    case 7://Clamp 2
      {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Clamp 2");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        Clamp2();
      }
      break;
    case 8://7 Segment Brightness
      {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Brightness");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        Seg_Bright();
      }
      break;

    case 9: // Learn Mode
      {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Learn Mode");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        Learn_Mode();
      }
      break;

    case 10: // UID
      {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("UID : ");
        lcd.print(UID);
        setrow(0, 3, 0x3e);
        setrow(0, 2, 0x10);
        setrow(0, 1, 0x3d);
        setrow(0, 0, 0x01);
      }
      break;

    case 11://RFID Card ADD or Delete or Master Card Erase
      {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Master");
        lcd.setCursor(4, 1);
        lcd.print("Settings");
        Master_Set();
      }
      break;
  }
}

void WriteIo(uint8_t bits)
{
  Wire.beginTransmission(address);
  Wire.write(bits);
  Wire.endTransmission();
}

uint8_t ReadIo()
{
  WriteIo(B00011111); // PCF8574 require us to set all outputs to 1 before doing a read.

  Wire.beginTransmission(address);
  Wire.requestFrom((int)address, 1); // Ask for 1 byte from slave
  uint8_t bits = Wire.read(); // read that one byte
  Wire.endTransmission();

  return bits;
}
