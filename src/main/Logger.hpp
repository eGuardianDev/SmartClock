#ifndef __Logger_hpp_
#define __Logger_hpp_

#include <Arduino.h>


class Logger{

public:
  int init();
  void debug  (String data);
  void log    (String data);
  void info   (String data);
  void error  (String data);
  void warning(String data);

};


#endif // __Logger_hpp_