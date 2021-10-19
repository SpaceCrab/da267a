#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <stdint.h>
#include <driver/i2c.h>

void accelInit();

void i2cWrite();

void i2cRead();

#endif
