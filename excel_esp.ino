#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "HTTPSRedirect.h"




Adafruit_MPU6050 mpu;


// GPIO where the DS18B20 is connected to
const int oneWireBus = 0;    


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);


// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);




// Enter network credentials:
const char* ssid     = "YOUR_WIFI/HOTSPOT_NAME";
const char* password = "YOUR_WIFI/HOTSPOT_PASSWORD";


String payload_base =  "";
String payload = "";


// Declare variables that will be published to Google Sheets
double value0 = 0;
double value1 = 0;
double value2 = 0;
double value3 = 0;
double value4 = 0;
double value5 = 0;
double value6 = 0;




void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens




  Serial.println("Adafruit MPU6050 test!");




  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");




  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }




  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }




  Serial.println("");




  // Connect to WiFi
  WiFi.begin(ssid, password);            
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");




  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());


  // Start the DS18B20 sensor
  sensors.begin();


  delay(100);
}




void loop() {




  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
 


  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);




  value0 = a.acceleration.x;
  value1 = a.acceleration.y;
  value2 = a.acceleration.z;
  value3 = g.gyro.x;
  value4 = g.gyro.y;
  value5 = g.gyro.z;
  value6 = temperatureC; //DS //temp.temperature; for MPU6050
 




    // Create byte string to send serially to the python program
  payload = payload_base + value0 + " " + value1 + " " + value2 + " " + value3 + " " + value4 + " " + value5 + " " + value6 + "";


  Serial.println(payload);


  // a delay of several seconds is required before publishing again    
  delay(1000);
}
