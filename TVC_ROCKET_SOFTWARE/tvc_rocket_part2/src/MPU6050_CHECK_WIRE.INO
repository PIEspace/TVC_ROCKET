#include <Wire.h>
#include<Arduino.h>

const int MPU6050_addr = 0x68; // I2C address of the MPU6050

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  MPU6050_Init();
}

void loop() {
  Read_MPU6050();
  Serial.print("Accelerometer: ");
  Serial.print("X = ");
  Serial.print(accelerometer_x);
  Serial.print(" | Y = ");
  Serial.print(accelerometer_y);
  Serial.print(" | Z = ");
  Serial.println(accelerometer_z);

  Serial.print("Gyroscope: ");
  Serial.print("X = ");
  Serial.print(gyro_x);
  Serial.print(" | Y = ");
  Serial.print(gyro_y);
  Serial.print(" | Z = ");
  Serial.println(gyro_z);

  delay(1000);
}

void MPU6050_Init() {
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void Read_MPU6050() {
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 14, true); // request a total of 14 registers

  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();
  accelerometer_z = Wire.read() << 8 | Wire.read();

  gyro_x = Wire.read() << 8 | Wire.read();
  gyro_y = Wire.read() << 8 | Wire.read();
  gyro_z = Wire.read() << 8 | Wire.read();
}
