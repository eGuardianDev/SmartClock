#include "RTCModule.hpp"
// using GDEM029T94 128x296, SSD1680, Waveshare 2.9" V2 variant
#define FullDisplayRefreshDelay 2000  // 2 seconds for full refresh

#include "EnviromentalSensors.hpp"

#include "fonts/FreeMonoBold34pt7b.h"

#define GxEPD2_DISPLAY_CLASS GxEPD2_BW

#define GxEPD2_DRIVER_CLASS GxEPD2_290_T94_V2  // GDEM029T94  128x296, SSD1680, (FPC-7519 rev.b), Waveshare 2.9" V2 variant

#ifndef EPD_CS
#define EPD_CS SS
#endif


#define GxEPD2_BW_IS_GxEPD2_BW true
#define IS_GxEPD(c, x) (c##x)

#define MAX_DISPLAY_BUFFER_SIZE 65536ul  // e.g.
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=5*/ EPD_CS, /*DC=*/17, /*RST=*/16, /*BUSY=*/4));  // my suggested wiring and proto board

long long lastFullRefresh;

// const char HelloWorld[] = "Hello World!";

void setFont24() {
  display.setFont(&FreeMonoBold24pt7b);
}

void setFont9() {
  display.setFont(&FreeMonoBold9pt7b);
}

void setFont34(){
  display.setFont(&FreeMonoBold34pt7b);
}

void printText(String input) {
  display.setRotation(1);
  setFont9();
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(input, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(input);
  } while (display.nextPage());
  display.hibernate();
}


void setupScreen() {
  lastFullRefresh = millis();
  display.init(115200, true, 2, false);  // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  printText(String("Starting System..."));
  delay(100);
}

void fullRefresh() {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
  } while (display.nextPage());
  lastFullRefresh = millis();
}

void checkLastUpdate() {

  if (millis() - lastFullRefresh > 60000) {
    display.setFullWindow();
    display.firstPage();
    do {
      display.fillScreen(GxEPD_WHITE);
    } while (display.nextPage());
    lastFullRefresh = millis();
    delay(4000);
  }
}