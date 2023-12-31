// LETS CHECK THE SWITCH and LED

#include<Arduino.h>

const int switch_one = 6;
const int switch_two = 7;
const int led_one = 8;
const int led_two = 9;

void setup(){
    Serial.begin(9600);
    pinMode(switch_one , INPUT);
    pinMode(switch_two , INPUT);

    pinMode(led_one , OUTPUT);
    pinMode(led_two , OUTPUT);

    digitalWrite(led_one , HIGH);
    delay(2000);
    digitalWrite(led_one , LOW);
    delay(2000);

    digitalWrite(led_two , HIGH);
    delay(2000);
    digitalWrite(led_two , LOW);
    delay(2000);
}

void loop(){
    int first_switch_value = digitalRead(switch_one);
    int second_switch_value = digitalRead(switch_two);

    if(first_switch_value == LOW)
    {
        digitalWrite(led_one , LOW);
    }
    else if (first_switch_value == HIGH)
    {
        digitalWrite(led_one , HIGH);
    }
    
    if (second_switch_value == LOW)
    {
        digitalWrite(led_two , LOW);
    }
    else if (second_switch_value == HIGH)
    {
        digitalWrite(led_two , HIGH);
    }
    
    
    

    // print on the serial monitor
    Serial.print(" switch = 1 ");
    Serial.print(first_switch_value);
    Serial.print(" , ");
    Serial.print(" switch = 2 ");
    Serial.println(second_switch_value);

}