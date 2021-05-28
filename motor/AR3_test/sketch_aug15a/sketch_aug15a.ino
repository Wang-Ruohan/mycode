String inData;
//定义电机引脚//////////////////////////////////////////////////////
#define numdata_length 6
String comdata = "";
int numdata[numdata_length] = {0};
int flag = 0;

int STEP[6]={22,28,36,40,46,51};
int DIR[6]={24,30,34,42,48,53};

/////////////////////////////////////////////////////////////////////
const int Input0 = 0;
const int Input5 = 5;
const int Input6 = 6;
const int Input7 = 7;
const int Input8 = 8;
const int Input9 = 9;
const int Input10 = 10;
const int Input1 = 1;
const int Input2 = 2;
const int Input3 = 3;
const int Input4 = 4;
const int Input11 = 11;
const int Input12 = 12;
const int Input13 = 13;
const int Input14 = 14;
const int Input15 = 15;
const int Input16 = 16;
const int Input17 = 17;
const int Input18 = 18;
const int Input19 = 19;
const int Input20 = 20;
const int Input21 = 21;
const int Input22 = 22;
const int Input23 = 23;
const int Input24 = 24;
const int Input25 = 25;
const int Input26 = 26;
const int Input27 = 27;



const int Output28 = 28;
const int Output29 = 29;
const int Output30 = 30;
const int Output31 = 31;
const int Output32 = 32;
const int Output33 = 33;
const int Output34 = 34;
const int Output35 = 35;
const int Output36 = 36;
const int Output37 = 37;
const int Output38 = 38;
const int Output39 = 39;
const int Output40 = 40;
const int Output41 = 41;
const int Output42 = 42;
const int Output43 = 43;
const int Output44 = 44;
const int Output45 = 45;
const int Output46 = 46;
const int Output47 = 47;
const int Output48 = 48;
const int Output49 = 49;
const int Output50 = 50;
const int Output51 = 51;
const int Output52 = 52;
const int Output53 = 53;


void setup() {
  // run once:
  Serial.begin(115200);
//定义引脚类型/////////////////////////////////////////////
  pinMode(STEP[0],OUTPUT); 
  pinMode(DIR[0],OUTPUT);
  pinMode(STEP[1],OUTPUT); 
  pinMode(DIR[1],OUTPUT);
  pinMode(STEP[2],OUTPUT); 
  pinMode(DIR[2],OUTPUT);
  pinMode(STEP[3],OUTPUT); 
  pinMode(DIR[3],OUTPUT);
  pinMode(STEP[4],OUTPUT); 
  pinMode(DIR[4],OUTPUT);
  pinMode(STEP[5],OUTPUT); 
  pinMode(DIR[5],OUTPUT);
 ////////////////////////////////////////////////////////////

  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  pinMode(A14, INPUT);
  pinMode(A15, INPUT);


  pinMode(Input0, INPUT_PULLUP);
  pinMode(Input1, INPUT_PULLUP);
  pinMode(Input2, INPUT_PULLUP);
  pinMode(Input3, INPUT_PULLUP);
  pinMode(Input4, INPUT_PULLUP);
  pinMode(Input5, INPUT_PULLUP);
  pinMode(Input6, INPUT_PULLUP);
  pinMode(Input7, INPUT_PULLUP);
  pinMode(Input8, INPUT_PULLUP);
  pinMode(Input9, INPUT_PULLUP);
  pinMode(Input10, INPUT_PULLUP);
  pinMode(Input11, INPUT_PULLUP);
  pinMode(Input12, INPUT_PULLUP);
  pinMode(Input13, INPUT_PULLUP);
  pinMode(Input14, INPUT_PULLUP);
  pinMode(Input15, INPUT_PULLUP);
  pinMode(Input16, INPUT_PULLUP);
  pinMode(Input17, INPUT_PULLUP);
  pinMode(Input18, INPUT_PULLUP);
  pinMode(Input19, INPUT_PULLUP);
  pinMode(Input20, INPUT_PULLUP);
  pinMode(Input21, INPUT_PULLUP);
  pinMode(Input22, INPUT_PULLUP);
  pinMode(Input23, INPUT_PULLUP);
  pinMode(Input24, INPUT_PULLUP);
  pinMode(Input25, INPUT_PULLUP);
  pinMode(Input26, INPUT_PULLUP);
  pinMode(Input27, INPUT_PULLUP);

  pinMode(Output28, OUTPUT);
  pinMode(Output29, OUTPUT);
  pinMode(Output30, OUTPUT);
  pinMode(Output31, OUTPUT);
  pinMode(Output32, OUTPUT);
  pinMode(Output33, OUTPUT);
  pinMode(Output34, OUTPUT);
  pinMode(Output35, OUTPUT);
  pinMode(Output36, OUTPUT);
  pinMode(Output37, OUTPUT);
  pinMode(Output38, OUTPUT);
  pinMode(Output39, OUTPUT);
  pinMode(Output40, OUTPUT);
  pinMode(Output41, OUTPUT);
  pinMode(Output42, OUTPUT);
  pinMode(Output43, OUTPUT);
  pinMode(Output44, OUTPUT);
  pinMode(Output45, OUTPUT);
  pinMode(Output46, OUTPUT);
  pinMode(Output47, OUTPUT);
  pinMode(Output48, OUTPUT);
  pinMode(Output49, OUTPUT);
  pinMode(Output50, OUTPUT);
  pinMode(Output51, OUTPUT);
  pinMode(Output52, OUTPUT);
  pinMode(Output53, OUTPUT);

  digitalWrite(Output28, HIGH);
  digitalWrite(Output29, HIGH);
  digitalWrite(Output30, HIGH);
  digitalWrite(Output31, HIGH);
  digitalWrite(Output32, HIGH);
  digitalWrite(Output33, HIGH);
  digitalWrite(Output34, HIGH);
  digitalWrite(Output35, HIGH);

}

void moveto(int i,int move_step){
 
   digitalWrite(DIR[i],LOW); 
   for(int x = 0; x < move_step; x++) {
    digitalWrite(STEP[i],HIGH); 
    delayMicroseconds(200); 
    digitalWrite(STEP[i],LOW); 
    delayMicroseconds(200); 
  }
}

void loop(){
  int j = 0;
  //不断循环检测串口缓存，一个个读入字符串
  while (Serial.available() > 0)
  {
    comdata += char(Serial.read());
    delay(2);
    flag = 1;
  }
  //如果接收到数据则执行comdata分析操作，否则什么都不做
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
  
  for(int i = 0; i < numdata_length; i++){
    moveto(i+1,numdata[i]);
    delay(10);
  }
  
}
