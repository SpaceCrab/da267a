#include <stdio.h>
#include "pins.h"
#include "driver/gpio.h"
#include <esp_task_wdt.h>
#include <esp32/rom/ets_sys.h>

void waitMS(unsigned int ms)
{
	TickType_t delay = (ms / portTick_PERIOD_MS);
	vTaskDelay(delay);
}

void app_main()
{
	initPins();

	while (1)
	{
		setLEDA(1);
		setLEDB(0);
		waitMS(500);
		setLEDA(0);
		setLEDB(1);
		waitMS(500);

	//	if(isButtonAPressed())
	//	{
	//		setLEDA(1);
	//		setLEDB(0);
	//	}
	//	else if (isButtonBPressed())
	//	{
	//		setLEDA(0);
	//		setLEDB(1);
	//	}
	//	else
	//	{
	//		setLEDA(1);
	//		setLEDB(0);
	//		waitMS(500);
	//		setLEDA(0);
	//		setLEDB(1);
	//		waitMS(500);
	//	}
	}
}
 

