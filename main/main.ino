#include <Arduino.h>

#include <Servo.h>
#include <FPM.h>
#include <SoftwareSerial.h>

//for power button control
/*
  the button has 4 type of state
  0. no input
  1. single click
  2. double click
  3. long click
*/
const int buttonPin = 4;
bool buttonActive = HIGH; // not input
bool lastButtonActive = HIGH;
int buttonState, lastButtonState = 0; // off
//time
int holdTime = 2000;
long downTime = -1;
long upTime = -1;
unsigned long debounceDelay = 50;
int DCgap = 250;
//bool
bool DCwaiting = false;
bool DConUp = false;
bool singleOK = true;
bool ignoreUp = false;
bool waitForUp = false;
bool holdEventPast = false;

// for servo control
/*
  Servo has two state
  0. open
  1. closed

  servo action case
  if button clicked once
    if finger_db != NULL 
      if servo closed && success read, then set open
    if servo opened, then set close
*/
Servo servo1;
Servo servo2;

const int initial_pos = 0;
const int max_pos = 180;
int pos = initial_pos;
bool isOpen = false; // closed
const int servoPin = 9;

// led
/*  */
const int ledPin = 13;

// fingerPrint
bool finger_readState = false; // switch off
SoftwareSerial fserial(2, 3);

FPM finger(&fserial);
FPM_System_Params params;

//////////////////////// main
void setup()
{
  Serial.begin(9600);
  Serial.println("FingerePrint Case Setup");

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH );
  //Serial.begin(9600);
  servo1.attach(servoPin);
  servo2.attach(servoPin);
 
}

void loop()
{
  int b = checkButton();
  /* if(b == 1){
    readyFingerPrint();
    if(isEmptyPrint()){
      enroll();
    }
    else{
      if(isOpen){
        controlServo(false);
      }
      else{
        if(readFinger() == FPM_OK){
          controlServo(true);
        }
      }
    }
  }
  else if(b == 2){
    enroll();
  } 
  else if(b == 3){
    deleteFingerPrint();
  } */
}
/////////////////////// end main

void controlServo(bool open_or_close){
  //  digitalWrite(servoPin,finger_readState && ButtonState);
    if(!isOpen){
      for(pos ; pos < max_pos ; pos += 1){
        servo1.write(pos);
        servo2.write(pos);
        delay(10);
      } 
    }
    isOpen != isOpen;
}
