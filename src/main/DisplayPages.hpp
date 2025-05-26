#ifndef _Display_Pages_hpp__
#define _Display_Pages_hpp__

#include "icons/thunderstorm.hpp"
#include "icons/snow.hpp"

#include "Weather.hpp"

void displayMainPage();
void displayWeatherPage();

enum Pages {
  TEST = -1,
  MAIN = 0,
  WEATHER = 1
} E_Page = MAIN ; // event page;

unsigned const short MAX_PAGES=2; 

void ChangePageLeft(){
  logger.log("Moved page left. Current page: " + String(E_Page));
  if(E_Page == 0) return;
  if(E_Page == WEATHER){
    E_Page = MAIN;
  }
}
void ChangePageRight(){
  logger.log("Moved page right. Current page: " + String(E_Page));
  if(E_Page == MAX_PAGES -1) return;
  if(E_Page == MAIN){
    E_Page = WEATHER;
  }
}


int lastMinute =0;

void DisplayPage(bool check = false){
  Logger logger;
  if(lastMinute == getMinute() && check){
    return;
  }
  lastMinute = getMinute();

  switch(E_Page){
    case TEST:

    break;
    case MAIN:
      displayMainPage();
    break;
    case WEATHER:
      displayWeatherPage();
    break;
    default:
    logger.error("Invalid page selection variable E_Page. Current selected page is invalid. Changing to default variable");
    E_Page = MAIN;
    break;
  }
  display.hibernate();

}

void displayMainPage() {
  Logger logger;
  logger.log("Updateing screen - displaying Main page with time and enviromental data");

  display.setPartialWindow(10, 10, 300, 30); 
  
  char temperature[10];
  dtostrf(getTemp(), 5, 2, temperature);
  char humidity[10];
  dtostrf(getHumidity(), 5, 2, humidity);
  char pressure[10];
  dtostrf(getPressure(), 5, 2, pressure);
 
  display.firstPage();
  do {
    display.setCursor(10, 20);  
    display.print(String("") +temperature + " C\n"+ humidity + " % " +pressure + " hPa");
  } while (display.nextPage());



  char hour[4];
  char minute[4];
  char second[4];
  dtostrf(getHour(), 2, 0, hour);
  dtostrf(getMinute(), 2, 0, minute);
  dtostrf(getSecond(), 2, 0, second);
  if(minute[0] == 32) { minute[0] = '0'; }
  if(hour[0] == 32) { hour[0] = '0'; }
  String timeStr =  String("") + hour +":"+ minute;


  setFont24();
  int x = 296/2-48-24;
  int y = 128/2 -24 ;
  // Define region for partial update (x, y, w, h)
  display.setPartialWindow(x, y, 250, 40); 

  display.firstPage();
  do {
    display.setCursor(x, y+30);
    display.print(timeStr);
  } while (display.nextPage());

  setFont9();
}


void displayWeatherPage(){

  checkWeather();

  logger.log("Updateing screen - displaying weather page");
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(0, 0, thunderstorm_bmp, 67, 67, GxEPD_BLACK);
  }
  while (display.nextPage());
  delay(2000);
}


void displayBitmapTest(){

  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(0, 0, thunderstorm_bmp, 67, 67, GxEPD_BLACK);
  }
  while (display.nextPage());
  display.hibernate();
  delay(2000);
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(0, 0, snow_bmp, 67, 67, GxEPD_BLACK);
  }
  while (display.nextPage());
  display.hibernate();
  delay(2000);

}


#endif //_Display_Pages_hpp__