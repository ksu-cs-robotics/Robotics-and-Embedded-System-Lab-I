/**********************************************************************;
* Project           : RES_Class, DC Motor Control, H-Bridge Motor Driver 
*
* Program name      : RES_Rotary_Encoder_Basic.ino
*
* Author            : Jong-Hoon Kim
*
* Date created      : 10/31/2022
*
* Purpose           : H-Bridge Motor Driver 
*
* Revision History  :
*
* Date        Author      Ref    Revision (Date in MMDDYYYY format) 
* MMDDYYYY    name      1  v-xx   revision note. 
*
*********************************************************************/
/*********************************************************************
*   Instructional Note:  
*           Arduino Leonardo has 4 interrupt pins ( 0, 1, 2, 3  13 )
*           Arduino Mega has 6 interrupt pins ( 2, 3, 18, 19, 20, 21)
*   reference website ( https://www.pjrc.com/teensy/td_libs_Encoder.html )                    
***********************************************************************/

#define PIN_SERVO_0           12
#define PIN_MOTOR_PWM_LEFT    5
#define PIN_MOTOR_IN0_LEFT    4
#define PIN_MOTOR_IN1_LEFT    3
#define PIN_JOY_SW            A0
#define PIN_JOY_X             A1
#define PIN_JOY_Y             A2
#define INTERVAL_PRINT        100000


long preTime = 0;
int motorSpeedLeft = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Motor Control Started");
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT); pinMode(PIN_MOTOR_IN0_LEFT, OUTPUT); pinMode(PIN_MOTOR_IN1_LEFT, OUTPUT);
  pinMode(PIN_JOY_SW, INPUT_PULLUP);
  pinMode(PIN_JOY_X, INPUT); pinMode(PIN_JOY_Y, INPUT);
  preTime = millis() + INTERVAL_PRINT; 
}

void loop() {
  if (preTime > millis()){
      preTime = millis() + INTERVAL_PRINT;
      Serial.print("Left Motor Power  = ");
      Serial.println(motorSpeedLeft);
    
  }

  motorSpeedLeft = map( analogRead(PIN_JOY_X), 0,1023, -255, 255);
  if (motorSpeedLeft < 0){
    analogWrite(PIN_MOTOR_PWM_LEFT, -motorSpeedLeft);   digitalWrite( PIN_MOTOR_IN0_LEFT, HIGH);    digitalWrite( PIN_MOTOR_IN1_LEFT , LOW);
    
  }else if (motorSpeedLeft > 0){
    analogWrite(PIN_MOTOR_PWM_LEFT, motorSpeedLeft);   digitalWrite( PIN_MOTOR_IN0_LEFT , LOW);    digitalWrite( PIN_MOTOR_IN1_LEFT , HIGH);
    
  }else{
    analogWrite(PIN_MOTOR_PWM_LEFT, 0);   digitalWrite( PIN_MOTOR_IN0_LEFT, LOW);    digitalWrite( PIN_MOTOR_IN1_LEFT , LOW);
  }
}




