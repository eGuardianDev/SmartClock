#ifndef _SerialCommunication_hpp__
#define _SerialCommunication_hpp__

int SerialRun(){
  Logger logger;
  
  int incomingByte = 0;
  
  bool gotString = true;
  char mode;
  byte temp1, temp2;
  char inString[20];
  
  byte j=0;
  if(!Serial.available()){
    return false;
  }
  while (Serial.available()) {
      mode = Serial.read();
      inString[j] = mode;
      j += 1;
      if(j == 0){
        switch (mode){
          case 'r':
          // the order YYMMDDwHHMMSS, with an 'x' at the end.
          setupDate(inString);
          break;
          default:
            logger.error(String("Serial buffer first character not recognized"));
            
        }
      }
  }
  Serial.println(String("Recieved data from serial: ") + inString);

}


#endif // _SerialCommunication_hpp__