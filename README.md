# easyFingerprint Arduino Library

## Introduction
This project make an easy-to-use library for Ardafruit Fingerprint Sensor R30x-series based on Ardafruit's library.

## Usage
* Firsly install Adafruit-Fingerprint-Sensor-Library, link in References.
* This library use  Adafruit_Fingerprint class, which use SoftwareSerial, so:
```cpp
easyFingerprint fp(int Tx, int Rx);
```
* Add this param to get debug information via UART.
```cpp
easyFingerprint fp(int Tx, int Rx, true);
```

# Notes
* Function send need a buffer with the size of 688 to get all the frame.
  * After the ACK frame, the sensor will send 15 package with package identifier is 0x02, each package has 32 bytes.
  * The last package will have 0x08 as package identifier, but also have 32 bytes data.
  * If your transmission have no problem, you will get all 16 frames(688 bytes), which contain 512 bytes of the template.
  * Recommend to use the default sensor baudrate (57600).

## TODO
* Add function to download the fingerprint template (to sync between device).
* Add more examples.
* Use EEPROM/Server to save usernames, replacing IDs.

## References
* Adafruit-Fingerprint-Sensor-Library: https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library [Copyright (c) 2012, Adafruit Industries]
