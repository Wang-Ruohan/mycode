#include "AccelStepper.h"

//编码器，利用中断实现（AB通道未实现正反转）
volatile long J1temp, J1counter,J2temp,J2counter=0;
#define J1Bchannel 3
#define J1Achannel 2
#define J2Bchannel 19
#define J2Achannel 18
#define J1dirPin  23
#define J1stepPin 22
#define J2dirPin  25
#define J2stepPin 24

String getstring;

AccelStepper stepper1(1,J1stepPin,J1dirPin);
AccelStepper stepper2(1,J2stepPin,J2dirPin);

void setup() {
  Serial.begin(115200);

  pinMode(J1stepPin,OUTPUT); 
  pinMode(J1dirPin,OUTPUT);
  pinMode(J1Bchannel,INPUT_PULLUP);
  pinMode(J1Achannel,INPUT_PULLUP);
  
  pinMode(J2stepPin,OUTPUT); 
  pinMode(J2dirPin,OUTPUT);
  pinMode(J2Bchannel,INPUT_PULLUP);
  pinMode(J2Achannel,INPUT_PULLUP);

  stepper1.setMaxSpeed(500);   
  stepper1.setAcceleration(100); 

  stepper2.setMaxSpeed(500);   
  stepper2.setAcceleration(100); 
  
  attachInterrupt(digitalPinToInterrupt(J1Achannel), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(J1Bchannel), ai1, RISING);
  /*attachInterrupt(digitalPinToInterrupt(Xchannel), ai2, RISING);*/
  attachInterrupt(digitalPinToInterrupt(J2Achannel), ai2, RISING);
  attachInterrupt(digitalPinToInterrupt(J2Bchannel), ai3, RISING);
}

void loop() {
  getstring="";
  
  if(J1temp!=J1counter){
   getstring+=J1counter;
  
  }

  if(J2temp!=J2counter){
    
   getstring=J2counter+getstring;
    }
 Serial.println(getstring);
 
  J1temp=J1counter;
  J2temp=J2counter;
  
 if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(400);              
  } 
   else if ( stepper1.currentPosition() == 400)
   {
    stepper1.moveTo(0);             
  }    
  stepper1.run();

  if ( stepper2.currentPosition() == 0 ){ 
    stepper2.moveTo(400);              
  } 
   else if ( stepper2.currentPosition() == 400)
   {
    stepper2.moveTo(0);             
  }    
  stepper2.run();
}

void ai0(){
  if ((digitalRead(J1Achannel)==HIGH)&&(digitalRead(J1Bchannel)==LOW)){
    J1counter--;
    }
    else{
      J1counter++;
      }
  }

void ai1(){
  if ((digitalRead(J1Achannel)==HIGH)&&(digitalRead(J1Bchannel)==HIGH)){
    J1counter--;
    }
    else{
      J1counter++;
    }
   
  }



void ai2(){
  if ((digitalRead(J2Achannel)==HIGH)&&(digitalRead(J2Bchannel)==LOW)){
    J2counter--;
    }
    else{
     J2counter++;
      }
  }

void ai3(){
  if ((digitalRead(J2Achannel)==HIGH)&&(digitalRead(J2Bchannel)==HIGH)){
    J2counter--;
    }
    else{
      J2counter++;
    }
   
  }
