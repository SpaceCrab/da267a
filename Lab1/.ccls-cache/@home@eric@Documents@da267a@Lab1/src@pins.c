#include "pins.h"
#include "driver/gpio.h"

#define LED_A  12
#define LED_B  14

#define BTN_A  26
#define BTN_B  27


void initPins()
{

	//Initializing the pins 12 and 14 for the LEDs
	gpio_config_t config;
	config.pin_bit_mask = (u_int64_t)1 << LED_A;
	config.pin_bit_mask |= (u_int64_t)1 << LED_B;
	config.mode = GPIO_MODE_OUTPUT;
	config.pull_down_en = 0;
	config.pull_up_en = 0;

	gpio_config(&config);

	//Initilazing pins 26 and 27 for the buttons
	config.pin_bit_mask = (u_int64_t)1 << BTN_A;
	config.pin_bit_mask |= (u_int64_t)1 << BTN_B;
	config.mode = GPIO_MODE_INPUT;
	config.pull_down_en = 0;
	config.pull_up_en = 1;

	gpio_config(&config);
}

//sets the A led to the value level
void setLEDA(uint8_t level)
{
	gpio_set_level(LED_A, level);
}

//sets the B led to the value level
void setLEDB(uint8_t level)
{
	gpio_set_level(LED_B, level);
}

//checks if the A button is pressed 
uint8_t isButtonAPressed()
{
	return !gpio_get_level(BTN_A);
}

//checks if the B button is pressed 
uint8_t isButtonBPressed()
{
	return !gpio_get_level(BTN_B);
}
