#include "AccelStepper.h"

// 定义步进电机引脚 
#define J1dirPin  27 //23
#define J1stepPin 26 //22    

#define J2dirPin  25
#define J2stepPin 24

#define J3dirPin  23 //27
#define J3stepPin 22 //26

#define J4dirPin  29
#define J4stepPin 28

#define J5dirPin  31
#define J5stepPin 30

#define J6dirPin  33
#define J6stepPin 32

 
AccelStepper stepper1(1,J1stepPin,J1dirPin);
AccelStepper stepper2(1,J2stepPin,J2dirPin);
AccelStepper stepper3(1,J3stepPin,J3dirPin);
AccelStepper stepper4(1,J4stepPin,J4dirPin);
AccelStepper stepper5(1,J5stepPin,J5dirPin);
AccelStepper stepper6(1,J6stepPin,J6dirPin);


 
void setup() {
  
  pinMode(J1stepPin,OUTPUT); 
  pinMode(J1dirPin,OUTPUT);
  
  pinMode(J2stepPin,OUTPUT);
  pinMode(J2dirPin,OUTPUT); 
   
  pinMode(J3stepPin,OUTPUT); 
  pinMode(J3dirPin,OUTPUT);
  
  pinMode(J4stepPin,OUTPUT);
  pinMode(J4dirPin,OUTPUT);
      
  pinMode(J5stepPin,OUTPUT); 
  pinMode(J5dirPin,OUTPUT);
  
  pinMode(J6stepPin,OUTPUT);
  pinMode(J6dirPin,OUTPUT);    

                                
  stepper1.setMaxSpeed(8000);   //J1 给了4000， 也就是90度
  stepper1.setAcceleration(5000); 
  
  stepper2.setMaxSpeed(4000); //J2 给了4000
  stepper2.setAcceleration(3000);
  
  stepper3.setMaxSpeed(3000);   //J3给了5000
  stepper3.setAcceleration(2000); 
  
  stepper4.setMaxSpeed(3000);  //J4给了6000
  stepper4.setAcceleration(2000);
  
  stepper5.setMaxSpeed(1000);  //J5给了1500
  stepper5.setAcceleration(1000); 
  
  stepper6.setMaxSpeed(3000);//J6给了5000
  stepper6.setAcceleration(2000);

  /*stepper1.setSpeed(500);
  stepper2.setSpeed(500);
  stepper3.setSpeed(500);
  stepper4.setSpeed(500);
  stepper5.setSpeed(500);
  stepper6.setSpeed(500);*/
}
 
void loop() {
  
//J1
  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(20000);              
  } 
   else if ( stepper1.currentPosition() == 20000)
   {
    stepper1.moveTo(0);             
  }    
 /*    
//J2
  if(stepper2.currentPosition()==0){
    stepper2.moveTo(2000);
    }
  if(stepper2.currentPosition()==2000){
    stepper2.moveTo(0);
    }
   
 
//J3
    if ( stepper3.currentPosition() == 0 ){ 
    stepper3.moveTo(2000);              
  } 
   else if ( stepper3.currentPosition() == 2000)
   {
    stepper3.moveTo(0);             
  }        */ 
 /* 
//J4
  if ( stepper4.currentPosition()==0){
    stepper4.moveTo(6000);
    }
    else if ( stepper4.currentPosition()==6000){
      stepper4.moveTo(0);
      }
      
//J5
    if ( stepper5.currentPosition() == 0 ){ 
    stepper5.moveTo(1000);              
  } 
   else if ( stepper5.currentPosition() == 1000)
   {
    stepper5.moveTo(0);             
  }   
        
//J6
  if(stepper6.currentPosition()==0){
    stepper6.moveTo(5000);
    }
    else if (stepper6.currentPosition()==5000){
      stepper6.moveTo(0);
      }
     */
  
  stepper1.run();
  stepper2.run();
  stepper3.run();
  //stepper4.run();  
  //stepper5.run();
  //stepper6.run();
 
}
