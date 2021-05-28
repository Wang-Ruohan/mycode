#include "Encoder.h"
#include "AccelStepper.h"
#include "MultiStepper.h"

#define numdata_length 6
String comdata = "";
long numdata[numdata_length] = {0};
int flag = 0;

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

void setup() {
  Serial.begin(2000000);
 // Serial.println("TwoKnobs Encoder Test:");

  // Configure each stepper 后面的注释是让他走了多少
  joint1.setMaxSpeed(10000);//13000
  joint2.setMaxSpeed(1500);//2500
  joint3.setMaxSpeed(2500);//1300
  joint4.setMaxSpeed(10000);//1200
  joint5.setMaxSpeed(3000);//500
  joint6.setMaxSpeed(3000);

  // Then give them to MultiStepper to manage
  steppers1.addStepper(joint1);
  steppers1.addStepper(joint2);
  steppers1.addStepper(joint3);
  steppers1.addStepper(joint4);
  steppers1.addStepper(joint5);
  steppers1.addStepper(joint6);
  
}


void loop() {
 long positions1[6];
  positions1[0] = 0; 
  positions1[1] = 0; 
  positions1[2] = 0; 
  positions1[3] = 0; 
  positions1[4] = 0; 
  positions1[5] = 0;
  
  steppers1.moveTo(positions1);
  steppers1.runSpeedToPosition();
  delay(1);
  int j = 0;
  while (Serial.available() > 0)
  {
    comdata += char(Serial.read());
    delay(2);
    flag = 1;
  }
  if(flag == 1) {
  for(int i = 0; i < comdata.length() ; i++){
    if(comdata[i] == ','){
      j++;
    }
    else{
      numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
    }
  }
  comdata = String("");
  flag = 0;
  }
  // Move to a different coordinate
  positions1[0] = -numdata[0];
  positions1[1] = numdata[1];
  positions1[2] = numdata[2];
  positions1[3] = numdata[3];
  positions1[4] = -numdata[4];
  positions1[5] = numdata[5];
  
  steppers1.moveTo(positions1);
  steppers1.runSpeedToPosition();
 // steppers1.runSpeedToPosition(); // Blocks until all are in position
  for(int i = 0; i < numdata_length; i++){
  numdata[i] = 0;
  }



  long newLeft, newRight;
  newLeft = J1encoder.read();
  newRight = J2encoder.read();
  if (newLeft != positionJ1 || newRight != positionJ2) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionJ1 = newLeft;
    positionJ2 = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    J1encoder.write(0);
    J2encoder.write(0);
  }
}
