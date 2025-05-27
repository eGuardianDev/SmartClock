#ifndef _Alarm_hpp__
#define _Alarm_hpp__

int hoursAlarm = 0;
int minutesAlarm = 0;
bool activeAlarm = false;
bool snoozed = false;
Preferences AlarmEEPROM;

void setupAlarm(){
  AlarmEEPROM.begin("infoSettings", RO_MODE);

  if(!AlarmEEPROM.isKey("AlarmSettings")){
  }else{
    hoursAlarm = AlarmEEPROM.getInt("hours");
    minutesAlarm = AlarmEEPROM.getInt("minutes");
    activeAlarm = AlarmEEPROM.getBool("active");
    logger.debug(String("[Alarm] current alarm is ")+ hoursAlarm + ":" + minutesAlarm +" active: " +activeAlarm);
  }
  AlarmEEPROM.end();

}



void checkAlarm(){
  if(activeAlarm == false) return;
  
  if(getHour() == hoursAlarm && getMinute() == minutesAlarm ){
    if(snoozed == false){
      testBuzzer();
    }
    if(val_button1 || val_button2){
      snoozed = true;
    }
  }
  else if(snoozed){
    snoozed = false;
  }
}


#endif //_Alarm_hpp__