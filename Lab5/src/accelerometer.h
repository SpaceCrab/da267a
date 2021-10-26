#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <stdint.h>
#include <driver/i2c.h>

void accelInit();

void i2cWrite();

float i2cRead();

#endif
