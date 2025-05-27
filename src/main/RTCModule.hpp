#ifndef _RTCModule_hpp__
#define _RTCModule_hpp__

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool RTCModuleReady = false;



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


void setupDate(char inString[20]) {

  byte temp1, temp2;
  
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
    // while (1) delay(10);
    RTCModuleReady = false;
    return;
  }
  if (rtc.lostPower()) {
    //reprogram to compiled time 
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  RTCModuleReady = true;
}


DateTime timeNow; 

float getYear(){
  if(!RTCModuleReady) return 0;
  timeNow = rtc.now();
  return timeNow.year();
}

float getMonth(){
  if(!RTCModuleReady) return 0;
  timeNow = rtc.now();
  return timeNow.month();
}

float getDay(){
  if(!RTCModuleReady) return 0;
  timeNow = rtc.now();
  return timeNow.day();
}

float getDOW(){
  if(!RTCModuleReady) return 0;
  timeNow = rtc.now();
  return timeNow.dayOfTheWeek();
}

float getHour(){
  if(!RTCModuleReady) return 0;
  timeNow = rtc.now();
  return timeNow.hour() ;
}
float getMinute(){
  if(!RTCModuleReady) return 0;
  timeNow = rtc.now();
  return timeNow.minute();
}
float getSecond(){
  if(!RTCModuleReady) return 0;
  timeNow = rtc.now();
  return timeNow.second();
}

void setupClock(int _hour, int _minute){
  rtc.adjust(DateTime(2000+(int)getYear(),getMonth(),getDay(),_hour,_minute,getSecond()));      
}

#endif //_RTCModule_hpp__