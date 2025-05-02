#ifndef _RTCModule_hpp__
#define _RTCModule_hpp__

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool RTCModuleReady = false;
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