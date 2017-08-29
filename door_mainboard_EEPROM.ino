#include "eeprom_anything.h"         // We are going to read and write PICC's UIDs from EEPROM
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "pitch.h"
#include <EEPROM.h>
#include <stdio.h>
#include <DS1302.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // set LCD I2C Address


const int kCePin   = 31;  //RST
const int kIoPin   = 33;  //DAT
const int kSclkPin = 35;  //CLK
long interval = 5000;
long previousMillis = 0;
long pingTimeout = 120000;
long previousMillis_pingTimeout = 0;

boolean b2_init = false;

DS1302 rtc(kCePin, kIoPin, kSclkPin);

Time current_time;

const int chipSelect = 53;

const int keynum = 10;
String keys[keynum];
String master_keys[] = {"10:7F:C6:48"};
String captain_keys[] = {"E8:39:F8:18", "10:7F:C6:48"};

String LCD_Display[] = {
  "System Testing",
  "Beta 1.0"
};
int display_index = 0;

#define openDoor 23

boolean successRead;
String readCard;

boolean masterMode = false;

struct userkey {
  char Card[12];
};

char action[50];

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Board1 initializing in i2c slave-8");
  successRead = false;
  ledsetup();
  Wire.begin();
  Serial.println("I2C initialization done");

  Serial.println("DS1302 Read Test");
  Serial.println("-------------------");

  //set clock to normal mode
  rtc.halt(false);

  //set write protect to false when changing the time
  rtc.writeProtect(true);
  showtime();
  //RTC Model initialized

  Serial.println("lcd initializing");
  init_lcd();

  Serial.println();
  Serial.println("mainboard initialization done.");
  tone(8, NOTE_E7, 1000);//beep

  //checking storage
  readCard = "";
  Serial.println("Board1 is ready");
  cooldown();
  Serial.print("Storage count:");
  Serial.println( EEPROM.read(0));
  printMenu();
  printTime();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval && !successRead) {
    previousMillis = currentMillis;
    printTime();
    printMsg();
    backlight_control();
  }
  get_Serial();
  board_2_Serial();
  if (digitalRead(openDoor)) {
    lcd_clearLine(0);
    lcd.setCursor(0, 0);
    lcd.print("  INSIDE OPEN  ");
    granted(3000);
    cooldown();
  }
  boolean finishChecking = false;
  if (!successRead)return;   //the program will not go further while you not get a successful read

  if ((readCard.c_str()[0] == '?' && readCard.c_str()[1] == '/') || (readCard.c_str()[0] == "?" && readCard.c_str()[1] == "/")) {
    Serial.print("[Board 2]");
    readCard.remove(0, 2);
    Serial.println(readCard);
    return;
  }

  if (masterMode) {
    switch (action[0]) {

      case '0':
        addID(readCard);

        finishChecking = true;
        break;

      case '3':
        deleteID(readCard);

        finishChecking = true;
        break;
    }
  }
  for (int i = 0; master_keys[i] != EOF && !finishChecking; i++) {
    if (readCard.indexOf(master_keys[i]) >= 0) {
      lcd_clearLine(0);
      lcd.setCursor(0, 0);
      lcd.print("Access Accepted");
      Serial.println("Access Accepted");
      for (int i = 0; captain_keys[i] != EOF && !finishChecking; i++) {
        if (readCard.indexOf(captain_keys[i]) >= 0) {
          lcd_clearLine(0);
          lcd.setCursor(0, 0);
          lcd.print("Welcome Captain");
        }
      }
      granted(5000);
      finishChecking = true;
    }
  }
  if (!finishChecking) {
    boolean captain = false;
    if (findID(readCard)) {
      for (int i = 0; captain_keys[i] != EOF && !finishChecking; i++) {
        if (readCard.indexOf(captain_keys[i]) >= 0) {
          lcd_clearLine(0);
          lcd.setCursor(0, 0);
          lcd.print("Welcome Captain");
          //music();
          captain = true;
        }
      }
      if (!captain) {
        lcd_clearLine(0);
        lcd.setCursor(0, 0);
        lcd.print("Access Accepted");
        Serial.println("Access Accepted");
      }
      granted(5000);
      finishChecking = true;
    }
    else {
      lcd_clearLine(0);
      lcd.setCursor(0, 0);
      lcd.print("Access Denied");
      Serial.println("Access Denied");
      denied();
    }
  }


  cooldown();
}

void cooldown() {
  if (masterMode) {
    masterMode = false;
    printMenu();
  }
  successRead = false;
  normalModeOn();
  printTime();
}

void readUIDCard() {
  Serial.print(F("Scanned PICC's UID:"));
  Serial.println(readCard);
}


boolean findID (String id) {
  int count = EEPROM.read(0);
  userkey read_userkey;
  int readCount;
  for ( int i = 1; i < count; i = i + readCount) {
    readCount = EEPROM_readAnything(i, read_userkey);

    boolean correct = false;
    for (int j = 0; j < 11; j++) {
      if (read_userkey.Card[j] == id.c_str()[j]) {
        correct = true;
      }
      else {
        correct = false;
        break;
      }
    }
    if (correct) return true;
  }
  return false;
}
//////////////////EEPROM part/////////////////////
boolean dumpIDs () {
  int count = EEPROM.read(0);
  int readCount;
  Serial.println("            ID");
  Serial.println("===================================");
  userkey read_userkey;
  for ( int i = 1; i < count; i = i + readCount) {
    readCount = EEPROM_readAnything(i, read_userkey);

    Serial.print("Reading ");
    Serial.print(readCount);
    Serial.print(", ");
    Serial.print(read_userkey.Card);
    Serial.print(" from EEPROM. Start from ");
    Serial.println(i);
  }
}

void addID(String id) {
  if ( !findID( id ) ) {
    int count = EEPROM.read(0);
    int start = count;
    userkey temp;
    strcpy(temp.Card, id.c_str());
    int writeCount = EEPROM_writeAnything(start, temp);
    count = writeCount + start;
    EEPROM.write( 0, count);
    Serial.print("Writing ");
    Serial.print(writeCount);
    Serial.print(", ");
    Serial.print(temp.Card);
    Serial.print(" to EEPROM. Start from ");
    Serial.println(start);
    greenBlink();
  }
  else {
    Serial.println(F("Failed! The ID had already exist on EEPROM"));
    tone(8, NOTE_F7, 500);
    redBlink();
  }
}

void clearAllID() {
  int count = EEPROM.read(0);
  tone(8, NOTE_F7, 2000);
  blueBlink();
  for (int i = 0 ; i < count ; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.write(0, 1);
  Serial.println("EEPROM Clear");
}

void deleteID(String id) {
  if ( !findID( id ) ) {     // Before we delete from the EEPROM, check to see if we have this card!
    Serial.println(F("Failed! There is something wrong with ID or bad EEPROM"));
    tone(8, NOTE_F7, 500);
    redBlink();
  }
  else {
    int num = EEPROM.read(0);
    int slot = findIDSLOT(id);

    userkey null_key;
    strcpy(null_key.Card, "           ");

    int writeCount = EEPROM_writeAnything(slot, null_key);

    Serial.print("Successful delete ");
    Serial.print(id);
    Serial.println(" from EEPROM");
    deleteCard();
  }
}

int findIDSLOT(String id) {
  int count = EEPROM.read(0);
  int readCount;
  userkey read_userkey;

  for ( int i = 1; i < count; i = i + readCount) {
    readCount = EEPROM_readAnything(i, read_userkey);
    boolean correct = false;
    for (int j = 0; j < 11; j++) {
      if (read_userkey.Card[j] == id.c_str()[j]) {
        correct = true;
      }
      else {
        correct = false;
        break;
      }
    }
    if (correct) return i;
  }

}

