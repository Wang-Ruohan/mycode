//一个电机加上编码器测试程序
//最终输出结果为J1关节的反馈转动角度


#include "AccelStepper.h"

// 定义步进电机和编码器的引脚 
#define J1dirPin  23
#define J1stepPin 22
#define Achannel  2
#define Bchannel  3

double degree=0.0;
double counter=0.0;
int A_last_state;//A通道初始状态记录
int A_current_state;//A通道目前状态
int B_current_state;//B通道目前状态
double set_steps=400;//这里可以调节想要转动的步数，J1电机每400步电机转一圈（驱动器细分决定），输出轴转36度（10：1减速比），J1关节转9度（4：1带传动减速比）
double encoder_max;
double motor_max;

AccelStepper stepper1(1,J1stepPin,J1dirPin);

double J1_degree;
double J2_degree;
String s_degree;
 
void setup() {
  Serial.begin(115200);

  encoder_max=1023/400.0*set_steps;
  motor_max=9/400.0*set_steps;

//电机
  pinMode(J1stepPin,OUTPUT); 
  pinMode(J1dirPin,OUTPUT);

//编码器
  pinMode(Achannel,INPUT_PULLUP);
  pinMode(Bchannel,INPUT_PULLUP);
  
  stepper1.setMaxSpeed(500);   
  stepper1.setAcceleration(100); 

  A_last_state=digitalRead(Achannel);
}

void loop() {
  s_degree="";
  A_current_state=digitalRead(Achannel);
  B_current_state=digitalRead(Bchannel);
  
//电机
  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(set_steps);              
  } 
   else if ( stepper1.currentPosition() == set_steps)
   {
    stepper1.moveTo(0);             
  }    
  stepper1.run();

//编码器
  if(A_current_state!=A_last_state){

    if(B_current_state!=A_current_state){
      counter=counter-1;
      }
       else{
            counter=counter+1;
           }
   

    }
    if(degree!=counter){
        Serial.println(counter);
        degree=counter;
      }
       //Serial.println(counter); 
     A_last_state=A_current_state;
}
