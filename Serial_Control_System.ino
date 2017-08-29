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
  Serial.println(F("S) Set time"));
  Serial.println();
}

void get_Serial() {
  int index = 0;
  if (Serial.available() > 0) {

    while (Serial.available() > 0) {
      delay(100);
      action[index] = Serial.read();
      index++;
    }
    Serial.println();
    Serial.print("Serial reciving data....   ");
    Serial.println(action);
    switch (action[0]) {
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
        backightmode = 0;
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
        tone(8, NOTE_A6, 500);
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

      case 'S':
        set_time();
        break;

    }
  }
}

void showtime() {
  current_time = rtc.getTime();
  char buf[50];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           current_time.year, current_time.mon, current_time.date,
           current_time.hour, current_time.min, current_time.sec);
  Serial.println(buf);
}

void set_time() {
  int data[6];
  String temp(action);
  temp = temp.substring(1, temp.length() - 1);
  Serial.println(temp);
  int data_index = 0;
  for (int i = 0, prev = 0; i <= temp.length() && data_index < 6; i++) {
    if (temp.charAt(i) == ',' || temp.charAt(i) == "," || temp.charAt(i) == ";" || temp.charAt(i) == ';') {
      String sub = temp.substring(prev, i);
      data[data_index] = sub.toInt();
      data_index++;
      prev = i + 1;
    }
  }
  change_time(data[0],data[1],data[2],data[3],data[4],data[5],"MON");
}

void change_time(int year, int mon, int date, int hour, int min, int sec, int dow) {
  rtc.writeProtect(false);
  rtc.setDate(date, mon, year);
  rtc.setTime(hour, min, sec);
  rtc.setDOW(dow);
}

