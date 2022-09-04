#define button1 12 //left
#define button2 11 //middle
#define button3 10 //right
#define LED3 4 // red
#define LED2 3 //yellow
#define LED1 2 //green
int beginR = 0, beginG = 0, beginY = 0, stopY = 0;

void setup()
{
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT_PULLUP);
  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
}

void loop()
{
  int mill = millis(); 
  swRed(mill);
  swGreen(mill);
  swYellow(mill);
}

void swRed(int mill)
{
  if (mill - beginR > 3000 && beginR != 0)
  {
    digitalWrite(LED3, LOW);
    beginR = 0;
  }
  else if (digitalRead(button1) == HIGH)
  {
    digitalWrite(LED3, !digitalRead(LED3));
    beginR = millis();
    delay(200);
  }
}

void swGreen(int mill)
{
  if (mill - beginG > 3000 && beginG != 0)
  {
    digitalWrite(LED1, LOW);
    beginG = 0;
  }
  else if (digitalRead(button3) == LOW && digitalRead(LED3) != HIGH)
  {
    digitalWrite(LED1, !digitalRead(LED1));
    beginG = millis();
    delay(200);
  }
}

void swYellow(int mill)
{
  if (mill - beginY <= 2000 && beginY != 0)
  {
    if ((mill - stopY) > 500) 
    {
      digitalWrite(LED2, !digitalRead(LED2));
      stopY = millis();
    }
  }
  else if (mill - beginY > 2000 && beginY != 0)
  {
    digitalWrite(LED2, LOW);
    beginY = 0;
  }
  else if (digitalRead(button2) == LOW && digitalRead(LED3) != HIGH && digitalRead(LED1) != HIGH)
  {
    digitalWrite(LED2, HIGH);
    beginY = millis();
    stopY = millis();
    delay(200);
  }
}
