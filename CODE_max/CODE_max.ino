#include<SPI.h>
byte address=0x00;
int CS=10;
void setup() {
  pinMode(CS,OUTPUT);
  pinMode(2,INPUT);
  SPI.begin();
}

void loop() {
  int ron=analogRead(2);
  ron=map(ron,0,1023,0,128);
  digitalWrite(CS,LOW);
  SPI.transfer(address);
  SPI.transfer(ron);
  digitalWrite(CS,HIGH);
}
