void readyFingerPrint(){
    if (finger.begin()) {
        finger.readParams(&params);
        Serial.println("Found fingerprint sensor!");
        Serial.print("Capacity: "); Serial.println(params.capacity);
        Serial.print("Packet length: "); Serial.println(FPM::packet_lengths[params.packet_len]);
    }
    else {
        Serial.println("Did not find fingerprint sensor :(");
    }
}

bool isEmptyPrint(){
    Serial.println("isEmptyPrint");
    uint16_t count;
    if (!get_template_count(&count))
        return true;
    Serial.print(count);
    Serial.println(" print(s) in module database.");
    if(count == 0) return true;
    else return false;
}

bool get_template_count(uint16_t * count) {
    int16_t p = finger.getTemplateCount(count);
    if (p == FPM_OK) {
        return true;
    }
    else {
        Serial.print("Unknown error: ");
        Serial.println(p);
        return false;
    }
}

void deleteFingerPrint(){
    
    int16_t p = finger.emptyDatabase();
    if (p == FPM_OK) {
        Serial.println("Database empty!");
    }
    else if (p == FPM_PACKETRECIEVEERR) {
        Serial.print("Communication error!");
    }
    else if (p == FPM_DBCLEARFAIL) {
        Serial.println("Could not clear database!");
    } 
    else if (p == FPM_TIMEOUT) {
        Serial.println("Timeout!");
    } 
    else if (p == FPM_READ_ERROR) {
        Serial.println("Got wrong PID or length!");
    } 
    else {
        Serial.println("Unknown error");
    }
}
