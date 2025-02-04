#include <Wire.h>
int fqc;
int lsrout = 12;
float lsron;
float lsroff;
bool on = false;
unsigned long end = 0;
unsigned long now;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(11520);
  pinMode(lsrout, OUTPUT);
  String data = "s";
  while (data == "s"){
      fqc = Serial.readStringUntil("|").toFloat();
      float per = 1/fqc;
    lsron =  10;
    lsroff = per - lsron;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    now = millis();
  if (Serial.available()){
  String a = Serial.readStringUntil("2");
  int r = a.toInt();
  if (r == 1 && !on && now > end){
    on = true;
    digitalWrite(lsrout, HIGH);
    end = now + lsron;
  }
  else if (r ==  1 && on && now > end){
    on = false;
    digitalWrite(lsrout, LOW);
    end = now + lsroff;
  }
  else if (r == 0){
    digitalWrite(lsrout, LOW);
    end = 0;
    on = false;
  }
}
}