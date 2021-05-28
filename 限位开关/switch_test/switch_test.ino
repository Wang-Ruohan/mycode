#include<AccelStepper.h>
#include<MultiStepper.h>

// left_Joint 1
#define leftJ1_STEP_PIN 22
#define leftJ1_DIR_PIN 23
#define switchpin 4

AccelStepper stepper1(1,leftJ1_STEP_PIN, leftJ1_DIR_PIN);

int switchflag=0;//没有接地时置0
//一个限位开关电路图解法 |是导线的意思
//NC  COM   NO
//|    |    |
//|    |    |
//|    |    |
//|    |    |
//5v  引脚  GND

int motorposition=0;

void setup() {
  Serial.begin(115200);
  pinMode(switchpin,INPUT);
  
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(3000); 

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(switchpin)==LOW){
    switchflag=1;
    }
 
  if(switchflag==0){
    motorposition+=1;
    }
   if(switchflag==1){
    motorposition-=1;
    }
    stepper1.moveTo(motorposition);
    stepper1.run();
}
