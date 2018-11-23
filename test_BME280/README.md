# BME280 温湿度・気圧センサ

written on 2018/11/23, by Ihara

## Kit

- BOSCH BME280使用 I2C/SPI対応 温湿度・気圧センサモジュールキット
- 秋月電子通商

## Library

- https://github.com/adafruit/Adafruit_BME280_Library

## Usage

### Connection

- I2Cで、5番ピンをVDDに接続して配線してください
- I2Cのアドレス選択は[0x77]となります
- 以下に配線図を示します

![BME280配線](img/BME280_I2C_connect.jpg)

### Code

``` c++
// define
dafruit_BME280 bme;

// check detection
bool status = bme.begin();

// temperature (celcius)
bme.readTemperature()

// pressure (hPa)
bme.readPressure() / 100.0F

// Approx. Altitude (m)
#define SEALEVELPRESSURE_HPA 1013.25
bme.readAltitude(SEALEVELPRESSURE_HPA)

// Humidity (%)
bme.readHumidity()

```
