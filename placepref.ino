#include <Wire.h>
int fqc;
int lsrout = 12;
float lsron;
float lsroff;
String frq = "";
bool setupfrq = false;
bool on = false;
unsigned long end = 0;
unsigned long now;
bool checkchar(String s, char c){
for(int i = 0; i < s.length(); i++){
    if (s[i] == c){
      return true;
    }
  } 
return false;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lsrout, OUTPUT);
  while (true){
    if (!setupfrq){
      if (Serial.available()){
            frq = Serial.readStringUntil('\n');
            if (checkchar(frq, '|')){
              setupfrq = true;
              float per = 1000/frq.toFloat();
              lsron = 10;
              lsroff = per - lsron;
              break;
            }

      }
    }
  }
}

void loop() {
  now = millis();
  if (Serial.available()){
  int r = Serial.parseInt();
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