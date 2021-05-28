#include "AccelStepper.h"

// 定义步进电机引脚 
#define J1RdirPin  23
#define J1RstepPin 22

#define J2RdirPin  25
#define J2RstepPin 24

#define J3RdirPin  27
#define J3RstepPin 26

#define J4RdirPin  29
#define J4RstepPin 28

#define J5RdirPin  31
#define J5RstepPin 30

#define J6RdirPin  33
#define J6RstepPin 32

#define J1LdirPin  35
#define J1LstepPin 34

#define J2LdirPin  37
#define J2LstepPin 36

#define J3LdirPin  39
#define J3LstepPin 38

#define J4LdirPin  41
#define J4LstepPin 40

#define J5LdirPin  43
#define J5LstepPin 42  

#define J6LdirPin  45
#define J6LstepPin 44

AccelStepper stepper1(1,J1RstepPin,J1RdirPin);
AccelStepper stepper2(1,J2RstepPin,J2RdirPin);
AccelStepper stepper3(1,J3RstepPin,J3RdirPin);
AccelStepper stepper4(1,J4RstepPin,J4RdirPin);
AccelStepper stepper5(1,J5RstepPin,J5RdirPin);
AccelStepper stepper6(1,J6RstepPin,J6RdirPin);
AccelStepper stepper7(1,J1LstepPin,J1LdirPin);
AccelStepper stepper8(1,J2LstepPin,J2LdirPin);
AccelStepper stepper9(1,J3LstepPin,J3LdirPin);
AccelStepper stepper10(1,J4LstepPin,J4LdirPin);
AccelStepper stepper11(1,J5LstepPin,J5LdirPin);
AccelStepper stepper12(1,J6LstepPin,J6LdirPin);


 
void setup() {
  
  pinMode(J1RstepPin,OUTPUT); 
  pinMode(J1RdirPin,OUTPUT);
  
  pinMode(J2RstepPin,OUTPUT);
  pinMode(J2RdirPin,OUTPUT); 
   
  pinMode(J3RstepPin,OUTPUT); 
  pinMode(J3RdirPin,OUTPUT);
  
  pinMode(J4RstepPin,OUTPUT);
  pinMode(J4RdirPin,OUTPUT);
      
  pinMode(J5RstepPin,OUTPUT); 
  pinMode(J5RdirPin,OUTPUT);
  
  pinMode(J6RstepPin,OUTPUT);
  pinMode(J6RdirPin,OUTPUT);    

  pinMode(J1LstepPin,OUTPUT); 
  pinMode(J1LdirPin,OUTPUT);
  
  pinMode(J2LstepPin,OUTPUT);
  pinMode(J2LdirPin,OUTPUT); 
   
  pinMode(J3LstepPin,OUTPUT); 
  pinMode(J3LdirPin,OUTPUT);
  
  pinMode(J4LstepPin,OUTPUT);
  pinMode(J4LdirPin,OUTPUT);
      
  pinMode(J5LstepPin,OUTPUT); 
  pinMode(J5LdirPin,OUTPUT);
  
  pinMode(J6LstepPin,OUTPUT);
  pinMode(J6LdirPin,OUTPUT);   

                                
  stepper1.setMaxSpeed(2000);
  stepper1.setAcceleration(3000); 
  
  stepper2.setMaxSpeed(2000);
  stepper2.setAcceleration(2000);
  
  stepper3.setMaxSpeed(2000);
  stepper3.setAcceleration(2000); 
  
  stepper4.setMaxSpeed(2000);
  stepper4.setAcceleration(2000);
  
  stepper5.setMaxSpeed(2000);
  stepper5.setAcceleration(500); 
  
  stepper6.setMaxSpeed(2000);
  stepper6.setAcceleration(500);

  stepper7.setMaxSpeed(2000);   
  stepper7.setAcceleration(3000); 
  
  stepper8.setMaxSpeed(2000);
  stepper8.setAcceleration(2000);
  
  stepper9.setMaxSpeed(2000);    
  stepper9.setAcceleration(2000); 
  
  stepper10.setMaxSpeed(2000);
  stepper10.setAcceleration(2000);
  
  stepper11.setMaxSpeed(2000);    
  stepper11.setAcceleration(500); 
  
  stepper12.setMaxSpeed(2000);
  stepper12.setAcceleration(500);
  
}
 
void loop() {
  
//J1
  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(200);              
  } 
   else if ( stepper1.currentPosition() == 200)
   {
    stepper1.moveTo(0);             
  }    
       
//J2
  if(stepper2.currentPosition()==0){
    stepper2.moveTo(250);
    }
    else if (stepper2.currentPosition()==250){
      stepper2.moveTo(0);
      }
      
//J3
    if ( stepper3.currentPosition() == 0 ){ 
    stepper3.moveTo(250);              
  } 
   else if ( stepper3.currentPosition() == 250)
   {
    stepper3.moveTo(0);             
  }         
  
//J4
  if ( stepper4.currentPosition()==0){
    stepper4.moveTo(100);
    }
    else if ( stepper4.currentPosition()==100){
      stepper4.moveTo(0);
      }
      
//J5
    if ( stepper5.currentPosition() == 0 ){ 
    stepper5.moveTo(100);              
  } 
   else if ( stepper5.currentPosition() == 100)
   {
    stepper5.moveTo(0);             
  }   

//J6
  if(stepper6.currentPosition()==0){
    stepper6.moveTo(100);
    }
    else if (stepper6.currentPosition()==100){
      stepper6.moveTo(0);
      }

//J1
  if ( stepper7.currentPosition() == 0 ){ 
    stepper7.moveTo(200);              
  } 
   else if ( stepper7.currentPosition() == 200)
   {
    stepper7.moveTo(0);             
  }    
       
//J2
  if(stepper8.currentPosition()==0){
    stepper8.moveTo(250);
    }
    else if (stepper8.currentPosition()==250){
      stepper8.moveTo(0);
      }
      
//J3
    if ( stepper9.currentPosition() == 0 ){ 
    stepper9.moveTo(250);              
  } 
   else if ( stepper9.currentPosition() == 250)
   {
    stepper9.moveTo(0);             
  }         
  
//J4
  if ( stepper10.currentPosition()==0){
    stepper10.moveTo(100);
    }
    else if ( stepper10.currentPosition()==100){
      stepper10.moveTo(0);
      }
      
//J5
    if ( stepper11.currentPosition() == 0 ){ 
    stepper11.moveTo(100);              
  } 
   else if ( stepper11.currentPosition() == 100)
   {
    stepper11.moveTo(0);             
  }   

//J6
  if(stepper12.currentPosition()==0){
    stepper12.moveTo(100);
    }
    else if (stepper12.currentPosition()==100){
      stepper12.moveTo(0);
      }
  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();
  stepper5.run();
  stepper6.run();
  stepper7.run();
  stepper8.run();
  stepper9.run();
  stepper10.run();
  stepper11.run();
  stepper12.run();
 
}
