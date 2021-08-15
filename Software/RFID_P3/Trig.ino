void trig()
{
  if (N_Status)
  {
    MsTimer2::stop();
    digitalWrite(fout, HIGH);
    N_Status = false;
    detachInterrupt(digitalPinToInterrupt(2));
    Trig_State=true;
  }
}

void trig_L()
{
  if (Learn_Status) {
    b = millis();
    digitalWrite(fout, HIGH);
    Learn_Status = false;
    detachInterrupt(digitalPinToInterrupt(2));
    Learn_State = true;
  }
}
