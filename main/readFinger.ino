
// read
int16_t readFinger(){
    int16_t p = -1;
    /* first get the finger image */
    Serial.println("readFinger: Waiting for valid finger");
    while (p != FPM_OK) {
        delay(1000);
        p = finger.getImage();
        switch (p) {
            case FPM_OK:
                Serial.println("Image taken");
                break;
            case FPM_NOFINGER:
                //Serial.println(".");
                break;
            case FPM_PACKETRECIEVEERR:
                Serial.println("Communication error");
                break;
            case FPM_IMAGEFAIL:
                Serial.println("Imaging error");
                break;
            case FPM_TIMEOUT:
                //Serial.println("Timeout!");
                break;
            case FPM_READ_ERROR:
                Serial.println("Got wrong PID or length!");
                break;
            default:
                Serial.println("Unknown error");
                break;
        }
        yield();
    }
    
    /* convert it */
    p = finger.image2Tz();
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
    p = 0;
    while (p != FPM_NOFINGER) {
        p = finger.getImage();
        yield();
    }
    Serial.println();

    /* search the database for the converted print */
    uint16_t fid, score;
    p = finger.searchDatabase(&fid, &score);
    delay(1000);
    if (p == FPM_OK) {
        // found a match!
        Serial.print("Found ID #"); Serial.print(fid);
        Serial.print(" with confidence of "); Serial.println(score);
        return p;
    } else if (p == FPM_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return p;
    } else if (p == FPM_NOTFOUND) {
        Serial.println("Did not find a match");
        return p;
    } else if (p == FPM_TIMEOUT) {
        Serial.print("Timeout!  ");
        return p;
    } else if (p == FPM_READ_ERROR) {
        Serial.println("Got wrong PID or length!");
        return p;
    } else {
        Serial.println("Unknown error");
        return p;
    }

    
}
