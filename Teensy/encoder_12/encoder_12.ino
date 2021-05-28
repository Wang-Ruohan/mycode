#include <Encoder.h>

int Relayleft= 16;
int Relayright=17;

Encoder LJ1encoder(2,3);
Encoder LJ2encoder(4,5);
Encoder LJ3encoder(6,7);
Encoder LJ4encoder(8,9);
Encoder LJ5encoder(10,11);
Encoder LJ6encoder(14,15);

Encoder RJ1encoder(20,21);
Encoder RJ2encoder(22,23);
Encoder RJ3encoder(35,36);
Encoder RJ4encoder(37,38);
Encoder RJ5encoder(29,31);
Encoder RJ6encoder(30,32);


long positionLJ1 = -999;
long positionLJ2 = -999;
long positionLJ3 = -999;
long positionLJ4 = -999;
long positionLJ5 = -999;
long positionLJ6 = -999;

long positionRJ1 = -999;
long positionRJ2 = -999;
long positionRJ3 = -999;
long positionRJ4 = -999;
long positionRJ5 = -999;
long positionRJ6 = -999;

long newLJ1,newLJ2,newLJ3,newLJ4,newLJ5,newLJ6,newRJ1,newRJ2,newRJ3,newRJ4,newRJ5,newRJ6;


void setup() {
  Serial.begin(2000000);
  Serial.println("TwoKnobs Encoder Test:");
  pinMode(Relayleft, OUTPUT); 
  pinMode(Relayright, OUTPUT); 
  digitalWrite(Relayleft, LOW);
  digitalWrite(Relayright, LOW);

}


  
void loop() {

  
  newLJ1 = LJ1encoder.read(); 
  newLJ2 = LJ2encoder.read();
  newLJ3 = LJ3encoder.read();
  newLJ4 = LJ4encoder.read();
  newLJ5 = LJ5encoder.read();
  newLJ6 = LJ6encoder.read();

  newRJ1 = RJ1encoder.read();
  newRJ2 = RJ2encoder.read();
  newRJ3 = RJ3encoder.read();
  newRJ4 = RJ4encoder.read();
  newRJ5 = RJ5encoder.read();
  newRJ6 = RJ6encoder.read();

  

   if (newLJ1!= positionLJ1||newLJ2!=positionLJ2||newLJ3!= positionLJ3||newLJ4!=positionLJ4||newLJ5!= positionLJ5||newLJ6!=positionLJ6||newRJ1!= positionRJ1||newRJ2!=positionRJ2||newRJ3!= positionRJ3||newRJ4!=positionRJ4||newRJ5!= positionRJ5||newRJ6!=positionRJ6) {
    Serial.print("LJ1 = ");
    Serial.print(newLJ1);
    Serial.print(", LJ2 = ");
    Serial.print(newLJ2);
    Serial.print(", LJ3 = ");
    Serial.print(newLJ3);
    Serial.print(", LJ4 = ");
    Serial.print(newLJ4);
    Serial.print(", LJ5 = ");
    Serial.print(newLJ5);
    Serial.print(", LJ6 = ");
    Serial.print(newLJ6);
    
    Serial.print(", RJ1 = ");
    Serial.print(newRJ1);
    Serial.print(", RJ2 = ");
    Serial.print(newRJ2);
    Serial.print(", RJ3 = ");
    Serial.print(newRJ3);
    Serial.print(", RJ4 = ");
    Serial.print(newRJ4);
    Serial.print(", RJ5 = ");
    Serial.print(newRJ5);
    Serial.print(", RJ6 = ");
    Serial.print(newRJ6);
    Serial.println();
    positionLJ1 = newLJ1;
    positionLJ2 = newLJ2;
    positionLJ3 = newLJ3;
    positionLJ4 = newLJ4;
    positionLJ5 = newLJ5;
    positionLJ6 = newLJ6;
    
    positionRJ1 = newRJ1;
    positionRJ2 = newRJ2;
    positionRJ3 = newRJ3;
    positionRJ4 = newRJ4;
    positionRJ5 = newRJ5;
    positionRJ6 = newRJ6;
  }   

   if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    LJ1encoder.write(0);
    LJ2encoder.write(0);
    LJ3encoder.write(0);          
    LJ4encoder.write(0);
    LJ5encoder.write(0);
    LJ6encoder.write(0);
    
    RJ1encoder.write(0);
    RJ2encoder.write(0);
    RJ3encoder.write(0);
    RJ4encoder.write(0);
    RJ5encoder.write(0);
    RJ6encoder.write(0);
  }

  // Move to a different coordinate
/*  positions1[0] = -500;
  positions1[1] = 100;
  positions1[2] = 100;
  positions1[3] = 100;
  positions1[4] = -100;
  positions1[5] = 100;

  steppers1.moveTo(positions1);
  steppers1.runSpeedToPosition();*/
}
