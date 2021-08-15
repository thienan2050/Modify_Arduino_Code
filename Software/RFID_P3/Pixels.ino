void Ring(unsigned int k, unsigned int j) {
  for (unsigned int i = 0; i < j; i++) {
    digitalWrite(Buzz, HIGH); delay(k);
    digitalWrite(Buzz, LOW); delay(k);
  }
}

void Screen3() {
  int i;
  bool Update = true;
  setrow(0, 3, 0x01);
  setrow(0, 2, 0x01);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  lcd.clear();
  readCard[0] = 0;
  while (!(ReadIo() & 0X02));
  delay(1);
  int c = 0;
  while (!isMaintenance(readCard)) {
    getID();
    if (!(ReadIo() & 0X01)) {
      c = (c + 1) % 2;
      Update = true;
    }
    if (!(ReadIo() & 0X04)) {
      c = (c + 1) % 2;
      Update = true;
    }
    if (c == 0 && Update) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Last Done:");
      lcd.setCursor(1, 1);
      lcd.print("Cycles: 1000");
      Update = false;
    }
    if (c == 1 && Update) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Due Date:");
      lcd.setCursor(1, 1);
      lcd.print("Cycles: 1001000");
      Update = false;
    }
    while (!(ReadIo() & 0X01) || !(ReadIo() & 0X04));
    delay(100);
    if (!(ReadIo() & 0X02)) {
      i = Screen_S();
      if (i == 0) {
        Screen5();
        Update = true;
      }
      while (!(ReadIo() & 0X02));
    }
  }
  lcd.clear();
}

void Screen4() {
  int i;
  bool Update = true;
  lcd.clear();
  readCard[0] = 0;
  setrow(0, 3, 0x01);
  setrow(0, 2, 0x01);
  setrow(0, 1, 0x01);
  setrow(0, 0, 0x01);
  while (!(ReadIo() & 0X02));
  delay(1);
  int c = 0;
  while (!isQuality(readCard)) {
    getID();
    if (!(ReadIo() & 0X01)) {
      c = (c + 1) % 2;
      Update = true;
    }
    if (!(ReadIo() & 0X04)) {
      c = (c + 1) % 2;
      Update = true;
    }
    if (c < 2 && Update) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Last Done:");
      lcd.setCursor(3, 1);
      lcd.print("Cycles: 1000");
      Update = false;
    }
    if (c >= 2 && Update) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Due Date:");
      lcd.setCursor(3, 1);
      lcd.print("Cycles: 1001000");
      Update = false;
    }
    while (!(ReadIo() & 0X01) || !(ReadIo() & 0X04));
    delay(200);
    if (!(ReadIo() & 0X02)) {
      i = Screen_S();
      if (i == 0) {
        Screen6();
        Update = true;
      }
      while (!(ReadIo() & 0X02));
    }
  }
  lcd.clear();
}

void Screen5() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Maintenance");
  lcd.setCursor(6, 1);
  lcd.print("Done");
  delay(1000);
}

void Screen6() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Quality");
  lcd.setCursor(6, 1);
  lcd.print("Done");
  delay(1000);
}

byte Screen_S() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Save ?");
  lcd.setCursor(0, 1);
  lcd.print("-> Yes      No");
  while (!(ReadIo() & 0X02));
  int b = 0;
  while ((ReadIo() & 0X02)) {
    if (!(ReadIo() & 0X01) || !(ReadIo() & 0X04)) {
      b = (b + 1) % 2;
      if (b == 0) {
        lcd.setCursor(0, 1);
        lcd.print("->");
        lcd.setCursor(8, 1);
        lcd.print("  ");
      }
      if (b == 1) {
        lcd.setCursor(0, 1);
        lcd.print("  ");
        lcd.setCursor(8, 1);
        lcd.print("->");
      }
      while (!(ReadIo() & 0X01) || !(ReadIo() & 0X04));
    }
    delay(200);
  }
  return b;
}


byte Select_Key() {
  while (!(ReadIo() & 0X02));
  int c = 0;
  while ((ReadIo() & 0X02)) {
    if (!(ReadIo() & 0X01))
      c = (c + 1) % 2;
    if (!(ReadIo() & 0X04))
      c = (c + 1) % 2;
    if (c == 0) {
      lcd.setCursor(0, 0);
      lcd.print("->");
      lcd.setCursor(0, 1);
      lcd.print("  ");
    }
    if (c == 1) {
      lcd.setCursor(0, 0);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("->");
    }
    while (!(ReadIo() & 0X01) && (ReadIo() & 0X04));
    while ((ReadIo() & 0X01) && !(ReadIo() & 0X04));
    delay(200);
    if (!(ReadIo() & 0X01) && !(ReadIo() & 0X04)) {
      c = 2;
      break;
    }
  }
  lcd.clear();
  return c;
}
