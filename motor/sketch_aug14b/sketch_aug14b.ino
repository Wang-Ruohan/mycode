const int dirPin = 34;  // 方向引脚
const int stepPin = 36; // 步进引脚
 
// 电机每圈步数
const int STEPS_PER_REV = 800;
 
void setup() {
  
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  
  digitalWrite(dirPin,LOW); 
  
  // 电机慢速旋转
  for(int x = 0; x < STEPS_PER_REV; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1000); 
  }
  
  // 等待一秒
  delay(1000); 
   digitalWrite(dirPin,HIGH);
  
  // 电机快速旋转
  for(int x = 0; x < (STEPS_PER_REV * 2); x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(1000);
  }
  
  // 等待一秒
  delay(1000);
}
