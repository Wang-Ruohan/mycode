#include <AccelStepper.h>
#include <MultiStepper.h>

#define numdata_length 12
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

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers1;
MultiStepper steppers2;
//test with uint8 converted to long
unsigned int x = 1000;
void setup() {
  Serial.begin(115200);

  // Configure each stepper 后面的注释是让他走了多少
  joint1.setMaxSpeed(100);//13000
  joint2.setMaxSpeed(150);//2500
  joint3.setMaxSpeed(250);//1300
  joint4.setMaxSpeed(100);//1200
  joint5.setMaxSpeed(300);//500
  joint6.setMaxSpeed(30);

  joint7.setMaxSpeed(100);// -13000
  joint8.setMaxSpeed(150);// -2500
  joint9.setMaxSpeed(250);// -1300
  joint10.setMaxSpeed(100);// -1200
  joint11.setMaxSpeed(300);// 500 就是五百，不是负的，因为机械结构没有装反
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

  long positions1[6]; // Array of desired stepper positions
  long positions2[6];
  
void loop() {

 
  // Move to a different coordinate
  positions1[0] +=5;
  positions1[1] =0;
  positions1[2] =0;
  positions1[3] =0;
  positions1[4] =0;
  positions1[5] =0;
  
  positions2[0] +=5;
  positions2[1] =0;
  positions2[2] =0;
  positions2[3] =0;
  positions2[4] =0;
  positions2[5] =0;
  steppers1.moveTo(positions1);
  steppers2.moveTo(positions2);
  steppers1.run();
  steppers2.run();
  //steppers1.runSpeedToPosition(); // Blocks until all are in position
 // steppers2.runSpeedToPosition(); 

}
