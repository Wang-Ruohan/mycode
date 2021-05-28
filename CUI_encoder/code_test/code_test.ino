//编码器，利用中断实现（AB通道未实现正反转）

volatile long temp, counter=0;
#define Bchannel 2
#define Achannel 3


void setup() {
  Serial.begin(115200);
  pinMode(Bchannel,INPUT_PULLUP);
  pinMode(Achannel,INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(Bchannel), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(Achannel), ai1, RISING);
  /*attachInterrupt(digitalPinToInterrupt(Xchannel), ai2, RISING);*/
}

void loop() {
 if (counter!=temp){
    Serial.println(counter);
    temp=counter;
    }
}
void ai0(){
  if (digitalRead(Achannel)==HIGH){
    if(digitalRead(Bchannel!=digitalRead(Achannel))){
         counter--;
      }
       else{
      counter=counter+1;
      }
    }
  }

void ai1(){
  if (digitalRead(Achannel)==HIGH){
    if(digitalRead(Bchannel)==digitalRead(Achannel)){
      counter++;
      }
      else{
        counter--;
        }
   
    }
   
  }
