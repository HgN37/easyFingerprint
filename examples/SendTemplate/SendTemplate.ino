/*
 * This example scan your finger and then send the template to computer 
 */

#include <easyFingerprint.h>

easyFingerprint fp(2, 3, true);

uint8_t buffer[688];

void setup() {
  Serial.begin(115200);
  fp.init(9600*6);
  fp.save(1);
  fp.send(1, buffer);
}

void loop() {
  
}
