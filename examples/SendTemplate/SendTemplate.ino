/*
 * This example scan your finger and then send the template to computer 
 */

#include <easyFingerprint.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint Adafruit_FP = Adafruit_Fingerprint(&mySerial);
easyFingerprint fp(&Adafruit_FP, true);

uint8_t buffer[688];

void setup() {
  Serial.begin(115200);
  fp.init(9600*6);
  fp.save(1);
  fp.send(1, buffer, &mySerial);
}

void loop() {
  
}
