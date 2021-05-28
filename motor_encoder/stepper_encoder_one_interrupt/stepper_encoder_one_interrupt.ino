#include "AccelStepper.h"

//编码器，利用中断实现（AB通道未实现正反转）
volatile long temp, counter=0;
#define Bchannel 2
#define Achannel 3
#define J1dirPin  23
#define J1stepPin 22

AccelStepper stepper1(1,J1stepPin,J1dirPin);

void setup() {
  Serial.begin(115200);

  pinMode(J1stepPin,OUTPUT); 
  pinMode(J1dirPin,OUTPUT);
  pinMode(Bchannel,INPUT_PULLUP);
  pinMode(Achannel,INPUT_PULLUP);

  stepper1.setMaxSpeed(500);   
  stepper1.setAcceleration(100); 
  
  attachInterrupt(digitalPinToInterrupt(Achannel), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(Bchannel), ai1, RISING);
  /*attachInterrupt(digitalPinToInterrupt(Xchannel), ai2, RISING);*/
}

void loop() {
  if(temp!=counter){
    Serial.println(counter);
  }
  temp=counter;
  
 if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(400);              
  } 
   else if ( stepper1.currentPosition() == 400)
   {
    stepper1.moveTo(0);             
  }    
  stepper1.run();
}

void ai0(){
  if ((digitalRead(Achannel)==HIGH)&&(digitalRead(Bchannel)==LOW)){
    counter++;
    }
    else{
      counter--;
      }
  }

void ai1(){
  if ((digitalRead(Achannel)==HIGH)&&(digitalRead(Bchannel)==HIGH)){
    counter++;
    }
    else{
      counter--;
    }
   
  }
