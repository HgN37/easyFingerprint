/*
 * This example scan your finger and then send the template to computer 
 */

#include <easyFingerprint.h>
#include <SoftwareSerial.h>

/* Choose which Serial to use */
easyFingerprint fp(&Serial1, true);
// SoftwareSerial swSerial(12, 13);
// easyFingerprint fp(&swSerial, true);

uint8_t buffer[688];

void setup() {
  Serial.begin(115200);
  fp.init(9600*6);
  while(FP_SUCCESS != fp.save(1));
  fp.upload(1, buffer);
}

void loop() {
  
}
