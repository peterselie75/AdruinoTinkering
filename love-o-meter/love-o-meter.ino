//header
//define constants and variables

const int sensorPin = A0;
const float baselineTemp = 20.0;

//setup
void setup(){
  	Serial.begin(9600); // open a serial port
// start with pin 2; add 1; repeat the loop
	for (int pinNumber =2; pinNumber<5; pinNumber ++){
      pinMode(pinNumber, OUTPUT);
      digitalWrite(pinNumber, LOW);
    }
}

//loop
void loop(){
 	int sensorValue = analogRead(sensorPin);
  	Serial.print("Sensor Value: ");
  	Serial.print(sensorValue);
//convert the ADC reading to Voltage
  float voltage = (sensorValue/1024.0*5.0);
// print new value to serial monitor
    Serial.print(",Volts: ");
  	Serial.print(voltage);
// convert voltage to temperature
  float temperature = (voltage - 0.5)*100;
  Serial.print(", degrees C: ");
  Serial.println(temperature);
  
// if temperature is below baseline
	if(temperature < baselineTemp){
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
  	}            
// low temperature
	if(temperature>=baselineTemp+2 && temperature < baselineTemp +4){
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);	
	}
// medium temperature
	if(temperature>=baselineTemp+4 && temperature < baselineTemp +6){
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
    }
  // high temperature
  if(temperature>=baselineTemp+6){
  	digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);	
	  }
}