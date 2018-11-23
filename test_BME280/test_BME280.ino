
/*
BME280とDHT11とTMP36GZで温度を比較する
  - BME280: I2C温度・湿度・気圧センサ
  - DHT11: デジタル温度・湿度センサ
  - TMP36GZ: アナログセンサ
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <dht.h>

#define SEALEVELPRESSURE_HPA (1013.25)

#define DHTOUT 8
#define TMPOUT A0

Adafruit_BME280 bme; // I2C
dht DHT;

unsigned long delayTime;


void setup()
{
    Serial.begin(9600);
    Serial.println(F("BME280 test"));

    bool status;

    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    Serial.println("-- Compare! --");
    delayTime = 2000;

    Serial.println();
}

void loop()
{
    printValues();
    delay(delayTime);
}

void printValues()
{
    Serial.print("BME280 ");
    float bme_t = bme.readTemperature();
    Serial.print(bme_t);
    Serial.println(" *C");

    int chk = DHT.read11(DHTOUT);
    Serial.print("DHT11 ");
    float dht_t = DHT.temperature;
    Serial.print(dht_t);
    Serial.println(" *C");

    Serial.print("TMP36GZ ");
    float org_t = analogRead(TMPOUT);
    float tmp_cel_t = 100 * ((org_t / 1023) * 5) - 50;
    Serial.print(tmp_cel_t);
    Serial.println(" *C");

    // Serial.print("Pressure = ");

    // Serial.print(bme.readPressure() / 100.0F);
    // Serial.println(" hPa");

    // Serial.print("Approx. Altitude = ");
    // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    // Serial.println(" m");

    // Serial.print("Humidity = ");
    // Serial.print(bme.readHumidity());
    // Serial.println(" %");

    Serial.println();
}
