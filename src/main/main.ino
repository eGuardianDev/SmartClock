#include "pins.hpp"
#include "Logger.hpp"

Logger logger;

#include "Libraries.hpp"
#include "Display.hpp"
#include "EnviromentalSensors.hpp"
#include "RTCModule.hpp"
#include "SerialCommunication.hpp"
#include "DisplayPages.hpp"

#include "Wifi.hpp"


#define DebugOn

#ifdef DebugOn
void Debugged(){
  logger.debug("Debug mode is on!");
  char temp[10];
  dtostrf(getTemp(), 5, 2, temp);
  logger.debug(String("Temp is ") + temp +  " °C"); 
 
  char hour[4];
  char minute[4];
  char second[4];
  dtostrf(getHour(), 2, 0, hour);
  dtostrf(getMinute(), 2, 0, minute);
  dtostrf(getSecond(), 2, 0, second);
  String currTime =  String("") + hour +":"+ minute;
  logger.debug(currTime);
  logger.debug(String("Current wifi state: ")+ checkWifiConnection());
 
  

  readLight();
  logger.debug(String("Light level: ") + val_light1 + " | " + val_light2);
  // checkLastUpdate();

  readButton();
  logger.debug(String("Buttons pressed: ") + val_button1 + " | " + val_button2);
}
#endif

void setup() {

  logger.init();
  
  setupBuzzer();
  delay(10);
  testBuzzer();

  setupScreen();

  setupBME();
  
  setupRTC();

  setupButtons();
  

  setupWifi();
}


int lastMinute =0;
void loop() {
  Logger logger;
  
  if(lastMinute != getMinute()){
    logger.debug("Currently Updatng Minutes");
    DisplayPage();
    lastMinute = getMinute();
    display.hibernate();
  }
  
  SerialRun();
  Debugged();
  delay(200);
}


