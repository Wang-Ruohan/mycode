void setup() {
 pinMode(22,OUTPUT);

}

void loop() {

   digitalWrite(22,!digitalRead(22));
   delay(1000);
}
