
 
//including the Servo library
#include<Servo.h>
Servo myServo;

// creating constants
const int piezo = A0;
const int switchPin =2;
const int yellowLED=3;
const int greenLED=4;
const int redLED=5;
  
// creating variables
int knockVal;
int switchVal;
  
// creating knocking Thresholds
const int quietKnock =10;
const int loudKnock = 100;
  
// knock variables
boolean locked = false;
int numberOfKnocks =0;
 
void setup(){
  myServo.attach(9);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(switchPin, INPUT);
  
  //begin communication
  Serial.begin(9600);
  
  //unlock the box
  digitalWrite(greenLED, HIGH);
  myServo.write(0);
  Serial.println("the box is unlocked");
  
}
	
void loop()
{
  if(locked == false)
  {
    switchVal = digitalRead(switchPin);
    if (switchVal == HIGH)
    {
      locked = true;
      digitalWrite(greenLED,LOW);

    }      
  }
}                   
                   
      