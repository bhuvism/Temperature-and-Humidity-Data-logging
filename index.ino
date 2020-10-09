#include <SD.h>       // Including SD Card Library
#include <SPI.h>      // Including SPI Library
#include "DHT.h"      // Including DHT Sensor Library

#define DHTPIN 8      // Declaring the pin to which DHT data pin is connected
#define DHTTYPE DHT22 // Selecting the type of DHT sensor used in this project(either DHT22 or DHT11 sensor)

long seconds=00;      // For storing second
long minutes=00;      // For storing minute
long hours=00;        // For storing hour 

int CS_pin = 10;         // Chip select pin of SD card module

DHT dht(DHTPIN, DHTTYPE);    // Declaring DHT object
File sd_file;             // Declaring File object


// In the setup function, we initialized the serial communication at 9600 baudrate. Here serial communication is used only for displaying logs in the Arduino Serial Monitor. The dht.begin() function will initialize the Arduino for reading data from DHT sensor. Similarly sd.begin() function will initialize the Arduino for write data to SD card module. After that we will open the file “data.txt” from SD card using sd.open() function. Then we will write titles ‘Time’, ‘Humidity’, ‘Temperature_C’, ‘Temperature_F’ and ‘Heat_index’ in it. After that we will close the connection to save the file.

void setup()  {
  Serial.begin(9600);
  pinMode(CS_pin, OUTPUT);
  dht.begin(); // Initialize the Arduino for reading data from DHT sensor
  // SD Card Initialization
  if (SD.begin())  {
    Serial.println("SD card is initialized. Ready to go");
  } 
  else  {
    Serial.println("Failed");
    return;
  }

  sd_file = SD.open("data.txt", FILE_WRITE);

  if (sd_file)  {
    Serial.print("Time");
    Serial.print(",");
    Serial.print("Humidity");
    Serial.print(",");
    Serial.print("Temperature_C");
    Serial.print(",");
    Serial.print("Temperature_F");
    Serial.print(",");
    Serial.println("Heat_index");

    sd_file.print("Time");
    sd_file.print(",");
    sd_file.print("Humidity");
    sd_file.print(",");
    sd_file.print("Temperature_C");
    sd_file.print(",");
    sd_file.print("Temperature_F");
    sd_file.print(",");
    sd_file.println("Heat_index");
  }
  sd_file.close(); //closing the file
} 

// In the loop function, we will open the SD card “data.txt” file again. If it is opened successfully we will call senddata() function, otherwise it will show ‘error opening file’ in the serial monitor.

void loop()  {
  sd_file = SD.open("data.txt", FILE_WRITE);   //  Replace the file name(data.txt) with the file you want to log data to
  if (sd_file)  {
    senddata();
  }
  // if the file didn't open, print an error:
  else  {
    Serial.println("error opening file");
  }
  delay(1000);
}

// In the senddata() function, we have made a loop which will count the time. Then we have read the temperature, humidity from DHT22 sensor and heat index is calculated. After storing these values in the variables, we will write these values to the SD card file. After that we will call sd_file.flush() to ensure that all data is stored in the SD card. These steps are repeated with a delay of 2 seconds.

void senddata()  {
  for(long seconds = 00; seconds < 60; seconds=seconds+2)  {
    float temp = dht.readTemperature(); //Reading the temperature as Celsius and storing in temp
    float hum = dht.readHumidity(); //Reading the humidity and storing in hum
    float fah = dht.readTemperature(true);
    float heat_index = dht.computeHeatIndex(fah, hum);

    sd_file.print(hours);
    sd_file.print(":");
    sd_file.print(minutes);
    sd_file.print(":");
    sd_file.print(seconds);
    sd_file.print(",  ");
    sd_file.print(hum);
    sd_file.print(",    ");
    sd_file.print(temp);
    sd_file.print(",      ");
    sd_file.print(fah);
    sd_file.print(",      ");
    sd_file.println(heat_index);

    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.print(seconds);
    Serial.print(",  ");
    Serial.print(hum);
    Serial.print(",    ");
    Serial.print(temp);
    Serial.print(",       ");
    Serial.print(fah);
    Serial.print(",      ");
    Serial.println(heat_index);

    if(seconds>=58)  {
      minutes= minutes + 1;
    }

    if (minutes>59)  {
      hours = hours + 1;
      minutes = 0;
    }

    sd_file.flush();    //saving the file

    delay(2000);
  }
  sd_file.close();      //closing the file
}
