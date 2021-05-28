#include "AccelStepper.h"

// 定义步进电机引脚 
#define J1dirPin  33
#define J1stepPin 32

AccelStepper stepper1(1,J1stepPin,J1dirPin);

void setup() {

  pinMode(J1stepPin,OUTPUT); 
  pinMode(J1dirPin,OUTPUT);     
                                
  stepper1.setMaxSpeed(1000);    
  stepper1.setAcceleration(200); 
}
 
void loop() {
 
  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(7500);              
  } 
   else if ( stepper1.currentPosition() == 7500)
   {
    stepper1.moveTo(0);             
  }         
  stepper1.run();
 
}
