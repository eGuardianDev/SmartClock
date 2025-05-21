#ifndef _Display_Pages_hpp__
#define _Display_Pages_hpp__

void updateMainPage();

enum Pages {
  TEST = -1,
  MAIN = 0,
  WEATHER = 1
} E_Page = MAIN ; // event page;

void DisplayPage(){
  Logger logger;

  switch(E_Page){
    case TEST:

    break;
    case MAIN:
      updateMainPage();
    break;
    case WEATHER:

    break;
    default:
    logger.error("Invalid page selection variable E_Page. Current selected page is invalid. Changing to default variable");
    E_Page = MAIN;
    break;
  }

}

void updateMainPage() {
  Logger logger;
  logger.debug("Updateing screen - displaying Main page with time and enviromental data");

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
    display.print(String("") +temperature + " C"+ humidity + " % " +pressure + " hPa");
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



#endif //_Display_Pages_hpp__