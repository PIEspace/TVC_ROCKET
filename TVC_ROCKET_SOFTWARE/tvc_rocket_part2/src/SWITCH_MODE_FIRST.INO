// SO IN THE SWITCH MODE FIRST SO ITS PREDEFINED DEFINE 

#include<Arduino.h>
#include<Servo.h>

// define the servo motor
Servo first_servo;
Servo second_servo;

// define the button and led
const int first_button = 6;
// define the led
const int first_led = 9;
// define the buzzer 
const int buzzer = 3;

int buttonState = LOW;
int lastButtonState = LOW;
int buttonPressCount = 0;



void setup(){
    Serial.begin(9600);

    first_servo.attach(4);
    second_servo.attach(5);

    pinMode(first_button , INPUT); //define the button state
    pinMode(first_led , OUTPUT); //define the led state 
    pinMode(buzzer , OUTPUT) ; //define the buzzer state 

    // lets define the servo angle 
    first_servo.write(120); //FIRST SERVO ANGLE IS 120 DEGREE
    second_servo.write(90); //SECOND SERVO ANGLE IS 90 DEGREE 


}

void PlayActiveTone(){
    int tone_frequencies[] = { 200 , 400 ,600, 800 , 1000 , 1200 , 1400 , 1600 , 1800 , 2000 };

    for(int tone_value = 0 ; tone_value <= 10 ; tone_value++){
        tone(buzzer , tone_frequencies[tone_value] , 100);
        delay(100);
    }
    for(int high_tone = 0; high_tone <= 2 ; high_tone++)
    {
    digitalWrite(buzzer , HIGH);
    delay(300); //delay for 300 millisecond 
    digitalWrite(buzzer , LOW);
    delay(300); //delay for 300 millisecond

    }
    
}

void servo_check_autopilot(){

    // first is normal mode 
    
    for(int z = 0; z <= 5 ; z++)
    {

    // define the first servo motor move from 120 degree to 140 degree
    for(int a = 120 ; a<= 140 ; a++){
        first_servo.write(a);delay(15);
    }
    
    // define the second servo motor move from 90 degree to 105 degree 
    for(int b = 90 ; b<= 105 ; b++){
        second_servo.write(b); delay(15);
    }

    // define the first servo motor move from 140 degree back to  120 degree 
    for(int c = 140 ; c >=120 ; c--){
        first_servo.write(c);delay(15);
    }

    // define the second servo motor move from 105 degree back to 90 degree 
    for(int d = 105 ; d>=90 ; d--){
        second_servo.write(d); delay(15);
    }

    // define the first motor move from 120  back to 100 degree 
    for(int e = 120 ; e >=100 ; e--){
        first_servo.write(e);delay(15);
    }

    // define the second servo motor move from 
    for(int f = 90 ; f >=80 ; f--){
        second_servo.write(f); delay(15);
    }

// define the first servo motor move from 100 degree to 120 degree 
    for(int g = 100 ; g <=120 ; g++){
        first_servo.write(g);delay(15);
    }

    // define the second servo motor move from 80 degree to 90 degree
    for(int h = 80 ; h <=90 ; h++){
        second_servo.write(h); delay(15);
    }
    }
    
}

void loop(){

    buttonState = digitalRead(first_button);

    if(buttonState != lastButtonState)
    {
        if(buttonState == HIGH)
        {
            buttonPressCount++;
            Serial.println("Button Pressed ! ");

            if(buttonPressCount == 3){
                Serial.println("Button pressed three times , LED is ON! ");
                digitalWrite(first_led , HIGH);
                PlayActiveTone();
                servo_check_autopilot();
            }

            if (buttonPressCount >4)
            {
                Serial.println("Button pressed again , LED is OFF !");
                digitalWrite(first_led , LOW);
                buttonPressCount = 0;
            }
            
        }
    }

    lastButtonState = buttonState;
    delay(50);

}

