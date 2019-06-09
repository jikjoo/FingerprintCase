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
