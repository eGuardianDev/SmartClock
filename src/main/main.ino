#include "Logger.hpp"

Logger logger;

void setup() {
  logger.init();
}

void loop() {
  logger.debug("This is a test!");
  delay(1000);
}
