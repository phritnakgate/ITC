#define LED_S_R 4
#define LED_S_Y 5
#define LED_S_G 6
#define SOUTH_BUTTON_PIN 2

#define LED_W_R 8
#define LED_W_Y 9
#define LED_W_G 10
#define WEST_BUTTON_PIN 3

#define LED_WA_R 11
#define LED_WA_G 12
#define WALK_BUTTON_PIN 7

#define goW 0
#define waitW 1
#define goS 2
#define waitS 3
#define walk 4
#define walkclose 5
#define walkopen 6
#define walkclose2 7
#define walkopen2 8
#define walkclose3 9

struct State {
  unsigned long ST_Out;
  unsigned long Time;
  unsigned long Next[10];};
  typedef const struct State SType;
  
SType FSM[10]={
  {B10000101,2000,{goW, goW, waitW, waitW, waitW, waitW, waitW, waitW}},
  {B01000101,300,{goS,  goS, goS, goS, walk, walk,  walk,  walk}},
  {B00110001,2000,{goS, waitS, goS, waitS, waitS, waitS, waitS, waitS}},
  {B00101001,300,{goW,  goW, goW, goW, walk,  walk,  walk,  goW}},
  {B00100110,300,{walk, walkclose, walkclose, walkclose, walk,  walkclose, walkclose, walkclose}},
  {B00100100,300,{walkopen, walkopen,  walkopen,  walkopen,  walkopen,  walkopen,  walkopen,  walkopen}},
  {B00100110,300,{walkclose2,  walkclose2,  walkclose2,  walkclose2,  walkclose2,  walkclose2,  walkclose2,  walkclose2}},
  {B00100100,300,{walkopen2, walkopen2,  walkopen2,  walkopen2,  walkopen2,  walkopen2,  walkopen2,  walkopen2}},
  {B00100110,300,{walkclose3,  walkclose3,  walkclose3,  walkclose3,  walkclose3,  walkclose3,  walkclose3,  walkclose3}},
  {B00100100,300,{goS,  goW, goS, goS, goS, goW, goS, goS}}
  };

  unsigned long S=0;
  void setup() {
  pinMode(LED_W_R, OUTPUT);
  pinMode(LED_W_Y, OUTPUT);
  pinMode(LED_W_G, OUTPUT); 
  pinMode(WEST_BUTTON_PIN, INPUT); 
  
  pinMode(LED_S_R, OUTPUT);
  pinMode(LED_S_Y, OUTPUT);
  pinMode(LED_S_G, OUTPUT); 
  pinMode(SOUTH_BUTTON_PIN, INPUT); 
  
  pinMode(LED_WA_R, OUTPUT);
  pinMode(LED_WA_G, OUTPUT);
  pinMode(WALK_BUTTON_PIN, INPUT);
}

int input,input1, input2, input3;

void loop() {
  digitalWrite(LED_WA_G, FSM[S].ST_Out & B00000010);
  digitalWrite(LED_WA_R, FSM[S].ST_Out & B00000001);

  digitalWrite(LED_S_R, FSM[S].ST_Out & B00100000);
  digitalWrite(LED_S_Y, FSM[S].ST_Out & B01000000);
  digitalWrite(LED_S_G, FSM[S].ST_Out & B10000000);
  
  digitalWrite(LED_W_R, FSM[S].ST_Out & B00000100);
  digitalWrite(LED_W_Y, FSM[S].ST_Out & B00001000);
  digitalWrite(LED_W_G, FSM[S].ST_Out & B00010000);
 
  delay(FSM[S].Time);
  input1 = digitalRead(WEST_BUTTON_PIN);    
  input2 = digitalRead(SOUTH_BUTTON_PIN);   
  input3 = digitalRead(WALK_BUTTON_PIN);    
  input = input3*4 + input2*2 + input1;   
  S = FSM[S].Next[input]; 
}
