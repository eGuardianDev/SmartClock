#ifndef _Display_Pages_hpp__
#define _Display_Pages_hpp__

#include "icons/clearSky.hpp"
#include "icons/fewClouds.hpp"
#include "icons/mist.hpp"
#include "icons/rain.hpp"
#include "icons/scatteredClouds.hpp"
#include "icons/showerRain.hpp"
#include "icons/snow.hpp"
#include "icons/thunderstorm.hpp"
#include "icons/brokenClouds.hpp"

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
    fullRefresh();
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

int currentPage = -1;
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
      if(weatherChanged() || E_Page != currentPage){
        displayWeatherPage();
      }
    break;
    default:
    logger.error("Invalid page selection variable E_Page. Current selected page is invalid. Changing to default variable");
    E_Page = MAIN;
    break;
  }
  currentPage = E_Page;
  display.hibernate();

}

void displayMainPage() {
  Logger logger;
  logger.log("Updateing screen - displaying Main page with time and enviromental data");

  int x1 = 5, y1 =64-24+5;
  display.setPartialWindow(x1, y1-12, 300, 30); 
  
  char temperature[10];
  dtostrf(getTemp(), 5, 2, temperature);
  char humidity[10];
  dtostrf(getHumidity(), 5, 2, humidity);
  char pressure[10];
  dtostrf(getPressure(), 5, 2, pressure);
 

  char spaced = '\0';

  if(humidity[0] == '\0' || humidity[4] == '\0') { spaced = ' ';}

  display.firstPage();
  do {
    display.setCursor(x1, y1);  
    display.print(String("") +temperature + "C\n " + spaced+ humidity + "%");
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


  setFont34();
   int x = 296/2-48-24+12-5;
   int y = 128/2-36;
  // Define region for partial update (x, y, w, h)
  display.setPartialWindow(x, y, 260, 60); 

  display.firstPage();
  do {
    display.setCursor(x, y+45);
    display.print(timeStr);
  } while (display.nextPage());

  setFont9();
}


void displayWeatherPage(){

  checkWeather();

  logger.log("Updateing screen - displaying weather page");
  display.setFullWindow();
  display.firstPage();
  int x = 15,y=25;
  do
  {
    double temp = getWeatherTemp();
    double humidty =getWeatherHumidity();
    String type = getWeatherType();
    logger.log(String("current weather: ") + String(temp) + " " + String(humidty) + " " + type);
    display.fillScreen(GxEPD_WHITE);

      if(type == "clear sky"){
        display.drawBitmap(x, y, clearSky_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "few clouds"){
        display.drawBitmap(x, y, fewClouds_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "scattered clouds" ){
        display.drawBitmap(x, y, scatteredClouds_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "broken clouds"  || type == "overcast clouds"){
        display.drawBitmap(x, y, brokenClouds_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "shower rain" ){
        display.drawBitmap(x, y, showerRain_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "rain"){
        display.drawBitmap(x, y, rain_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "thunderstorm"){
        display.drawBitmap(x, y, thunderstorm_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "light rain"){
        display.drawBitmap(x, y, showerRain_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "snow"){
        display.drawBitmap(x, y, snow_bmp, 67, 67, GxEPD_BLACK);
      }
      else if(type == "mist"){
        display.drawBitmap(x, y, mist_bmp, 67, 67, GxEPD_BLACK);
      }else{
        logger.error("Invalid weather type");
      }
    
    display.setCursor(x+80, y+24);
    display.print(city);
    display.setCursor(x+70, y+40);
    display.print(type + " " + (int)round(temp-273) + "C");
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