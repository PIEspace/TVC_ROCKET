// LETS CHECK THE ARDUINO FIRST

#include<Arduino.h>

void setup(){
    Serial.begin(9600);

}

void loop(){
    Serial.println(millis() /1000);
    

}