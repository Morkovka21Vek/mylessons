/*
  газ/тормоз,руль\n
  0,0\n
*/

#include <Servo.h>

Servo myservo;

#define mot_pin1 6
#define mot_pin2 3 
#define servo_pin 5

int valX;
int valY;

void setup() {
  pinMode(mot_pin1, OUTPUT);
  pinMode(mot_pin2, OUTPUT);
  Serial.begin(9600);
  myservo.attach(servo_pin);
}

void loop() {
    if (Serial.available() > 0) {
      String inputString = Serial.readStringUntil('\n');
      
      int tokens[2];

      int index = 0;
      if ((index = inputString.indexOf(',')) >= 0) {
        int token = inputString.substring(0, index).toInt();
        tokens[0] = token;
        inputString.remove(0, index + 1);
      }

      tokens[1] = inputString.toInt();
  
//      Serial.print(tokens[0].toInt());
//      Serial.print("; ");
//      Serial.println(tokens[1].toInt());

      if (tokens[0] > 0)
      {
        analogWrite(mot_pin1, tokens[0]);
        analogWrite(mot_pin2, LOW);
      }
      else if (tokens[0] < 0)
      {
        analogWrite(mot_pin1, LOW);
        analogWrite(mot_pin2, -tokens[0]);
      }
      else
      {
        analogWrite(mot_pin1, LOW);
        analogWrite(mot_pin2, LOW);
      }
  
      myservo.write(tokens[1]);
    }
}
