int backightmode = 0; //0 for auto; 1 for manual

void init_lcd() {
  lcd.begin(16, 2);
  // lcd blink 3 times
  for (int i = 0; i < 3; i++) {
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

void lcd_clearLine(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }
}

void lcd_granted() {

}

void printMsg() {
  if (display_index > 1) display_index = 0;
  lcd_clearLine(0);
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print(LCD_Display[display_index]);
  display_index++;
}

void printTime() {
  lcd_clearLine(1);
  current_time = rtc.getTime();
  if (current_time.year == 2011) {
    printTime();
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print(current_time.year);
  lcd.print("/");
  lcd.print(current_time.mon);
  lcd.print("/");
  lcd.print(current_time.date);
  lcd.print(" ");
  if (current_time.hour < 10) {
    lcd.print("0");
  }
  lcd.print(current_time.hour);
  lcd.print(":");
  if (current_time.min < 10) {
    lcd.print("0");
  }
  lcd.print(current_time.min);
}

void backlight_control() {
  if (backightmode == 1) {
    return;
  }
  Time t = rtc.getTime();
  if (t.year == 2011) {
    return;
  }

  if (t.hour >= 21) {
    lcd.noBacklight();
  }
  else if (t.hour > 8 && t.hour < 21) {
    lcd.backlight();
  }
}

