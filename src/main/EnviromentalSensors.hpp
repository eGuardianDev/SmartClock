
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; 
bool BME280SensorReady = false;
void setupBME() {
  Logger logger;
  logger.log("Starting BME280 sensor for humidity, temp, altitude");
  unsigned status;
  status = bme.begin();  
  if (!status) {
    logger.error("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    BME280SensorReady = false;
    return;
  }
  BME280SensorReady = true;
}

float getTemp(){
  if(!BME280SensorReady){ return 0; }
  // °C
  return (float) bme.readTemperature();
}

float getPressure(){
  if(!BME280SensorReady){ return 0; }
  // hPa
  return (float) bme.readPressure() / 100.0F;
}

float getAltitude(){
  if(!BME280SensorReady){ return 0; }
  // m
  return (float) bme.readAltitude(SEALEVELPRESSURE_HPA);
}

float getHumidity(){
  if(!BME280SensorReady){ return 0; }
  // %
  return (float) bme.readHumidity();
}