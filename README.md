# easyFingerprint Arduino Library

## Introduction
This project make an easy-to-use library for Ardafruit Fingerprint Sensor R30x-series based on Ardafruit's library.

## Usage
* This library use  Adafruit_Fingerprint class, which use SoftwareSerial, so:
```c 
SoftwareSerial mySerial(12, 13);
Adafruit_Fingerprint Adafruit_FP = Adafruit_Fingerprint(&mySerial);
easyFingerprint fp(&Adafruit_FP);
```
* Add this line to get debug information through UART.
```c
#define FP_DEBUG_SERIAL
```

## TODO
* Add function to upload the fingerprint template (to save on server, share database between device,...).
* Add more examples.
* Use EEPROM to save usernames, replacing IDs.

## References
* Adafruit-Fingerprint-Sensor-Library: https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library [Copyright (c) 2012, Adafruit Industries]