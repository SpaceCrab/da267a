#include <stdint.h>
#include <driver/i2c.h>
#include "i2cUtility.h"
#include "I2CUtil.h"
#include "accelerometer.h"

#define MPU6050_PWR_MGMT_1   0x6B  // Power Management 1
#define MPU6050_SMPLRT_DIV   0x19  // Sample Rate Divider
#define MPU6050_GYRO_CONFIG  0x1B  // Gyroscope Configuration
#define MPU6050_ACCEL_CONFIG 0x1C  // Accelerometer Configuration
#define MPU6050_FIFO_EN      0x23  // FIFO Enable
#define MPU6050_INT_PIN_CFG  0x37  // INT Pin / Bypass Enable Configuration
#define MPU6050_INT_ENABLE   0x38  // Interrupt Enable
#define MPU6050_INT_STATUS   0x3A  // Interrupt Status

#define MPU6050_ACCEL_XOUT_H 0x3B  // Accelerometer Measurement X-axis register
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D  // Accelerometer Measurement Y-axis register
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F  // Accelerometer Measurement Z-axis register
#define MPU6050_ACCEL_ZOUT_L 0x40
#define MPU6050_TEMP_OUT_H   0x41
#define MPU6050_TEMP_OUT_L   0x42
#define MPU6050_GYRO_XOUT_H  0x43
#define MPU6050_GYRO_XOUT_L  0x44
#define MPU6050_GYRO_YOUT_H  0x45
#define MPU6050_GYRO_YOUT_L  0x46
#define MPU6050_GYRO_ZOUT_H  0x47
#define MPU6050_GYRO_ZOUT_L  0x48

#define MPU6050_FIFO_COUNT_H 0x72  // FIFO Count Registers
#define MPU6050_FIFO_COUNT_L 0x73

#define MPU6050_WHO_AM_I     0x75 
#define MPU6050_ADDR         0x68
#define SCL_PIN              32
#define SDA_PIN              33

void accelInit()
{
   initI2C(SDA_PIN, SCL_PIN);
   //uint8_t adress, uint8_t reg, uint8_t data
   //
   //Setting power Management to 1
   printf("about to write to MPU\n");
   writeI2C(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1);
   printf("about to write to MPU2\n");
   //configures the accelerometer
   writeI2C(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 1);
   printf("about to write to MPU3\n");
   //sets the the samplerate of the accelerometer to 32Hz
   writeI2C(MPU6050_ADDR, MPU6050_SMPLRT_DIV, 250);
}

void accelWrite()
{
}

int16_t accelReadX()
{
   uint8_t buffer = 0;
   int16_t raw;

    readI2C(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, &buffer, 1);
    raw = (int16_t)buffer << 8;

    readI2C(MPU6050_ADDR, MPU6050_ACCEL_XOUT_L, &buffer, 1);
    raw |= buffer;

    return raw; 
}

int16_t accelReadY()
{
    uint8_t buffer;
    int16_t raw;

    readI2C(MPU6050_ADDR, MPU6050_ACCEL_YOUT_H, &buffer, 1);
    raw = (int16_t)buffer << 8;

    readI2C(MPU6050_ADDR, MPU6050_ACCEL_YOUT_L, &buffer, 1);
    raw |= buffer;

    return raw; 
}

int16_t accelReadZ()
{
    uint8_t buffer;
    int16_t raw;

    readI2C(MPU6050_ADDR, MPU6050_ACCEL_ZOUT_H, &buffer, 1);
    raw = (int16_t)buffer << 8;

    readI2C(MPU6050_ADDR, MPU6050_ACCEL_ZOUT_L, &buffer, 1);
    raw |= buffer;

    return raw; 
}
