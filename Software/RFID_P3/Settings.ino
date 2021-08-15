void SC_Set()
{
  int sc_count = 0, Count = 0, Screw_Count_Prev;
  setrow(0, 3, 0x5B);
  setrow(0, 2, 0x4e);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  Screw_Count_Prev = Screw_Count;
  if (!(ReadIo() & 0X02)) {
    setdigit(15, 3, 0, false);
    setdigit(15, 2, 0, false);
    setdigit(15, 1, Screw_Count / 10, false);
    setdigit(15, 0, Screw_Count % 10, false);
    lcd.clear();
    lcd.print("Screw Count: ");
    lcd.print(Screw_Count / 10);
    lcd.print(Screw_Count % 10);
    //Serial.println("Entered Case 0");
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01)) {
        sc_count = 1;
        a = millis();
        while (!(ReadIo() & 0X01)) {
          b = millis();
          if (b < a)
            b = b + (2 ^ 32) - 1;
          if ((a + 500) < b && sc_count < 6) {
            sc_count++;
            a = b;
          }
          else if ((a + 250) < b && sc_count >= 6 && sc_count < 14) {
            sc_count++;
            a = b;
          }
          else if ((a + 100) < b && sc_count >= 14 && sc_count < 34) {
            sc_count++;
            a = b;
          }
          else if ((a + 10) < b && sc_count >= 34) {
            sc_count++;
            a = b;
          }
          lcd.clear();
          lcd.print("Screw Count: ");
          lcd.print(((Screw_Count + sc_count) % 100) / 10);
          lcd.print((Screw_Count + sc_count) % 10);
          setdigit(15, 3, 0, false);
          setdigit(15, 2, 0, false);
          setdigit(15, 1, ((Screw_Count + sc_count) % 100) / 10, false);
          setdigit(15, 0, (Screw_Count + sc_count) % 10, false);
          delay(80);
        }
        Screw_Count = (Screw_Count + sc_count) % 100;
      }
      if (!(ReadIo() & 0X04)) {
        sc_count = 0;
        a = millis();
        while (!(ReadIo() & 0X04)) {
          b = millis();
          if (b < a)
            b = b + (2 ^ 32) - 1;
          if ((a + 500) < b && sc_count < 6) {
            sc_count++;
            a = b;
          }
          else if ((a + 250) < b && sc_count >= 6 && sc_count < 14) {
            sc_count++;
            a = b;
          }
          else if ((a + 100) < b && sc_count >= 14 && sc_count < 34) {
            sc_count++;
            a = b;
          }
          else if ((a + 10) < b && sc_count >= 34) {
            sc_count++;
            a = b;
          }
          lcd.clear();
          lcd.print("Screw Count: ");
          lcd.print(((Screw_Count + 99 - (sc_count % 100)) % 100) / 10);
          lcd.print((Screw_Count + 99 - (sc_count % 100)) % 10);
          setdigit(15, 3, 0, false);
          setdigit(15, 2, 0, false);
          setdigit(15, 1, ((Screw_Count + 99 - (sc_count % 100)) % 100) / 10, false);
          setdigit(15, 0, (Screw_Count + 99 - (sc_count % 100)) % 10, false);
          delay(80);
        }
        Screw_Count = (Screw_Count + 99 - (sc_count % 100)) % 100;
      }
      else;
    }
    if (Screw_Count != Screw_Count_Prev)
      SC_Counter = 0;
    EEPROM.write(411, Screw_Count);
    delay(5);
    while (!(ReadIo() & 0X02));
    delay(5);
  }
}

void HT_Set()
{
  int HT_Count, HT1 = 0, Count = 0, LT1 = 0;
  float HT2 = 0;
  setrow(0, 3, 0x37);
  setrow(0, 2, 0x0f);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  if (!(ReadIo() & 0X02)) {
    HT1 = HT * 100;
    LT1 = LT * 100;
    HT1 = HT1 % 1000;
    LT1 = LT1 % 1000;
    lcd.clear();
    lcd.print("High Time: ");
    lcd.print( HT1 / 100);
    lcd.print(".");
    lcd.print((HT1 % 100) / 10);
    lcd.print(HT1 % 10);
    setdigit(15, 3, 0, false);
    setdigit(15, 2, (HT1 / 100), true);
    setdigit(15, 1, (HT1 % 100) / 10, false);
    setdigit(15, 0, HT1 % 10, false);
    Serial.println("Entered Case 1");
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01)) {
        HT_Count = 1;
        Count = 0;
        a = millis();
        while (!(ReadIo() & 0X01)) {
          b = millis();
          if (b < a)
            b = b + (2 ^ 32) - 1;
          if ((a + 500) < b && Count < 6) {
            HT_Count = HT_Count + 1;
            Count++;
            a = b;
          }
          else if ((a + 250) < b && Count >= 6 && Count < 14) {
            HT_Count = HT_Count + 5;
            a = b;
            Count++;
          }
          else if ((a + 100) < b && Count >= 14 && Count < 34) {
            HT_Count = HT_Count + 10;
            a = b;
            Count++;
          }
          else if ((a + 10) < b && Count >= 34) {
            HT_Count = HT_Count + 10;
            a = b;
            Count++;
          }
          if ((HT1 + HT_Count) > 999)
          {
            HT1 = LT1 + 1;
            HT_Count = 0;
          }
          lcd.clear();
          lcd.print("High Time: ");
          lcd.print(((HT1 + HT_Count) % 1000) / 100);
          lcd.print(".");
          lcd.print(((HT1 + HT_Count) % 100) / 10);
          lcd.print((HT1 + HT_Count) % 10);
          setdigit(15, 3, 0, false);
          setdigit(15, 2, ((HT1 + HT_Count) % 1000) / 100, true);
          setdigit(15, 1, ((HT1 + HT_Count) % 100) / 10, false);
          setdigit(15, 0, (HT1 + HT_Count) % 10, false);
          delay(50);
        }
        HT1 = (HT1 + HT_Count) % 1000;
      }
      if (!(ReadIo() & 0X04)) {
        Count = 0;
        HT_Count = 1;
        a = millis();
        while (!(ReadIo() & 0X04)) {
          Serial.println("In HT down");
          b = millis();
          if (b < a)
            b = b + (2 ^ 32) - 1;
          if ((a + 500) < b && Count < 6) {
            HT_Count = HT_Count + 1;
            a = b;
            Count++;
          }
          else if ((a + 250) < b && Count >= 6 && Count < 14) {
            HT_Count = HT_Count + 5;
            a = b;
            Count++;
          }
          else if ((a + 100) < b && Count >= 14 && Count < 34) {
            HT_Count = HT_Count + 10;
            a = b;
            Count++;
          }
          else if ((a + 10) < b && Count >= 34) {
            HT_Count = HT_Count + 10;
            a = b;
            Count++;
          }
          if ((HT1 + 1000 - (HT_Count % 1000)) % 1000 <= LT1) {
            HT_Count = 0;
            HT1 = 999;
          }
          lcd.clear();
          lcd.print("High Time: ");
          lcd.print(((HT1 + 1000 - (HT_Count % 1000)) % 1000) / 100);
          lcd.print(".");
          lcd.print(((HT1 + 1000 - (HT_Count % 1000)) % 100) / 10);
          lcd.print((HT1 + 1000 - (HT_Count % 1000)) % 10);
          setdigit(15, 3, 0, false);
          setdigit(15, 2, ((HT1 + 1000 - (HT_Count % 1000)) % 1000) / 100, true);
          setdigit(15, 1, ((HT1 + 1000 - (HT_Count % 1000)) % 100) / 10, false);
          setdigit(15, 0, (HT1 + 1000 - (HT_Count % 1000)) % 10, false);
          delay(50);
        }
        HT1 = (HT1 + 1000 - (HT_Count % 1000)) % 1000;
      }
    }
    HT = HT1 / 100 + (HT1 % 100) * 0.01;
    EEPROM.write(412, HT1 / 100);
    EEPROM.write(413, HT1 % 100);
    delay(5);
    while (!(ReadIo() & 0X02));
    delay(5);
  }
}

void LT_Set()
{
  int LT_Count, LT1 = 0, Count = 0;
  float LT2 = 0;
  int HT1 = HT * 100;
  setrow(0, 3, 0x0E);
  setrow(0, 2, 0x0f);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  if (!(ReadIo() & 0X02)) {
    LT1 = LT * 100;
    HT1 = HT1 % 1000;
    LT1 = LT1 % 1000;
    lcd.clear();
    lcd.print("Low Time: ");
    lcd.print( LT1 / 100);
    lcd.print(".");
    lcd.print((LT1 % 100) / 10);
    lcd.print(LT1 % 10);
    setdigit(15, 3, 0, false);
    setdigit(15, 2, LT1 / 100, true);
    setdigit(15, 1, (LT1 % 100) / 10, false);
    setdigit(15, 0, LT1 % 10, false);
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01)) {
        LT_Count = 1;
        Count = 0;
        a = millis();
        while (!(ReadIo() & 0X01)) {
          b = millis();
          if (b < a)
            b = b + (2 ^ 32) - 1;
          if ((a + 500) < b && Count < 6) {
            LT_Count = LT_Count + 1;
            Count++;
            a = b;
          }
          else if ((a + 250) < b && Count >= 6 && Count < 14) {
            LT_Count = LT_Count + 5;
            a = b;
            Count++;
          }
          else if ((a + 100) < b && Count >= 14 && Count < 34) {
            LT_Count = LT_Count + 10;
            a = b;
            Count++;
          }
          else if ((a + 10) < b && Count >= 34) {
            LT_Count = LT_Count + 10;
            a = b;
            Count++;
          }
          if ((LT_Count + LT1) % 1000 >= HT1)
          {
            LT_Count = 0;
            LT1 = 0;
          }
          lcd.clear();
          lcd.print("Low Time: ");
          lcd.print(((LT1 + LT_Count) % 1000) / 100);
          lcd.print(".");
          lcd.print(((LT1 + LT_Count) % 100) / 10);
          lcd.print((LT1 + LT_Count) % 10);
          setdigit(15, 3, 0, false);
          setdigit(15, 2, ((LT1 + LT_Count) % 1000) / 100, true);
          setdigit(15, 1, ((LT1 + LT_Count) % 100) / 10, false);
          setdigit(15, 0, (LT1 + LT_Count) % 10, false);
          delay(50);
        }
        LT1 = (LT1 + LT_Count) % 1000;
      }
      if (!(ReadIo() & 0X04)) {
        Count = 0;
        LT_Count = 1;
        a = millis();
        while (!(ReadIo() & 0X04)) {
          Serial.println("In LT down");
          b = millis();
          if (b < a)
            b = b + (2 ^ 32) - 1;
          if ((a + 500) < b && Count < 6) {
            LT_Count = LT_Count + 1;
            a = b;
            Count++;
          }
          else if ((a + 250) < b && Count >= 6 && Count < 14) {
            LT_Count = LT_Count + 5;
            a = b;
            Count++;
          }
          else if ((a + 100) < b && Count >= 14 && Count < 34) {
            LT_Count = LT_Count + 10;
            a = b;
            Count++;
          }
          else if ((a + 10) < b && Count >= 34) {
            LT_Count = LT_Count + 10;
            a = b;
            Count++;
          }
          if (LT1 < LT_Count) {
            LT_Count = 0;
            LT1 = HT1 - LT_Count;
          }
          lcd.clear();
          lcd.print("Low Time: ");
          lcd.print(((LT1 + 1000 - (LT_Count % 1000)) % 1000) / 100);
          lcd.print(".");
          lcd.print((((LT1 + 1000 - (LT_Count % 1000)) % 1000) % 100) / 10);
          lcd.print((LT1 + 1000 - (LT_Count % 1000)) % 10);
          setdigit(15, 3, 0, false);
          setdigit(15, 2, ((LT1 + 1000 - (LT_Count % 1000)) % 1000) / 100, true);
          setdigit(15, 1, (((LT1 + 1000 - (LT_Count % 1000)) % 1000) % 100) / 10, false);
          setdigit(15, 0, ((LT1 + 1000 - (LT_Count % 1000)) % 1000) % 10, false);
          delay(80);
        }
        LT1 = (LT1 + 1000 - (LT_Count % 1000)) % 1000;
      }
    }
    LT = LT1 / 100 + (LT1 % 100) * .01;
    LT2 = LT * 100;
    Serial.println(LT2);
    EEPROM.write(414, (int)LT2 / 100);
    EEPROM.write(415, (int)LT2 % 100);
    delay(5);
    while (!(ReadIo() & 0X02));
    delay(50);
  }
}

void Buzz_Set()
{
  setrow(0, 3, 0x1f);
  setrow(0, 2, 0x1c);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  if (!(ReadIo() & 0X02))
  {
    if (Buzzer) {
      lcd.clear();
      lcd.print("Buzzer ON");
      setrow(0, 3, 0x01);
      setrow(0, 2, 0x7e);
      setrow(0, 1, 0x15);
      setrow(0, 0, 0x01);
    }
    else
    {
      lcd.clear();
      lcd.print("Buzzer OFF");
      setrow(0, 3, 0x7e);
      setrow(0, 2, 0x47);
      setrow(0, 1, 0x47);
      setrow(0, 0, 0x01);
    }
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01) || !(ReadIo() & 0X04))
        Buzzer = !Buzzer;

      if (Buzzer) {
        lcd.clear();
        lcd.print("Buzzer ON");
        setrow(0, 3, 0x01);
        setrow(0, 2, 0x7e);
        setrow(0, 1, 0x15);
        setrow(0, 0, 0x01);
      }
      else
      {
        lcd.clear();
        lcd.print("Buzzer OFF");
        setrow(0, 3, 0x7e);
        setrow(0, 2, 0x47);
        setrow(0, 1, 0x47);
        setrow(0, 0, 0x01);
      }
      delay(200);
    }

    if (Buzzer)
      EEPROM.write(416, 1);
    else
      EEPROM.write(416, 0);
    while (!(ReadIo() & 0X02));
    delay(5);
  }
}

void Rev_Set()
{
  setrow(0, 3, 0x05);
  setrow(0, 2, 0x4f);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  if (!(ReadIo() & 0X02))
  {
    if (Rev_Mode) {
      lcd.clear();
      lcd.print("Reverse Mode ON");
      setrow(0, 3, 0x01);
      setrow(0, 2, 0x7e);
      setrow(0, 1, 0x15);
      setrow(0, 0, 0x01);
    }
    else
    {
      lcd.clear();
      lcd.print("Reverse Mode OFF");
      setrow(0, 3, 0x7e);
      setrow(0, 2, 0x47);
      setrow(0, 1, 0x47);
      setrow(0, 0, 0x01);
    }
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01) || !(ReadIo() & 0X04))
        Rev_Mode = !Rev_Mode;

      if (Rev_Mode) {
        lcd.clear();
        lcd.print("Reverse Mode ON");
        setrow(0, 3, 0x01);
        setrow(0, 2, 0x7e);
        setrow(0, 1, 0x15);
        setrow(0, 0, 0x01);
      }
      else
      {
        lcd.clear();
        lcd.print("Reverse Mode OFF");
        setrow(0, 3, 0x7e);
        setrow(0, 2, 0x47);
        setrow(0, 1, 0x47);
        setrow(0, 0, 0x01);
      }
      delay(200);
    }
    delay(5);
    if (Rev_Mode)
      EEPROM.write(418, 1);
    else
      EEPROM.write(418, 0);
    while (!(ReadIo() & 0X02));
    delay(5);
  }
}

void Rev_State_Set()
{
  setrow(0, 3, 0x05);
  setrow(0, 2, 0x4f);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x5B);
  if (!(ReadIo() & 0X02))
  {
    if (Rev_State) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Reverse");
      lcd.setCursor(3, 1);
      lcd.print("State ON");
      setrow(0, 3, 0x01);
      setrow(0, 2, 0x7e);
      setrow(0, 1, 0x15);
      setrow(0, 0, 0x01);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Reverse");
      lcd.setCursor(3, 1);
      lcd.print("State OFF");
      setrow(0, 3, 0x7e);
      setrow(0, 2, 0x47);
      setrow(0, 1, 0x47);
      setrow(0, 0, 0x01);
    }
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01) || !(ReadIo() & 0X04))
        Rev_State = !Rev_State;

      if (Rev_State) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Reverse");
        lcd.setCursor(3, 1);
        lcd.print("State ON");
        setrow(0, 3, 0x01);
        setrow(0, 2, 0x7e);
        setrow(0, 1, 0x15);
        setrow(0, 0, 0x01);
      }
      else
      {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Reverse");
        lcd.setCursor(3, 1);
        lcd.print("State OFF");
        setrow(0, 3, 0x7e);
        setrow(0, 2, 0x47);
        setrow(0, 1, 0x47);
        setrow(0, 0, 0x01);
      }
      delay(200);
    }
    delay(5);
    if (Rev_State)
      EEPROM.write(419, 1);
    else
      EEPROM.write(419, 0);
    while (!(ReadIo() & 0X02));
    delay(5);
  }
}

void Clamp1()
{
  setrow(0, 3, 0X4e);
  setrow(0, 2, 0x67);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x30);
  if (!(ReadIo() & 0X02))
  {
    if (Clamp1_Status) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Clamp 1");
      lcd.setCursor(3, 1);
      lcd.print("State ON");
      setrow(0, 3, 0x01);
      setrow(0, 2, 0x7e);
      setrow(0, 1, 0x15);
      setrow(0, 0, 0x01);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Clamp 1");
      lcd.setCursor(3, 1);
      lcd.print("State OFF");
      setrow(0, 3, 0x7e);
      setrow(0, 2, 0x47);
      setrow(0, 1, 0x47);
      setrow(0, 0, 0x01);
    }
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01) || !(ReadIo() & 0X04))
        Clamp1_Status = !Clamp1_Status;

      if (Clamp1_Status) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Clamp 1");
        lcd.setCursor(3, 1);
        lcd.print("State ON");
        setrow(0, 3, 0x01);
        setrow(0, 2, 0x7e);
        setrow(0, 1, 0x15);
        setrow(0, 0, 0x01);
      }
      else
      {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Clamp 1");
        lcd.setCursor(3, 1);
        lcd.print("State OFF");
        setrow(0, 3, 0x7e);
        setrow(0, 2, 0x47);
        setrow(0, 1, 0x47);
        setrow(0, 0, 0x01);
      }
      delay(200);
    }
    delay(5);
    if (Clamp1_Status)
      EEPROM.write(421, 1);
    else
      EEPROM.write(419, 0);
    while (!(ReadIo() & 0X02));
    delay(5);
  }
}

void Clamp2()
{
  setrow(0, 3, 0x67);
  setrow(0, 2, 0x4f);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x6D);
  if (!(ReadIo() & 0X02))
  {
    if (Clamp2_Status) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Clamp 2");
      lcd.setCursor(3, 1);
      lcd.print("State ON");
      setrow(0, 3, 0x01);
      setrow(0, 2, 0x7e);
      setrow(0, 1, 0x15);
      setrow(0, 0, 0x01);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Clamp 2");
      lcd.setCursor(3, 1);
      lcd.print("State OFF");
      setrow(0, 3, 0x7e);
      setrow(0, 2, 0x47);
      setrow(0, 1, 0x47);
      setrow(0, 0, 0x01);
    }
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01) || !(ReadIo() & 0X04))
        Clamp2_Status = !Clamp2_Status;

      if (Clamp2_Status) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Clamp 2");
        lcd.setCursor(3, 1);
        lcd.print("State ON");
        setrow(0, 3, 0x01);
        setrow(0, 2, 0x7e);
        setrow(0, 1, 0x15);
        setrow(0, 0, 0x01);
      }
      else
      {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Clamp 2");
        lcd.setCursor(3, 1);
        lcd.print("State OFF");
        setrow(0, 3, 0x7e);
        setrow(0, 2, 0x47);
        setrow(0, 1, 0x47);
        setrow(0, 0, 0x01);
      }
      delay(200);
    }
    delay(5);
    if (Clamp2_Status)
      EEPROM.write(421, 1);
    else
      EEPROM.write(419, 0);
    while (!(ReadIo() & 0X02));
    delay(5);
  }
}

void Seg_Bright()
{
  setrow(0, 3, 0x1f);
  setrow(0, 2, 0x05);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  int bright1 = bright % 4;
  int count = 0;
  if (!(ReadIo() & 0X02)) {
    lcd.clear();
    lcd.print("Brightness: ");
    lcd.print(bright1 + 1);
    setrow(8, 3, 0x1f);
    setrow(8, 2, 0x05);
    setrow(8, 1, 0x01);
    setdigit(8, 0, bright1 + 1, false);
    while (!(ReadIo() & 0X02));
    delay(5);
    while ((ReadIo() & 0X02)) {
      if (!(ReadIo() & 0X01)) {
        a = millis();
        count = 1;
        while (!(ReadIo() & 0X01)) {
          b = millis();
          if ((b - a) > 250) {
            a = b;
            count = 1;
          }
          if (count == 1) {
            bright1 = (bright1 + 1) % 4;
            tm1637.set((bright1 + 1) * 2 - 1);
            lcd.clear();
            lcd.print("Brightness: ");
            lcd.print(bright1 + 1);
            setrow(8, 3, 0x1f);
            setrow(8, 2, 0x05);
            setrow(8, 1, 0x01);
            setdigit(8, 0, bright1 + 1, false);
            count = 0;
          }
        }
      }
      if (!(ReadIo() & 0X04)) {
        a = millis();
        count = 1;
        while (!(ReadIo() & 0X04)) {
          b = millis();
          if ((b - a) > 250) {
            a = b;
            count = 1;
          }
          if (count == 1) {
            bright1 = (4 + bright1 - 1) % 4;
            tm1637.set((bright1 + 1) * 2 - 1);
            lcd.clear();
            lcd.print("Brightness: ");
            lcd.print(bright1 + 1);
            setrow(8, 3, 0x1f);
            setrow(8, 2, 0x05);
            setrow(8, 1, 0x01);
            setdigit(8, 0, bright1 + 1, false);
            count = 0;
          }
        }
      }
    }
    delay(5);
    bright = bright1;
    EEPROM.write(420, bright);
    while (!(ReadIo() & 0X02));
    delay(5);
  }
}

void Master_Set()
{
  int i = 0, j, k;
  setrow(0, 3, 0x4E);
  setrow(0, 2, 0x3D);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  if (!(ReadIo() & 0X02)) {
    while (!(ReadIo() & 0X02));
    delay(5);
    while (i != 2) {
      setrow(0, 3, 0x4E);
      setrow(0, 2, 0x01);
      setrow(0, 1, 0x77);
      setrow(0, 0, 0x3d);
      getID();  // sets successRead to 1 when we get read from reader otherwise 0
      i = Screen1();
      Screen2(i);
    }
    lcd.clear();
    lcd.setCursor(3, 0);
    programMode = false;
    lcd.print("Exit Master");
    lcd.setCursor(4, 1);
    lcd.print("Settings");
    delay(1000);
  }
}

byte Screen1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-> Add Card");
  lcd.setCursor(3, 1);
  lcd.print("Delete Card");
  return (Select_Key());
}

byte Screen2(int i) {
  bool Update = true;
  lcd.clear();
  while (!(ReadIo() & 0X02));
  delay(1);
  int c = 0;
  while (1) {
    if (!(ReadIo() & 0X04)) {
      c = (c + 1) % 4;
      Update = true;
    }
    if (!(ReadIo() & 0X01)) {
      c = (c + 3) % 4;
      Update = true;
    }
    if (c < 2 && Update) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("-> Master Card");
      lcd.setCursor(3, 1);
      lcd.print("Production Card");
      Update = false;
    }
    if (c >= 2 && Update) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("-> Quality Card");
      lcd.setCursor(3, 1);
      lcd.print("Maintenance Card");
      Update = false;
    }
    if (c % 2 == 0) {
      lcd.setCursor(0, 0);
      lcd.print("->");
      lcd.setCursor(0, 1);
      lcd.print("  ");
    }
    if (c % 2 == 1) {
      lcd.setCursor(0, 0);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("->");
    }
    while (!(ReadIo() & 0X01) && (ReadIo() & 0X04));
    while ((ReadIo() & 0X01) && !(ReadIo() & 0X04));
    delay(200);
    if (!(ReadIo() & 0X02) && i == 0) {
      Update = true;
      Add_Card(c);
    }
    if (!(ReadIo() & 0X02) && i == 1) {
      Update = true;
      Delete_Card(c);
    }
    if (!(ReadIo() & 0X01) && !(ReadIo() & 0X04)) {
      c = 2;
      while (!(ReadIo() & 0X01) && !(ReadIo() & 0X04));
      break;
    }
  }
  lcd.clear();
  return c;
}
