/*
 * by TZW 2018/11/08
 * 供电12V
 * 控制器arduino uno , A4988，42步进电机
 * 16细分
 * 减速比90:1
 * 串口配置：115200，n，8,1
 * 参数设置：每次开机重置
 * A####   角度设定####*0.1度，刻度0.1，默认10.0度
 * T####   连续运转间隔设定，单位ms
 * 运转命令：
 * G1      连续正转
 * G2      连续反转
 * G3      停转
 * G4      单次正转
 * G5      单次反转
 * 
 */

#include "stdio.h"
//硬件引脚配置
#define en  2        //电机使能引脚
#define stp 36        //脉冲
#define dir 34        //方向
#define buz 10       //轰鸣器
/*
 *    |f(Hz)
 * fh |   ------------
 *    | /              \
 * f0 |/                \
 *    |                  |
 *   -|---------------------->t(s)                          
 */                           

#define f0       100              //起跳频率  100-500Hz，30转/分钟
#define a        800              //加速度    100-5000Hz/S^2
#define fh       1600             //最高频率  Hz  对应8转/秒，480转/分钟
#define delat_f  100              //每档频率增加量  Hz
#define M        16               //细分
#define I        90               //齿轮减速比
#define k       (fh-f0)/delat_f   //加速度档数

String comdata="";             //命令接收字符串
unsigned long numdata=0;       //命令参数
unsigned int no_data;          //串口空闲计数
unsigned int serial_count;     //接收字节数

unsigned int delay_time_ms = 100;
unsigned int delay_time_s = 0;

unsigned int fk[k+1];             //各档位频率
unsigned int nk[k+1];             //各档位步数
unsigned int accn[k+1];           //各档位加速度节点
unsigned int delay_microk[k+1];   //各档位延时us

unsigned long acc_step = 0;       //每次运行的加速节点
unsigned long dcc_step = 0;       //每次运行的减速节点

char run_on = 0;
float target_angle = 10.0;        //目标运行角度
unsigned long target_steps = target_angle*5*M*I/9;   //目标运行步数，角度*细分*减速比*200/360
void setup()
{
  Serial.begin(115200);
  stepper_init();
  init_process_string();
  f_init();
  Serial.println("START");
}

void loop()
{
  Serial_receive();
  if((run_on)&&(target_steps))
  {
    do_step(target_steps);
    if(delay_time_s>0)
    {
      for(unsigned char i=0;i<delay_time_s;i++)
        delay(1000);
    }
    if(delay_time_ms>0)
        delay(delay_time_ms);
  }
}

void f_init(void)
{
  float delat_t =delat_f*1.0/a;  //每档用时，秒
  unsigned char i=0;
  for(i=0;i<=k;i++)
  {
    fk[i] = i*delat_f+f0;        //每档对应频率
    /*
    Serial.print("fk");
    Serial.print(i);
    Serial.print("=");
    Serial.println(fk[i]);
    */
    nk[i] = fk[i]*delat_t;       //每档运行步数
    /*
    Serial.print("nk");
    Serial.print(i);
    Serial.print("=");
    Serial.println(nk[i]);
    */
    
    delay_microk[i] = 1000000.0/fk[i]/M-5;  //每步延时=1/频率/细分  （s）
    
    Serial.print("t");
    Serial.print(i);
    Serial.print("=");
    Serial.println(delay_microk[i]);
    
    if(i==0)
    {
      accn[i]=nk[i];             //每档截止步数
    }
    else
    {
      accn[i]=accn[i-1]+nk[i];
    }
    
    Serial.print("accn");
    Serial.print(i);
    Serial.print("=");
    Serial.println(accn[i]);
    
  }
}

void Serial_receive(void) //串口接收，处理命令
{
  char c ;
  while (Serial.available() > 0)  //连续接收
  {
    c = Serial.read();
    no_data = 0;             //收到数据，重置空闲计时
    if (c != '\n')           //排除换行符
    {
      comdata += c;          //接收的字符串       
      serial_count++;        //字节计数
    }
    delay(2);                //缓冲，若2ms内串口无数据，认为一条命令结束，退出接收
  }
  if (serial_count>0)
  {
    Serial.println(comdata); 
    process_string();         //处理命令
    init_process_string();    //清除命令
  }
  else init_process_string();
  
  no_data++;      //串口空闲计时no_data*100us
  delayMicroseconds(100);
  if (no_data > 200000)   //空闲时间大于20S，释放电机
     stepper_off();
}

void process_string(void)   //命令处理函数
{
  //命令组成：标识符+参数
  for(int i = 1; i < serial_count ; i++)
  numdata = numdata * 10 + (comdata[i] - '0');  //字符串转数值
  if(comdata[0]=='G')  //控制标识符
  {
    buz_d();
    switch(numdata)
    {
       case 1:  //间隔连续正转
       {run_on=1;digitalWrite(dir,LOW);}
       break;
       case 2:  //间隔连续反转
       {run_on=1;digitalWrite(dir,HIGH);}
       break;
       case 3:  //停转
       {run_on=0;}
       break;
       case 4:  //正传1次
       {run_on=0;digitalWrite(dir,LOW);do_step(target_steps);}
       break;
       case 5:  //反转一次
       {run_on=0;digitalWrite(dir,HIGH);do_step(target_steps);}
       break;  
       default:
       break;
     }
   }
   else if(comdata[0]=='S') //设定运转步数，并运转一次
   {
     buz_d();
     if(numdata>0)
     {
       target_steps=numdata;do_step(target_steps);
     }
   }
   else if(comdata[0]=='A') //设定运转角度 *0.1
   {
      buz_d();
      if(numdata>3)
      {
        target_angle=0.1*numdata;
        target_steps = target_angle*5*M*I/9;
        Serial.print("target_steps:");
        Serial.println(target_steps);
      }
   }
   else if(comdata[0]=='T') //设定连续运转间隔时间 *ms
   {
      buz_d();
      if(numdata>0)
      {
        delay_time_ms=numdata;
        delay_time_s=delay_time_ms/1000;
        delay_time_ms=delay_time_ms%1000;
        Serial.print("delay_time_s:");
        Serial.println(delay_time_s);
        Serial.print("delay_time_ms:");
        Serial.println(delay_time_ms);
      }
   }
   else init_process_string();
}
void init_process_string(void)  //初始化串口接收相关变量
{
   serial_count=0;
   comdata="";
   numdata=0;
}

void do_step(unsigned long steps)  //电机运转函数
{
  unsigned long step_count=0;
  unsigned char i=0;
  unsigned char acck=0;
  unsigned long half_steps;
  half_steps = steps/2;
  acc_step = 0;
  for(i=0;i<k;i++)                 //根据总运行步数计算加速档位，加减速节点
  {
    if(half_steps>accn[i])
    {
      acc_step = accn[i];          //加速节点
      acck=i+1;                    //加减速档位
    }
  }
  
  Serial.print("acck:");
  Serial.println(acck);
  dcc_step = steps-acc_step;       //减速节点
  
  Serial.print("acc_step:");
  Serial.println(acc_step);
    
  Serial.print("dcc_step:");
  Serial.println(dcc_step);
  
  stepper_on();                     //开启电机
  
  Serial.print("acc_begin:");
  Serial.println(step_count);

  for(int i=0;i<acck;i++)           //加速过程
  {
    for(unsigned int count=0;count<nk[i];count++)
    {
      one_step();
      delayMicroseconds(delay_microk[i]);
      step_count++;
    }
  }

  Serial.print("acc_end:");
  Serial.println(step_count);

  Serial.print("step_begin:");
  Serial.println(step_count);

  while(step_count<dcc_step)          //匀速过程
  {
    one_step();
    delayMicroseconds(delay_microk[acck]);
    step_count++;
  }

  Serial.print("step_end:");
  Serial.println(step_count);
  
  Serial.print("dcc_begin:");
  Serial.println(step_count);

  for(int i=(acck-1);i>=0;i--)        //减速过程
  {
    for(unsigned int count=0;count<nk[i];count++)
    {
      one_step();
      delayMicroseconds(delay_microk[i]);
      step_count++;
    }
  }

  Serial.print("dcc_end:");
  Serial.println(step_count);
  while(step_count<steps)  //消除异常误差，正常情况不会执行,可不用           
  {
    one_step();
    delayMicroseconds(delay_microk[0]);
    step_count++;
  }

  Serial.print("stop:");
  Serial.println(step_count);
  
  Serial.println("V");    //运行结束
  
}
void one_step(void)       //驱动一个脉冲
{
  digitalWrite(stp,HIGH);
  delayMicroseconds(2);
  digitalWrite(stp,LOW);
  delayMicroseconds(2);
}
void stepper_init(void)    //硬件初始化
{
  pinMode(en,OUTPUT);
  pinMode(stp,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(buz,OUTPUT);
  digitalWrite(en,HIGH);
  digitalWrite(stp,LOW);
  digitalWrite(dir,LOW);
  digitalWrite(buz,LOW);
}
void stepper_on(void)     //使能电机
{
  digitalWrite(en,LOW);
}
void stepper_off(void)     //释放电机
{
  digitalWrite(en,HIGH);
}
void buz_d(void)           //轰鸣器
{
  digitalWrite(buz,HIGH);
  delay(50);
  digitalWrite(buz,LOW);
}
