int Relayleft= 2;
int Relayright= 3;

void setup(){
 pinMode(Relayleft, OUTPUT); 
 pinMode(Relayright, OUTPUT); 
}

void loop(){
  digitalWrite(Relayleft, HIGH);
  digitalWrite(Relayright, HIGH);
  delay(5000);
  
  digitalWrite(Relayleft, LOW); 
  digitalWrite(Relayright, LOW); 
  delay(5000);
}
