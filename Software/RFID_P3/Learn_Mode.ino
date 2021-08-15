int HTL = 0, LTL = 0;

void Learn_Mode()
{
  bool Exit_Learn = false;
  bool Save = false;
  setrow(0, 3, 0x0e);
  setrow(0, 2, 0x4f);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  if (!(ReadIo() & 0X02)) {
    pixels.setPixelColor(0, pixels.Color(255, 255, 0));
    pixels.setPixelColor(1, pixels.Color(255, 255, 0));
    pixels.show();
    Learn_Count = 0;
    HTL = (HT - LT) * 1000;
    LTL = LT * 1000;
    setrow(12, 3, 0X5b);
    setrow(12, 2, 0x01);
    setdigit(12, 1, Learn_Count / 10, false);
    setdigit(12, 0, Learn_Count % 10, false);
    while (!(ReadIo() & 0X02));
    delay(5);
    while (1) {
      setrow(12, 3, 0X5b);
      setrow(12, 2, 0x01);
      setdigit(12, 1, Learn_Count / 10, false);
      setdigit(12, 0, Learn_Count % 10, false);
      if (digitalRead(fin) == 0 && Learn_Count < 40) {
        attachInterrupt(digitalPinToInterrupt(2), trig_L, FALLING);
        a = millis();
        digitalWrite(fout, LOW);
        Learn_Status = true;

        if (Learn_Count == 10 && Buzzer) {
          digitalWrite(Buzz, HIGH);
          delay(100);
          digitalWrite(Buzz, LOW);
        }

        while (digitalRead(fin) == 0) {

          if (Learn_State) {
            if (a > b)
              b = b + (2 ^ 32) - 1;

            if ((b - a) > HTL && (b - a) < 9999)
              HTL = b - a;

            if ((b - a) < LTL)
              LTL = b - a;
            if (Buzzer)
            {
              digitalWrite(Buzz, HIGH);
              delay(100);
              digitalWrite(Buzz, LOW);
            }
            Learn_Count++;
            setrow(12, 3, 0X5b);
            setrow(12, 2, 0x01);
            setdigit(12, 1, Learn_Count / 10, false);
            setdigit(12, 0, Learn_Count % 10, false);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Learn Count: ");//Text printed on LCD when system is ON
            lcd.print(Learn_Count);//Text printed on LCD when system is ON
            lcd.setCursor(0, 1);
            lcd.print("HT: ");//Text printed on LCD when system is ON
            lcd.print(HTL * 10); //Text printed on LCD when system is ON
            lcd.setCursor(8, 1);
            lcd.print("LT: ");//Text printed on LCD when system is ON
            lcd.print(LTL * 10); //Text printed on LCD when system is ON
            delay(50);
            Learn_State = false;
            delay(100);
          }
        }
        digitalWrite(fout, HIGH);
        Learn_Status = true;
        detachInterrupt(digitalPinToInterrupt(2));
      }

      if (!(ReadIo() & 0X02) && Learn_Count < 10) {
        a = millis();
        while (!(ReadIo() & 0X02)) {
          b = millis();
          if (b < a)
            b = b + (2 ^ 32) - 1;
          if ((b - a) > 3000) {
            Exit_Learn = true;
            break;
          }
        }
      }

      if (!(ReadIo() & 0X02) && Learn_Count >= 10)
        break;

      if ((!(ReadIo() & 0X02) || (ReadIo() & 0X02)) && Exit_Learn) {
        setrow(0, 3, 0x4f);
        setrow(0, 2, 0x0f);
        setrow(0, 1, 0x01);
        setrow(0, 0, 0x15);
        while (!(ReadIo() & 0X02));
        delay(5);
        while ((ReadIo() & 0X02)) {
          if (!(ReadIo() & 0X01) || !(ReadIo() & 0X04))
            Save = !Save;
          if (Save) {
            setrow(0, 3, 0x4f);
            setrow(0, 2, 0x0f);
            setrow(0, 1, 0x01);
            setrow(0, 0, 0x3b);
          }
          else {
            setrow(0, 3, 0x4f);
            setrow(0, 2, 0x0f);
            setrow(0, 1, 0x01);
            setrow(0, 0, 0x15);
          }
          delay(200);
        }
        Exit_Learn = false;
        if (Save) {
          Save = false;
          break;
        }
      }
    }

    if (!(ReadIo() & 0X02) && Learn_Count >= 10 || Learn_Count == 40) {
      setrow(0, 3, 0x5b);
      setrow(0, 2, 0x77);
      setrow(0, 1, 0x01);
      setrow(0, 0, 0x15);
      while (!(ReadIo() & 0X02));
      delay(5);
      while ((ReadIo() & 0X02)) {
        if (!(ReadIo() & 0X01) || !(ReadIo() & 0X04))
          Save = !Save;
        delay(200);

        if (Save) {
          setrow(0, 3, 0x5b);
          setrow(0, 2, 0x77);
          setrow(0, 1, 0x01);
          setrow(0, 0, 0x3b);
        }
        else {
          setrow(0, 3, 0x5b);
          setrow(0, 2, 0x77);
          setrow(0, 1, 0x01);
          setrow(0, 0, 0x15);
        }
      }
    }
    if (Save) {
      HTL = HTL / 10;
      LTL = LTL / 10;
      HT = HTL / 100.0;
      LT = LTL / 100.0;
      EEPROM.write(412, HTL / 100);
      EEPROM.write(413, HTL % 100);
      EEPROM.write(414, LTL / 100);
      EEPROM.write(415, LTL % 100);
      digitalWrite(Buzz, HIGH); delay(50);
      digitalWrite(Buzz, LOW); delay(50);
      digitalWrite(Buzz, HIGH); delay(50);
      digitalWrite(Buzz, LOW);
    }
    else;
    Learn_Count = 0;
  }
  delay(5);
  while (!(ReadIo() & 0X02));
  delay(5);
}
