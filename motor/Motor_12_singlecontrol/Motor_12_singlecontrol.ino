#include "Encoder.h"
#include "AccelStepper.h"

// 定义步进电机引脚
#define LJ1dirPin  23
#define LJ1stepPin 22
#define LJ2dirPin  25
#define LJ2stepPin 24
#define LJ3dirPin  27
#define LJ3stepPin 26
#define LJ4dirPin  29
#define LJ4stepPin 28
#define LJ5dirPin  31
#define LJ5stepPin 30
#define LJ6dirPin  33
#define LJ6stepPin 32
#define RJ1dirPin  35
#define RJ1stepPin 34
#define RJ2dirPin  37
#define RJ2stepPin 36
#define RJ3dirPin  39
#define RJ3stepPin 38
#define RJ4dirPin  41
#define RJ4stepPin 40
#define RJ5dirPin  43
#define RJ5stepPin 42
#define RJ6dirPin  45
#define RJ6stepPin 44

/*
Encoder J1encoder(2,3);
Encoder J2encoder(4,5);
Encoder J3encoder(6,7);
Encoder J4encoder(8,9);
Encoder J5encoder(10,11);
Encoder J6encoder(12,13);*/

AccelStepper stepper1(1,LJ1stepPin,LJ1dirPin);
AccelStepper stepper2(1,LJ2stepPin,LJ2dirPin);
AccelStepper stepper3(1,LJ3stepPin,LJ3dirPin);
AccelStepper stepper4(1,LJ4stepPin,LJ4dirPin);
AccelStepper stepper5(1,LJ5stepPin,LJ5dirPin);
AccelStepper stepper6(1,LJ6stepPin,LJ6dirPin);
AccelStepper stepper7(1,RJ1stepPin,RJ1dirPin);
AccelStepper stepper8(1,RJ2stepPin,RJ2dirPin);
AccelStepper stepper9(1,RJ3stepPin,RJ3dirPin);
AccelStepper stepper10(1,RJ4stepPin,RJ4dirPin);
AccelStepper stepper11(1,RJ5stepPin,RJ5dirPin);
AccelStepper stepper12(1,RJ6stepPin,RJ6dirPin);
/*
long positionJ1 = -999;
long positionJ2 = -999;
long positionJ3 = -999;
long positionJ4 = -999;
long positionJ5 = -999;
long positionJ6 = -999;

long newJ1,newJ2,newJ3,newJ4,newJ5,newJ6;*/

void setup() {
  Serial.begin(2000000); 
//Serial.println("TwoKnobs Encoder Test:");
  
  pinMode(LJ1stepPin,OUTPUT);
  pinMode(LJ1dirPin,OUTPUT);
  pinMode(LJ2stepPin,OUTPUT);
  pinMode(LJ2dirPin,OUTPUT);
  pinMode(LJ3stepPin,OUTPUT);
  pinMode(LJ3dirPin,OUTPUT);
  pinMode(LJ4stepPin,OUTPUT);
  pinMode(LJ4dirPin,OUTPUT);
  pinMode(LJ5stepPin,OUTPUT);
  pinMode(LJ5dirPin,OUTPUT);
  pinMode(LJ6stepPin,OUTPUT);
  pinMode(LJ6dirPin,OUTPUT);
  pinMode(RJ1stepPin,OUTPUT);
  pinMode(RJ1dirPin,OUTPUT);
  pinMode(RJ2stepPin,OUTPUT);
  pinMode(RJ2dirPin,OUTPUT);
  pinMode(RJ3stepPin,OUTPUT);
  pinMode(RJ3dirPin,OUTPUT);
  pinMode(RJ4stepPin,OUTPUT);
  pinMode(RJ4dirPin,OUTPUT);
  pinMode(RJ5stepPin,OUTPUT);
  pinMode(RJ5dirPin,OUTPUT);
  pinMode(RJ6stepPin,OUTPUT);
  pinMode(RJ6dirPin,OUTPUT);
  
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

  stepper7.setMaxSpeed(500);
  stepper7.setAcceleration(1000);
  stepper8.setMaxSpeed(500);
  stepper8.setAcceleration(1000);
  stepper9.setMaxSpeed(500);
  stepper9.setAcceleration(1000);
  stepper10.setMaxSpeed(500);
  stepper10.setAcceleration(1000);
  stepper11.setMaxSpeed(500);
  stepper11.setAcceleration(1000);
  stepper12.setMaxSpeed(500);
  stepper12.setAcceleration(1000);
 
  
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
    stepper2.moveTo(1000);              
  }
   else if ( stepper2.currentPosition() == 1000)
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
  
//J1 50：1减速比，4：1带传动 步进角0.9° 编码器转一圈 需要走400步，J1关节转了1.8°
  if ( stepper7.currentPosition() == 0 ){ 
    stepper7.moveTo(-400);              
  }
   else if ( stepper7.currentPosition() == -400)
   {
    stepper7.moveTo(0);
  }
  stepper7.run();
//J2 50：1减速比，无外加减速 步进角0.9° 编码器转一圈 需要走400步，J2关节转了7.2°
  if ( stepper8.currentPosition() == 0 ){ 
    stepper8.moveTo(-1000);              
  }
   else if ( stepper8.currentPosition() == -1000)
   {
    stepper8.moveTo(0);
  }
  stepper8.run();
//J3 50：1减速比 无外加减速 步进角0.9° 编码器转一圈 需要走400步，J3关节转了7.2°
  if ( stepper9.currentPosition() == 0 ){ 
    stepper9.moveTo(-400);              
  }
   else if ( stepper9.currentPosition() == -400)
   {
    stepper9.moveTo(0);
  }
  stepper9.run();
//J4 13*212/289的减速比 2.8：1减速比 步进角0.9度 编码器转一圈 需要走400步 J4关节转了13.482°
  if ( stepper10.currentPosition() == 0 ){ 
    stepper10.moveTo(-400);              
  }
   else if ( stepper10.currentPosition() == -400)
   {
    stepper10.moveTo(0);
  }
  stepper10.run();
//J5 无减速比 步进角1.8度 编码器转一圈 需要走800步 J5关节转多少度需要计算
  if ( stepper11.currentPosition() == 0 ){ 
    stepper11.moveTo(-400);              
  }
   else if ( stepper11.currentPosition() == -400)
   {
    stepper11.moveTo(0);
  }
  stepper11.run();
//J6 19*38/137的减速比 步进角0.9° 编码器转一圈 需要走400步 J6关节转了68.31°
  if ( stepper12.currentPosition() == 0 ){ 
    stepper12.moveTo(-400);              
  }
   else if ( stepper12.currentPosition() == -400)
   {
    stepper12.moveTo(0);
  }
  stepper12.run();
  /*
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
  }*/
}
