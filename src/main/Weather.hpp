#ifndef _Weather_hpp__
#define _Weather_hpp__

#include "Wifi.hpp"
#include "api.hpp"


const String city = "Sofia";
const String countryCode = "BG";

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

String jsonBuffer;

String httpGETRequest(const char* serverName);


JSONVar weatherObject = JSON.parse(jsonBuffer);

void checkWeather() {
  if(!checkWifiConnection()){
    logger.log("no internet conneciton");
    return;
  }

  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
      
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      weatherObject = JSON.parse(jsonBuffer);
  
      if (JSON.typeof(weatherObject) == "undefined") {
        logger.error("Parsing input failed!");
        return;
      }
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}



double getWeatherTemp(){
  return (weatherObject["main"]["temp"]);
}
double getWeatherHumidity(){
  return (weatherObject["main"]["humidity"]);
}
String getWeatherType(){
  return weatherObject["weather"][0]["description"];
}

double HoldTemp;
String HoldWeather; 
bool weatherChanged(){
  if(HoldTemp != getWeatherTemp() || HoldWeather != getWeatherType() ){
    HoldTemp = getWeatherTemp();
    HoldWeather = getWeatherType();
    return true;
  }
  return false;
}
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}


#endif //_Weather_hpp__