/* Purpose: This sketch uses ROS as well as MultiStepper, AccelStepper, and Servo libraries to control the 
 * BCN3D Moveo robotic arm. In this setup, a Ramps 1.4 shield is used on top of an Arduino Mega 2560.  
 * Subscribing to the following ROS topics: 1) joint_steps, 2) gripper_angle
 *    1) joint_steps is computed from the simulation in PC and sent Arduino via rosserial.  It contains
 *       the steps (relative to the starting position) necessary for each motor to move to reach the goal position.
 *    2) gripper_angle contains the necessary gripper angle to grasp the object when the goal state is reached 
 * 
 * Publishing to the following ROS topics: joint_steps_feedback
 *    1) joint_steps_feedback is a topic used for debugging to make sure the Arduino is receiving the joint_steps data
 *    
 *       accurately
 *       
 *       
 *       
 * Author: Jesse Weisberg
 */
#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <ros.h>
//#include <sstream>
#include <std_msgs/Int16.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <math.h>
#include <std_msgs/Int16.h>
#include <std_msgs/UInt16.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <SCoop.h>

using namespace std;

// left_Joint 1
#define leftJ1_STEP_PIN 22
#define leftJ1_DIR_PIN 23

// left_Joint 2
#define leftJ2_STEP_PIN 24
#define leftJ2_DIR_PIN 25

// left_Joint 3
#define leftJ3_STEP_PIN 26
#define leftJ3_DIR_PIN 27

// left_Joint 4
#define leftJ4_STEP_PIN 28
#define leftJ4_DIR_PIN 29

// left_Joint 5 
#define leftJ5_STEP_PIN 30
#define leftJ5_DIR_PIN 31

// left_Joint 6 
#define leftJ6_STEP_PIN 32
#define leftJ6_DIR_PIN 33


// right_Joint 1
#define rightJ1_STEP_PIN 34
#define rightJ1_DIR_PIN 35

// right_Joint 2
#define rightJ2_STEP_PIN 36
#define rightJ2_DIR_PIN 37

// right_Joint 3
#define rightJ3_STEP_PIN 38
#define rightJ3_DIR_PIN 39

// right_Joint 4
#define rightJ4_STEP_PIN 40
#define rightJ4_DIR_PIN 41

// right_Joint 5 
#define rightJ5_STEP_PIN 42
#define rightJ5_DIR_PIN 43

// right_Joint 6 
#define rightJ6_STEP_PIN 44
#define rightJ6_DIR_PIN 45

AccelStepper left_joint1(1,leftJ1_STEP_PIN, leftJ1_DIR_PIN);
AccelStepper left_joint2(1,leftJ2_STEP_PIN, leftJ2_DIR_PIN);
AccelStepper left_joint3(1,leftJ3_STEP_PIN, leftJ3_DIR_PIN);
AccelStepper left_joint4(1,leftJ4_STEP_PIN, leftJ4_DIR_PIN);
AccelStepper left_joint5(1,leftJ5_STEP_PIN, leftJ5_DIR_PIN);
AccelStepper left_joint6(1,leftJ6_STEP_PIN, leftJ6_DIR_PIN);


AccelStepper right_joint1(1,rightJ1_STEP_PIN, rightJ1_DIR_PIN);
AccelStepper right_joint2(1,rightJ2_STEP_PIN, rightJ2_DIR_PIN);
AccelStepper right_joint3(1,rightJ3_STEP_PIN, rightJ3_DIR_PIN);
AccelStepper right_joint4(1,rightJ4_STEP_PIN, rightJ4_DIR_PIN);
AccelStepper right_joint5(1,rightJ5_STEP_PIN, rightJ5_DIR_PIN);
AccelStepper right_joint6(1,rightJ6_STEP_PIN, rightJ6_DIR_PIN);

MultiStepper left_steppers;
MultiStepper right_steppers;

int joint_step[12];
std_msgs::String getdata;

ros::NodeHandle nh;
std_msgs::Int16 msg;
std_msgs::Int16MultiArray step_msg;
int Relayleft=2;
int Relayright=3;

void arm_cb(const std_msgs::Int16MultiArray& arm_steps){
  for(int i=0;i<12;i++)
  {
    joint_step[i] = arm_steps.data[i];
  }
}

defineTaskLoop(serial_read){
  //如果软件串口有数据
  if(Serial1.available())
  {
    //从软件串口读出一字节，写入硬件串口
     getdata.data=Serial1.read();
  }
  }

void left_gripper(const std_msgs::Int16& cmd_msg){
  if(cmd_msg.data==0) digitalWrite(Relayright,LOW);
  if(cmd_msg.data==1) digitalWrite(Relayright,HIGH);
}

void right_gripper(const std_msgs::Int16& cmd_msg){
  if(cmd_msg.data==0) digitalWrite(Relayleft,LOW);
  if(cmd_msg.data==1) digitalWrite(Relayleft,HIGH);
  
}

//instantiate subscribers
ros::Subscriber<std_msgs::Int16MultiArray>  arm_sub("joint_steps",arm_cb);//subscribes to joint_steps on arm
ros::Publisher arm_pub("re_joint_steps",&getdata);
//ros::Publisher chatter("chatter", &str_msg);
ros::Subscriber<std_msgs::Int16> left_gripper_sub("left_fin", left_gripper);
ros::Subscriber<std_msgs::Int16> right_gripper_sub("right_fin", right_gripper);

//to publish from terminal: rostopic pub gripper_angle std_msgs/UInt16 <0-180>

void setup() {
  //put your setup code here, to run once:
  //std_msgs::String msg;
  //msg.data = getdata.str();
  //ROS_INFO("%s", msg.data.c_str());
  Serial.begin(115200);
  Serial1.begin(115200);
  nh.initNode();
  nh.subscribe(arm_sub);
  //arm_pub.publish(msg);
  nh.subscribe(left_gripper_sub);
  nh.subscribe(right_gripper_sub);

  pinMode(Relayleft,OUTPUT);
  pinMode(Relayright,OUTPUT);

  // Configure each stepper
  left_joint1.setMaxSpeed(1000);
  left_joint2.setMaxSpeed(1000);
  left_joint3.setMaxSpeed(1000);
  left_joint4.setMaxSpeed(1300);
  left_joint5.setMaxSpeed(1000);
  left_joint6.setMaxSpeed(1000);

  right_joint1.setMaxSpeed(1000);
  right_joint2.setMaxSpeed(1000);
  right_joint3.setMaxSpeed(1000);
  right_joint4.setMaxSpeed(1300);
  right_joint5.setMaxSpeed(1000);
  right_joint6.setMaxSpeed(1000);

  // Then give them to MultiStepper to manage
  left_steppers.addStepper(left_joint1);
  left_steppers.addStepper(left_joint2);
  left_steppers.addStepper(left_joint3);
  left_steppers.addStepper(left_joint4);
  left_steppers.addStepper(left_joint5);
  left_steppers.addStepper(left_joint6);

  right_steppers.addStepper(right_joint1);
  right_steppers.addStepper(right_joint2);
  right_steppers.addStepper(right_joint3);
  right_steppers.addStepper(right_joint4);
  right_steppers.addStepper(right_joint5);
  right_steppers.addStepper(right_joint6);

}

void loop() {
  
    /*long left_positions[6];  // Array of desired stepper positions must be long
    long right_positions[6];
    
    left_positions[0] = joint_step[0]; // negated since the real robot rotates in the opposite direction as ROS
    //positions[0]=0;
    left_positions[1] = joint_step[1];
    //positions[1]=0;
    left_positions[2] = joint_step[2];
    //positions[2]=0; 
    left_positions[3] = -joint_step[3];
    //positions[3]=0;
    left_positions[4] = joint_step[4]; 
    //positions[4] = 0;
    left_positions[5] = joint_step[5]; 
    //Serial.println(positions[3]);


    right_positions[0] = joint_step[6]; // negated since the real robot rotates in the opposite direction as ROS
    //positions[0]=0;
    right_positions[1] = joint_step[7];
    //positions[1]=0;
    right_positions[2] = joint_step[8];
    //positions[2]=0; 
    right_positions[3] = -joint_step[9];
    //positions[3]=0;
    right_positions[4] = joint_step[10]; 
    //positions[4] = 0;
    right_positions[5] = joint_step[11]; 
    //Serial.println(positions[3]);
    
    left_steppers.moveTo(left_positions);
    right_steppers.moveTo(right_positions);
    left_steppers.run(); // Blocks until all are in position
    right_steppers.run();
    
    nh.spinOnce();
    delay(1);*/
    arm_pub.publish(&getdata);
    //nh.spinOnce;
    yield();
  
}
