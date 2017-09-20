# easyFingerprint Arduino Library

## Introduction
This project make an easy-to-use library for Ardafruit Fingerprint Sensor R30x-series based on Ardafruit's library.

## Usage
* This library use  Adafruit_Fingerprint class, which use SoftwareSerial, so:
```cpp
SoftwareSerial mySerial(12, 13);
Adafruit_Fingerprint Adafruit_FP = Adafruit_Fingerprint(&mySerial);
easyFingerprint fp(&Adafruit_FP);
```
* Add this param to get debug information through UART.
```cpp
easyFingerprint fp(&Adafruit_FP, debug=true);
```

## TODO
* Add function to download the fingerprint template (to sync between device).
* Add more examples.
* Use EEPROM/Server to save usernames, replacing IDs.

## References
* Adafruit-Fingerprint-Sensor-Library: https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library [Copyright (c) 2012, Adafruit Industries]
