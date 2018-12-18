/*
 * multi_I2C_sensor_test
 * MLX90614:Infrared themometer
 * BME280:humidity, temperature & pressure sensor
 */


#include <Wire.h> // I2C library, required for MLX90614
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BNO055.h>


#define SEALEVELPRESSURE_HPA (1013.25)



Adafruit_BME280 bme; // I2C
Adafruit_BNO055 bno = Adafruit_BNO055(55); // I2C


const byte LED_PIN = 13; // Optional LED attached to pin 8 (active low)
bool status_bme;

void setup() 
{
  Serial.begin(9600); // Initialize Serial to log output

  status_bme = bme.begin();
  if (!status_bme) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }   
  if(!bno.begin()){
    Serial.print("ERROR, no BNO055 detected");
    while(1);
  }

  bno.setExtCrystalUse(true);
  
  pinMode(LED_PIN, OUTPUT); // LED pin as output
  setLED(LOW); // LED OFF
}

void loop() 
{
  delay(2000);
  setLED(HIGH); //LED on

  sensors_event_t event;
  bno.getEvent(&event);
  
  Serial.print("BME280 Temperature: " + String(bme.readTemperature()));
  Serial.println(" *C");
  Serial.print("BME280 Pressure: " + String(bme.readPressure()/100.0F));
  Serial.println(" hPa");
  Serial.print("BME280 Altitude: " + String(bme.readAltitude(SEALEVELPRESSURE_HPA)));
  Serial.println(" m");
  Serial.print("BME280 Humidity: " + String(bme.readHumidity()));
  Serial.println(" %");
  Serial.println();

  Serial.print("X:");
  Serial.print(event.orientation.x,4);
  Serial.print(", Y:");
  Serial.print(event.orientation.y,4);
  Serial.print(", Z:");
  Serial.println(event.orientation.z,4);


  setLED(LOW);

}

void setLED(bool on)
{
  if (on)
    digitalWrite(LED_PIN, LOW);
  else
    digitalWrite(LED_PIN, HIGH);
}
