#ifndef PINS_H_
#define PINS_H_

#include <stdint.h>

//intializes the 4 pins
void initpins();

//switches state of LEDA
void setLEDA(uint8_t level);

//switches state of LEDB
void setLEDB(uint8_t level);

//true if button A is pressed
uint8_t isButtonAPressed();

//true if button B is pressed
uint8_t isButtonBPressed();

#endif
