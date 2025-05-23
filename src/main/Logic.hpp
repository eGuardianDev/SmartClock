#ifndef _Loggic_hpp__
#define _Loggic_hpp__

#include "DisplayPages.hpp"

enum States{
  BOOT  = 0,
  IDLE  = 1,
  ALARM = 2,
} E_State = BOOT;


void buttonCheck(){
  //val_button1 val_button2
  switch(E_State){
    case BOOT:
      // enter debug mode or something
      // logger.log("Entering");
    break;
    case IDLE:
      if(val_button1 == 1){
        if(val_button2 == 1){
          // nothing yet
        }else{
          // move page left;
          ChangePageLeft();
          DisplayPage();
        }
      }
      else if(val_button2 == 1){
        // move page right;
        ChangePageRight();
        DisplayPage();
      }
    break;
    case ALARM:
      if(val_button1 == 1 || val_button2 == 1){
        // snooze;
      }
    break;
    default:


    break;
  }
}



#endif //_Loggic_hpp__