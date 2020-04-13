
#include "RES_Smoothing_Data.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  Serial.println("Smoothing Data");
  delay(1000);
  for(int i = 0; i < 1000; i++){
     Serial.print("data ");Serial.print(i); Serial.print(" ");
    Serial.println(((noisy_data[i]*1000)+ 400))/2;
    delay(10);
  }

}

void loop() {
  // put your main code here, to run repeatedly:


}
