#include<ros.h>
#include<std_msgs/String.h>
#include<std_msgs/UInt16.h>

#define button 8

ros::NodeHandle n;

std_msgs::String button_msg;

ros::Publisher button_publisher("button_press",&button_msg);

void setup(){
  pinMode(button,INPUT);
  n.initNode();
  n.advertise(button_publisher);
  
  }

void loop(){
  if(digitalRead(button)==HIGH){
    button_msg.data="Pressed";
    }
    else{
      button_msg.data="NOT Pressed";
      }
  button_publisher.publish(&button_msg);
  n.spinOnce();
  delay(100);
  
  }
