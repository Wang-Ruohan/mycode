//编码器正反转记录位置程序

#define Achannel 2
#define Bchannel 3
#define Xchannel 4

int Astate;//A channel's current state
int Bstate;//B channel's current state
int Xstate;//X channel's current state
int counter=0;
int temp=0;


void setup() {
  Serial.begin(9600);
  pinMode(Achannel,INPUT_PULLUP);
  pinMode(Bchannel,INPUT_PULLUP);
  pinMode(Xchannel,INPUT_PULLUP);
}

void loop() {
  Xstate=digitalRead(Xchannel);//Read the current state of channel X
  Astate=digitalRead(Achannel);//Read the current state of channel A
  Bstate=digitalRead(Bchannel);//Read the current state of channel B
    if (Xstate==HIGH){
      if (Astate==Bstate){
        counter=counter-1;
        }
      else {
        counter=counter+1;
        }
      }
      Serial.println(counter);

     

}
