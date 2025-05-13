#include "pins.hpp"
#include "Logger.hpp"
#include "Libraries.hpp"
#include "Display.hpp"
#include "EnviromentalSensors.hpp"
#include "RTCModule.hpp"
Logger logger;
// 
void setup() {
  logger.init();


  setupBuzzer();
  
  delay(100);
  testBuzzer();
  

  setupScreen();

  setupBME();
  setupRTC();
  setupButtons();
  
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
  if(minute[0] == 32) { minute[0] = '0'; }
  if(hour[0] == 32) { hour[0] = '0'; }
  String currTime =  String("") + hour +":"+ minute;
  logger.log(currTime);
  
  if(lastMinute != getMinute()){
    updateTimePartial(currTime);
    updateTempPartial();
    lastMinute = getMinute();
    display.hibernate();
  }
  
  checkForUpdates();

  readLight();
  logger.log(String("Light level: ") + val_light1 + " | " + val_light2);
  // checkLastUpdate();

  readButton();
  logger.log(String("Buttons pressed: ") + val_button1 + " | " + val_button2);
  delay(400);
}
