int fqc;
int lsrout = 12;
#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(11520);
  pinMode(lsrout, OUTPUT);
  String data = "s";
  while (data == "s"){
      fqc = mySerial.readStringUntil("|").toFloat();
      float per = 1/fqc;
      float lsron =  10;
      float lsroff = per - lsron;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  String a = Serial.readStringUntil("2");
  int r = a.toInt();
  if (r == 1){
    digitalWrite(lsrout, HIGH);
    delay(lsron);
    digitalWrite(lsrout, LOW);
    delay(lsroff);
  }
  else if (r == 0){
    digitalWrite(lsrout, LOW);
  }

}