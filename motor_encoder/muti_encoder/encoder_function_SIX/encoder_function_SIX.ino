#include "Encoder.h"
#include "AccelStepper.h"

// 定义步进电机引脚
#define J1dirPin  23
#define J1stepPin 22
#define J2dirPin  25
#define J2stepPin 24
#define J3dirPin  27
#define J3stepPin 26
#define J4dirPin  29
#define J4stepPin 28
#define J5dirPin  31
#define J5stepPin 30
#define J6dirPin  33
#define J6stepPin 32


Encoder J1encoder(2,3);
Encoder J2encoder(4,5);
Encoder J3encoder(6,7);
Encoder J4encoder(8,9);
Encoder J5encoder(10,11);
Encoder J6encoder(12,13);

AccelStepper stepper1(1,J1stepPin,J1dirPin);
AccelStepper stepper2(1,J2stepPin,J2dirPin);
AccelStepper stepper3(1,J3stepPin,J3dirPin);
AccelStepper stepper4(1,J4stepPin,J4dirPin);
AccelStepper stepper5(1,J5stepPin,J5dirPin);
AccelStepper stepper6(1,J6stepPin,J6dirPin);

long positionJ1 = -999;
long positionJ2 = -999;
long positionJ3 = -999;
long positionJ4 = -999;
long positionJ5 = -999;
long positionJ6 = -999;

long newJ1,newJ2,newJ3,newJ4,newJ5,newJ6;

void setup() {
  Serial.begin(2000000);
  Serial.println("TwoKnobs Encoder Test:");
  
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
  
  stepper1.setMaxSpeed(500);
  stepper1.setAcceleration(1000);
  stepper2.setMaxSpeed(500);
  stepper2.setAcceleration(1000);
  stepper3.setMaxSpeed(500);
  stepper3.setAcceleration(1000);
  stepper4.setMaxSpeed(500);
  stepper4.setAcceleration(1000);
  stepper5.setMaxSpeed(500);
  stepper5.setAcceleration(1000);
  stepper6.setMaxSpeed(500);
  stepper6.setAcceleration(1000);
 
  
}


void loop() {
  
//先都假设让电机屁股输出轴（或者说是编码器）转一圈
//J1 50：1减速比，4：1带传动 步进角0.9° 编码器转一圈 需要走400步，J1关节转了1.8°
  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(400);              
  }
   else if ( stepper1.currentPosition() == 400)
   {
    stepper1.moveTo(0);
  }
  stepper1.run();
//J2 50：1减速比，无外加减速 步进角0.9° 编码器转一圈 需要走400步，J2关节转了7.2°
  if ( stepper2.currentPosition() == 0 ){ 
    stepper2.moveTo(400);              
  }
   else if ( stepper2.currentPosition() == 400)
   {
    stepper2.moveTo(0);
  }
  stepper2.run();
//J3 50：1减速比 无外加减速 步进角0.9° 编码器转一圈 需要走400步，J3关节转了7.2°
  if ( stepper3.currentPosition() == 0 ){ 
    stepper3.moveTo(400);              
  }
   else if ( stepper3.currentPosition() == 400)
   {
    stepper3.moveTo(0);
  }
  stepper3.run();
//J4 13*212/289的减速比 2.8：1减速比 步进角0.9度 编码器转一圈 需要走400步 J4关节转了13.482°
  if ( stepper4.currentPosition() == 0 ){ 
    stepper4.moveTo(400);              
  }
   else if ( stepper4.currentPosition() == 400)
   {
    stepper4.moveTo(0);
  }
  stepper4.run();
//J5 无减速比 步进角1.8度 编码器转一圈 需要走800步 J5关节转多少度需要计算
  if ( stepper5.currentPosition() == 0 ){ 
    stepper5.moveTo(400);              
  }
   else if ( stepper5.currentPosition() == 400)
   {
    stepper5.moveTo(0);
  }
  stepper5.run();
//J6 19*38/137的减速比 步进角0.9° 编码器转一圈 需要走400步 J6关节转了68.31°
  if ( stepper6.currentPosition() == 0 ){ 
    stepper6.moveTo(400);              
  }
   else if ( stepper6.currentPosition() == 400)
   {
    stepper6.moveTo(0);
  }
  stepper6.run();

  newJ1 = J1encoder.read();
  newJ2 = J2encoder.read();
  if (newJ1!= positionJ1||newJ2!=positionJ2||newJ3!= positionJ3||newJ4!=positionJ4||newJ5!= positionJ5||newJ6!=positionJ6) {
    Serial.print("J1 = ");
    Serial.print(newJ1);
    Serial.print(", J2 = ");
    Serial.print(newJ2);
    Serial.print(", J3 = ");
    Serial.print(newJ3);
    Serial.print(", J4 = ");
    Serial.print(newJ4);
    Serial.print(", J5 = ");
    Serial.print(newJ5);
    Serial.print(", J6 = ");
    Serial.print(newJ6);
    Serial.println();
    positionJ1 = newJ1;
    positionJ2 = newJ2;
    positionJ3 = newJ3;
    positionJ4 = newJ4;
    positionJ5 = newJ5;
    positionJ6 = newJ6;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    J1encoder.write(0);
    J2encoder.write(0);
    J3encoder.write(0);
    J4encoder.write(0);
    J5encoder.write(0);
    J6encoder.write(0);
  }
}
