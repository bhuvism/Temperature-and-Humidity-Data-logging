# Temperature-and-Humidity-Data-logging
Temperature and Humidity Data logging to SD card using SD card module and Arduino UNO

### Components required
  1. Arduino Uno
  
  2. SD Card Module
  
  3. DHT22/DHT11 Temperature and Humidity Sensor
  
  4. SD Card (Higher than 8GB)
  
  5. Breadboard(if required)
  
  6. Connecting wires
  
### Prerequisites:
 1. Arduino IDE [get it here](https://arduino.en.softonic.com/)
 
 2. You need to manually add DHT library to Arduino IDE as it is not included by default. You can ignore it if you have already included it. Otherwise you can do it following the     steps below.
      a).Open Arduino IDE
      b).Go to Sketch >> Include Library >> Manage Libraries
      c).Search for DHT sensor library and install it
 
 3. A file to store data(in the SD card). 
 
 ### Connections
 
 1. SD Card Module Ground to Arduino Ground
 
 2. VCC of the module to 5V output of Arduino
 
 3. MISO of module to pin 12 of Arduino
 
 4. MOSI of module to pin 11 of Arduino
 
 5. SCK of module to pin 13 of Arduino
 
 6. CS of module to pin 10 of Arduino
 
 Then we can connect the DHT22/DHT11 Sensor to the Arduino UNO
 
 1. Connect VCC of DHT22 to 5V output of Arduino
 
 2. Ground to ground of Arduino
 
 3. Data pin of DHT22 to pin 8 of Arduino
