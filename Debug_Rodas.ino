int md2 = 10;
int md1 = 9;
int me1 = 11;
int me2 = 3;

void setup() {
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  pinMode(me1, OUTPUT);
  pinMode(me2, OUTPUT);  

}

void loop() {
  
  digitalWrite(md1,HIGH);
  digitalWrite(me1,HIGH);
  digitalWrite(md2,LOW);
  digitalWrite(me2,LOW);
  
  delay(3000);
  
   digitalWrite(md1,LOW);
  digitalWrite(me1,LOW);
  digitalWrite(md2,HIGH);
  digitalWrite(me2,HIGH);
  
  delay(3000);
  

}
