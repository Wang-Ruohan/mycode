#include <Stepper.h>
#include <SCoop.h>

int StepsRequired1;
int StepsRequired2;
int count=0;

Stepper steppermotor1(400,44,45); 
Stepper steppermotor2(400,32,33);

defineTaskLoop(cnt){
  count+=2;
  Serial.println(count);
  sleep(500);
  }

defineTaskLoop(motorrun){
  StepsRequired1 = 40;//count;
  steppermotor1.step(StepsRequired1);
  }

defineTaskLoop(motorrun2){
  StepsRequired2 = 40;//count;
  steppermotor2.step(StepsRequired2);
  }

void setup()
{
  Serial.begin(115200);
  steppermotor1.setSpeed(800);
  steppermotor2.setSpeed(800);
  mySCoop.start();
}
 
void loop()
{
  yield();
}
