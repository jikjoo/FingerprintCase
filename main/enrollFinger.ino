
//enroll
void enroll(){
    Serial.println("enroll: Searching for a free slot to store the template...");
    int16_t fid;
    if (get_free_id(&fid)){
        if(enroll_finger(fid) != FPM_OK){
            led_twice();
        }
    }
    else
        Serial.println("No free slot in flash library!");
}



bool get_free_id(int16_t * fid) {
    int16_t p = -1;
    for (int page = 0; page < (params.capacity / FPM_TEMPLATES_PER_PAGE) + 1; page++) {
        p = finger.getFreeIndex(page, fid);
        switch (p) {
            case FPM_OK:
                if (*fid != FPM_NOFREEINDEX) {
                    Serial.print("Free slot at ID ");
                    Serial.println(*fid);
                    return true;
                }
            case FPM_PACKETRECIEVEERR:
                Serial.println("Communication error!");
                return false;
            case FPM_TIMEOUT:
                Serial.print("Timeout!  ");
                return false;
            case FPM_READ_ERROR:
                Serial.println("Got wrong PID or length!");
                return false;
            default:
                Serial.println("Unknown error!");
                return false;
        }
        yield();
    }
}

int16_t enroll_finger(int16_t fid) {
    int16_t p = -1;
    Serial.println("Waiting for valid finger to enroll");
    
    finger.led_on();
    while (p != FPM_OK) {
        p = finger.getImageNL();
        delay(100);
        switch (p) {
            case FPM_OK:
                Serial.println("Image taken");
                break;
            case FPM_NOFINGER:
                Serial.print(".");
                break;
            case FPM_PACKETRECIEVEERR:
                Serial.println("Communication error");
                return p;
            case FPM_IMAGEFAIL:
                Serial.println("Imaging error");
                return p;
            case FPM_TIMEOUT:
                Serial.print("Timeout!  ");
                return p;
            case FPM_READ_ERROR:
                Serial.println("Got wrong PID or length!");
                return p;
            default:
                Serial.println("Unknown error");
                return p;
        }
        yield();
    }
    // OK success!
    finger.led_off();
    //led_once(500);

    p = finger.image2Tz(1);
    delay(1000);
    switch (p) {
        case FPM_OK:
            Serial.println("Image converted");
            break;
        case FPM_IMAGEMESS:
            Serial.println("Image too messy");
            return p;
        case FPM_PACKETRECIEVEERR:
            Serial.println("Communication error");
            return p;
        case FPM_FEATUREFAIL:
            Serial.println("Could not find fingerprint features");
            return p;
        case FPM_INVALIDIMAGE:
            Serial.println("Could not find fingerprint features");
            return p;
        case FPM_TIMEOUT:
            Serial.println("Timeout!");
            return p;
        case FPM_READ_ERROR:
            Serial.println("Got wrong PID or length!");
            return p;
        default:
            Serial.println("Unknown error");
            return p;
    }
    Serial.println("Remove finger");
    delay(2000);
    p = 0;
    while (p != FPM_NOFINGER) {
        p = finger.getImageNL();
        yield();
    }

    p = -1;
    finger.led_on();
    Serial.println("Place same finger again");
    while (p != FPM_OK) {
        p = finger.getImageNL();
        delay(100);
        switch (p) {
            case FPM_OK:
                Serial.println("Image taken");
                break;
            case FPM_NOFINGER:
                Serial.print(".");
                break;
            case FPM_PACKETRECIEVEERR:
                Serial.println("Communication error");
                return p;
            case FPM_IMAGEFAIL:
                Serial.println("Imaging error");
                return p;
            case FPM_TIMEOUT:
                Serial.println("Timeout!");
                return p;
            case FPM_READ_ERROR:
                Serial.println("Got wrong PID or length!");
                return p;
            default:
                Serial.println("Unknown error");
                return p;
        }
        yield();
    }
    finger.led_off();
    // OK success!

    p = finger.image2Tz(2);
    delay(1000);
    switch (p) {
        case FPM_OK:
            Serial.println("Image converted");
            break;
        case FPM_IMAGEMESS:
            Serial.println("Image too messy");
            return p;
        case FPM_PACKETRECIEVEERR:
            Serial.println("Communication error");
            return p;
        case FPM_FEATUREFAIL:
            Serial.println("Could not find fingerprint features");
            return p;
        case FPM_INVALIDIMAGE:
            Serial.println("Could not find fingerprint features");
            return p;
        case FPM_TIMEOUT:
            Serial.println("Timeout!");
            return p;
        case FPM_READ_ERROR:
            Serial.println("Got wrong PID or length!");
            return p;
        default:
            Serial.println("Unknown error");
            return p;
    }


    // OK converted!
    p = finger.createModel();
    if (p == FPM_OK) {
        Serial.println("Prints matched!");
    } else if (p == FPM_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return p;
    } else if (p == FPM_ENROLLMISMATCH) {
        Serial.println("Fingerprints did not match");
        return p;
    } else if (p == FPM_TIMEOUT) {
        Serial.println("Timeout!");
        return p;
    } else if (p == FPM_READ_ERROR) {
        Serial.println("Got wrong PID or length!");
        return p;
    } else {
        Serial.println("Unknown error");
        return p;
    }

    Serial.print("ID "); Serial.println(fid);
    p = finger.storeModel(fid);
    delay(1000);
    if (p == FPM_OK) {
        Serial.println("Stored!");
        led_once(500);
        return p;
    } else if (p == FPM_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return p;
    } else if (p == FPM_BADLOCATION) {
        Serial.println("Could not store in that location");
        return p;
    } else if (p == FPM_FLASHERR) {
        Serial.println("Error writing to flash");
        return p;
    } else if (p == FPM_TIMEOUT) {
        Serial.println("Timeout!");
        return p;
    } else if (p == FPM_READ_ERROR) {
        Serial.println("Got wrong PID or length!");
        return p;
    } else {
        Serial.println("Unknown error");
        return p;
    }
}
