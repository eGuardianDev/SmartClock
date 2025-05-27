#include <WebServer.h>

WebServer server(80);
Preferences WebPageEEPROM;

void handleRoot() {
  String html = "<!DOCTYPE html><html><body>"
                "<h2>Alarm clock configuration settings</h2>"
                "<form action=\"/submit\">"
                "<input type=\"text\" name=\"Location\" required>"
                "<input type=\"text\" name=\"Country\" required>"
                "<input type=\"submit\" value=\"Send\">"
                "</form>"
                "<form action=\"/submit\">"
                "<input type=\"time\" name=\"Time\" required>"
                "<input type=\"submit\" value=\"Send\">"
                "</form>"
                "<form action=\"/submit\">"
                "<input type=\"time\" name=\"Alarm\" required>"
                "<input type=\"hidden\" name=\"activeAlarm\" value=\"no\">"
                "<input type=\"checkbox\" name=\"activeAlarm\"   onclick=\"this.previousElementSibling.disabled = this.checked;\">"
                "<input type=\"submit\" value=\"Send\">"
                "</form>"
                
                ;
  server.send(200, "text/html", html);
}

void handleSubmit() {
  if (server.hasArg("Location")) {
    String location = server.arg("Location");
    String country = server.arg("Country");

    WebPageEEPROM.begin("infoSettings", RW_MODE);
    WebPageEEPROM.putString("location",location);
    WebPageEEPROM.putString("country",country);
    WebPageEEPROM.end();
    logger.log("[Webserver/Settings] Set new country!");
  
    city = location;
    countryCode = country;

    server.send(200, "text/plain", "Received: " + location + " " + country);
  } else if (server.hasArg("Time")) {
    String time = server.arg("Time");
    int hour = (time[0] -'0') * 10 + (time[1]-'0');
    int minute = (time[3] - '0') * 10 + (time[4] -'0');
    setupClock(hour, minute);
    server.send(200, "text/plain", "Received: " + String(hour)+":"+String(minute));
  } else if (server.hasArg("Alarm")) {
    String time = server.arg("Alarm");
    String _activeAlarm = server.arg("activeAlarm");
    int hour = (time[0] -'0') * 10 + (time[1]-'0');
    int minute = (time[3] - '0') * 10 + (time[4] -'0');

    WebPageEEPROM.begin("AlarmSettings", RW_MODE);
    WebPageEEPROM.putInt("hours",hour);
    WebPageEEPROM.putInt("minutes",minute);
    if(_activeAlarm == "on"){
      WebPageEEPROM.putBool("active",true);
      activeAlarm = true;
    }else{
      WebPageEEPROM.putBool("active",false);
      activeAlarm = false;
    }
    WebPageEEPROM.end();
    logger.log("[Webserver/Settings] Set alarm!");
  
    hoursAlarm = hour;
    minutesAlarm = minute;



    server.send(200, "text/plain", "Received: " + time + " active alarm: " + activeAlarm);
  } else {
    server.send(400, "text/plain", "No data received");
  }
}

void setupWebServer() {
 

  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);

  server.begin();
  Serial.println("Web server started");
}

void loopServer() {
  server.handleClient();
}
