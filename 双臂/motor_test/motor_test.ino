#include <Stepper.h>
#include <SCoop.h>

int StepsRequired;
int count=0;

Stepper steppermotor(32, 8, 10, 9, 11); 

/*defineTaskLoop(cnt){
  count+=2;
  Serial.println(count);
  sleep(500);
  }*/

defineTaskLoop(motorrun){
  StepsRequired = 1;//count;
  steppermotor.step(StepsRequired);
  }

void setup()
{
  Serial.begin(115200);
  steppermotor.setSpeed(800);
  mySCoop.start();
}
 
void loop()
{
  yield();
}
