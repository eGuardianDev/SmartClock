#include "Logger.hpp"
  
  
int Logger::init(){
  if(Serial){
    return 1;
  }
  
  Serial.begin(9600);
  return 0;
}


void Logger::debug(char * data){
  if(DEBUG){
    Serial.print("| DEBUG | ");
    Serial.println(data);
  }
}
static void Logger::log(char *data){
  Serial.print("| Log | ");
  Serial.println(data);
}
static void Logger::info(char *data){
  Serial.print("| Info | ");
  Serial.println(data);
}
static void Logger::error(char *data){
  Serial.print("| Error | ");
  Serial.println(data);
}
static void Logger::warning(char *data){
  Serial.print("| Warning | ");
  Serial.println(data);
}

