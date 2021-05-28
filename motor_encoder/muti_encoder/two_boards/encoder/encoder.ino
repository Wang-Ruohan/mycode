#include <Encoder.h>

Encoder J1encoder(2,3);
Encoder J2encoder(4,5);
Encoder J3encoder(6,7);
Encoder J4encoder(8,9);
Encoder J5encoder(10,11);
Encoder J6encoder(12,13);

String device_A_String="";
String device_B_String="";
String getdata;

long positionJ1 = -999;
long positionJ2 = -999;
long positionJ3 = -999;
long positionJ4 = -999;
long positionJ5 = -999;
long positionJ6 = -999;
long newJ1,newJ2,newJ3,newJ4,newJ5,newJ6;

void setup() {
   Serial.begin(2000000);
   Serial.println("TwoKnobs Encoder Test:");
   Serial1.begin(115200);
}

void loop() {
  newJ1 = J1encoder.read();
  newJ2 = J2encoder.read();
  newJ3 = J3encoder.read();
  newJ4 = J4encoder.read();
  newJ5 = J5encoder.read();
  newJ6 = J6encoder.read();
   if (newJ1!= positionJ1||newJ2!=positionJ2||newJ3!= positionJ3||newJ4!=positionJ4||newJ5!= positionJ5||newJ6!=positionJ6) {
    getdata=(String)newJ1+","+(String)newJ2+","+(String)newJ3+","+(String)newJ4+","+(String)newJ5+","+(String)newJ6;
 /*   Serial.print("J1 = ");
    Serial.print(newJ1);
    Serial.print(", J2 = ");
    Serial.print(newJ2);
    Serial.print(", J3 = ");
    Serial.print(newJ3);
    Serial.print(", J4 = ");
    Serial.print(newJ4);
    Serial.print(", J5 = ");
    Serial.print(newJ5);
    Serial.print(", J6 = ");
    Serial.print(newJ6);
    Serial.println();*/
    Serial.println(getdata);
    positionJ1 = (long)newJ1;
    positionJ2 = (long)newJ2;
    positionJ3 = (long)newJ3;
    positionJ4 = (long)newJ4;
    positionJ5 = (long)newJ5;
    positionJ6 = (long)newJ6;
    Serial1.println(getdata);
  }

   if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    J1encoder.write(0);
    J2encoder.write(0);
    J3encoder.write(0);
    J4encoder.write(0);
    J5encoder.write(0);
    J6encoder.write(0);
  }

}
