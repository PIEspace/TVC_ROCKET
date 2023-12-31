#include <Wire.h>
#include <Servo.h>
#include<Arduino.h>

const int MPU6050_addr = 0x68; // I2C address of the MPU6050

int16_t gyro_x;
long gyro_integration = 0;

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  servoMotor.attach(4); // Servo signal pin is connected to digital pin 9
  MPU6050_Init();
}

void loop() {
  Read_MPU6050();

  // Integrate gyro data over time to get an estimation of the angle
  gyro_integration += gyro_x;

  // Map the integrated angle value to the servo range (adjust as needed)
  int servoPosition = map(gyro_integration, -10 , 10 , 120, 140);
  servoPosition = constrain(servoPosition, 120, 140);

  // Move the servo motor to the calculated position
  servoMotor.write(servoPosition);

  // Print gyro value and servo position to the serial monitor
  Serial.print("Gyro X: ");
  Serial.print(gyro_x);
  Serial.print(" | Integrated Angle: ");
  Serial.print(gyro_integration / 1000.0); // Convert back to degrees
  Serial.print(" | Servo Position: ");
  Serial.println(servoPosition);

  delay(100); // Adjust the delay as needed
}

void MPU6050_Init() {
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void Read_MPU6050() {
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x43); // starting with register 0x43 (GYRO_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 2, true); // request 2 registers for gyro data

  gyro_x = Wire.read() << 8 | Wire.read();
}
