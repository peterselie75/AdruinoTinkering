//
// H-bridge control and enable
const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
// button pins
const int directionSwitchStatePin = 4;
const int onOffSwitchStatePin = 5;
// potentiometer pin
const int potPin = A0;

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup()
{
    pinMode(directionSwitchStatePin, INPUT);
    pinMode(onOffSwitchStatePin, INPUT);
    pinMode(controlPin1, OUTPUT);
    pinMode(controlPin2, OUTPUT);
    pinMode(enablePin, OUTPUT);
    // turn the motor off, initially
    digitalWrite(enablePin, LOW);
}

void loop()
{
    onOffSwitchState = digitalRead(onOffSwitchStatePin);
    delay(1);
    directionSwitchState = digitalRead(directionSwitchStatePin);
    motorSpeed = analogRead(potPin) / 4;

    if (onOffSwitchState != previousOnOffSwitchState)
    {
        if (onOffSwitchState == HIGH)
        {
            motorEnabled = !motorEnabled; // exclamation point inverts the boolean value
        }                                 // end of nested(if)
    }                                     // end of outer (if)

    if (directionSwitchState != previousDirectionSwitchState)
    {
        if (directionSwitchState == HIGH)
        {
            motorDirection = !motorDirection; // flip motor direction
        }                                     // end of nested if()
    }                                         // end of outer (if)

    if (motorDirection == 1)
    { // configure H bridge
        digitalWrite(controlPin1, HIGH);
        digitalWrite(controlPin2, LOW);
    }
    else
    {
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, HIGH);
    }

    if (motorEnabled == 1)
    {
        // set speed with PWM
        analogWrite(enablePin, motorSpeed);
    }
    else
    {
        analogWrite(enablePin, 0);
    }

    previousDirectionSwitchState = directionSwitchState;
    previousOnOffSwitchState = onOffSwitchState;
} // end of loop()