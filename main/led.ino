void led_on(){
    digitalWrite(ledPin,HIGH);
}

void led_off(){
    digitalWrite(ledPin,LOW);
}

void led_once(const int interval){
    //Serial.print("--led--");
    int led_last = digitalRead(ledPin);
    led_off();
    delay(interval);
    led_on();
    delay(interval);
    led_off();
    digitalWrite(ledPin,led_last);  
    /* unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  } */
}

void led_twice(){
    led_once(500);
    led_once(500);
}

void led_triple(){
    led_once(300);
    led_once(300);
    led_once(300);
}
