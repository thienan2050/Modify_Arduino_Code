void Reverse()
{
  delay(100);
  if (digitalRead(rin) == 0 && digitalRead(fin) == 0) {
    digitalWrite(fout, LOW);
    delay(50);
    if (Rev_Mode && SC_Counter > 0 && !NG_Status)
      SC_Counter--;
    while (digitalRead(rin) == 0 && digitalRead(fin) == 0 );
    NG_Status = false;
    digitalWrite(fout, HIGH);
    lcd.clear();
    lcd.print("CURRENT / BATCH:");
    lcd.setCursor(0, 1);
    lcd.print(SC_Counter);
    lcd.print("/");
    lcd.print(Screw_Count);
  }
}
