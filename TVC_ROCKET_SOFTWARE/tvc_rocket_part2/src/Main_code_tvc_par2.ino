/*

lets write the tvc demonstration project code 

this code is written by pie.space 

follow me on social media account 

Instagram = https://www.instagram.com/creativeindia__/?hl=en
YouTube = https://www.youtube.com/@PIE_SPACE_1
GitHUB = https://github.com/PIEspace

*/

#include<Arduino.h>
#include<FastLED.h>
#include<Servo.h>

// define the ws2812-b led pin and number of led
#define LED_PIN 2 //Change this to the pin where you data line is connected 
#define NUM_LED 1 //change this to the number of Led in your strips

CRGB led [NUM_LED];


// Define the Buzzer 
const int Buzzer = 3;

// define the Switch
const int First_Switch = 6;
const int Second_Switch = 7;

// define the led 
const int Led_First = 8;
const int Led_Second = 9;

// LETS DEFINE THE SERVO MOTOR
Servo FIRST_SERVO_MOTOR;
Servo SECOND_SERVO_MOTOR;


// define the servo pin connection 
// first servo motor pin number = 4
// second servo motor pin number = 5

const int First_Servo_Pin_Number = 4;
const int Second_Servo_Pin_Number = 5;

// define the millis function 
unsigned long previousTime = 0;
const int delay_time = 100;


void led_check_start_program(){
    for (int b = 0; b < 30; b++)
    {
        // Define an array of colors
     CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Purple , CRGB::OrangeRed , CRGB::LimeGreen , CRGB::OrangeRed , CRGB::GreenYellow};

     // Choose a random color from the array
      CRGB randomColor = colors[random(0, sizeof(colors) / sizeof(colors[0]))];

      // Turn off all LEDs
      FastLED.clear();

     // Set all LEDs to the random color
     fill_solid(led, NUM_LED, randomColor);

     // Show the colors on the LEDs
      FastLED.show();
  
      // Pause for a moment to display the color
      delay(100);
  
     // Turn off all LEDs
     FastLED.clear();
  
      // Show the colors on the LEDs
     FastLED.show();
    }
    
}

void buzzer_start_program(){
     int buzzer_tone_frequency [] = {200 , 400,800,1200,1600,2000,2400,2800,3200,3600,4000};

    for (int buzzer_tone_value = 0 ; buzzer_tone_value < 11 ; buzzer_tone_value++)
    {
        tone(Buzzer , buzzer_tone_frequency[buzzer_tone_value] , 100);
        delay(50);
    }

    int buzzer_tone_frequncy_second [] = {600,1200,1800,2400,3000,3600,4200,4800,5400,6000};


    for (int large_tone = 0;large_tone < 10 ; large_tone ++) {
      tone(Buzzer , buzzer_tone_frequncy_second[large_tone] , 100);
      delay(150);
    }

    for (int beep_tone = 0; beep_tone < 3; beep_tone++) {

      tone(Buzzer, 1800);
      delay(100);
      noTone(Buzzer);

      tone(Buzzer, 2400);
      delay(100);
      noTone(Buzzer);

      tone(Buzzer, 1200);
      delay(100);
      noTone(Buzzer);

      digitalWrite(Buzzer, LOW);
      delay(50);
    
    }
    
}

void setup(){
    // define the bud rate in this case i am using 115200 bits per second(bps)
    Serial.begin(115200);
    // define the buzzer pinMode
    pinMode(Buzzer , OUTPUT);
    // define the Switch PinMode
    pinMode(First_Switch , INPUT);
    pinMode(Second_Switch , INPUT);
    // define the led PinMode
    pinMode(Led_First , OUTPUT);
    pinMode(Led_Second , OUTPUT);
    // define the ws2812-b 
    FastLED.addLeds<WS2812 , LED_PIN , GRB >(led , NUM_LED);

    // START THE SETUP CODE 
   
    
    unsigned long currentTime = millis();
    if(currentTime - previousTime >=delay_time){
        // save the current time 
        previousTime = currentTime;
        // lets call the function 
        led_check_start_program();
    }

    buzzer_start_program();


}

void loop(){

}