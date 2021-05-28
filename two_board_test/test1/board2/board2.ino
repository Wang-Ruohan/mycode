#include <SoftwareSerial.h>

void setup()  
{
  //硬件串口波特率
  Serial.begin(115200);
  //软件串口波特率
  Serial1.begin(115200);
} 
void loop()
{
  //如果硬件串口有数据
  if(Serial.available())
  {
    //从硬件串口读出一字节，写入软件串口
    Serial1.write(Serial.read());
  }
  //如果软件串口有数据
  if(Serial1.available())
  {
    //从软件串口读出一字节，写入硬件串口
    Serial.write(Serial1.read());
  }
}
