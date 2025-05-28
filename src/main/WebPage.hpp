#include <WebServer.h>

WebServer server(80);
Preferences WebPageEEPROM;

void handleRoot() {
  String html = "<!DOCTYPE html>"
"<html lang=\"en\">"
"<head>"
"<meta charset=\"UTF-8\">"
"<title>Alarm Clock Configuration</title>"
"<style>"
"body {"
"    font-family: Arial, sans-serif;"
"    max-width: 600px;"
"    margin: 40px auto;"
"    padding: 20px;"
"    background-color: #f8f9fa;"
"    border: 1px solid #ccc;"
"    border-radius: 8px;"
"}"
"h2 {"
"    text-align: center;"
"}"
"form {"
"    margin-bottom: 20px;"
"    padding: 10px;"
"    background-color: #fff;"
"    border: 1px solid #ddd;"
"    border-radius: 5px;"
"}"
"h4 {"
"    margin: 10px 0 5px;"
"}"
"input[type=\"text\"],"
"input[type=\"time\"] {"
"    width: 200px;"
"    padding: 5px;"
"    margin-bottom: 10px;"
"    box-sizing: border-box;"
"}"
"input[type=\"submit\"] {"
"    background-color: #007bff;"
"    color: white;"
"    border: none;"
"    padding: 6px 12px;"
"    border-radius: 4px;"
"    cursor: pointer;"
"}"
"input[type=\"submit\"]:hover {"
"    background-color: #0056b3;"
"}"
"label {"
"    margin-left: 5px;"
"}"
"</style>"
"</head>"
"<body>"
"<h2>Alarm Clock Configuration Settings</h2>"

"<form action=\"/submit\">"
"<h4>Location:</h4>"
"<input type=\"text\" name=\"Location\" required><br>"

"<h4>Country:</h4>"
"<input type=\"text\" name=\"Country\" required><br>"

"<input type=\"submit\" value=\"Send\">"
"</form>"

"<form action=\"/submit\">"
"<h4>Set Time:</h4>"
"<input type=\"time\" name=\"Time\" required><br>"

"<input type=\"submit\" value=\"Send\">"
"</form>"

"<form action=\"/submit\">"
"<h4>Set Alarm Time:</h4>"
"<input type=\"time\" name=\"Alarm\" required><br>"

"<input type=\"hidden\" name=\"activeAlarm\" value=\"no\">"
"<input type=\"checkbox\" id=\"activeAlarmCheck\" name=\"activeAlarm\" onclick=\"this.previousElementSibling.disabled = this.checked;\">"
"<label for=\"activeAlarmCheck\">Active</label><br>"

"<input type=\"submit\" value=\"Send\">"
"</form>"

"</body>"
"</html>"
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
