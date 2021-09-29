#include "pins.h"
#include "driver/gpio.h"

#define LED_A  13

void initPins()
{

	//Initializing the pins 12 and 14 for the LEDs
	gpio_config_t config;
	config.pin_bit_mask = (u_int64_t)1 << LED_A;
	config.mode = GPIO_MODE_OUTPUT;
	config.pull_down_en = 0;
	config.pull_up_en = 0;

	gpio_config(&config);

}

//sets the A led to the value level
void setLEDA(uint8_t level)
{
	gpio_set_level(LED_A, level);
}

