void isMaster_Present()
{
  if (digitalRead(wipeB) == LOW) {  // when button pressed pin should get low, button connected to ground
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.setPixelColor(1, pixels.Color(0, 255, 0));
    pixels.show();
    bool buttonState = monitorWipeButton(1000); // Give user enough time to cancel operation
    if (buttonState == true && digitalRead(wipeB) == LOW) {
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      pixels.show();
      for (uint16_t x = 0; x < 170; x = x + 1) {    //Loop end of EEPROM address
        if (EEPROM.read(x) == 0) {              //If EEPROM address 0
        }
        else {
          EEPROM.write(x, 0);       // if not write 0 to clear, it takes 3.3mS
        }
      }
     
      for (int z = 0; z < 2; z++)
      {
        pixels.setPixelColor(0, pixels.Color(255, 255, 0));
        pixels.setPixelColor(1, pixels.Color(255, 255, 0));
        pixels.show();
        delay(500);
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.setPixelColor(1, pixels.Color(0, 0, 0));
        pixels.show();
        delay(500);
      }
      //EEPROM Successfully Formated
    }
    else;
    //Formatting Cancelled// Show some feedback that the wipe button did not pressed for 15 seconds
  }

  if (EEPROM.read(1) != 143) {
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Scan");
    lcd.setCursor(3, 1);
    lcd.print("Master Card");
    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.setPixelColor(1, pixels.Color(255, 255, 255));
    pixels.show();
    do {
      successRead = getID();            // sets successRead to 1 when we get read from reader otherwise 0
    } while (!successRead);                  // Program will not go further while you not get a successful read
    successRead = false;
    for ( uint8_t j = 0; j < 4; j++ ) {        // Loop 4 times
      EEPROM.write( Master + j, readCard[j] );  // Write scanned PICC's UID to EEPROM, start from address 3
    }
    EEPROM.write(1, 143);                  // Write to EEPROM we defined Master Card.
    EEPROM.write(2, 1);
    for (int z = 0; z < 2; z++)
    {
      pixels.setPixelColor(2, pixels.Color(0, 0, 255));
      pixels.setPixelColor(3, pixels.Color(0, 0, 255));
      pixels.show();
      delay(500);
      pixels.setPixelColor(2, pixels.Color(255, 255, 255));
      pixels.setPixelColor(3, pixels.Color(255, 255, 255));
      pixels.show();
      delay(500);
    }
    //Master Card Defined
  }
  readCard[0] = 0;
}

void isProduction_Present()
{
  if (EEPROM.read(3) != 143) {
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Scan");
    lcd.setCursor(3, 1);
    lcd.print("Production Card");
    do {
      successRead = getID();            // sets successRead to 1 when we get read from reader otherwise 0
    } while (!successRead);                  // Program will not go further while you not get a successful read
    successRead = false;
    for ( uint8_t j = 0; j < 4; j++ ) {        // Loop 4 times
      EEPROM.write( Production + j, readCard[j] );  // Write scanned PICC's UID to EEPROM, start from address 3
    }
    EEPROM.write(3, 143);                  // Write to EEPROM we defined Master Card.
    EEPROM.write(4, 1);
    for (int z = 0; z < 2; z++)
    {
      pixels.setPixelColor(2, pixels.Color(255, 255, 0));
      pixels.setPixelColor(3, pixels.Color(255, 255, 0));
      pixels.show();
      delay(200);
      pixels.setPixelColor(2, pixels.Color(255, 255, 255));
      pixels.setPixelColor(3, pixels.Color(255, 255, 255));
      pixels.show();
      delay(200);
    }
  }
  readCard[0] = 0;
}

void isMaintenance_Present()
{
  if (EEPROM.read(5) != 143) {
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Scan");
    lcd.setCursor(3, 1);
    lcd.print("Maintenance Card");
    do {
      successRead = getID();            // sets successRead to 1 when we get read from reader otherwise 0
    } while (!successRead);                  // Program will not go further while you not get a successful read
    successRead = false;
    for ( uint8_t j = 0; j < 4; j++ ) {        // Loop 4 times
      EEPROM.write( Maintenance + j, readCard[j] );  // Write scanned PICC's UID to EEPROM, start from address 3
    }
    EEPROM.write(5, 143);                  // Write to EEPROM we defined Master Card.
    EEPROM.write(6, 1);
    for (int z = 0; z < 2; z++)
    {
      pixels.setPixelColor(2, pixels.Color(128, 0, 128));
      pixels.setPixelColor(3, pixels.Color(128, 0, 128));
      pixels.show();
      delay(200);
      pixels.setPixelColor(2, pixels.Color(255, 255, 255));
      pixels.setPixelColor(3, pixels.Color(255, 255, 255));
      pixels.show();
      delay(200);
    }
  }
  readCard[0] = 0;
}

void isQuality_Present()
{
  if (EEPROM.read(7) != 143) {
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Scan");
    lcd.setCursor(3, 1);
    lcd.print("Quality Card");
    do {
      successRead = getID();            // sets successRead to 1 when we get read from reader otherwise 0
    } while (!successRead);                  // Program will not go further while you not get a successful read
    successRead = false;
    for ( uint8_t j = 0; j < 4; j++ ) {        // Loop 4 times
      EEPROM.write( Quality + j, readCard[j] );  // Write scanned PICC's UID to EEPROM, start from address 3
    }
    EEPROM.write(7, 143);                  // Write to EEPROM we defined Master Card.
    EEPROM.write(8, 1);
    for (int z = 0; z < 2; z++)
    {
      pixels.setPixelColor(2, pixels.Color(255, 165, 0));
      pixels.setPixelColor(3, pixels.Color(255, 165, 0));
      pixels.show();
      delay(200);
      pixels.setPixelColor(2, pixels.Color(255, 255, 255));
      pixels.setPixelColor(3, pixels.Color(255, 255, 255));
      pixels.show();
      delay(200);
    }
  }
  readCard[0] = 0;
}

void Add_Card(int c) {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Scan New");
  if (c == 0) {
    lcd.setCursor(3, 1);
    lcd.print("Master Card");
  }
  if (c == 1) {
    lcd.setCursor(1, 1);
    lcd.print("Production Card");
  }
  if (c == 2) {
    lcd.setCursor(3, 1);
    lcd.print("Quality Card");
  }
  if (c == 3) {
    lcd.setCursor(0, 1);
    lcd.print("Maintenance Card");
  }
  setrow(0, 3, 0x01);
  setrow(0, 2, 0x77);
  setrow(0, 1, 0x3D);
  setrow(0, 0, 0x3D);
  while (1) {
    successRead = getID();
    if (successRead) {
      successRead = false;
      writeID(readCard, c);
      readCard[0] = 0;
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Successfully");
      lcd.setCursor(5, 1);
      lcd.print("Added");
      break;
    }
  }
}
void Delete_Card(int c) {
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Scan");
  if (c == 0) {
    lcd.setCursor(3, 1);
    lcd.print("Master Card");
  }
  if (c == 1) {
    lcd.setCursor(1, 1);
    lcd.print("Production Card");
  }
  if (c == 2) {
    lcd.setCursor(3, 1);
    lcd.print("Quality Card");
  }
  if (c == 3) {
    lcd.setCursor(0, 1);
    lcd.print("Maintenance Card");
  }
  setrow(0, 3, 0x01);
  setrow(0, 2, 0x77);
  setrow(0, 1, 0x3D);
  setrow(0, 0, 0x3D);
  while (1) {
    successRead = getID();
    if (successRead) {
      successRead = false;
      deleteID(readCard, c);
      readCard[0] = 0;
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Successfully");
      lcd.setCursor(4, 1);
      lcd.print("Deleted");
      break;
    }
  }
}

uint8_t getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  // There are Mifare PICCs which have 4 byte or 7 byte UID care if you use 7 byte PICC
  // I think we should assume every PICC as they have 4 byte UID
  // Until we support 7 byte PICCs
  //Scanned Card UID:
  for ( uint8_t i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
  }
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}

void ShowReaderDetails() {
  // Get the MFRC522 software version
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);


  if ((v == 0x00) || (v == 0xFF)) {
    //WARNING: Communication failure, is the MFRC522 properly connected?
    //SYSTEM HALTED: Check connections.
    // Visualize system is halted

    while (true); // do not go further
  }
}
//////////////////////////////////////// Normal Mode Led  ///////////////////////////////////

//////////////////////////////////////// Read an ID from EEPROM //////////////////////////////
void readID( uint8_t number ) {
  uint8_t start = (number * 4 ) + 6;    // Figure out starting position
  for ( uint8_t i = 0; i < 4; i++ ) {     // Loop 4 times to get the 4 Bytes
    storedCard[i] = EEPROM.read(start + i);   // Assign values read from EEPROM to array
  }
}

///////////////////////////////////////// Add ID to EEPROM   ///////////////////////////////////
void writeID( byte a[], int c) {
  if ( !findID( a , c)) {     // Before we write to the EEPROM, check to see if we have seen this card before!
    int num = EEPROM.read((c + 1) * 2);
    if (num < 10)
    {
      uint8_t start = ( num * 4 ) + c * 40 + 10; // Figure out where the next slot starts
      num++;                // Increment the counter by one
      EEPROM.write( (c + 1) * 2, num );     // Write the new count to the counter
      for ( uint8_t j = 0; j < 4; j++ ) {   // Loop 4 times
        EEPROM.write( start + j, a[j] );  // Write the array values to EEPROM in the right position
      }
    }
    if (num == 10) {
      uint8_t start = c * 40 + 10; // Figure out where the next slot starts
      for ( uint8_t j = 0; j < 36; j++ ) {         // Loop the card shift times
        EEPROM.write( start + j, EEPROM.read(start + 4 + j));   // Shift the array values to 4 places earlier in the EEPROM
      }
      for ( uint8_t j = 0; j < 4; j++ ) {   // Loop 4 times
        EEPROM.write( start + j + 36, a[j] );  // Write the array values to EEPROM in the right position
      }
    }
    for (int z = 0; z < 2; z++)
    {
      pixels.setPixelColor(2, pixels.Color(0, 255, 0));
      pixels.setPixelColor(3, pixels.Color(0, 255, 0));
      pixels.show();
      delay(250);
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
      pixels.show();
      delay(250);
    }
    //Succesfully added ID record to EEPROM
  }
  else {

  }
}

///////////////////////////////////////// Remove ID from EEPROM   ///////////////////////////////////
void deleteID( byte a[], int c) {
  if ( !findID( a , c) ) {     // Before we delete from the EEPROM, check to see if we have this card!

    //Failed! There is something wrong with ID or bad EEPROM
  }
  else {
    int num = EEPROM.read((c + 1) * 2);
    if (num == 0) {
      Add_Card(c);
    }
    else {
      uint8_t slot;       // Figure out the slot number of the card
      uint8_t start;      // = ( num * 4 ) + 6; // Figure out where the next slot starts
      uint8_t looping;    // The number of times the loop repeats
      uint8_t j;
      slot = findIDSLOT(a, c);   // Figure out the slot number of the card to delete
      start = (slot * 4) + c * 40 + 10;
      looping = (num - slot) * 4 - 4;
      num--;      // Decrement the counter by one
      EEPROM.write( (c + 1) * 2, num );   // Write the new count to the counter
      for ( uint8_t k = 0; k < 4; k++ ) {         // Shifting loop
        EEPROM.write( start + j + k, 0);
      }
      for ( j = 0; j < looping; j++ ) {         // Loop the card shift times
        EEPROM.write( start + j, EEPROM.read(start + 4 + j));   // Shift the array values to 4 places earlier in the EEPROM
      }
      for (int z = 0; z < 2; z++)
      {
        pixels.setPixelColor(2, pixels.Color(255, 0, 0));
        pixels.setPixelColor(3, pixels.Color(255, 0, 0));
        pixels.show();
        delay(500);
        pixels.setPixelColor(2, pixels.Color(0, 0, 0));
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.show();
        delay(500);
      }
    }
    //Succesfully removed ID record from EEPROM

  }

}
///////////////////////////////////////// Check Bytes   ///////////////////////////////////
bool checkTwo ( byte a[], byte b[] ) {
  for ( uint8_t k = 0; k < 4; k++ ) {   // Loop 4 times
    if ( a[k] != b[k] ) {     // IF a != b then false, because: one fails, all fail
      return false;
    }
  }
  return true;
}

///////////////////////////////////////// Find Slot   ///////////////////////////////////
uint8_t findIDSLOT( byte find[], int c) {
  uint8_t count = EEPROM.read((c + 1) * 2);       // Read the first Byte of EEPROM that
  int Start = c * 40 + 10;
  for ( uint8_t i = 0; i < count; i++ ) { // Loop once for each EEPROM entry
    uint8_t start = c * 40 + 10 + i * 4;  // Figure out starting position
    for ( uint8_t i = 0; i < 4; i++ ) {     // Loop 4 times to get the 4 Bytes
      storedCard[i] = EEPROM.read(start + i);   // Assign values read from EEPROM to array
    }
    if ( checkTwo( find, storedCard ) ) {   // Check to see if the storedCard read from EEPROM
      // is the same as the find[] ID card passed
      return i;         // The slot number of the card
    }
  }
}

///////////////////////////////////////// Find ID From EEPROM   ///////////////////////////////////
bool findID( byte find1[], int c ) {
  uint8_t count = EEPROM.read((c + 1) * 2);       // Read the first Byte of EEPROM that
  int Start = c * 40 + 10;
  for ( uint8_t i = 0; i < count; i++ ) { // Loop once for each EEPROM entry
    uint8_t start = c * 40 + 10 + i * 4;  // Figure out starting position
    for ( uint8_t i = 0; i < 4; i++ ) {     // Loop 4 times to get the 4 Bytes
      storedCard[i] = EEPROM.read(start + i);   // Assign values read from EEPROM to array
    }
    if ( checkTwo( find1, storedCard ) ) {   // Check to see if the storedCard read from EEPROM
      // is the same as the find[] ID card passed
      return true;         // The slot number of the card
    }
  }
  return false;
}

////////////////////// Check readCard IF is masterCard   ///////////////////////////////////
// Check to see if the ID passed is the master programing card
bool isMaster( byte test[] ) {
  uint8_t count = EEPROM.read(2);     // Read the first Byte of EEPROM that
  for ( uint8_t i = 1; i <= count; i++ ) {    // Loop once for each EEPROM entry
    readID(i);          // Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( test, storedCard ) ) {   // Check to see if the storedCard read from EEPROM
      pixels.setPixelColor(2, pixels.Color(0, 0, 255));
      pixels.setPixelColor(3, pixels.Color(0, 0, 255));
      pixels.show();
      return true;
    }
    else {    // If not, return false
    }
  }
  return false;
}

bool isProduction( byte test[] ) {
  uint8_t count = EEPROM.read(4);     // Read the first Byte of EEPROM that
  for ( uint8_t i = 1; i <= count; i++ ) {    // Loop once for each EEPROM entry
    readID(i + 10);          // Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( test, storedCard ) ) {   // Check to see if the storedCard read from EEPROM
      pixels.setPixelColor(2, pixels.Color(255, 255, 0));
      pixels.setPixelColor(3, pixels.Color(255, 255, 0));
      pixels.show();
      return true;
    }
    else {    // If not, return false
    }
  }
  return false;
}

bool isMaintenance( byte test[] ) {
  uint8_t count = EEPROM.read(6);     // Read the first Byte of EEPROM that
  for ( uint8_t i = 1; i <= count; i++ ) {    // Loop once for each EEPROM entry
    readID(i + 20);          // Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( test, storedCard ) ) {   // Check to see if the storedCard read from EEPROM
      pixels.setPixelColor(2, pixels.Color(128, 0, 128));
      pixels.setPixelColor(3, pixels.Color(128, 0, 128));
      pixels.show();
      return true;
    }
    else {    // If not, return false
    }
  }
  return false;
}

bool isQuality( byte test[] ) {
  uint8_t count = EEPROM.read(8);     // Read the first Byte of EEPROM that
  for ( uint8_t i = 1; i <= count; i++ ) {    // Loop once for each EEPROM entry
    readID(i + 30);          // Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( test, storedCard ) ) {   // Check to see if the storedCard read from EEPROM
      pixels.setPixelColor(2, pixels.Color(255, 165, 0));
      pixels.setPixelColor(3, pixels.Color(255, 165, 0));
      pixels.show();
      return true;
    }
    else {    // If not, return false
    }
  }
  return false;
}
bool monitorWipeButton(uint32_t interval) {
  uint32_t now = (uint32_t)millis();
  while ((uint32_t)millis() - now < interval)  {
    // check on every half a second
    if (((uint32_t)millis() % 500) == 0) {
      if (digitalRead(wipeB) != LOW)
        return false;
    }
  }
  return true;
}
