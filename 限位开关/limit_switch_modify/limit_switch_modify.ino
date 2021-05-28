//left_positions与right_positions赋初值为0，设置为全局变量
//+=1与=1的区别，=1会反复跳转到=1的判断中
//每次+=10会出现moveto的位置每次都更新但是还没到最新的moveto位置，触发限位开关无效

#include <AccelStepper.h>
#include <MultiStepper.h>

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
long left_positions[6]={0,0,0,0,0,0};  // Array of desired stepper positions must be long
long right_positions[6]={0,0,0,0,0,0};



int L1_Flag=0;
int L2_Flag=0;
int L3_Flag=0;
//int L4_Flag=2;

int R1_Flag=0;
int R2_Flag=0;
int R3_Flag=0;
//int R4_Flag=2;



void setup() {
  //put your setup code here, to run once:
  Serial.begin(115200);

  //limit switch
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);

 
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
  
   //long first_rotation[6]={1,1,1,1,1,1};
   //long second_rotation[6]={8000,600,600,600,600,600};

   //限位开关到了极限位置，标志位+1
   
    if(digitalRead(4)==LOW){
      L1_Flag+=1;
      }
    if(digitalRead(5)==LOW){
     L2_Flag+=1;
      }
    if(digitalRead(6)==LOW){
       L3_Flag+=1;
      }
    //if(digitalRead(7)==LOW){
    //  L4_Flag+=1;
    //  }
    
      
    if(digitalRead(8)==LOW){
      R1_Flag+=1;
      }
    if(digitalRead(9)==LOW){
      R2_Flag+=1;
      }
    if(digitalRead(10)==LOW){
      R3_Flag+=1;
      }
    //if(digitalRead(11)==LOW){
    //  R4_Flag+=1;
    //  }
   
      
    //当标志位数值为0的时候，电机朝一个方向转动；当标志位为1的时候，电机反转固定步数；当标志位为2的时候，从ros系统中读取
    
    if(L1_Flag==0){
      left_positions[0]+=1;
      }
    if(L1_Flag==1){
      left_positions[0]-=16500;
      L1_Flag=2;
      }
    

    if(L2_Flag==0){
      left_positions[1]-=1;
      }
    if(L2_Flag==1){
      left_positions[1]+=3000;
      L2_Flag=2;
      }
    

    if(L3_Flag==0){
      left_positions[2]+=1;
      }
    if(L3_Flag==1){
      left_positions[2]-=3550;
      L3_Flag=2;
      }

    
      left_positions[3] = joint_step[3];  
      left_positions[4] = joint_step[4];
      left_positions[5] = joint_step[5];


    if(R1_Flag==0){
      right_positions[0]-=1;
      }
    if(R1_Flag==1){
      right_positions[0]+=17500;
      R1_Flag=2;
      }


    if(R2_Flag==0){
      right_positions[1]+=1;
      }
    if(R2_Flag==1){
      right_positions[1]-=4380;
      R2_Flag=2;
      }
   
    
    if(R3_Flag==0){
      right_positions[2]-=1;
      }
    if(R3_Flag==1){
      right_positions[2]+=3650;
      R3_Flag=2;
      }

 
      right_positions[3] = joint_step[9];
      right_positions[4] = joint_step[10];   
      right_positions[5] = joint_step[11];      


    left_steppers.moveTo(left_positions);
    right_steppers.moveTo(right_positions);
    left_steppers.run(); // Blocks until all are in position
    right_steppers.run();
   
    delay(1); 
}
