#include <SCoop.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

#define LJ1_STEP_PIN 32
#define LJ1_DIR_PIN 33

int count=0;

AccelStepper joint1(1,LJ1_STEP_PIN, LJ1_DIR_PIN);
MultiStepper steppers1;

defineTask(motor1)
void motor1::setup(){
   joint1.setMaxSpeed(3000);
   steppers1.addStepper(joint1);
  }
void motor1::loop(){
    long positions1;
    positions1=count;
    steppers1.moveTo(positions1);
    steppers1.runSpeedToPosition();
  }


defineTaskLoop(cnt){
  count+=200;
  Serial.println(count);
  sleep(1000);
  }

void setup() {
     Serial.begin(115200);
     mySCoop.start();

}

void loop() {
    yield();
}
