# easyFingerprint Arduino Library

## Update
[No more support] This library is not working with the latest version of its dependencies.

## Introduction
This project make an easy-to-use library for Ardafruit Fingerprint Sensor R30x-series based on Ardafruit's library.

## Usage
* Firstly install Adafruit-Fingerprint-Sensor-Library, link in References.
* This library now support both Software Serial and Hardware Serial:
```cpp
// Software Serial
SoftwareSerial swSerial(2, 3);
easyFingerprint fp(&swSerial);
// Hardware Serial
easyFingerprint fp(&Serial1);
```
* It's recommended to use Hardware Serial instead of Software Serial, especially if you need to use upload and download function. And please don't use Software Serial with Arduino Mega Board.
* Add this param to get debug information via UART.
```cpp
easyFingerprint fp(&Serial1, true);
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
easyFingerprint fp1(&Serial1);
easyFingerprint fp2(&Serial2);
fp1.upload(1,buffer);
fp2.download(1,buffer);
```
* If you get wrong frame while using upload function, I can confirm that it's hardware or wire error [Tested].

## References
* Adafruit-Fingerprint-Sensor-Library: https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library [Copyright (c) 2012, Adafruit Industries]
