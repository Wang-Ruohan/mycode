#include "Encoder.h"
#include "AccelStepper.h"

// 定义步进电机引脚
#define J1dirPin  23
#define J1stepPin 22

Encoder J1encoder(2, 3);
Encoder J2encoder(7, 8);
AccelStepper stepper1(1,J1stepPin,J1dirPin);

long positionLeft  = -999;
long positionRight = -999;

void setup() {
  Serial.begin(2000000);
  Serial.println("TwoKnobs Encoder Test:");
  
  pinMode(J1stepPin,OUTPUT); 
  pinMode(J1dirPin,OUTPUT);
  
  stepper1.setMaxSpeed(500);   //Max:100,000
  stepper1.setAcceleration(10); //Max:10
}


void loop() {

  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(200);              
  } 
   else if ( stepper1.currentPosition() == 200)
   {
    stepper1.moveTo(0);             
  }
  stepper1.run();

  long newLeft, newRight;
  newLeft = J1encoder.read();
  newRight = J2encoder.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    J1encoder.write(0);
    J2encoder.write(0);
  }
}
