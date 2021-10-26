
#ifndef i2cUtility_H
#define i2cUtility_H

#include <stdint.h>

/*
 * Initialises I2C bus, uses controller 0
 */
void initI2C(int sdapin, int sclpin);

/*
 * Writes one byte into a register
 */
void writeI2C(uint8_t adress, uint8_t reg, uint8_t data);

/*
 * Reads len bytes and places them into a buffer, buffer must be pre  allocated
 */
void readI2C(uint8_t adress, uint8_t reg, uint8_t *buffer, int len);

#endif
