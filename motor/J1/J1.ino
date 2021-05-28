#include "AccelStepper.h"

#define FULLSTEP 4    //全步进参数
#define HALFSTEP 8    //半步进参数

// 定义步进电机引脚 
#define xdirPin  34     // 一号28BYJ48连接的ULN2003电机驱动板引脚 in1
#define xstepPin  36     // 一号28BYJ48连接的ULN2003电机驱动板引脚 in2
#define xenablePin  30  // 一号28BYJ48连接的ULN2003电机驱动板引脚 in3

 
AccelStepper stepper1(1,xstepPin,xdirPin);
 
void setup() {
  
  pinMode(xstepPin,OUTPUT); 
  pinMode(xdirPin,OUTPUT);     
  pinMode(xenablePin,OUTPUT);  
  digitalWrite(xenablePin,LOW); 
                                
  stepper1.setMaxSpeed(100);    
  stepper1.setAcceleration(1000); 
}
 
void loop() {
 
  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(2048);              
  } 
   else if ( stepper1.currentPosition() == 2048)
   {
    stepper1.moveTo(0);             
  }         
  stepper1.run();
 
}
