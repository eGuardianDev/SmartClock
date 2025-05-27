#define DebugOn


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
#include "Weather.hpp"
#include "Alarm.hpp"

#include "Logic.hpp"

#include "WebPage.hpp"


#ifdef DebugOn
void Debugged(){
  logger.log("Debug mode is on!");
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
  
  logger.debug(WiFi.localIP().toString());

  logger.debug(String("Light level: ") + val_light1 + " | " + val_light2);

  logger.debug(String("Buttons pressed: ") + val_button1 + " | " + val_button2);
}
#endif

void setup() {

  logger.init();
  
  setupBuzzer();
  delay(10);
  testBuzzer();

  setupScreen();

  // displayBitmapTest();

  setupBME();
  
  setupRTC();

  setupButtons();
  


  if(setupWifi()){
    setupWebServer();
    setup_mDNS();
  }

  setupWeather();
  setupAlarm();

  E_State = IDLE;
}


void loop() {
  Logger logger;
  
  buttonCheck();
  SerialRun();

  readButton();
  readLight();

  DisplayPage(true);
  loopServer();
  checkAlarm();

  #ifdef DebugOn
    Debugged();  
  #endif
  delay(100);
}


