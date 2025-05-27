#ifndef _Libraries_hpp__
#define _Libraries_hpp__

// from ds3231 example
#include "RTClib.h"

// from  BME280 example
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


// from GxEPD2 Example
// select the display class and display driver class in the following file (new style):
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>



// Wifi

#include <WiFiProvisioner.h>
#include <Preferences.h>

#include <WiFi.h>
#include <HTTPClient.h>

#include <ESPmDNS.h>

// weather api
#include <Arduino_JSON.h>


#endif //_Libraries_hpp__