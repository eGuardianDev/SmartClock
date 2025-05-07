#ifndef _RTCModule_hpp__
#define _RTCModule_hpp__

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool RTCModuleReady = false;

int incomingByte = 0; // for incoming serial data


byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;


void setupClock(){
  rtc.adjust(DateTime(2000+(int)year,month,date,hour,minute,second));

        
}

void getDateStuff(byte& year, byte& month, byte& date, byte& dOW,
                  byte& hour, byte& minute, byte& second) {
    // Call this if you notice something coming in on
    // the serial port. The stuff coming in should be in
    // the order YYMMDDwHHMMSS, with an 'x' at the end.
    bool gotString = true;
    char inChar;
    byte temp1, temp2;
    char inString[20];
    
    byte j=0;
    if(Serial.available()){

    while (Serial.available()) {
        inChar = Serial.read();
        inString[j] = inChar;
        j += 1;
        if (inChar == 'x') {
            gotString = true;
        }
    }
    }else{
      return;
    }

    Serial.println(inString);
    // Read year first
    temp1 = (byte)inString[0] -48;
    temp2 = (byte)inString[1] -48;
    year = temp1*10 + temp2;
    // now month
    temp1 = (byte)inString[2] -48;
    temp2 = (byte)inString[3] -48;
    month = temp1*10 + temp2;
    // now date
    temp1 = (byte)inString[4] -48;
    temp2 = (byte)inString[5] -48;
    date = temp1*10 + temp2;
    // now Day of Week
    dOW = (byte)inString[6] - 48;
    // now hour
    temp1 = (byte)inString[7] -48;
    temp2 = (byte)inString[8] -48;
    hour = temp1*10 + temp2;
    // now minute
    temp1 = (byte)inString[9] -48;
    temp2 = (byte)inString[10] -48;
    minute = temp1*10 + temp2;
    // now second
    temp1 = (byte)inString[11] -48;
    temp2 = (byte)inString[12] -48;
    second = temp1*10 + temp2;


    Serial.println("Setting to: "+ String(year) + "/" + String(month) + "/" + String(date) + " " + String(hour) + ":" + String(minute) + ":" + String(second));
    setupClock();
}



void setupRTC () {
  Logger logger;

  if (! rtc.begin()) {
    logger.error("Couldn't find RTC");
    while (1) delay(10);
  }
  if (rtc.lostPower()) {
    //reprogram to compiled time 
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  RTCModuleReady = true;
}

void checkForUpdates(){
  getDateStuff(year, month, date, dOW, hour, minute, second);
}

float getYear(){
  DateTime now = rtc.now();
  return now.year();
}

float getMonth(){
  DateTime now = rtc.now();
  return now.month();
}

float getDay(){
  DateTime now = rtc.now();
  return now.day();
}

float getDOW(){
  DateTime now = rtc.now();
  return now.dayOfTheWeek();
}

float getHour(){
  DateTime now = rtc.now();
  return now.hour() ;
}
float getMinute(){
  DateTime now = rtc.now();
  return now.minute();
}
float getSecond(){
  DateTime now = rtc.now();
  return now.second();
}

#endif //_RTCModule_hpp__