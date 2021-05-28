#include <Encoder.h>
#include <AccelStepper.h>
#include <MultiStepper.h>


//需要从机械臂的后面看左右 L为left R为right
// Joint 1
#define LJ1_STEP_PIN 22
#define LJ1_DIR_PIN 23

// Joint 2
#define LJ2_STEP_PIN 24 
#define LJ2_DIR_PIN 25

// Joint 3
#define LJ3_STEP_PIN 26
#define LJ3_DIR_PIN 27

// Joint 4
#define LJ4_STEP_PIN 28
#define LJ4_DIR_PIN 29

// Joint 5 
#define LJ5_STEP_PIN 30
#define LJ5_DIR_PIN 31

// Joint 6 
#define LJ6_STEP_PIN 32
#define LJ6_DIR_PIN 33
//
// Joint 1
#define RJ1_STEP_PIN 34
#define RJ1_DIR_PIN 35

// Joint 2
#define RJ2_STEP_PIN 36
#define RJ2_DIR_PIN 37

// Joint 3
#define RJ3_STEP_PIN 38
#define RJ3_DIR_PIN 39

// Joint 4
#define RJ4_STEP_PIN 40
#define RJ4_DIR_PIN 41

// Joint 5 
#define RJ5_STEP_PIN 42
#define RJ5_DIR_PIN 43

// Joint 6 
#define RJ6_STEP_PIN 44
#define RJ6_DIR_PIN 45

Encoder LJ1encoder(2,3);
Encoder LJ2encoder(4,5);
Encoder LJ3encoder(6,7);
Encoder LJ4encoder(8,9);
Encoder LJ5encoder(10,11);
Encoder LJ6encoder(12,13);

Encoder RJ1encoder(46,47);
Encoder RJ2encoder(48,49);
Encoder RJ3encoder(50,51);
Encoder RJ4encoder(52,53);
Encoder RJ5encoder(16,17);
Encoder RJ6encoder(14,15);

// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper joint1(1,LJ1_STEP_PIN, LJ1_DIR_PIN);
AccelStepper joint2(1,LJ2_STEP_PIN, LJ2_DIR_PIN);
AccelStepper joint3(1,LJ3_STEP_PIN, LJ3_DIR_PIN);
AccelStepper joint4(1,LJ4_STEP_PIN, LJ4_DIR_PIN);
AccelStepper joint5(1,LJ5_STEP_PIN, LJ5_DIR_PIN);
AccelStepper joint6(1,LJ6_STEP_PIN, LJ6_DIR_PIN);

AccelStepper joint7(1,RJ1_STEP_PIN, RJ1_DIR_PIN);
AccelStepper joint8(1,RJ2_STEP_PIN, RJ2_DIR_PIN);
AccelStepper joint9(1,RJ3_STEP_PIN, RJ3_DIR_PIN);
AccelStepper joint10(1,RJ4_STEP_PIN, RJ4_DIR_PIN);
AccelStepper joint11(1,RJ5_STEP_PIN, RJ5_DIR_PIN);
AccelStepper joint12(1,RJ6_STEP_PIN, RJ6_DIR_PIN);
MultiStepper steppers1;
MultiStepper steppers2;

long positionLJ1 = -999;
long positionLJ2 = -999;
long positionLJ3 = -999;
long positionLJ4 = -999;
long positionLJ5 = -999;
long positionLJ6 = -999;

long positionRJ1 = -999;
long positionRJ2 = -999;
long positionRJ3 = -999;
long positionRJ4 = -999;
long positionRJ5 = -999;
long positionRJ6 = -999;

long newLJ1,newLJ2,newLJ3,newLJ4,newLJ5,newLJ6,newRJ1,newRJ2,newRJ3,newRJ4,newRJ5,newRJ6;


void setup() {
  Serial.begin(2000000);
  Serial.println("TwoKnobs Encoder Test:");

  // Configure each stepper 后面的注释是 最大速度 走了多少
  joint1.setMaxSpeed(100);//         10000   13000
  joint2.setMaxSpeed(150);//          1500    2500
  joint3.setMaxSpeed(250);//          2500    1300
  joint4.setMaxSpeed(100);//         10000    1200
  joint5.setMaxSpeed(30);//          3000    500
  joint6.setMaxSpeed(30);

    // Configure each stepper 后面的注释是 最大速度 走了多少
  joint7.setMaxSpeed(100);//         10000   13000
  joint8.setMaxSpeed(150);//          1500    2500
  joint9.setMaxSpeed(250);//          2500    1300
  joint10.setMaxSpeed(100);//         10000    1200
  joint11.setMaxSpeed(30);//          3000    500
  joint12.setMaxSpeed(30);

  // Then give them to MultiStepper to manage
  steppers1.addStepper(joint1);
  steppers1.addStepper(joint2);
  steppers1.addStepper(joint3);
  steppers1.addStepper(joint4);
  steppers1.addStepper(joint5);
  steppers1.addStepper(joint6);

  steppers2.addStepper(joint7);
  steppers2.addStepper(joint8);
  steppers2.addStepper(joint9);
  steppers2.addStepper(joint10);
  steppers2.addStepper(joint11);
  steppers2.addStepper(joint12);

}
  long positions1[6];
  long positions2[6];
  
void loop() {
 // long positions1[6]; // Array of desired stepper positions

 /* positions1[0] = 400; 
  positions1[1] = 0; 
  positions1[2] = 0; 
  positions1[3] = 0; 
  positions1[4] = 0; 
  positions1[5] = 0;*/
/*
  positions1[0] += -5; 
  positions1[1] += 1; 
  positions1[2] += 1; 
  positions1[3] += 1; 
  positions1[4] += -1; 
  positions1[5] += 1;
  
  positions2[0] += -5; 
  positions2[1] += 1; 
  positions2[2] += 1; 
  positions2[3] += 1; 
  positions2[4] += -1; 
  positions2[5] += 1;
  steppers1.moveTo(positions1);
  steppers1.run();

  steppers2.moveTo(positions2);
  steppers2.run();*/
  
  newLJ1 = LJ1encoder.read(); 
  newLJ2 = LJ2encoder.read();
  newLJ3 = LJ3encoder.read();
  newLJ4 = LJ4encoder.read();
  newLJ5 = LJ5encoder.read();
  newLJ6 = LJ6encoder.read();

  newRJ1 = RJ1encoder.read();
  newRJ2 = RJ2encoder.read();
  newRJ3 = RJ3encoder.read();
  newRJ4 = RJ4encoder.read();
  newRJ5 = RJ5encoder.read();
  newRJ6 = RJ6encoder.read();

  

   if (newLJ1!= positionLJ1||newLJ2!=positionLJ2||newLJ3!= positionLJ3||newLJ4!=positionLJ4||newLJ5!= positionLJ5||newLJ6!=positionLJ6||newRJ1!= positionRJ1||newRJ2!=positionRJ2||newRJ3!= positionRJ3||newRJ4!=positionRJ4||newRJ5!= positionRJ5||newRJ6!=positionRJ6) {
    Serial.print("LJ1 = ");
    Serial.print(newLJ1);
    Serial.print(", LJ2 = ");
    Serial.print(newLJ2);
    Serial.print(", LJ3 = ");
    Serial.print(newLJ3);
    Serial.print(", LJ4 = ");
    Serial.print(newLJ4);
    Serial.print(", LJ5 = ");
    Serial.print(newLJ5);
    Serial.print(", LJ6 = ");
    Serial.print(newLJ6);
    
    Serial.print(", RJ1 = ");
    Serial.print(newRJ1);
    Serial.print(", RJ2 = ");
    Serial.print(newRJ2);
    Serial.print(", RJ3 = ");
    Serial.print(newRJ3);
    Serial.print(", RJ4 = ");
    Serial.print(newRJ4);
    Serial.print(", RJ5 = ");
    Serial.print(newRJ5);
    Serial.print(", RJ6 = ");
    Serial.print(newRJ6);
    Serial.println();
    positionLJ1 = newLJ1;
    positionLJ2 = newLJ2;
    positionLJ3 = newLJ3;
    positionLJ4 = newLJ4;
    positionLJ5 = newLJ5;
    positionLJ6 = newLJ6;
    
    positionRJ1 = newRJ1;
    positionRJ2 = newRJ2;
    positionRJ3 = newRJ3;
    positionRJ4 = newRJ4;
    positionRJ5 = newRJ5;
    positionRJ6 = newRJ6;
  }   

   if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    LJ1encoder.write(0);
    LJ2encoder.write(0);
    LJ3encoder.write(0);          
    LJ4encoder.write(0);
    LJ5encoder.write(0);
    LJ6encoder.write(0);
    
    RJ1encoder.write(0);
    RJ2encoder.write(0);
    RJ3encoder.write(0);
    RJ4encoder.write(0);
    RJ5encoder.write(0);
    RJ6encoder.write(0);
  }

  // Move to a different coordinate
/*  positions1[0] = -500;
  positions1[1] = 100;
  positions1[2] = 100;
  positions1[3] = 100;
  positions1[4] = -100;
  positions1[5] = 100;

  steppers1.moveTo(positions1);
  steppers1.runSpeedToPosition();*/
}
