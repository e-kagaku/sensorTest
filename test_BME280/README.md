# BME280 温湿度・気圧センサ

written on 2018/11/23, by Ihara

## キット

- BOSCH BME280使用 I2C/SPI対応 温湿度・気圧センサモジュールキット
- [AE-BME280]
- 通販コード　K-09421
- 秋月電子通商
- 発売日　2015/06/01

## 使用ライブラリ

- Adafruitのライブラリ
- https://github.com/adafruit/Adafruit_BME280_Library

## 測定範囲，精度

| 項目 | 内容 |
| ---- | ---- |
| 電源電圧(Vdd) | 	1.71V～3.6V |
| 測定範囲(温度) |	-40℃～+85℃ |
| 精度(温度) |	±1℃ |
| 測定の最小単位(温度) | 0.01℃ |
| 測定範囲(相対湿度) |	0％～100% |
| 精度(湿度) | 	±3% |
| 測定の最小単位(湿度) | 0.008% |
| 測定範囲(気圧) |	300hPa～1100ｈPa |
| 精度(気圧) |	±1hPa |
| 精度(気圧) |	±1hPa |

## 使い方

### 接続方法

- I2Cで、5番ピンをVDDに接続して配線してください
- I2Cのアドレス選択は[0x77]となります
- 以下に配線図を示します
- 3.3Vまでしか対応していないため注意
- SCK（SCL）とSDI（SDA）はプルアップ抵抗が必要？？
  - 中本に確認依頼中
  - J1,J2をジャンパすると基板上のプルアップを使うことが出来て、外部で用意する必要ない？？
  - Wire.hをインクルードするとArduino内部で自動でプルアップしてくれる説もある？？

![BME280配線](img/BME280_I2C_connect.jpg)

### プログラム

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

## 参考URL

- http://www.ne.jp/asahi/o-family/extdisk/BME280/BME280_DJP.pdf
  - センサのデータシート、私的に日本語に訳されてある

- https://github.com/adafruit/Adafruit_BME280_Library
  - AdafruitのBME280用ライブラリ
  - 温度とかの補正がされているのかどうかは不明
  - Adafruitのモジュールと秋月のものとの差は不明

- https://github.com/SWITCHSCIENCE/samplecodes/tree/master/BME280
  - SWITCH SCIENCEのライブラリ
  - calibrationなどの関数が用意されている

- http://intellectualcuriosity.hatenablog.com/entry/2017/12/14/212651
  - BME280を使った製作例
  - BME280で取得した値をwifi通信している
  - Adafruitライブラリ使用

