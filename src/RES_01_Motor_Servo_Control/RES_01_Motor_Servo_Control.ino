#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int joyX = A2;  int joyY = A1;  int joySW = A0;  
int servoPin = 12;
int motorA_1 = 11; int motorA_2 = 12; int motorA_PWM = 13;
int motorB_1 = 10; int motorB_2 = 9; int motorB_PWM = 8;

int joyX_Val = 0;
int joyY_Val = 0;
int joySW_Val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(joyX, INPUT);  pinMode(joyY, INPUT);  pinMode(joySW, INPUT); digitalWrite(joySW,HIGH);
  pinMode(motorA_1, OUTPUT); pinMode(motorA_2, OUTPUT); pinMode(motorA_PWM, OUTPUT); 
  pinMode(motorB_1, OUTPUT); pinMode(motorB_2, OUTPUT); pinMode(motorB_PWM, OUTPUT); 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  joyX_Val = map(analogRead(joyX), 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
  myservo.write(joyX_Val);                  // sets the servo position according to the scaled value
  joyY_Val = map(analogRead(joyY), 0, 1023, -255, 255);     // scale it for use with the servo (value between -255 and 255)
  if (joyY_Val> 0){
     digitalWrite(motorA_1,HIGH); digitalWrite(motorA_2,LOW);
     digitalWrite(motorB_1,HIGH); digitalWrite(motorB_2,LOW);
  }else{
     digitalWrite(motorA_1,LOW); digitalWrite(motorA_2,HIGH);    
     digitalWrite(motorB_1,LOW); digitalWrite(motorB_2,HIGH);    
  }
  analogWrite(motorA_PWM, abs( joyY_Val));
  analogWrite(motorB_PWM, abs( joyY_Val));

  Serial.print( joyX_Val);  Serial.print(" ");  Serial.println( joyY_Val);
  delay(15);                           // waits for the servo to get there
}
