#include <Wire.h>
#include<Arduino.h>

const int MPU6050_addr = 0x68; // I2C address of the MPU6050

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;

int16_t accel_x_offset, accel_y_offset, accel_z_offset;
int16_t gyro_x_offset, gyro_y_offset, gyro_z_offset;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  MPU6050_Init();
  Calibrate_MPU6050();
}

void loop() {
  Read_MPU6050();
  
  // Apply calibration offsets
  accelerometer_x -= accel_x_offset;
  accelerometer_y -= accel_y_offset;
  accelerometer_z -= accel_z_offset;

  gyro_x -= gyro_x_offset;
  gyro_y -= gyro_y_offset;
  gyro_z -= gyro_z_offset;

  // Your code here using calibrated data

  delay(1000);
}

void MPU6050_Init() {
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void Calibrate_MPU6050() {
  // Collect data for calibration
  int numSamples = 1000;

  for (int i = 0; i < numSamples; i++) {
    Read_MPU6050();
    accel_x_offset += accelerometer_x;
    accel_y_offset += accelerometer_y;
    accel_z_offset += accelerometer_z;
    gyro_x_offset += gyro_x;
    gyro_y_offset += gyro_y;
    gyro_z_offset += gyro_z;
    delay(5);
  }

  // Calculate average offsets
  accel_x_offset /= numSamples;
  accel_y_offset /= numSamples;
  accel_z_offset /= numSamples;
  gyro_x_offset /= numSamples;
  gyro_y_offset /= numSamples;
  gyro_z_offset /= numSamples;

  // Print calibration offsets
  Serial.println("Calibration Offsets:");
  Serial.print("Accel X: "); Serial.println(accel_x_offset);
  Serial.print("Accel Y: "); Serial.println(accel_y_offset);
  Serial.print("Accel Z: "); Serial.println(accel_z_offset);
  Serial.print("Gyro X: "); Serial.println(gyro_x_offset);
  Serial.print("Gyro Y: "); Serial.println(gyro_y_offset);
  Serial.print("Gyro Z: "); Serial.println(gyro_z_offset);
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
