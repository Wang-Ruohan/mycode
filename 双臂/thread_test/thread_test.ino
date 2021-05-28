#include <SCoop.h>

int count=0;
defineTask(led)
void led::setup(){
  pinMode(13,OUTPUT);
  }
void led::loop(){
  digitalWrite(13,!digitalRead(13));
  sleep(1000);
  }

defineTaskLoop(cnt){
  Serial.println(count++);
  sleep(1000);
  }
void setup() {
     Serial.begin(115200);
     mySCoop.start();

}

void loop() {
    
    yield();
}
