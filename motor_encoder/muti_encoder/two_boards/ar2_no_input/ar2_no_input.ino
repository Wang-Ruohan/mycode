#include <SCoop.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

String device_B_String="";
String device_A_String="";

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


// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper joint1(1,LJ1_STEP_PIN, LJ1_DIR_PIN);
AccelStepper joint2(1,LJ2_STEP_PIN, LJ2_DIR_PIN);
AccelStepper joint3(1,LJ3_STEP_PIN, LJ3_DIR_PIN);
AccelStepper joint4(1,LJ4_STEP_PIN, LJ4_DIR_PIN);
AccelStepper joint5(1,LJ5_STEP_PIN, LJ5_DIR_PIN);
AccelStepper joint6(1,LJ6_STEP_PIN, LJ6_DIR_PIN);
MultiStepper steppers1;


void setup() {
  Serial.begin(2000000);
  Serial1.begin(115200);

  // Configure each stepper 后面的注释是 最大速度 走了多少
  joint1.setMaxSpeed(100);//         10000   13000
  joint2.setMaxSpeed(150);//          1500    2500
  joint3.setMaxSpeed(250);//          2500    1300
  joint4.setMaxSpeed(100);//         10000    1200
  joint5.setMaxSpeed(300);//          3000    500
  joint6.setMaxSpeed(300);

  // Then give them to MultiStepper to manage
  steppers1.addStepper(joint1);
  steppers1.addStepper(joint2);
  steppers1.addStepper(joint3);
  steppers1.addStepper(joint4);
  steppers1.addStepper(joint5);
  steppers1.addStepper(joint6);
  mySCoop.start();
}

defineTaskLoop(serial_read){
  //如果软件串口有数据
  if(Serial1.available())
  {
    //从软件串口读出一字节，写入硬件串口
    Serial.write(Serial1.read());
  }
  }

long positions1[6];

void loop() {


 /* positions1[0] = 0; 
  positions1[1] = 0; 
  positions1[2] = 0; 
  positions1[3] = 0; 
  positions1[4] = 0; 
  positions1[5] = 0;*/

 /* positions1[0] += -5; 
  positions1[1] += 1; 
  positions1[2] += 1; 
  positions1[3] += 1; 
  positions1[4] += -1; 
  positions1[5] += 1;*/
  steppers1.moveTo(positions1);
  steppers1.runSpeedToPosition();
/*
  //如果软件串口有数据
  if(Serial1.available())
  {
    //从软件串口读出一字节，写入硬件串口
    Serial.write(Serial1.read());
  }
*/
  // Move to a different coordinate
  /*positions1[0] = -500;
  positions1[1] = 100;
  positions1[2] = 100;
  positions1[3] = 100;
  positions1[4] = -100;
  positions1[5] = 100;

  steppers1.moveTo(positions1);
  steppers1.runSpeedToPosition();*/
  yield();
}
