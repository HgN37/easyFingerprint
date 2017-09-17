#include "easyFingerprint.h"

/*
 * This example show how to save and scan new fingerprint
 * 1. You need to put your finger on the sensor until the red light off.
 * 2. Remove your finger and wait the red light on again.
 * 3. Do step 1 and 2 again with same finger. Now your fingerprint is saved.
 * 4. Put a finger on the sensor and it will return if it's the same or not.
 */

// #define FP_DEBUG_SERIAL

SoftwareSerial mySerial(12, 13);
Adafruit_Fingerprint Adafruit_FP = Adafruit_Fingerprint(&mySerial);
easyFingerprint fp(&Adafruit_FP);

uint16_t _id = 1;
int _respond;

void setup() {
  Serial.begin(115200);
  Serial.println("\r\nFingerprint sensor init...");
  _respond = fp.init();
  if(_respond != FP_SUCCESS){
    Serial.println("ERR: Can't find fingerprint sensor :(");
    while(1);
  } else {
    Serial.println("SUCCESS: Found fingerprint sensor");
  }

  Serial.println("\r\n***CLEAR DATABASE***");
  fp.erase();
  if(_respond != FP_SUCCESS){
    Serial.println("ERR: Can't clear flash");
    while(1);
  } else {
    Serial.println("SUCCESS: Flash is clear");
  }

  Serial.println("\r\n***PLEASE REGISTER YOUR FINGERPRINT***");
  fp.save(_id);
  if(_respond != FP_SUCCESS){
    Serial.println("ERR: Can't save fingerprint");
    while(1);
  } else {
    Serial.print("SUCCESS: Fingerprint is saved to ID ");
    Serial.println(int(_id), DEC);
  }
}

void loop() {
  Serial.println("\r\n***SCAN YOUR FINGERPRINT***");
  _respond = fp.scan(&_id);
  if(_respond != FP_SUCCESS){
    Serial.println("ERR: No fingerprint match");
  } else {
    Serial.print("SUCCESS: Hello ID ");
    Serial.println(int(_id), DEC);
  }
  delay(2000);
}
