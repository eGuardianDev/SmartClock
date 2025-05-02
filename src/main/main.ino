#include "Logger.hpp"
#include "Libraries.hpp"
#include "Display.hpp"
#include "EnviromentalSensors.hpp"
#include "RTCModule.hpp"
Logger logger;
// 
void setup() {
  logger.init();
  setupScreen();
  setupBME();
  setupRTC();
}

int lastMinute =0;
void loop() {
  logger.debug("This is a test!");
  char temp[10];
  dtostrf(getTemp(), 5, 2, temp);
  logger.log(String("Temp is ") + temp +  " °C"); 
 
  char hour[4];
  char minute[4];
  char second[4];
  dtostrf(getHour(), 2, 0, hour);
  dtostrf(getMinute(), 2, 0, minute);
  dtostrf(getSecond(), 2, 0, second);
  String currTime =  String("Current time: ") + hour +":"+ minute;
  logger.log(currTime);
  
  if(lastMinute != getMinute()){
    updateTimePartial(currTime);
    lastMinute = getMinute();
  }
  
  // checkLastUpdate();
  delay(400);
}
