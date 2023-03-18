#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>


#include <Arduino.h>
//#include <Wire.h>
#include <SFE_BMP180.h>

#define SEALEVELPRESSURE_HPA (1015)

Adafruit_BME280 bme; // use I2C interface

Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

void setup() {
  // put your setup code here, to run once:
  //  Serial.begin(115200);
  
  Serial.begin(9600);
  Serial.println(F("BME280 Sensor event test"));

    if (!bme.begin(0x77)) //0x76
    { 
      Serial.println("No encuentro un sensor BME280 valido!");
      while (1)  delay(10);
    }

    bme_temp->printSensorDetails();
    bme_pressure->printSensorDetails();
    bme_humidity->printSensorDetails();
}

void loop() {
  // put your main code here, to run repeatedly:
    sensors_event_t temp_event, pressure_event, humidity_event;
    bme_temp->getEvent(&temp_event);
    bme_pressure->getEvent(&pressure_event);
    bme_humidity->getEvent(&humidity_event);
    
    Serial.print(F("Temperatura = "));
    Serial.print(temp_event.temperature);
    Serial.println(" *C");
    Serial.print(F("Humedad = "));
    Serial.print(humidity_event.relative_humidity);
    Serial.println(" %");
    Serial.print(F("Presion = "));
    Serial.print(pressure_event.pressure);
    Serial.println(" hPa");
    Serial.println();
    delay(1000);
}
