// LETS WRITE THE TVC CODE SO IN THIS CODE WILL USE PID 
/*
// WHEN WE START THE CODE FIRST WE WILL START WITH THE SCHEMATIC DIAGRAM 

DIAGRAM:-

arduino nano  =  mpu6050
arduino nano  = buzzer 
arduino nano = ws2812-b
arduino nano = switch
arduino nano = led

*/


#include<Arduino.h>
#include<FastLED.h>
#include<Servo.h>
#include<Wire.h>

// define the buzzer 
const int BUZZER = 3;

// DEFINE THE WS2812-B LED STRIPE 
#define LED_PIN     2   // Change this to the pin where your data line is connected
#define NUM_LEDS    1  // Change this to the number of LEDs in your strip

CRGB leds[NUM_LEDS];

// LETS DEFINE THE SERVO MOTOR
Servo FIRST_SERVO_MOTOR;
Servo SECOND_SERVO_MOTOR;

// DEFINE THE SERVO MOTOR POSITION 
// define the first servo motor
int First_Servo_Position_first = 120;  //    120 = 140 = 120 = 100 = 120   
int First_Servo_Position_second = 140;
int First_Servo_Position_third = 100;

// define the second servo motor
int Second_Servo_Position_first = 90;
int Second_Servo_Position_second = 105;
int Second_Servo_Position_third = 80;

// define the servo pin connection 
// first servo motor pin number = 4
// second servo motor pin number = 5

const int First_Servo_Pin_Number = 4;
const int Second_Servo_Pin_Number = 5;

// define the button and led 
// define the button
const int first_switch = 6; //attach the first switch pin number = d6
const int second_switch = 7; //attach the second switch pin number = d7 
// define the led 
const int first_led = 8; //attach the first led pin number = d8
const int second_led = 9; //attach the second led pin number = d9

// define the mpu6050
const int MPU6050_ADDRESS = 0X68; //I2C address of the mpu6050 sensor 
// define the constant and variable 
int16_t accelerometer_x , accelerometer_y , accelerometer_z;
int16_t gyro_x , gyro_y , gyro_z;

int16_t accelerometer_x_offset , accelerometer_y_offset , accelerometer_z_offset;
int16_t gyro_x_offset , gyro_y_offset , gyro_z_offset;


// define the some variable 
int ButtonState = LOW;
int LastButtonState = LOW;
int ButtonPressCount = 0;


void flight_computer_on_beep(){
    // Mavic Pro drone sound frequencies
  int frequencies[] = {400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000};

  for (int i = 0; i < 9 ; i++) {
    tone(BUZZER, frequencies[i], 200); // Play each frequency for 100 milliseconds
    delay(50); // Add a small delay between tones for a more realistic sound

  }

  noTone(BUZZER); // Stop the buzzer after playing the sound
  delay(500); // Add a pause between each play for a more natural feel

  // hard tone
  for(int loud_buzzer = 0 ; loud_buzzer <= 4 ; loud_buzzer++)
  {
  digitalWrite(BUZZER , HIGH);
  delay(100); //DELAY FOR 100 MILLISECOND 
  digitalWrite(BUZZER , LOW);
  delay(100); //DELAY FOR 100 MILLISECOND 
  }
}


void led_indicate(){
    for (int i = 0; i <= 3; i++)
    {
        // Fill the entire strip with a color (red in this case)
       fill_solid(leds, NUM_LEDS, CRGB::Red);
       FastLED.show();
       delay(100);  // Pause for 200 milliseconds

       // Fill the entire strip with another color (green in this case)
       fill_solid(leds, NUM_LEDS, CRGB::Green);
       FastLED.show();
       delay(100);  // Pause for 200 milliseconds

       // Fill the entire strip with another color (blue in this case)
       fill_solid(leds, NUM_LEDS, CRGB::Blue);
       FastLED.show();
       delay(100);  // Pause for 200 milliseconds

       // Fill the entire strip with another color (orange in this case)
       fill_solid(leds, NUM_LEDS, CRGB::Orange);
       FastLED.show();
       delay(100);  // Pause for 200 milliseconds

       // Fill the entire strip with another color (skyBlue in this case)
       fill_solid(leds, NUM_LEDS, CRGB::SkyBlue);
       FastLED.show();
       delay(100);  // Pause for 200 milliseconds

    //    now turn off the led 
       fill_solid(leds, NUM_LEDS, CRGB::Black);
       FastLED.show();
       delay(100);  // Pause for 200 milliseconds
      
    }
}

void servo_check(){
  for(int first_servo_check = 0 ;first_servo_check <= 2 ; first_servo_check++ )
  {
    FIRST_SERVO_MOTOR.write(First_Servo_Position_first); //first position is 120 degree 
    delay(200);  //pause for 200 millisecond 
    FIRST_SERVO_MOTOR.write(First_Servo_Position_second); //second position is 140 degree
    delay(200);  //pause for 200 millisecond 
    FIRST_SERVO_MOTOR.write(First_Servo_Position_first); //first position is 120 degree 
    delay(200);  //pause for 200 millisecond 
    FIRST_SERVO_MOTOR.write(First_Servo_Position_third); //third position is 100 degree 
    delay(200);  //pause for 200 millisecond 
    FIRST_SERVO_MOTOR.write(First_Servo_Position_first); //first position is 120 degree
  }
  
  for(int second_servo_check = 0 ; second_servo_check <=2 ; second_servo_check++)
  {
    SECOND_SERVO_MOTOR.write(Second_Servo_Position_first); //first position is 90 degree 
    delay(200);  //pause for 200 millisecond 
    SECOND_SERVO_MOTOR.write(Second_Servo_Position_second); //second position is 110 degree
    delay(200);  //pause for 200 millisecond 
    SECOND_SERVO_MOTOR.write(Second_Servo_Position_first); //first position is 90 degree 
    delay(200);  //pause for 200 millisecond 
    SECOND_SERVO_MOTOR.write(Second_Servo_Position_third); //third position is 80 degree 
    delay(200);  //pause for 200 millisecond 
    SECOND_SERVO_MOTOR.write(Second_Servo_Position_first); //first position is  90  //pause for 200 millisecond  degree
  }

}


// define the mpu6050 initialize function and calibrate function 
void MPU6050_INIT(){
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(0X6B); 
  Wire.write(0);
  Wire.endTransmission(true);
}

void Calibrate_MPU6050(){
  int number_samples = 1000;

  for(int i = 0 ; i< number_samples ; i++)
  {
    Read_MPU6050();

    accelerometer_x_offset += accelerometer_x;
    accelerometer_y_offset += accelerometer_y;
    accelerometer_z_offset += accelerometer_z;
    gyro_x_offset += gyro_x;
    gyro_y_offset += gyro_y;
    gyro_z_offset += gyro_z;
    delay(5);
  }

  // calculate the average offset 
  accelerometer_x_offset /= number_samples;
  accelerometer_y_offset /= number_samples;
  accelerometer_z_offset /= number_samples;
  gyro_x_offset /= number_samples;
  gyro_y_offset /= number_samples;
  gyro_z_offset /= number_samples;

  // print calculate offset 
  Serial.println("Calibration offsets: ");
  Serial.print("Accel X: "); Serial.println(accelerometer_x_offset);
  Serial.print("Accel Y: "); Serial.println(accelerometer_y_offset);
  Serial.print("Accel Z: "); Serial.println(accelerometer_z_offset);
  Serial.print("Gyro X: "); Serial.println(gyro_x_offset);
  Serial.print("Gyro Y: "); Serial.println(gyro_y_offset);
  Serial.print("Gyro Z: "); Serial.println(gyro_z_offset);


}

void Read_MPU6050() {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDRESS, 14, true); // request a total of 14 registers

  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();
  accelerometer_z = Wire.read() << 8 | Wire.read();

  gyro_x = Wire.read() << 8 | Wire.read();
  gyro_y = Wire.read() << 8 | Wire.read();
  gyro_z = Wire.read() << 8 | Wire.read();
}


void buzzer_main_program_start(){
     // Mavic Pro drone sound frequencies
  int frequencies[] = {200 , 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000 };

  for (int i = 0; i <= 10 ; i++) {
    tone(BUZZER, frequencies[i], 100); // Play each frequency for 100 milliseconds
    delay(50); // Add a small delay between tones for a more realistic sound
  }
  noTone(BUZZER); // Stop the buzzer after playing the sound
  delay(500); // Add a pause between each play for a more natural feel


  int frequencies_two[] = {300,600,900,1200,1500,2100,2400,2700,3000 };

  for (int j = 0; j <= 10 ; j++) {
    tone(BUZZER, frequencies_two[j], 100); // Play each frequency for 100 milliseconds
    delay(50); // Add a small delay between tones for a more realistic sound
  }
  noTone(BUZZER); // Stop the buzzer after playing the sound
  delay(500); // Add a pause between each play for a more natural feel

}

void main_led_blink(){
  for(int last_led_blink = 0 ; last_led_blink<= 3 ; last_led_blink++ )
  {
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    delay(200);  // Pause for 200 milliseconds

    // Fill the entire strip with another color (skyBlue in this case)
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(100);  // Pause for 200 milliseconds

  }

}


void circuit_diagram(){
  Serial.println(" Arduino nano |");
  Serial.println("-------------------------------------------------------------------");
  Serial.println(" Ws2812-B     | GND | 5V | D2");
  Serial.println("-------------------------------------------------------------------");
  Serial.println(" Buzzer       | GND | D3");
  Serial.println("-------------------------------------------------------------------");
  Serial.println(" MPU6050      | 5V | GND | SCL | SDA ");
  Serial.println("-------------------------------------------------------------------");
  Serial.println(" Switch       | 5V | GND | D6 |D7 ");
  Serial.println("-------------------------------------------------------------------");
  Serial.println(" Led          | GND | D8 | D9");
  Serial.println("-------------------------------------------------------------------");
  Serial.println(" So here a circuit diagram : ");
}

void setup(){
    Serial.begin(9600); //define the bud rate
    
    // DEFINE THE PIN_MODE OF YOUR INPUT/OUTPUT DEVICES 
    pinMode(BUZZER , OUTPUT);
    // define the fast led stripe 
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    // define the servo pinOut
    FIRST_SERVO_MOTOR.attach(First_Servo_Pin_Number);
    SECOND_SERVO_MOTOR.attach(Second_Servo_Pin_Number);

    // define the switch and led 
    pinMode(first_switch , INPUT);
    pinMode(second_switch , INPUT);
    pinMode(first_led , OUTPUT);
    pinMode(second_led , OUTPUT);

    // define the mpu6050 
    Wire.begin();
  
    // start code : 
    // DEFINE THE FIRST TURN ON FLIGHT COMPUTER 
    FIRST_SERVO_MOTOR.write(First_Servo_Position_first); //first servo position is 120 degree 
    SECOND_SERVO_MOTOR.write(Second_Servo_Position_first); //second servo position is 90 degree 
    circuit_diagram();
    delay(1000); //delay for 1 second 
    flight_computer_on_beep();
    led_indicate();
    servo_check();
    MPU6050_INIT();
    Calibrate_MPU6050();
    buzzer_main_program_start();
    main_led_blink();
    Serial.println(" Your Flight Computer is Now Ready ! ");

    
}

// define the tone for first channel 
// autopilot mode will start here 

void PlayActiveTone_First(){
    int tone_frequencies[] = { 200 , 400 ,600, 800 , 1000 , 1200 , 1400 , 1600 , 1800 , 2000 };
    for(int tone_value = 0 ; tone_value <= 10 ; tone_value++){
        tone(BUZZER , tone_frequencies[tone_value] , 100);
        delay(100);
    }

    int tone_frequency_second [] = {300 , 600 , 900 , 1200  , 1500 , 1800 , 2100 , 2400 , 2700 , 3000};
    for( int tone_value_second = 0; tone_value_second <= 10 ; tone_value_second++){
      tone(BUZZER , tone_frequency_second[tone_value_second] , 100);
      delay(100);
    }
    for(int high_tone = 0; high_tone <= 2 ; high_tone++)
    {
    digitalWrite(BUZZER , HIGH);
    delay(300); //delay for 300 millisecond 
    digitalWrite(BUZZER , LOW);
    delay(300); //delay for 300 millisecond

    }
    
}

// define the autopilot tune 


void servo_check_autopilot_Mode_First(){

    // first is normal mode 
    
    for(int Autopilot_Start_Count = 0; Autopilot_Start_Count <= 5; Autopilot_Start_Count++)
    {
    // define the first servo motor move from 120 degree to 140 degree
    for(int First_Move_a = 120 ; First_Move_a<= 140 ; First_Move_a++){
        FIRST_SERVO_MOTOR.write(First_Move_a);delay(15);
    }
    
    // define the second servo motor move from 90 degree to 105 degree 
    for(int Second_Move_b = 90 ; Second_Move_b<= 105 ; Second_Move_b++){
        SECOND_SERVO_MOTOR.write(Second_Move_b); delay(15);
    }

    // define the first servo motor move from 140 degree back to  120 degree 
    for(int Third_Move_c = 140 ; Third_Move_c >=120 ; Third_Move_c--){
        FIRST_SERVO_MOTOR.write(Third_Move_c);delay(15);
    }

    // define the second servo motor move from 105 degree back to 90 degree 
    for(int Four_Move_d = 105 ; Four_Move_d>=90 ; Four_Move_d--){
        SECOND_SERVO_MOTOR.write(Four_Move_d); delay(15);
    }

    // define the first motor move from 120  back to 100 degree 
    for(int Five_Move_e = 120 ; Five_Move_e >=100 ; Five_Move_e--){
        FIRST_SERVO_MOTOR.write(Five_Move_e);delay(15);
    }

    // define the second servo motor move from 
    for(int Six_Move_f = 90 ; Six_Move_f >=80 ; Six_Move_f--){
        SECOND_SERVO_MOTOR.write(Six_Move_f); delay(15);
    }

// define the first servo motor move from 100 degree to 120 degree 
    for(int Seven_Move_g = 100 ; Seven_Move_g <=120 ; Seven_Move_g++){
        FIRST_SERVO_MOTOR.write(Seven_Move_g);delay(15);
    }

    // define the second servo motor move from 80 degree to 90 degree
    for(int Eight_Move_h = 80 ; Eight_Move_h <=90 ; Eight_Move_h++){
        SECOND_SERVO_MOTOR.write(Eight_Move_h); delay(15);
    }
    }
    
}

void servo_check_autopilot_Mode_Second(){
  for(int Autopilot_Start_Count_Second = 0 ;Autopilot_Start_Count_Second <= 5 ; Autopilot_Start_Count_Second++ ){
  FIRST_SERVO_MOTOR.write(120);delay(400); //delay for 1 second means 1000 millisecond
  SECOND_SERVO_MOTOR.write(90);delay(400); //delay for 1 second means 1000 millisecond 

  FIRST_SERVO_MOTOR.write(140);delay(400); //delay for 1 second means 1000 millisecond 
  SECOND_SERVO_MOTOR.write(105);delay(400); //delay for 1 second means 1000 millisecond 

  FIRST_SERVO_MOTOR.write(120);delay(400); //delay for 1 second means 1000 millisecond 
  SECOND_SERVO_MOTOR.write(90);delay(400); //delay for 1 second means 1000 millisecond 

  FIRST_SERVO_MOTOR.write(100);delay(400); //delay for 1 second means 1000 millisecond 
  SECOND_SERVO_MOTOR.write(80);delay(400); //delay for 1 second means 1000 millisecond 

  FIRST_SERVO_MOTOR.write(120);delay(400); //delay for 1 second means 1000 millisecond
  SECOND_SERVO_MOTOR.write(90);delay(400); //delay for 1 second means 1000 millisecond 
  }
  
}


void servo_check_autopilot_Mode_Third(){

    // first is normal mode 
    
    for(int Autopilot_Start_Count_third = 0; Autopilot_Start_Count_third <= 40; Autopilot_Start_Count_third++)
    {
    // define the first servo motor move from 120 degree to 140 degree
    for(int First_Move_a = 120 ; First_Move_a<= 140 ; First_Move_a++){
        FIRST_SERVO_MOTOR.write(First_Move_a);delay(5);
    }
    
    // define the second servo motor move from 90 degree to 105 degree 
    for(int Second_Move_b = 90 ; Second_Move_b<= 105 ; Second_Move_b++){
        SECOND_SERVO_MOTOR.write(Second_Move_b); delay(5);
    }

    // define the first servo motor move from 140 degree back to  120 degree 
    for(int Third_Move_c = 140 ; Third_Move_c >=120 ; Third_Move_c--){
        FIRST_SERVO_MOTOR.write(Third_Move_c);delay(5);
    }

    // define the second servo motor move from 105 degree back to 90 degree 
    for(int Four_Move_d = 105 ; Four_Move_d>=90 ; Four_Move_d--){
        SECOND_SERVO_MOTOR.write(Four_Move_d); delay(5);
    }

    // define the first motor move from 120  back to 100 degree 
    for(int Five_Move_e = 120 ; Five_Move_e >=100 ; Five_Move_e--){
        FIRST_SERVO_MOTOR.write(Five_Move_e);delay(5);
    }

    // define the second servo motor move from 
    for(int Six_Move_f = 90 ; Six_Move_f >=80 ; Six_Move_f--){
        SECOND_SERVO_MOTOR.write(Six_Move_f); delay(5);
    }

// define the first servo motor move from 100 degree to 120 degree 
    for(int Seven_Move_g = 100 ; Seven_Move_g <=120 ; Seven_Move_g++){
        FIRST_SERVO_MOTOR.write(Seven_Move_g);delay(5);
    }

    // define the second servo motor move from 80 degree to 90 degree
    for(int Eight_Move_h = 80 ; Eight_Move_h <=90 ; Eight_Move_h++){
        SECOND_SERVO_MOTOR.write(Eight_Move_h); delay(5);
    }
    }
    
}

void led_glow_stripe(){
  // in this led stripe they have three mode
  for(int led_fast_glow = 0; led_fast_glow <= 10 ; led_fast_glow++ ){
    // Fill the entire strip with a color (red in this case)
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(100);  // Pause for 500 milliseconds

  // Fill the entire strip with another color (green in this case)
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(100);  // Pause for 500 milliseconds

  // Fill the entire strip with another color (blue in this case )
  fill_solid(leds , NUM_LEDS , CRGB::Blue);
  FastLED.show();
  delay(100);

  }
   fill_solid(leds , NUM_LEDS , CRGB::Black);
  FastLED.show();
  delay(100);
}

void loop(){

  
 ButtonState = digitalRead(first_switch); //its a first switch

    if(ButtonState != LastButtonState)
    {
        if(ButtonState == HIGH)
        {
            ButtonPressCount++;
            Serial.println("Button Pressed ! ");

            if(ButtonPressCount == 3){
                Serial.println("Button pressed three times , LED is ON! ");
                Serial.println("Autopilot mode on ");
                digitalWrite(first_led , HIGH);
                PlayActiveTone_First();
                led_glow_stripe();
                servo_check_autopilot_Mode_First();
                servo_check_autopilot_Mode_Second();
                servo_check_autopilot_Mode_Third();
                PlayActiveTone_First();
            }

            if (ButtonPressCount >= 3)
            {
                Serial.println("Button pressed again , LED is OFF !");
                Serial.println("Autopilot mode Off");
                digitalWrite(first_led , LOW);
                ButtonPressCount = 0;
            }
            
        }
    }
    LastButtonState = ButtonState;
    delay(50);
  

}
