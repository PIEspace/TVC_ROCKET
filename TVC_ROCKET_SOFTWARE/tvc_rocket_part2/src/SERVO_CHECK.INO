// LETS CHECK THE SERVO MOTOR

#include<Arduino.h>
#include<Servo.h>

Servo first_servo;
Servo second_servo;

// define the servo position 

void setup(){
    Serial.begin(9600);
    first_servo.attach(4);
    second_servo.attach(5);

    first_servo.write(120);
    delay(1000);

    second_servo.write(90);
    delay(1000);
   

}

void loop(){
    first_servo.write(120);
    second_servo.write(90);
    delay(100);

    first_servo.write(140);
    second_servo.write(105);
    delay(100);

    first_servo.write(120);
    second_servo.write(90);
    delay(100);

    first_servo.write(100);
    second_servo.write(80);
    delay(100);

    first_servo.write(120);
    second_servo.write(90);
    delay(100);

   



}