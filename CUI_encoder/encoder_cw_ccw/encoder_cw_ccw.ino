//编码器正反转记录位置程序

#define Achannel 2
#define Bchannel 3

int Astate;//A channel's current state
int Alaststate;//A channel's last state
int Bstate;//B channel's current state
int counter=0;
int temp=0;


void setup() {
  Serial.begin(9600);
  pinMode(Achannel,INPUT_PULLUP);
  pinMode(Bchannel,INPUT_PULLUP);
  Alaststate=digitalRead(Achannel);//Read the last state of A channel
}

void loop() {
  Astate=digitalRead(Achannel);//Read the current state of channel A
  Bstate=digitalRead(Bchannel);//Read the current state of channel B
    if (Astate!=Alaststate){//if A channel's level changes
     if (Bstate!=Astate){//and if B channel's level is different from A
       counter=counter-1;//the motor shaft: ccw(电机减速箱一端的轴)
       }
       else{
         counter=counter+1;//the motor shaft: cw
         }
         Serial.println(counter);
        
    }
        Alaststate=Astate;
    //print when shaft move
      
     

}
