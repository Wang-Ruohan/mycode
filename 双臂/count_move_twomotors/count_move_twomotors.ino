#include <SCoop.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

#define LJ1_STEP_PIN 32
#define LJ1_DIR_PIN 33
#define RJ1_STEP_PIN 44
#define RJ1_DIR_PIN 45

int numdataL1=2000;
int numdataR1=1000;

AccelStepper joint1(1,LJ1_STEP_PIN, LJ1_DIR_PIN);
AccelStepper joint2(1,RJ1_STEP_PIN, RJ1_DIR_PIN);

MultiStepper steppers1;
MultiStepper steppers2;

defineTask(J6motor1)
void J6motor1::setup(){

  }
void J6motor1::loop(){
    steppers1.moveTo(numdataL1);
    steppers1.runSpeedToPosition();
    int count=0;
    Serial.println(count++);
  }

defineTask(J6motor2)
void J6motor2::setup(){
 
  }
void J6motor2::loop(){
    steppers2.moveTo(numdataR1);
    steppers2.runSpeedToPosition();
  }

void setup() {
     Serial.begin(115200);
     joint1.setMaxSpeed(3000);
     steppers1.addStepper(joint1);
     joint2.setMaxSpeed(3000);
     steppers2.addStepper(joint2);
     mySCoop.start();

}

void loop() {
    yield();
}
