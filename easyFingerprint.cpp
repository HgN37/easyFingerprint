#include "easyFingerprint.h"

easyFingerprint::easyFingerprint(Adafruit_Fingerprint* fp){
    Adafruit = fp;
}

int easyFingerprint::init(void){
    #ifdef FP_DEBUG_SERIAL
    Serial.println("\r\nFingerprint sensor init...");
    #endif
    Adafruit->begin(9600*6);
    bool _respond = Adafruit->verifyPassword();
    #ifdef FP_DEBUG_SERIAL
    if(true != _respond){
        Serial.println("Can't find fingerprint sensor :(");
    } else{
        Serial.println("Found fingerprint sensor :)");
    }
    #endif
    if(true != _respond){
        return FP_FAILURE;
    }
    else{
        return FP_SUCCESS;
    }
}

int easyFingerprint::save(uint16_t id){
    int _respond;
    #ifdef FP_DEBUG_SERIAL
    Serial.println("");
    Serial.println("Fingerprint Register...");
    #endif
    /* Check if Flash ID valid */
    if(id > (FP_MAX_REG - 1)){
        #ifdef FP_DEBUG_SERIAL
        Serial.println("ID not valid");
        #endif
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
    #ifdef FP_DEBUG_SERIAL
    if(FINGERPRINT_OK == _respond){
      Serial.println("SUCCESS: Fingerprint model created.");
    } else if(FINGERPRINT_ENROLLMISMATCH == _respond){
      Serial.println("ERR: Not same finger.");
    } else {
      Serial.print("ERR: Unknown error 0x");
      Serial.println(_respond, HEX);
    }
    #endif
    if(FINGERPRINT_OK != _respond){
        return FP_FAILURE;
    }
    
    /* Save to flash */
    _respond = Adafruit->storeModel(id);
    #ifdef FP_DEBUG_SERIAL
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
    #endif
    if(FINGERPRINT_OK != _respond){
        return FP_FAILURE;
    }
    return FP_SUCCESS;
}

int easyFingerprint::scan(uint16_t* id){
    int _respond;
    uint16_t _result = NULL;
    #ifdef FP_DEBUG_SERIAL
    Serial.println("");
    Serial.println("Waiting for fingerprint...");
    #endif
    /* Read fingerprint */
    while(FINGERPRINT_OK == Adafruit->getImage());
    while(FINGERPRINT_OK != Adafruit->getImage());
    Adafruit->image2Tz(1);
    
    /* Search from database */
    _respond = Adafruit->fingerFastSearch();
    #ifdef FP_DEBUG_SERIAL
    if(FINGERPRINT_OK == _respond){
        Serial.println("SUCCESS: Fingerprint found.");
    } else if(FINGERPRINT_NOTFOUND == _respond){
        Serial.println("ERR: Fingerprint not found.");
    } else {
        Serial.print("ERR: Unknown error 0x");
        Serial.println(_respond, HEX);
    }
    #endif
    if(_respond != FINGERPRINT_OK){
        return FP_FAILURE;
    }
    #ifdef FP_DEBUG_SERIAL
    Serial.print("fingerID: ");
    Serial.println(Adafruit->fingerID);
    Serial.print("confidence: ");
    Serial.println(Adafruit->confidence);
    #endif
    if(Adafruit->confidence > 100){
        *id = Adafruit->fingerID;
    }
    return FP_SUCCESS;
}

int easyFingerprint::erase(void){
    int _respond = Adafruit->emptyDatabase();
    #ifdef FP_DEBUG_SERIAL
    if(FINGERPRINT_OK == _respond){
        Serial.print("SUCCESS: Database clear");
    } else if(FINGERPRINT_DBCLEARFAIL == _respond){
        Serial.print("ERR: Can't clear database");
    } else{
        Serial.print("ERR: Unknown error 0x");
        Serial.println(_respond, HEX); 
    }
    #endif
    if(FINGERPRINT_OK != _respond){
        return FP_FAILURE;
    } else{
        return FP_SUCCESS;
    }
}
