#include "easyFingerprint.h"

easyFingerprint fp1(10, 11, true);
easyFingerprint fp2(12, 13, true);
uint8_t fpBuffer[688];
int _respond;
int _id = 0;

void setup(){
  Serial.begin(115200);
  while(!Serial);
  Serial.println("__Start FP1:");
  _respond = fp1.init(57600);
  if(FP_SUCCESS != _respond){
    Serial.println("Fail");
    while(1);
  }
  Serial.println("__Start FP2:");
  _respond = fp2.init(57600);
  if(FP_SUCCESS != _respond){
    Serial.println("Fail");
    while(1);
  }
  /* Save 1 fingerprint to ID1 FP1 */
  Serial.println("__Please register your fingerprint device 1");
  _respond = fp1.save(1);
  if(FP_SUCCESS != _respond){
    Serial.println("Fail");
    while(1);
  }
  /* Upload ID1 from FP1 to arduino */
  Serial.println("__Your fingerprint is uploading");
  _respond = fp1.upload(1, fpBuffer);
  if(FP_SUCCESS != _respond){
    Serial.println("Fail");
    while(1);
  }
  /* Download from arduino to ID1 FP2 */
  _respond = fp2.download(1, fpBuffer);
  if(FP_SUCCESS != _respond){
    Serial.println("Fail");
    while(1);
  }
  Serial.println("__SYNC SUCCESS__");
}

void loop(){
  fp1.scan(&_id, 100);
  if(0 != _id){
    Serial.print("FP1 match ID ");
    Serial.println(_id, DEC);
  }
  fp2.scan(&_id, 100);
  if(0 != _id){
    Serial.print("FP2 match ID ");
    Serial.println(_id, DEC);
  }
}

