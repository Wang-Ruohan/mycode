//一个电机加上编码器测试程序
//最终输出结果为J1,J2关节的反馈转动角度

#include "AccelStepper.h"

//定义步进电机引脚
#define J1_stepPin   22
#define J1_dirPin    23

#define J2_stepPin   24
#define J2_dirPin    25

//定义编码器引脚
#define J1_Achannel  2
#define J1_Bchannel  3

#define J2_Achannel  18
#define J2_Bchannel  19

/*定义不同关节编码器变量*/
//计数
double J1_temp=0.0;
double J2_temp=0.0;
double J1_counter=0.0;
double J2_counter=0.0;

//A通道初始状态记录
int J1_A_last_state;
int J2_A_last_state;

//A通道现在状态记录
int J1_A_current_state;
int J2_A_current_state;

//B通道目前状态记录
int J1_B_current_state;
int J2_B_current_state;

//这里可以调节想要转动的角度
double J1_set_angle=9.0;  //J1电机每400步电机转一圈（驱动器细分400），输出轴转36度（10：1减速比）， J1关节转9度（4：1带传动减速比）
double J2_set_angle=7.2;  //J2电机每400步电机转一圈（驱动器细分400），输出轴转7.2度（50：1减速比），J2关节转7.2度（无减速）

//其他运算变量
double J1_set_step;
double J2_set_step;

double J1_encoder_max;
double J2_encoder_max;

double J1_motor_max;
double J2_motor_max;

double J1_degree;
double J2_degree;

AccelStepper stepper1(1,J1_stepPin,J1_dirPin);
AccelStepper stepper2(1,J2_stepPin,J2_dirPin);


void setup() {
  Serial.begin(115200);
  Serial.begin(115200);
  

//参数计算
  J1_set_step    = 400/9.0*J1_set_angle;
  J1_encoder_max = 1023/9.0*J1_set_angle;
  J1_motor_max   = J1_set_angle;
  
  J2_set_step    = 400/7.2*J2_set_angle;
  J2_encoder_max = 1023/7.2*J2_set_angle;
  J2_motor_max   = J2_set_angle;
  

//电机
  pinMode(J2_stepPin,OUTPUT);
  pinMode(J1_stepPin,OUTPUT); 
  pinMode(J1_dirPin,OUTPUT);
  pinMode(J2_dirPin,OUTPUT);
  

//编码器
  pinMode(J1_Achannel,INPUT_PULLUP);
  pinMode(J1_Bchannel,INPUT_PULLUP);
  pinMode(J2_Achannel,INPUT_PULLUP);
  pinMode(J2_Bchannel,INPUT_PULLUP);
  
  stepper1.setMaxSpeed(500);   
  stepper1.setAcceleration(100); 
  stepper2.setMaxSpeed(500);
  stepper2.setAcceleration(100);

  J1_A_last_state=digitalRead(J1_Achannel);
  J2_A_last_state=digitalRead(J2_Achannel);
  
}

void loop() {
  
  J1_A_current_state=digitalRead(J1_Achannel);
  J1_B_current_state=digitalRead(J1_Bchannel);
  J2_A_current_state=digitalRead(J2_Achannel);
  J2_B_current_state=digitalRead(J2_Bchannel);
  
//J1电机
  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(J1_set_step);              
  } 
   else if (stepper1.currentPosition() == J1_set_step)
   {
    stepper1.moveTo(0);             
  }    
  
//J2电机
  if ( stepper2.currentPosition() == 0 ){ 
    stepper2.moveTo(J2_set_step);              
  } 
   else if ( stepper2.currentPosition() == J2_set_step)
   {
    stepper2.moveTo(0);             
  }   

//J1编码器

  if(J1_A_current_state!=J1_A_last_state){

    if(J1_B_current_state!=J1_A_current_state){
      J1_counter=J1_counter-1;
      }
       else{
            J1_counter=J1_counter+1;
           }
     J1_degree=J1_counter*J1_motor_max/J1_encoder_max;
     
    }



//J2编码器
  if(J2_A_current_state!=J2_A_last_state){

    if(J2_B_current_state!=J2_A_current_state){
      J2_counter=J2_counter-1;
      }
       else{
            J2_counter=J2_counter+1;
           }
     //Serial.print("J2 degree:");
     //double J2_degree=J2_counter*J2_motor_max/J2_encoder_max;
     J2_degree=J2_counter*J2_motor_max/J2_encoder_max;
     //
    
    }
 
    if(J1_temp!=J1_counter){
      Serial.print("J1:");
      Serial.print(J1_degree,6);
      Serial.print("   ");
     // Serial.print("J2:");
      //Serial.println(J2_degree,6);
      J1_temp=J1_counter;
      }
 
     if(J2_temp!=J2_counter){
      Serial.println(J2_degree,6);
      J2_temp=J2_counter;
      }
     J1_A_last_state=J1_A_current_state;
     J2_A_last_state=J2_A_current_state;
     
    stepper1.run();
    stepper2.run();

}
