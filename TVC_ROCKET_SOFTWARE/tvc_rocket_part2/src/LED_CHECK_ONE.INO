

#include<Arduino.h>


const int buttonPin = 6; // Change this to the actual pin where your button is connected
const int ledPin = 9;   // Change this to the actual pin where your LED is connected

int buttonState = LOW;
int lastButtonState = LOW;
int buttonPressCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPressCount++;
      Serial.println("Button pressed!");

      if (buttonPressCount == 3) {
        Serial.println("Button pressed three times. LED is ON!");
        digitalWrite(ledPin, HIGH);
      }

      if ( buttonPressCount > 4) {
        Serial.println("Button pressed again , LED is OFF !");
        digitalWrite(ledPin , LOW);
        buttonPressCount = 0;
      
      }
    }
  }

  lastButtonState = buttonState;

  delay(50); // Debounce delay
}
