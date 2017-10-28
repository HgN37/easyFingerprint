#include "easyFingerprint.h"

easyFingerprint fp1(&Serial1, true);
easyFingerprint fp2(&Serial2, true);
char fbuffer[688];
uint16_t id;

void setup(){
  Serial.begin(115200);
  while(!Serial);
  fp1.init(57600);
  fp2.init(57600);
  fp1.erase();
  fp2.erase();
  while(FP_SUCCESS != fp2.save(1));
  fp2.upload(1, fbuffer);
  fp1.download(1, fbuffer);
}

void loop(){
  fp2.scan(&id);
  fp1.scan(&id);
}

