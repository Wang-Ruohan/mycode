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
//#include <SCoop.h>

using namespace std;

int joint_step[12];
std_msgs::String getdata;

ros::NodeHandle nh;
std_msgs::Int16 msg;
std_msgs::Int16MultiArray step_msg;

void arm_cb(const std_msgs::Int16MultiArray& arm_steps){
  for(int i=0;i<12;i++)
  {
    joint_step[i] = arm_steps.data[i];
  }
}

/*defineTaskLoop(serial_read){
  //如果软件串口有数据
  if(Serial1.available())
  {
    //从软件串口读出一字节，写入硬件串口
     getdata.data=Serial1.read();
  }
  }*/

//instantiate subscribers
ros::Subscriber<std_msgs::Int16MultiArray>  arm_sub("joint_steps",arm_cb);//subscribes to joint_steps on arm
ros::Publisher arm_pub("re_joint_steps",&getdata);
//ros::Publisher chatter("chatter", &str_msg);

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


}

void loop() {
    if(Serial1.available())
  {
    //从软件串口读出一字节，写入硬件串口
     getdata.data=Serial1.read();
     arm_pub.publish(&getdata);
  }
    nh.spinOnce();
    delay(1);
   // yield();
  
}
