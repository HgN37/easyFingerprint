#include "easyFingerprint.h"

easyFingerprint::easyFingerprint(Adafruit_Fingerprint* fp, bool debug = false){
    Adafruit = fp;
    _debug = debug;
}

int easyFingerprint::init(uint32_t baud){
    if(_debug == true){
    Serial.println("\r\nFingerprint sensor init...");
    }
    Adafruit->begin(baud);
    bool _respond = Adafruit->verifyPassword();
    if(_debug == true){
    if(true != _respond){
        Serial.println("Can't find fingerprint sensor :(");
    } else{
        Serial.println("Found fingerprint sensor :)");
    }
    }
    if(true != _respond){
        return FP_FAILURE;
    }
    else{
        return FP_SUCCESS;
    }
}

int easyFingerprint::save(uint16_t id){
    int _respond;
    if(_debug == true){
    Serial.println("");
    Serial.println("Fingerprint Register...");
    }
    /* Check if Flash ID valid */
    if(id > (FP_MAX_REG - 1)){
        if(_debug == true){
        Serial.println("ID not valid");
        }
        return FP_FAILURE;
    }
    /* Get finger character file and save to CharBuffer1 */
    while(FINGERPRINT_OK == Adafruit->getImage());
    while(FINGERPRINT_OK != Adafruit->getImage());
    Adafruit->image2Tz(1);
    /* Get finger character file and save to CharBuffer2 */
    while(FINGERPRINT_OK == Adafruit->getImage());
    while(FINGERPRINT_OK != Adafruit->getImage());
    Adafruit->image2Tz(2);
    
    /* Combine 2 character file to make template */
    _respond = Adafruit->createModel();
    if(_debug == true){
    if(FINGERPRINT_OK == _respond){
      Serial.println("SUCCESS: Fingerprint model created.");
    } else if(FINGERPRINT_ENROLLMISMATCH == _respond){
      Serial.println("ERR: Not same finger.");
    } else {
      Serial.print("ERR: Unknown error 0x");
      Serial.println(_respond, HEX);
    }
    }
    if(FINGERPRINT_OK != _respond){
        return FP_FAILURE;
    }
    
    /* Save to flash */
    _respond = Adafruit->storeModel(id);
    if(_debug == true){
    if(FINGERPRINT_OK == _respond){
      Serial.println("SUCCESS: Fingerprint has been saved.");
    } else if(FINGERPRINT_BADLOCATION == _respond){
      Serial.println("ERR: Flash ID is not valid.");
    } else if(FINGERPRINT_FLASHERR == _respond) {
      Serial.println("ERR: Flash can't be written.");
    } else {
        Serial.print("ERR: Unknown error 0x");
        Serial.println(_respond, HEX);
    }
    }
    if(FINGERPRINT_OK != _respond){
        return FP_FAILURE;
    }
    return FP_SUCCESS;
}

int easyFingerprint::scan(uint16_t* id){
    int _respond;
    uint16_t _result = NULL;
    if(_debug == true){
    Serial.println("");
    Serial.println("Waiting for fingerprint...");
    }
    /* Read fingerprint */
    while(FINGERPRINT_OK == Adafruit->getImage());
    while(FINGERPRINT_OK != Adafruit->getImage());
    Adafruit->image2Tz(1);
    
    /* Search from database */
    _respond = Adafruit->fingerFastSearch();
    if(_debug == true){
    if(FINGERPRINT_OK == _respond){
        Serial.println("SUCCESS: Fingerprint found.");
    } else if(FINGERPRINT_NOTFOUND == _respond){
        Serial.println("ERR: Fingerprint not found.");
    } else {
        Serial.print("ERR: Unknown error 0x");
        Serial.println(_respond, HEX);
    }
    }
    if(_respond != FINGERPRINT_OK){
        return FP_FAILURE;
    }
    if(_debug == true){
    Serial.print("fingerID: ");
    Serial.println(Adafruit->fingerID);
    Serial.print("confidence: ");
    Serial.println(Adafruit->confidence);
    }
    if(Adafruit->confidence > 100){
        *id = Adafruit->fingerID;
    }
    return FP_SUCCESS;
}

int easyFingerprint::erase(void){
    int _respond = Adafruit->emptyDatabase();
    if(_debug == true){
    if(FINGERPRINT_OK == _respond){
        Serial.println("SUCCESS: Database clear");
    } else if(FINGERPRINT_DBCLEARFAIL == _respond){
        Serial.println("ERR: Can't clear database");
    } else{
        Serial.print("ERR: Unknown error 0x");
        Serial.println(_respond, HEX); 
    }
    }
    if(FINGERPRINT_OK != _respond){
        return FP_FAILURE;
    } else{
        return FP_SUCCESS;
    }
}

int easyFingerprint::del(uint16_t id){
    int _respond;
    _respond = Adafruit->deleteModel(id);
    if(_debug == true){
      if(FINGERPRINT_OK == _respond){
          Serial.println("SUCCESS: Template deleted");
      } else if(FINGERPRINT_DELETEFAIL == _respond){
          Serial.println("ERR: Can't delete template");
      } else{
          Serial.print("ERR: Unknown error 0x");
          Serial.println(_respond, HEX); 
      }
    }
}

int easyFingerprint::send(uint16_t id, uint8_t buffer[], SoftwareSerial* ss){
  int _respond = Adafruit->loadModel(id);
  if(_debug == true){
    if(FINGERPRINT_OK == _respond){
        Serial.println("SUCCESS: Template loaded");
    } else if(FINGERPRINT_DBRANGEFAIL == _respond){
        Serial.println("ERR: Template is not valid");
    } else{
        Serial.print("ERR: Unknown error 0x");
        Serial.println(_respond, HEX); 
    }
  }
  if(FINGERPRINT_OK != _respond){
    return FP_FAILURE;
  }
  _respond = Adafruit->getModel();
  if(_debug == true){
    if(FINGERPRINT_OK == _respond){
        Serial.println("SUCCESS: Template uploading");
    } else if(FINGERPRINT_DBRANGEFAIL == _respond){
        Serial.println("ERR: Template upload error");
    } else{
        Serial.print("ERR: Unknown error 0x");
        Serial.println(_respond, HEX); 
    }
  }
  if(FINGERPRINT_OK != _respond){
    return FP_FAILURE;
  }
  uint32_t _start;
  uint8_t k;
  uint32_t i;
  _start = millis();
  while((millis() - _start) < 1000){
    if(ss->available()){
      k = ss->read();
      buffer[i] = k;
      i++;
    }
  }
  if(_debug == true){
    for(i = 0; i < 688; i++){
      if((i%43) == 0){
        Serial.println("");
      }
      Serial.print("0x");
      Serial.print(int(buffer[i]), HEX);
      Serial.print(" ");
    }
  }
  return FP_SUCCESS;
}

