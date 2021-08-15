void Forward()
{
  int LT4 = LT * 1000;
  attachInterrupt(digitalPinToInterrupt(2), trig, FALLING);
  MsTimer2::set((int)LT4, LT_Timer);
  MsTimer2::start();
  digitalWrite(fout, LOW);
  a = millis();
  HT1_Status = false;
  N_Status = true;
  //trigg = true;
  bool disp = true;
  NG_Status = false;
  while (digitalRead(fin) == 0)
  {
    pixels.setPixelColor(0, pixels.Color(0, 255, 255));
    pixels.setPixelColor(1, pixels.Color(0, 255, 255));
    pixels.show();
    if (LT_Time) {
      LT_Time = false; //LT is Passed
    }
    if (HT_Time) {
      HT_Time = false; //More than HT
    }
    if (HT1_Time) {
      digitalWrite(Buzz, HIGH);
      HT1_Time = false;
    }
    if (Trig_State) {
      Trig_State = false;
      pixels.setPixelColor(0, pixels.Color(255, 255, 255));
      pixels.show();
      delay(50);
      if (!LT_Status && !HT_Status && !HT1_Status)
        LT_Trig();

      if (LT_Status && !HT_Status && !HT1_Status)
        HT_Trig();

      if (LT_Status && HT_Status && !HT1_Status)
        HT1_Trig();
      if (SC_Counter == Screw_Count) {
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
    }
  }
  delay(5);
  digitalWrite(fout, HIGH);
  digitalWrite(Buzz, LOW);
  By_Pass1 = false;
  By_Pass2 = false;
  MsTimer2::stop();
  detachInterrupt(digitalPinToInterrupt(2));
}
//--------------------------------------Timer Interrupts--------------------------------
void LT_Timer()
{
  int HT4 = (HT - LT) * 1000;
  MsTimer2::stop();
  MsTimer2::set((int)HT4, HT_Timer);
  MsTimer2::start();
  LT_Status = true; //LT is Passed
  LT_Time = true;
}

void HT_Timer()
{
  MsTimer2::stop();
  MsTimer2::set(2000, HT_Timer1);
  MsTimer2::start();
  HT_Status = true; //More than HT
  HT_Time = true;
}

void HT_Timer1()
{
  MsTimer2::stop();
  HT1_Status = true;
  HT1_Time = true;
}
//-----------------------------------------Trigger Functions-------------------------------
void LT_Trig()
{
  LT_Status = false;
  HT_Status = false;
  HT1_Status = false;
  NG_Status = true; // Updated by Vinay --> for resolving screw count should not be -1 after NG in Lt
  if (b < a)
    b = b + 2 ^ 32 - 1;
  WriteIo(B10011111);
  pixels.setPixelColor(0, pixels.Color(255, 165, 0));
  pixels.setPixelColor(1, pixels.Color(255, 165, 0));
  pixels.show();
  if (Buzzer) {
    digitalWrite(Buzz, HIGH); delay(50);
    digitalWrite(Buzz, LOW); delay(50);
    digitalWrite(Buzz, HIGH); delay(50);
    digitalWrite(Buzz, LOW);
  }
  delay(500);
  WriteIo(B00011111);
}

void HT_Trig()
{
  LT_Status = false;
  HT_Status = false;
  HT1_Status = false;
  if (b < a)
    b = b + 2 ^ 32 - 1;
  WriteIo(B00111111);
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.setPixelColor(1, pixels.Color(0, 255, 0));
  pixels.show();
  if (Buzzer)
  {
    digitalWrite(Buzz, HIGH);
    delay(100);
    digitalWrite(Buzz, LOW);
  }
  
  SC_Counter++;
  lcd.clear();
  lcd.print("CURRENT / BATCH:");
  lcd.setCursor(0, 1);
  lcd.print(SC_Counter);
  lcd.print("/");
  lcd.print(Screw_Count);
  setrow(12, 3, 0X4e);
  setrow(12, 2, 0x01);
  setdigit(12, 1, SC_Counter / 10, false);
  setdigit(12, 0, SC_Counter % 10, false);
  delay(300);
  WriteIo(B00011111);
}

void HT1_Trig()
{
  LT_Status = false;
  HT_Status = false;
  HT1_Status = false;
  WriteIo(B10011111);
  NG_Status = true;
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.show();
  if (Buzzer)
  {
    digitalWrite(Buzz, HIGH); delay(50);
    digitalWrite(Buzz, LOW); delay(50);
    digitalWrite(Buzz, HIGH); delay(50);
    digitalWrite(Buzz, LOW);
  }
  if (b < a)
    b = b + 2 ^ 32 - 1;
  delay(500);
  WriteIo(B00011111);
}
