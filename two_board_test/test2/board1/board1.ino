#include<SoftwareSerial.h>
//新建一个softSerial对象，rx:6,tx:5

void setup() {
  // 初始化串口通信:
  Serial.begin(9600);
  //初始化软串口通信；
  Serial1.begin(9600);
}

// 两个字符串分别用于存储A、B两端传来的数据:
  String device_B_String="";
  String device_A_String="";
  
void loop() {
  // 读取从计算机传入的数据，并通过serial1发送个设备B:
  if(Serial.available()>0)
  {
    if(Serial.peek()!='\n')   //在没接收到回车换行的条件下
    {
      device_B_String+=(char)Serial.read();   //这段代码是在把字符串联成字符串
    }
    else
    {  //这段代码实现从缓冲区读取数据，并将数据发送到计算机显示和软串口发送；
      Serial.read();
      Serial.print("you said:");
      Serial.println(device_B_String);
      Serial1.println(device_B_String);
      device_B_String="";
    }
  }
  //读取从设备A传入的数据，并在串口监视器中显示
  
  if(Serial1.available()>0)
  {
   
    if(Serial1.peek()!='\n')
    {
      device_A_String+=(char)Serial1.read();
    }
    else
    {
      Serial1.read();
      Serial.print("device A said:");
      Serial.println(device_A_String);
      device_A_String="";
    }
  }
 
 
 
}
 
