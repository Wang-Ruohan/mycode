#include <SCoop.h>
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

Encoder J1encoder(2,3);
Encoder J2encoder(4,5);
Encoder J3encoder(6,7);
Encoder J4encoder(8,9);
Encoder J5encoder(10,11);
Encoder J6encoder(12,13);

// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper joint1(1,LJ1_STEP_PIN, LJ1_DIR_PIN);
AccelStepper joint2(1,LJ2_STEP_PIN, LJ2_DIR_PIN);
AccelStepper joint3(1,LJ3_STEP_PIN, LJ3_DIR_PIN);
AccelStepper joint4(1,LJ4_STEP_PIN, LJ4_DIR_PIN);
AccelStepper joint5(1,LJ5_STEP_PIN, LJ5_DIR_PIN);
AccelStepper joint6(1,LJ6_STEP_PIN, LJ6_DIR_PIN);
MultiStepper steppers1;

long positionJ1 = -999;
long positionJ2 = -999;
long positionJ3 = -999;
long positionJ4 = -999;
long positionJ5 = -999;
long positionJ6 = -999;
long newJ1,newJ2,newJ3,newJ4,newJ5,newJ6;

defineTaskLoop(arm_moving){
  long positions1[6]; // Array of desired stepper positions
  positions1[0] = 0; 
  positions1[1] = 0; 
  positions1[2] = 0; 
  positions1[3] = 0; 
  positions1[4] = 0; 
  positions1[5] = 0;

  steppers1.moveTo(positions1);
  steppers1.runSpeedToPosition();

   // Move to a different coordinate
  positions1[0] = -500;
  positions1[1] = 100;
  positions1[2] = 100;
  positions1[3] = 100;
  positions1[4] = -100;
  positions1[5] = 100;

  steppers1.moveTo(positions1);
  steppers1.runSpeedToPosition();
  
  }


defineTaskLoop(encoder_reading){
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


void setup() {
  Serial.begin(2000000);
  Serial.println("TwoKnobs Encoder Test:");

  // Configure each stepper 后面的注释是 最大速度 走了多少
  joint1.setMaxSpeed(1000);//          10000   13000
  joint2.setMaxSpeed(1500);//          1500    2500
  joint3.setMaxSpeed(2500);//          2500    1300
  joint4.setMaxSpeed(10000);//         1000    1200
  joint5.setMaxSpeed(3000);//          3000    500
  joint6.setMaxSpeed(3000);

  // Then give them to MultiStepper to manage
  steppers1.addStepper(joint1);
  steppers1.addStepper(joint2);
  steppers1.addStepper(joint3);
  steppers1.addStepper(joint4);
  steppers1.addStepper(joint5);
  steppers1.addStepper(joint6);
  mySCoop.start();

}

void loop() {
  yield();
  
}
