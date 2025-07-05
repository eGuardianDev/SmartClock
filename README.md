# SmartClock
A small "smart" alarm clock for IoT course.

### Idea
A small clock with alarm and basic functions. Integrationg with WiFi via ESP32 for data sharing, maybe smart home automation. Different sensors for tracking enviroment data and sleep patterns.  

### Tools
 - [Bit map to code](https://www.teachmemicro.com/lcd-bitmap-converter-online/)

### Parts
- Display: probably E-Ink or 7-segment.
- Sensors: Microphone for noise, temperature, humidity, light.
- Actuators control: attach lights and motor to make waking up easier.
- Main controller: ESP32

### Plans and ideas
- [X] Theoretical idea
- [X] Finding & ordering parts
  - [X] Finding compatable parts
  - [X] Making an order 
- [X] Testing parts and finding libraries
  - [X] Display 
    - E-Ink no touch 89x38cm - 296x128res [2.9" inch SPI](https://erelement.com/shop/e-ink-2-9-grey/)
  - [X] Sensors
    - ~~Microphone [Sound sensor wc](https://erelement.com/shop/sound-sensor-module/)~~
    - Enviroment [bme280](https://erelement.com/shop/bme280-ws/)
    - ~~Hand movement [qtr-md-08a](https://erelement.com/shop/qtr-md-08a/) [pir](https://erelement.com/shop/pir-sensor/)~~
    - light [photoresistor](https://elimex.bg/product/70488-fotorezistor-pgm5516-ldr5516)
    - ~~SD Card [reader](https://elimex.bg/product/75637-kit-k2162-micro-sd-kartochetets-za-uno)~~
  - [ ] ~~Actuators~~
  - [X] WiFi control 
- [X] Simple prototype
  - [X] WiFi server / API 
  - [X] Sensor and calibration
  - [ ] ~~Actuators connection~~
- [ ] Code
  - [X] Initialize everything
  - [X] Wifi connection
  - [X] Clock logic
  - [X] API logic 
    - [X] Weather 
    - [ ] Time sync 
    - [ ] Todo?
  - [ ] sleep tracking
  - [ ] calendar
  - [ ] Low-power/sleep mode 
- [X] Final design
  - [X] Container
  - [X] Compression of electronics
- [ ] Presentation material
  - [ ] Documentation 
    - [X] CAD design
    - [X] Schematics
    - [ ] Software
  - [X] Presentation
  - [X] Video?
  
### Current progress
 - [X] fix main page
 - [X] fix weather page
 - [ ] enter sleep mode
 - [X] add alarm
 - [X] test wifi provisioner
 - [ ] add time sync
 - [ ] hand move test
 - [ ] docs
 - [X] presentation

### problems met
 - bitmap size containment
 - system event configuration
 - hardware and electronics problem
 - usb charging
 - compilation time
 - interupts not fixed
 - maybe e-ink wasn't the best idea


### Settings and ideas
 - There should be different wake up patterns for the alarm. For example - ring 1 second, wait 3-5 seconds, repeat.
 - Extending the suspend button away, maybe using second ESP with ESP now protocol in deep sleep or unpowered.
 - sync alarm with phone
 - Weather forecast

### Diagram
![Diagram](https://github.com/eGuardianDev/SmartClock/blob/main/Docs/SystemDiagram.drawio.png)

### Main body CAD design
![TechDrawCadBody](https://github.com/eGuardianDev/SmartClock/blob/main/Docs/TechDrawCadBody.png)

### Electronics schematics
![schematiElectronicsSchematicscs](https://github.com/eGuardianDev/SmartClock/blob/main/Docs/ElectronicsSchematics.png)

### 3D PCB Design
![render](https://github.com/eGuardianDev/SmartClock/blob/main/Docs/PCBRender.gif)

### 3D render of all objects
![render](https://github.com/eGuardianDev/SmartClock/blob/main/Docs/render.gif)
