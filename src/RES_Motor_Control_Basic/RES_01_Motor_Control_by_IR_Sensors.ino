#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int joyX = A2;  int joyY = A1;  int joySW = A0;  
int servoPin = 7;
int IR_Left_Pin = 3;  // connect IR Left sensor module to Arduino pin D3
int IR_Right_Pin = 4; // connect IR Right sensor module to Arduino pin D4
int Motor_Left_In_1 = 11; int Motor_Left_In_2 = 12; int Motor_Left_In_PWM = 13;
int Motor_Right_In_1 = 10; int Motor_Right_In_2 = 9; int Motor_Right_In_PWM = 8;

float joyX_Val = 0; // robot direction control 
int joyY_Val = 0;  // robot speed control
int joySW_Val = 0;
int Motor_Left_Speed=0;
int Motor_Right_Speed=0;
int IRLeftSensor = 0;
int IRRightSensor = 0;

void setup() {
  Serial.begin(9600);
  pinMode(joyX, INPUT);  pinMode(joyY, INPUT);  pinMode(joySW, INPUT); digitalWrite(joySW,HIGH);
  pinMode(IR_Left, INPUT); pinMode(IR_Right, INPUT); // IR Sensor pin INPUT
  pinMode(Motor_Left_In_1, OUTPUT); pinMode(Motor_Left_In_2, OUTPUT); pinMode(Motor_Left_In_PWM, OUTPUT); 
  pinMode(Motor_Right_In_1, OUTPUT); pinMode(Motor_Right_In_2, OUTPUT); pinMode(Motor_Right_In_PWM, OUTPUT); 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop(){
 IRLeftSensor= digitalRead(IR_Left_Pin); // Set the GPIO as Input
 IRRightSensor= digitalRead(IR_Right_Pin); // Set the GPIO as Input
  if (IRLeftSensor == 1){ // Check if the pin high or not
      Serial.println(“left "); // print Motion Detected! on the serial monitor window
  }   
  if (IRRightSensor == 1){ // Check if the pin high or not
      Serial.println(“right!"); // print Motion Ended! on the serial monitor window
  }  
}

void motorControlByIRSensors() {
  if ((IRLeftSensor == 1) && (IRRightSensor==1)){ // stop both motors
     digitalWrite(Motor_Left_In_1,LOW); digitalWrite(Motor_Left_In_2,LOW);
     digitalWrite(Motor_Right_In_1,LOW); digitalWrite(Motor_Right_In_2,LOW);
     analogWrite(Motor_Left_In_PWM, 0  );
     analogWrite(Motor_Right_In_PWM, 0  );    
  }else if ((IRLeftSensor == 1) && (IRRightSensor==0)){ // turn left
     digitalWrite(Motor_Left_In_1,LOW); digitalWrite(Motor_Left_In_2,HIGH);
     digitalWrite(Motor_Right_In_1,HIGH); digitalWrite(Motor_Right_In_2,LOW);
     analogWrite(Motor_Left_In_PWM, 255  );
     analogWrite(Motor_Right_In_PWM, 255  );   
    
  }else if ((IRLeftSensor == 0) && (IRRightSensor==1)){ // turn right
     digitalWrite(Motor_Left_In_1,HIGH); digitalWrite(Motor_Left_In_2,LOW);
     digitalWrite(Motor_Right_In_1,LOW); digitalWrite(Motor_Right_In_2,HIGH);
     analogWrite(Motor_Left_In_PWM, 255  );
     analogWrite(Motor_Right_In_PWM, 255  );      
  }else{ // run straight 
     digitalWrite(Motor_Left_In_1,HIGH); digitalWrite(Motor_Left_In_2,LOW);
     digitalWrite(Motor_Right_In_1,HIGH); digitalWrite(Motor_Right_In_2,LOW);
     analogWrite(Motor_Left_In_PWM, 255  );
     analogWrite(Motor_Right_In_PWM, 255  );        
  }
}

void motorControlByJoystick() {
  joyY_Val = map(analogRead(joyY), 0, 1023, -255, 255);     // robot speed control 
  joyX_Val = myMap(analogRead(joyX), 0, 1023, -1.0, 1.0);     // robot direction control   
  if (joyY_Val > 0){
     digitalWrite(Motor_Left_In_1,HIGH); digitalWrite(Motor_Left_In_2,LOW);
     digitalWrite(Motor_Right_In_1,HIGH); digitalWrite(Motor_Right_In_2,LOW);
     Motor_Left_Speed = joyY_Val - (joyY_Val * -joyX_Val);
     Motor_Right_Speed = joyY_Val - (joyY_Val * joyX_Val);
  }else if (joyY_Val < 0){
     digitalWrite(Motor_Left_In_1,LOW); digitalWrite(Motor_Left_In_2,HIGH);    
     digitalWrite(Motor_Right_In_1,LOW); digitalWrite(Motor_Right_In_2,HIGH);    
     Motor_Left_Speed = abs(joyY_Val) - (abs(joyY_Val) * joyX_Val);
     Motor_Right_Speed = abs(joyY_Val) - (abs(joyY_Val) * -joyX_Val);         
  }else{
     digitalWrite(Motor_Left_In_1,LOW); digitalWrite(Motor_Left_In_2,LOW);    
     digitalWrite(Motor_Right_In_1,LOW); digitalWrite(Motor_Right_In_2,LOW);          
     Motor_Left_Speed = 0 ;
     Motor_Right_Speed = 0 ;    
  }
  if (Motor_Left_Speed > 255) Motor_Left_Speed = 255;
  if (Motor_Right_Speed > 255) Motor_Right_Speed = 255;  
  analogWrite(Motor_Left_In_PWM, Motor_Left_Speed  );
  analogWrite(Motor_Right_In_PWM, Motor_Right_Speed  );
  Serial.print( Motor_Left_Speed);  Serial.print("  ");  Serial.print( Motor_Right_Speed); Serial.print(" =  ");
  Serial.print( joyX_Val);  Serial.print("  ");  Serial.println( joyY_Val);
  delay(15);                           // waits for the servo to get there
}


float myMap(float x, float in_min, float in_max, float out_min, float out_max) {
  float out = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  if (out > out_max) return out_max;
  else if (out < out_min) return out_min;
  else return out;  
}
