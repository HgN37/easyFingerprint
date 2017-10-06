#ifndef __FINGERPRINT_H__
#define __FINGERPRINT_H__

#include "Arduino.h"
#include "Adafruit_Fingerprint.h"
#include "SoftwareSerial.h"

#define FP_SUCCESS 0
#define FP_FAILURE 1

#define FP_MAX_REG 100

class easyFingerprint{
public:
    easyFingerprint(int Tx, int Rx, bool debug = false);
    int init(uint32_t baud);
    int save(uint16_t id, uint32_t timeout = 3000);
    int scan(uint16_t* id, uint32_t timeout = 1000);
    int erase(void);
    int del(uint16_t id);
    int upload(uint16_t id, uint8_t buffer[]);
    int download(uint16_t id, uint8_t buffer[]);
private:
    Adafruit_Fingerprint* Adafruit;
    SoftwareSerial* ss;
    bool _debug;
};

#endif
