
// button
int checkButton(){
  int event = 0;
  int buttonActive = digitalRead(buttonPin);
  // Button pressed down
  if(buttonActive == HIGH && lastButtonActive == LOW && millis() - upTime > debounceDelay){
    downTime = millis();
    ignoreUp = false;
    waitForUp = false;
    singleOK = true;
    holdEventPast = false;
    if(millis() - upTime < DCgap && DConUp == false && DCwaiting == true) DConUp = true;
    else DConUp = false;
    DCwaiting = false;
  }
  //Button released
  else if(buttonActive == LOW && lastButtonActive == HIGH && millis() - downTime > debounceDelay){
    if(not ignoreUp){
      upTime = millis();
      // Double click
      if(DConUp == false) DCwaiting = true;
      else {
        event = 2;
        DConUp = false;
        DCwaiting = false;
        singleOK = false;
      }
    }
  }
  // Test for normal click
  if(buttonActive == LOW && millis() - upTime >= DCgap && DCwaiting == true && DConUp==false && singleOK == true){
    event = 1;
    DCwaiting = false;
  }
  // Test for hold
  if (buttonActive == HIGH && (millis() - downTime) >= holdTime) {
  // Trigger "normal" hold
    if (not holdEventPast) {
      event = 3;
      waitForUp = true;
      ignoreUp = true;
      DConUp = false;
      DCwaiting = false;
      //downTime = millis();
      holdEventPast = true;
    }
  }
  
  lastButtonActive = buttonActive;
  switch (event)
  {
  case 1:
    Serial.println("normal clicked");
    break;
  case 2:
    Serial.println("double clicked");
    break;
  case 3:
    Serial.println("button holded");
    break;
  default:
    break;
  }
  return event;
}
