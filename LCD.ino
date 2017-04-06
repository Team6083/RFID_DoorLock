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
  lcd.setCursor(0, 1);
  lcd.print(t.yr);
  lcd.print("-");
  lcd.print(t.mon);
  lcd.print("-");
  lcd.print(t.date);
  lcd.print(" ");
  lcd.print(t.hr);
  lcd.print(":");
  lcd.print(t.min);
  /*if(t.hr>12){
    lcd.print("PM");
  }
  else{
    lcd.print("AM");
  }*/
}

