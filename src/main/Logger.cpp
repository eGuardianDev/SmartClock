#define DebugOn
#include "Logger.hpp"
  
int Logger::init(){
  if(Serial){
    return 1;
  }
  
  Serial.begin(115200);
  return 0;
}


void Logger::debug(String data){
  
  #ifdef DebugOn
  Serial.print("| DEBUG | ");
  Serial.println(data);
  #endif
  
}
 void Logger::log(String data){
  Serial.print("| Log | ");
  Serial.println(data);
}
 void Logger::info(String data){
  Serial.print("| Info | ");
  Serial.println(data);
}
 void Logger::error(String data){
  Serial.print("| Error | ");
  Serial.println(data);
}
 void Logger::warning(String data){
  Serial.print("| Warning | ");
  Serial.println(data);
}

