#include <Encoder.h>


Encoder J1encoder(5, 6);
Encoder J2encoder(7, 8);




void setup() {
  Serial.begin(2000000);
  Serial.println("TwoKnobs Encoder Test:");
}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  long newLeft, newRight;
  newLeft = J1encoder.read();
  newRight = J2encoder.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    J1encoder.write(0);
    J2encoder.write(0);
  }
}
