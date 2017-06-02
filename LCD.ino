int backightmode = 0; //0 for auto; 1 for manual

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
  Time t = rtc.getTime();
  if(t.year == 2011){
    printTime();
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print(t.year);
  lcd.print("-");
  lcd.print(t.mon);
  lcd.print("-");
  lcd.print(t.date);
  lcd.print(" ");
  if(t.hour<10){
    lcd.print("0");
  }
  lcd.print(t.hour);
  lcd.print(":");
  if(t.min<10){
    lcd.print("0");
  }
  lcd.print(t.min);
  /*if(t.hour>12){
    lcd.print("PM");
  }
  else{
    lcd.print("AM");
  }*/
}

void backlight_control(){
  if(backightmode==1){
    return;
  }
  Time t = rtc.getTime();
  if(t.year == 2011){
    return;
  }

  if(t.hour>=21){
    lcd.noBacklight();
  }
  else if(t.hour>8&&t.hour<21){
    lcd.backlight();
  }
}

