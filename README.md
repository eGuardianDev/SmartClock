# SmartClock
A small "smart" alarm clock for IoT course.

### Idea
A small clock with alarm and basic functions. Integrationg with WiFi via ESP32 for data sharing, maybe smart home automation. Different sensors for tracking enviroment data and sleep patterns.  


### Parts
- Display: probably E-Ink or 7-segment.
- Sensors: Microphone for noise, temperature, humidity, light.
- Actuators control: attach lights and motor to make waking up easier.
- Main controller: ESP32

### Plan of attack
- [ ] Theoretical idea
- [ ] Finding & ordering parts
  - [ ] Finding compatable parts
  - [ ] Making an order 
- [ ] Testing parts and finding libraries
  - [ ] Display 
    - E-Ink no touch 89x38cm - 296x128res [2.9" inch SPI](https://erelement.com/shop/e-ink-2-9-grey/)
  - [ ] Sensors
    - Microphone [Sound sensor wc](https://erelement.com/shop/sound-sensor-module/)
    - Enviroment [bme280](https://erelement.com/shop/bme280-ws/)
    - Hand movement [qtr-md-08a](https://erelement.com/shop/qtr-md-08a/) [pir](https://erelement.com/shop/pir-sensor/)
    - light [photoresistor](https://elimex.bg/product/70488-fotorezistor-pgm5516-ldr5516)
  - [ ] Actuators
  - [ ] WiFi control 
  - [ ]
- [ ] Simple prototype
  - [ ] WiFi server / API 
  - [ ] Sensor calibration
  - [ ] Actuators connection
- [ ] Code finilization
  - [ ] Battery power saving? 
- [ ] Final design
  - [ ] Container
  - [ ] Compression of electronics
- [ ] Presentation material
  - [ ] Documentation 
  - [ ] Presentation
  - [ ] Video?
  
### Settings and ideas
 - There should be different wake up patterns for the alarm. For example - ring 1 second, wait 3-5 seconds, repeat.
 - Extending the suspend button away, maybe using second ESP with ESP now protocol in deep sleep or unpowered.
 - sync alarm with phone


### Diagram
![Diagram](https://github.com/eGuardianDev/SmartClock/blob/main/Docs/SystemDiagram.drawio.png)
