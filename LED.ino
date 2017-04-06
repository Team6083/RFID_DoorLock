#define redLed 26    // Set Led Pins
#define greenLed 30
#define blueLed 27

#define relay 36     // Set Relay Pin
#define wipeB 34     // Button pin for WipeMode

//#define COMMON_ANODE

#ifdef COMMON_ANODE
#define LED_ON LOW
#define LED_OFF HIGH
#else
#define LED_ON HIGH
#define LED_OFF LOW
#endif


void ledsetup(){
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(openDoor, INPUT);
  blueSolid();
}


//////////////////////////////////////// Normal Mode Led  ///////////////////////////////////
void blueSolid () {
  digitalWrite(blueLed, LED_ON);   // Blue LED ON and ready to read card
  digitalWrite(redLed, LED_OFF);  // Make sure Red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure Green LED is off
}

/////////////////////////////////////////  Access Granted    ///////////////////////////////////
void granted (int setDelay) {
  tone(8, NOTE_E7, 500);
  digitalWrite(blueLed, LED_OFF);   // Turn off blue LED
  digitalWrite(redLed, LED_OFF);  // Turn off red LED
  digitalWrite(greenLed, LED_ON);   // Turn on green LED
  digitalWrite(relay, LOW);     // Unlock door!
  delay(setDelay);          // Hold door lock open for given seconds
  digitalWrite(relay, HIGH);    // Relock door
  delay(1000);            // Hold green LED on for a second
}

void redSolid () {
  digitalWrite(blueLed, LED_OFF);   // Turn off blue LED
  digitalWrite(redLed, LED_ON);  // Turn on red LED
  digitalWrite(greenLed, LED_OFF);   // Turn off green LED
  delay(2000);
}

void redBlink() {
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
}

void deleteCard() {
  tone(8, NOTE_F7, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  noTone(8);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  tone(8, NOTE_F7, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  noTone(8);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  tone(8, NOTE_F7, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
}

void blueBlink() {
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
}

void greenBlink() {
  tone(8, NOTE_E7, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is on
  delay(200);
  noTone(8);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
  tone(8, NOTE_E7, 200);
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  noTone(8);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
  tone(8, NOTE_E7, 200);
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  delay(200);
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  delay(200);
}

void denied() {
  tone(8, 523, 200);
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(relay, HIGH);    // Make sure Door is Locked
  delay(200);
  noTone(8);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  tone(8, 523, 200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  delay(200);
  noTone(8);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  tone(8, 523, 200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  delay(200);
  tone(8, 523, 1000);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  delay(200);
  delay(3800);
}

void cycleLeds() {
  tone(8, NOTE_E7, 200);
  digitalWrite(redLed, LED_OFF);   // Make sure red LED is off
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  noTone(8);
  tone(8, NOTE_B0, 200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
    digitalWrite(redLed, LED_OFF);   // Make sure red LED is off
  digitalWrite(greenLed, LED_ON);   // Make sure green LED is on
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
  tone(8, NOTE_B0, 200);
  digitalWrite(redLed, LED_OFF);  // Make sure red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(blueLed, LED_ON);  // Make sure blue LED is on
  delay(200);
  digitalWrite(redLed, LED_ON);   // Make sure red LED is on
  digitalWrite(greenLed, LED_OFF);  // Make sure green LED is off
  digitalWrite(blueLed, LED_OFF);   // Make sure blue LED is off
  delay(200);
}

//////////////////////////////////////// Normal Mode Led  ///////////////////////////////////
void normalModeOn () {
  digitalWrite(blueLed, LED_ON);   // Blue LED ON and ready to read card
  digitalWrite(redLed, LED_OFF);  // Make sure Red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure Green LED is off
  digitalWrite(relay, HIGH);    // Make sure Door is Locked
}
//////////////////////////////////////// Master Mode Led    /////////////////////////////////
void MasterCardMode_addcard (){
  digitalWrite(blueLed, LED_ON);   // Blue LED ON and ready to read card
  digitalWrite(redLed, LED_OFF);  // Make sure Red LED is off
  digitalWrite(greenLed, LED_ON);  // Make sure Green LED is off
  digitalWrite(relay, HIGH);    // Make sure Door is Locked
}

void MasterCardMode_removecard (){
  digitalWrite(blueLed, LED_ON);   // Blue LED ON and ready to read card
  digitalWrite(redLed, LED_ON);  // Make sure Red LED is off
  digitalWrite(greenLed, LED_OFF);  // Make sure Green LED is off
  digitalWrite(relay, HIGH);    // Make sure Door is Locked
}
