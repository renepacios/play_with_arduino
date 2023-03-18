//https://programarfacil.com/blog/arduino-blog/bmp180-arduino/ 

#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>


#include <Arduino.h>
//#include <Wire.h>
#include <SFE_BMP180.h>

// Temporizador
unsigned long ultimoEnvio = 0;
const unsigned long tiempoEnvio = 3000; // 3 segundos
 
// Sensor BMP180
SFE_BMP180 bmp180;
 
// Modo funcionamiento BMP180
const byte modoPresBMP180 = 3;
 
// Altitud actual en metros
const double altitudActual = 106;
 
void setup()
{
  Serial.begin(9600);
 
  // Esperar hasta que se inicie el monitor serie
  while (!Serial)
    ;
 
  // Iniciar sensor de temperatura
  if (bmp180.begin())
  {
    Serial.println(F("BMP180 iniciado correctamente"));
  }
  else
  {
    Serial.println(F("Error al inicial BMP180"));
    // No dejar continuar
    while (1)
      ;
  }
}
 
void loop()
{
  // Overflow millis
  if (ultimoEnvio > millis())
  {
    ultimoEnvio = millis();
  }
 
  // Temporizador
  if (millis() - ultimoEnvio >= tiempoEnvio)
  {
    // Marca de tiempo
    ultimoEnvio = millis();
 
    // Variables para obtener datos del sensor BMP180
    byte status;
    double temp, pres, altitud;
 
    //Inicio de lectura de temperatura
    status = bmp180.startTemperature();
 
    // Comprobar resultado de la lectura temperatura
    // Devuelve 0 si hay error
    // milisegundos que hay que esperar en caso contrario
    if (status != 0)
    {
      // Pausa hasta que finalice la lectura
      delay(status);
 
      // Obtener temperatura
      // La temperatura se almacena en temp en grados Celsius
      status = bmp180.getTemperature(temp);
 
      // Comprobar resultado de la temperatura
      // Devuelve 0 si hay error
      // Devuelve 1 si todo ha ido bien
      if (status != 0)
      {
        Serial.print(F("Temperatura: "));
        Serial.print(temp, 2);
        Serial.println(F(" ºC"));
 
        // Inicio lectura de presión
        status = bmp180.startPressure(modoPresBMP180);
 
        // Comprobar resultado de la lectura presión
        // Devuelve 0 si hay error
        // milisegundos que hay que esperar en caso contrario
        if (status != 0)
        {
          // Pausa hata que finalice la lectura
          delay(status);
 
          // Obtener presión atomosférica
          // La prsión se almacena en la variable pres en milibar (mbar)
          // Esta función requiere la medida de temperatura
          status = bmp180.getPressure(pres, temp);
 
          // Comprobar resultado de la presión
          // Devuelve 0 si hay error
          // Devuelve 1 si todo ha ido bien
          if (status != 0)
          {
            Serial.print(F("Presión: "));
            Serial.print(pres, 2);
            Serial.println(F(" mbar"));
 
            // Obtener altitud
 
            // Paso 1, establecer la presión a la altitud actual para que nos devuelva la presión compensada a nivel del mar
            double presNivelMar = bmp180.sealevel(pres, altitudActual);
 
            Serial.print(F("Presión a nivel del mar: "));
            Serial.print(pres, 2);
            Serial.println(F(" mbar"));
 
            // Paso 2, obtener la altitud con las dos presiones
            altitud = bmp180.altitude(pres, presNivelMar);
 
            Serial.print(F("Altitud: "));
            Serial.print(altitud, 2);
            Serial.println(F(" metros"));
          }
        }
      }
    }
  }
}