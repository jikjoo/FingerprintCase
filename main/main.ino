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
bool buttonActive = LOW; // not input
bool lastButtonActive = LOW;
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

const int initial_pos = 0; //open state
const int max_pos = 90; // closed state
int pos = initial_pos; // current state
bool isOpen = true; // open
const int servoPin1 = 9;
const int servoPin2 = 7;

// led
const int ledPin = 13;
int ledState = LOW;
unsigned long previousMillis = 0;
// fingerPrint
/*  pin #2 is IN from sensor (GREEN wire)
 *  pin #3 is OUT from arduino  (WHITE/YELLOW wire)
 */
bool finger_readState = false; // switch off
SoftwareSerial fserial(2, 3);

FPM finger(&fserial);
FPM_System_Params params;

//////////////////////// main
void setup()
{
  Serial.begin(9600);
  Serial.println("FingerePrint Case Setup");
  fserial.begin(57600);   
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH );
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  readyFingerPrint();
  servo1.write(initial_pos);
  //servo2.write(initial_pos);
}

void loop()
{
  digitalWrite(ledPin, isOpen);
  int b = checkButton();
  if(isOpen){
    if(b == 1){
      if(isEmptyPrint()){
        led_once(2000);
        enroll();
      }
      else{
        Serial.println("Close case");
        closeServo();
      }
    }
    else if(b == 2){
      led_once(2000);
      enroll();
    } 
    else if(b == 3){
      led_triple();
      deleteFingerPrint();
    }
  }
  else{ // if closed
    if(b==1){
      if(readFinger() == FPM_OK){
        Serial.println("Open case");
        openServo();
      }
      else{
        Serial.println("Fail to Open");
        led_twice();
      }
    }
  }
}
