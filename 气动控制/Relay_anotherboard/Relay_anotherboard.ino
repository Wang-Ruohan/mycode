int Relayleft= 22;
int Relayright= 23;


void setup(){
 Serial.begin(9600);
 pinMode(Relayleft, OUTPUT); 
 pinMode(Relayright, OUTPUT); 
 digitalWrite(Relayleft, LOW);
 digitalWrite(Relayright, LOW);
}

void loop(){
/*
  if(Serial.available()>0){
char   comdata=Serial.read();
  
 if(comdata=='1'){
  digitalWrite(Relayleft, HIGH); 
  digitalWrite(Relayright, HIGH); 
  Serial.println(comdata);
  }
 if(comdata=='2'){
  digitalWrite(Relayleft, LOW); 
  digitalWrite(Relayright, LOW); 
  Serial.println(comdata);
}
  }*/
}
