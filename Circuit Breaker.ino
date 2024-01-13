int line = 0;
int relay = 2;
int light = 13;

const int energizeDelay = 10000; //time to wait before re-energizing power
const int fastTripValue = 400; //when voltage drops to 4.7 volts at any time, the power will shut off immediately
const int slowTripValue = 612; //when the voltage drops under 7.2 volts for more than 10 seconds, the power will shut off simulating a slow blow fuse

int tripCount = 0;
int slowTripCount = 0;
int fastTripTimer = 0;
int slowTripTimer = 0;

void setup() {
  pinMode(line, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(light, OUTPUT);
}

void powerFail(){ //This function will shut off the power after 3 times of failed attempts to re-energize power. The indicator light will continuosly blink.
  digitalWrite(relay, HIGH);
  
  while(true){
    digitalWrite(light, HIGH);
    delay(500);
    digitalWrite(light, LOW);
    delay(500);
  }
}

void trip(){
  tripCount++;
  fastTripTimer = 0;
  slowTripTimer = 0;
  slowTripCount = 0;
  
  if(tripCount >= 3)
    powerFail(); //If the fault continues to cause the breaker to trip within 10 seconds 3 times. The power will not be re-energized requiring manual reset
    
  digitalWrite(relay, HIGH);
  delay(energizeDelay);
  digitalWrite(relay, LOW);
  
  digitalWrite(light, LOW);
}

void loop() {
  while(analogRead(line) > fastTripValue){
    digitalWrite(relay, LOW);

    if(fastTripTimer < 10000)
      fastTripTimer++;
    else
      tripCount = 0;

    if(slowTripTimer < 10000)
      slowTripTimer++;
    else
      slowTripCount = 0;
    
    if(analogRead(line) < slowTripValue){
      digitalWrite(light,HIGH);
      delay(10);
      digitalWrite(light, LOW);
      slowTripTimer = 0;
      if(slowTripCount < 100)
        slowTripCount++;
      else{
        digitalWrite(light, HIGH);
        trip();
      }
    }
  }
  trip();
}
