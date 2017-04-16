void init_lcd(){
  lcd.begin(16, 2);
  // lcd blink 3 times
  for(int i = 0; i < 3; i++) {
    lcd.backlight(); // open backlight
    delay(250);
    lcd.noBacklight(); // close backloght
    delay(250);
  }

  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setup Complete");
}

void lcd_clearLine(int line){
  lcd.setCursor(0, line);
  for(int i=0;i<16;i++){
    lcd.print(" ");
  }
}

void lcd_granted(){

}

void printTime(){
  Time t = rtc.time();
  if(t.yr == 2011){
    printTime();
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print(t.yr);
  lcd.print("-");
  lcd.print(t.mon);
  lcd.print("-");
  lcd.print(t.date);
  lcd.print(" ");
  lcd.print(t.hr);
  lcd.print(":");
  if(t.min<10){
    lcd.print("0");
    lcd.print(t.min);
  }
  else{
    lcd.print(t.min);
  }
  /*if(t.hr>12){
    lcd.print("PM");
  }
  else{
    lcd.print("AM");
  }*/
}

void backlight_control(){
  Time t = rtc.time();
  if(t.yr == 2011){
    return;
  }

  if(t.hr>=21){
    lcd.backlight();
  }
  else if(t.hr>8&&t.hr<21){
    lcd.noBacklight();
  }
}

