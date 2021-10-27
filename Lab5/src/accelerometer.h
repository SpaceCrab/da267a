#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <stdint.h>
#include <driver/i2c.h>

void accelInit();

void accelWrite();

int16_t accelReadX();

int16_t accelReadY();

int16_t accelReadZ();

#endif
