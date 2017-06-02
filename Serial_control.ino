void printMenu() {
  Serial.println("------------------------------------------------------");
  Serial.println(F("////////////////////////////////////////////"));
  Serial.println(F("// Programming Menu                       //"));
  Serial.println(F("////////////////////////////////////////////"));
  Serial.println();
  Serial.println(F("0) Add a PICC"));
  Serial.println(F("1) Show all PICCs"));
  Serial.println(F("2) "));
  Serial.println(F("3) Remove a PICC"));
  Serial.println(F("4) "));
  Serial.println();
  Serial.println(F("C) Turn on the backlight"));
  Serial.println(F("c) Turn off the backlight"));
  Serial.println(F("6) Change Master Tag//not finished yet"));
  Serial.println(F("X) Delete All Tags /not implemented"));
  Serial.println(F("O) Open the door"));
  Serial.println(F("T) Get time"));
  Serial.println();
}

void get_Serial(){
  if(Serial.available() > 0){
    action = Serial.read();
    Serial.println();
    Serial.print("Serial reciving data....   ");
    Serial.println(action);
    switch(action){
      case '0':
        masterMode = true;
        cycleLeds();
        MasterCardMode_addcard();
        Serial.println(F("Scan a PICC to ADD"));
        Serial.println(F("Enter 'E' to Exit"));
        Serial.println(F("-----------------------------"));
      break;
      
      case '1':
        dumpIDs();
        Serial.println();
        delay(1000);
        printMenu();
      break;

      case 'C':
        lcd.backlight();
        backightmode = 1;
      break;
      case 'A':
        backightmode=0;
      break;
      
      case 'c':
        lcd.noBacklight();
        backightmode = 1;
      break;
      
      case 'X':
        clearAllID();
        printMenu();
      break;
      
      case 'E':
        Serial.println("Exiting...");
        tone(8,NOTE_A6,500);
        delay(1000);
        cooldown();
      break;
      
      case '3':
        masterMode = true;
        cycleLeds();
        MasterCardMode_removecard();
        Serial.println(F("Scan a PICC to REMOVE"));
        Serial.println(F("Enter 'E' to Exit"));
        Serial.println(F("-----------------------------"));
      break;
      case'O':
        lcd_clearLine(0);
        lcd.setCursor(0, 0);
        lcd.print("  INSIDE OPEN  ");
        granted(3000);
        cooldown();
      break;

      case'T':
          showtime();
      break;
      
      case 'R':
        Serial1.begin(9600);
      break;
    }
  }
}

void showtime(){
  Time t = rtc.getTime();
          char buf[50];
          snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
                  t.year, t.mon, t.date,
                  t.hour, t.min, t.sec);
          Serial.println(buf); 
}

