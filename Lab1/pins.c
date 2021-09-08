#include "pins.h"
#include "driver/gpio.h"

#define LED_A  12
#define LED_B  14

#define BTN_A  26
#define BTN_B  27


void initPins()
{

	gpio_config_t config;
	config.pin_bit_mask = (u_int64_t)1 << LED_A;
	config.pin_bit_mask |= (u_int64_t)1 << LED_B;
	config.mode = GPIO_MODE_OUTPUT;
	config.pull_down_en = 0;
	config.pull_up_en = 0;

	gpio_config(&config);

//	config.pin_bit_mask = (u_int64_t)1 << BTN_A;
//	config.pin_bit_mask |= (u_int64_t)1 << BTN_B;
//	config.mode = GPIO_MODE_INPUT;
//	config.pull_down_en = 0;
//	config.pull_up_en = 1;

//	gpio_config(&config);
}

void setLEDA(uint8_t level)
{
	level = level%1
	gpio_set_level(LED_A, level);
}

void setLEDB(uint8_t level)
{
	level = level%1
	gpio_set_level(LED_B, level);
}

uint8_t isButtonAPressed()
{
	return !gpio_get_level(BTN_A);
}

uint8_t isButtonBPressed()
{
	return !gpio_get_level(BTN_B);
}
