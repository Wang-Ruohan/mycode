#include <AccelStepper.h>
#include <MultiStepper.h>
//鍒嗗壊瀛楃涓�*******************************
#define numdata_length 5
String comdata = "";
long numdata[numdata_length] = {0};
int flag = 0;
//鍙橀噺澹版槑*********************************
// Joint 1


// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper joint1(
 #define E1_STEP_PIN 36
#define E1_DIR_PIN 34
#define E1_ENABLE_PIN 30
1,E1_STEP_PIN, E1_DIR_PIN);

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;

//test with uint8 converted to long
unsigned int x = 1000;
void setup() {
  Serial.begin(115200);

  // Configure each stepper
  joint1.setMaxSpeed(150);


  // Then give them to MultiStepper to manage
  steppers.addStepper(joint1);
 
}

void loop() {
  long positions[1]; // Array of desired stepper positions

  // Back of the envelope calculation for microsteps/revolution, where positions[i] is the number of steps (or microsteps).
  positions[0] = 0; //4100 microsteps is 1/8 revolutions ----> 32800 microsteps/rev

  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1);
  //杈撳叆涓嬩竴涓綅缃�//******************************
  int j = 0;
  //涓嶆柇寰幆妫�娴嬩覆鍙ｇ紦瀛橈紝涓�涓釜璇诲叆瀛楃涓�
  while (Serial.available() > 0)
  {
    comdata += char(Serial.read());
    delay(2);
    flag = 1;
  }
  //濡傛灉鎺ユ敹鍒版暟鎹垯鎵цcomdata鍒嗘瀽鎿嶄綔锛屽惁鍒欎粈涔堥兘涓嶅仛
  if(flag == 1) {
  for(int i = 0; i < comdata.length() ; i++){
    if(comdata[i] == ','){
      j++;
    }
    else{
      numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
    }
  }
  comdata = String("");
  flag = 0;
  for(int i = 0; i < numdata_length; i++){
    Serial.println(numdata[i]);
    }
  }
  // Move to a different coordinate
  positions[0] = numdata[0];

  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  for(int i = 0; i < numdata_length; i++){
  numdata[i] = 0;
  }
  delay(1000);
}
