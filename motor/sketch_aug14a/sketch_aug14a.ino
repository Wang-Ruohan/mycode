void setup() {
 pinMode(22,OUTPUT);
 pinMode(23,OUTPUT);

}

void loop() {
   digitalWrite(23,HIGH);
// for (int i=1000;i>=0;i--){
   digitalWrite(22,HIGH);
   delayMicroseconds(200);
   digitalWrite(22,LOW);
   delayMicroseconds(200);
  
//  }
//  delay(500);

}
