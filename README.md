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

## Notes
* Function upload need a buffer with the size of 688 to get all the frame.
  * After the ACK frame, the sensor will send 15 package with package identifier is 0x02, each package has 32 bytes.
  * The last package will have 0x08 as package identifier, but also have 32 bytes data.
  * If your transmission have no problem, you will get all 16 frames(688 bytes), which contain 512 bytes of the template.
  * Recommend to use the default sensor baudrate (57600).
* To sync 2 fingerprint device, just upload from device 1 to buffer, then download that buffer to device 2.
```cpp
uint8_t buffer[688];
easyFingerprint fp1(10, 11);
easyFingerprint fp2(12, 13);
fp1.upload(1,buffer);
fp2.download(1,buffer);
```

## References
* Adafruit-Fingerprint-Sensor-Library: https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library [Copyright (c) 2012, Adafruit Industries]
