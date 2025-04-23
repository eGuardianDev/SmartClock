#ifndef __Logger_hpp_
#define __Logger_hpp_

#include <Arduino.h>

const bool DEBUG = true;

class Logger{

public:
  int init();
  void debug  (char * data);
  void log    (char *data[]);
  void info   (char *data[]);
  void error  (char *data[]);
  void warning(char *data[]);

};

#endif // __Logger_hpp_