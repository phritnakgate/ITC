// Slave 2

#include <Wire.h>
#define Master 1
#define Slave1 2
#define Slave2 3
#define Maximum 30

char Massage[Maximum];
unsigned i = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin(Slave2);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop()
{

}

void receiveEvent(int x)
{
  for (int c = 0; c < x; c++)
    Massage[c] = Wire.read();
}

void requestEvent()
{
  
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
  
   // display token
  
  if (Massage[6] == '1') { 
    int addr = Massage[8] - '0';
    
    if (addr == Slave2) { Serial.println(Massage);
      for (i = 10; Massage[i] != '\0'; i++)
      {
        Serial.print(Massage[i]);
      }
      i = 0;
      Serial.println();
      Massage[6] = '0';
      Massage[8] = '\0';
     Serial.println(Massage);
    }
  }
  if (Massage[6] == '1') Wire.write(Massage, sizeof(Massage));
  Massage[6] = '0';
  Massage[8] = '\0';
   
  
}
