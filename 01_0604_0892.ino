int dl=500;
void setup() {
  
}

void loop() {
  //Red Right
  pinMode(13,INPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  delay(dl);
  //Red Left
  pinMode(13,INPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  delay(dl);
  //Green Right
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  digitalWrite(13,LOW);
  delay(dl);
  //Green Left
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  digitalWrite(13,HIGH);
  delay(dl);
  //Yellow Right
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,INPUT);
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);
  delay(dl);
  //Yellow Left
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,INPUT);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  delay(dl);
  //Yellow Right
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,INPUT);
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);
  delay(dl);
  //Green Left
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  digitalWrite(13,HIGH);
  delay(dl);
  //Green Right
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  digitalWrite(13,LOW);
  delay(dl);
  //Red Left
  pinMode(13,INPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  delay(dl);
  //Begin
  pinMode(13,INPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  delay(dl);
  
}
