#ifndef _EnviromentalSensors_hpp__
#define _EnviromentalSensors_hpp__

#define SEALEVELPRESSURE_HPA (1013.25)

// ============================
//  temp and humidity sensors
// ============================

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

// ============================
//       light sensors
// ============================

int val_light1 = 0;
int val_light2 = 0;

void setupLightSensors(){
  
}

void readLight(){
  val_light1 = analogRead(pin_light1);
  val_light2 = analogRead(pin_light2);
}


// ============================
//  button press
// ============================

bool val_button1, val_button2;
void setupButtons(){
  pinMode(pin_button1,INPUT_PULLUP);
  pinMode(pin_button2,INPUT_PULLUP);
  // pinMode(pin_button1_gnd,OUTPUT);
  // pinMode(pin_button2_gnd,OUTPUT);
  // digitalWrite(pin_button1_gnd,LOW);
  // digitalWrite(pin_button2_gnd,LOW);
  
}

void readButton(){
  val_button1 = !digitalRead(pin_button1);
  val_button2 = !digitalRead(pin_button2);
}


//================== buzzer ==================


void setupBuzzer(){
  Logger logger;
  logger.log("Setting buzzer");
  pinMode(pin_buzzer, OUTPUT);
}

void testBuzzer(){
  Logger logger;
  logger.log("Testing buzzer");
  for(int i =180; i<255;++i){
    analogWrite(pin_buzzer, i);
    delay(5);
  }
  analogWrite(pin_buzzer, 0);
}


#endif //_EnviromentalSensors_hpp__