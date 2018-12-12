/*
 * multi_I2C_sensor_test
 * MLX90614:Infrared themometer
 * BME280:humidity, temperature & pressure sensor
 */


#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)


Adafruit_BME280 bme; // I2C
IRTherm therm; // Create an IRTherm object to interact with throughout

const byte LED_PIN = 13; // Optional LED attached to pin 8 (active low)
bool status_bme,status_therm;

void setup() 
{
  Serial.begin(9600); // Initialize Serial to log output

  status_bme = bme.begin();
  status_therm = therm.begin(); // Initialize thermal IR sensor
  therm.setUnit(TEMP_C); // TEMP_C for Celsius 
  if (!status_bme) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }   
  if (!status_therm) {
    Serial.println("Could not find a valid MLX90614 sensor, check wiring!");
    while (1);
  } 
  
  pinMode(LED_PIN, OUTPUT); // LED pin as output
  setLED(LOW); // LED OFF
}

void loop() 
{
  delay(500);
  setLED(HIGH); //LED on
  
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
	// temperatures.
	// They'll be floats, calculated out to the unit you set with setUnit().
    Serial.print("Therm Object: " + String(therm.object()));
    Serial.println(" *C"); // Degree Symbol
    Serial.print("Therm Ambient: " + String(therm.ambient()));
    Serial.println(" *C");
    Serial.print("BME280 Temperature: " + String(bme.readTemperature()));
    Serial.println(" *C");
    Serial.print("BME280 Pressure: " + String(bme.readPressure()/100.0F));
    Serial.println(" hPa");
    Serial.print("BME280 Altitude: " + String(bme.readAltitude(SEALEVELPRESSURE_HPA)));
    Serial.println(" m");
    Serial.print("BME280 Humidity: " + String(bme.readHumidity()));
    Serial.println(" %");
    Serial.println();
  }
  setLED(LOW);

}

void setLED(bool on)
{
  if (on)
    digitalWrite(LED_PIN, LOW);
  else
    digitalWrite(LED_PIN, HIGH);
}
