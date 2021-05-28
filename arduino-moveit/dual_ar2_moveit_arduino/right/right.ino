/* Purpose: This sketch uses ROS as well as MultiStepper, AccelStepper, and Servo libraries to control the 
 * BCN3D Moveo robotic arm. In this setup, a Ramps 1.4 shield is used on top of an Arduino Mega 2560.  
 * Subscribing to the following ROS topics: 1) joint_steps, 2) gripper_angle
 *    1) joint_steps is computed from the simulation in PC and sent Arduino via rosserial.  It contains
 *       the steps (relative to the starting position) necessary for each motor to move to reach the goal position.
 *    2) gripper_angle contains the necessary gripper angle to grasp the object when the goal state is reached 
 * 
 * Publishing to the following ROS topics: joint_steps_feedback
 *    1) joint_steps_feedback is a topic used for debugging to make sure the Arduino is receiving the joint_steps data
 *       accurately
 *       
 * Author: Jesse Weisberg
 */
#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <math.h>
#include <std_msgs/Int16.h>
#include <std_msgs/UInt16.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

// Joint 1
#define J1_STEP_PIN 34
#define J1_DIR_PIN 35

// Joint 2
#define J2_STEP_PIN 36
#define J2_DIR_PIN 37

// Joint 3
#define J3_STEP_PIN 38
#define J3_DIR_PIN 39

// Joint 4
#define J4_STEP_PIN 40
#define J4_DIR_PIN 41

// Joint 5 
#define J5_STEP_PIN 42
#define J5_DIR_PIN 43

// Joint 6 
#define J6_STEP_PIN 44
#define J6_DIR_PIN 45

AccelStepper joint1(1,J1_STEP_PIN, J1_DIR_PIN);
AccelStepper joint2(1,J2_STEP_PIN, J2_DIR_PIN);
AccelStepper joint3(1,J3_STEP_PIN, J3_DIR_PIN);
AccelStepper joint4(1,J4_STEP_PIN, J4_DIR_PIN);
AccelStepper joint5(1,J5_STEP_PIN, J5_DIR_PIN);
AccelStepper joint6(1,J6_STEP_PIN, J6_DIR_PIN);


MultiStepper steppers;

int joint_step[6];

ros::NodeHandle nh;
std_msgs::Int16 msg;
std_msgs::Int16MultiArray step_msg;

void arm_cb(const std_msgs::Int16MultiArray& arm_steps){
  for(int i=0;i<6;i++)
  {
    joint_step[i] = arm_steps.data[i];
  }
}

//instantiate subscribers
ros::Subscriber<std_msgs::Int16MultiArray>  arm_sub("joint_steps",arm_cb); //subscribes to joint_steps on arm

//to publish from terminal: rostopic pub gripper_angle std_msgs/UInt16 <0-180>

void setup() {
  //put your setup code here, to run once:
  Serial.begin(115200);
  nh.initNode();
  nh.subscribe(arm_sub);

  // Configure each stepper
  joint1.setMaxSpeed(1000);
  joint2.setMaxSpeed(1000);
  joint3.setMaxSpeed(1000);
  joint4.setMaxSpeed(1300);
  joint5.setMaxSpeed(1000);
  joint6.setMaxSpeed(1000);

  // Then give them to MultiStepper to manage
  steppers.addStepper(joint1);
  steppers.addStepper(joint2);
  steppers.addStepper(joint3);
  steppers.addStepper(joint4);
  steppers.addStepper(joint5);
  steppers.addStepper(joint6);

}

void loop() {
  
    long positions[6];  // Array of desired stepper positions must be long
    positions[0] = joint_step[0]; // negated since the real robot rotates in the opposite direction as ROS
    //positions[0]=0;
    positions[1] = joint_step[1];
    //positions[1]=0;
    positions[2] = joint_step[2];
    //positions[2]=0; 
    positions[3] = -joint_step[3];
    //positions[3]=0;
    positions[4] = joint_step[4]; 
    //positions[4] = 0;
    positions[5] = joint_step[5]; 
    Serial.println(positions[3]);
    
    steppers.moveTo(positions);
    steppers.runSpeedToPosition(); // Blocks until all are in position
    
  nh.spinOnce();
  delay(1);
  
}
