#include <AccelStepper.h>
#include <MultiStepper.h>
//鍒嗗壊瀛楃涓�*******************************
#define numdata_length 5
String comdata = "";
long numdata[numdata_length] = {0};
int flag = 0;
//鍙橀噺澹版槑*********************************
// Joint 1
#define E1_STEP_PIN 36
#define E1_DIR_PIN 34
#define E1_ENABLE_PIN 30

// Joint 2
#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

// Joint 3
#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

// Joint 4
#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38

// Joint 5 
#define E0_STEP_PIN 26
#define E0_DIR_PIN 28
#define E0_ENABLE_PIN 24


// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper joint1(1,E1_STEP_PIN, E1_DIR_PIN);
AccelStepper joint2(1,Z_STEP_PIN, Z_DIR_PIN);
AccelStepper joint3(1,Y_STEP_PIN, Y_DIR_PIN);
AccelStepper joint4(1,X_STEP_PIN, X_DIR_PIN);
AccelStepper joint5(1, E0_STEP_PIN, E0_DIR_PIN);

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;

//test with uint8 converted to long
unsigned int x = 1000;
void setup() {
  Serial.begin(115200);

  // Configure each stepper
  joint1.setMaxSpeed(1000);
  joint2.setMaxSpeed(150);
  joint3.setMaxSpeed(200);
  joint4.setMaxSpeed(200);
  joint5.setMaxSpeed(200);

  // Then give them to MultiStepper to manage
  steppers.addStepper(joint1);
  steppers.addStepper(joint2);
  steppers.addStepper(joint3);
  steppers.addStepper(joint4);
  steppers.addStepper(joint5);
}

void loop() {
  long positions[5]; // Array of desired stepper positions

  // Back of the envelope calculation for microsteps/revolution, where positions[i] is the number of steps (or microsteps).
  positions[0] = 0; //4100 microsteps is 1/8 revolutions ----> 32800 microsteps/rev
  positions[1] = 0; //2000 is 40/360 revolutions ---> 18000 microsteps/rev
  positions[2] = 0; //4000 is 20/360 revolutions ---> 72000 microsteps/rev
  positions[3] = 0; //820 is 1/4 revolution (200steps/revolution * 16microsteps/step (since microstepping) ~= 32800 microsteps/rev)
  positions[4] = 0; //2000 is 50/360 revolution ---> 14400
  
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1);
  //杈撳叆涓嬩竴涓綅缃�//******************************
  int j = 0;
  //涓嶆柇寰幆妫�娴嬩覆鍙ｇ紦瀛橈紝涓�涓釜璇诲叆瀛楃涓�
  while (Serial.available() > 0)
  {
    comdata += char(Serial.read());
    delay(1);
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
  positions[1] = numdata[1];
  positions[2] = numdata[2];
  positions[3] = numdata[3];
  positions[4] = numdata[4];
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  for(int i = 0; i < numdata_length; i++){
  numdata[i] = 0;
  }
  delay(1000);
}
