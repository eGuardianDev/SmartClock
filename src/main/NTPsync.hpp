#ifndef _NTPsync_hpp__
#define _NTPsync_hpp__

#include "NTPClient.h"
#include "WiFiUdp.h"

const long utcOffsetInSeconds = 0;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

short connectToNTPServer(){
  if(!checkWifiConnection()){
    return 1;
  }
  timeClient.begin();
}

short syncWithNTPServer(){
  timeClient.update();
}

short getNTPsyncHours(){
  timeClient.getHours()
}
short getNTPsyncMinutes(){
  timeClient.getMinutes()
}
short getNTPsyncSeconds(){
  timeClient.getSeconds()
}






#endif //_NTPsync_hpp__