// Master
#include <Wire.h>

#define Master 1
#define Slave1 2
#define Slave2 3
#define Maximum 30

char Massage[Maximum] = "Token#0#";
unsigned i = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin(Master);
  Wire.onReceive(receiveEvent);
  //mas1
  Wire.beginTransmission(Slave1);
  Wire.write(Massage, sizeof(Massage));
  Wire.endTransmission();
  //mas1
  Wire.beginTransmission(Slave2);
  Wire.write(Massage, sizeof(Massage));
  Wire.endTransmission();
}
//เป็นการเช็คข้อมูลเเละการอ่านข้อมูล
void PrintSend()
{//
  Serial.println(Massage); 
  
  if (Massage[6] == '1') {
    
    int addr = Massage[8] - '0';
    
    if (addr != Master) {
     
      Wire.beginTransmission(addr);
      Wire.write(Massage, sizeof(Massage));
      Wire.endTransmission();
    }
    
    else {
      for (i = 10; Massage[i] != '\0'; i++)
      {
        Serial.print(Massage[i]);
      }
      Serial.println();
      i = 0;
    }
    
    Massage[6] = '0';
    Massage[8] = '\0';
    Serial.println(Massage);
  }}
  //รับมาเเละเช็คว่าถูกต้องไหม
  void checkmassage()
{
  for (int i = 0; Wire.available() && i < Maximum - 1; i++)
  {
    Massage[i] = Wire.read();
    
    if(!Wire.available())
      Massage[i] = '\0';
    
  }
  
  if (Massage[6] != '1') {
    char sthk[9] = "Token#0#";
    for (int i = 0; sthk[i] != '\0'; i++)
    {
      Massage[i] = sthk[i];
    }
    Massage[8] = '\0';
  }
}
void loop()
{
  
  Wire.requestFrom(Slave1, sizeof(Massage));
  checkmassage();
  if (Massage[6] == '1') PrintSend();
  
  Wire.requestFrom(Slave2, sizeof(Massage));
  checkmassage();
  if (Massage[6] == '1') PrintSend();
  
  while (Serial.available()) {
    char inChar = (char) Serial.read();
  
    
     if ( i < Maximum - 1) {
      Massage[i] = inChar;
      i++;
    }
    
    if(!Serial.available()) {
      Massage[i] = '\0';
      i = 0;
    }
  }
  if(Massage[6]!='1' || Massage[8]<'1'|| Massage[8]>'3' ){
    Massage[6] = '0';
    Massage[8] = '\0';
  }
  if (Massage[6] == '1') PrintSend();
  
  delay(1000);
}
//การรับข้อมูลมาที่ละตัว
void receiveEvent(int x)
{
  
  for (int i = 0; i < x; i++)
    Massage[i] = Wire.read();
  
}