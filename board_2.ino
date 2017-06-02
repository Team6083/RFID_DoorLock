void board_2_Serial(){
  String temp = "";
  bool ifRead = false;
  
  while(Serial1.available() > 0){
    if(ifRead==false){
      //Serial.println("Serial 1 reciving data....   ");
      delay(50);
    }
    temp += (char)Serial1.read();
    ifRead = true;
  }

  if(ifRead){
    /*Serial.print("[Serial 1] ");
    Serial.println(temp); */
    if(temp.charAt(0) == '#'){
      readCard = temp.substring(1,12);
      successRead=true;
      readUIDCard();
    }
  }
  
}







/////////////////////////////////// Recive from I2C ///////////////////////////////////

void receiveEvent(int howMany){
  readCard = "";
  while(Wire.available()){
    readCard += (char)Wire.read();
  }
  delay(500);
  successRead = true;
  readUIDCard();
}

