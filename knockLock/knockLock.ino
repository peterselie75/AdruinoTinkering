
 
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
      digitalWrite(redLED,HIGH);
      myServo.write(90);
      Serial.println("the box is locked");
    }      
  }
  if(locked==true)
  {
    knockVal = analogRead(piezo);
    if(numberOfKnocks < 3 && knockVal > 0) //chrcks two conditions to be met
    {
      if (checkForKnock(knockVal) == true) //check if it is a valid knock
      {
        numberOfKnocks ++; //add one
      }
          // subtract knocks made so far
      Serial.print(3-numberOfKnocks);
      Serial.print( "more knocks to go");
    }
  }
  if(numberOfKnocks >=3)
  {
    locked = false;
    myServo.write(0);
    delay(20);
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    Serial.println("the box is unlocked");
  }

}                   
                   
boolean checkForKnock(int value) 
{
  if(value > quietKnock && value < loudKnock)
  {
    digitalWrite(yellowLED, HIGH);
    delay(50);
    digitalWrite(yellowLED, LOW);
    Serial.print("valid knock of value ");
    Serial.println(value);
    return true;
      
  }
  else
  {
    Serial.print("Bad knock value ");
    Serial.println(value);
    return false;
  }
}    // end of the function