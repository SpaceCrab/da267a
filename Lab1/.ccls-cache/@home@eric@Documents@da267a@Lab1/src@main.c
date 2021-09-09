#include "pins.h"
#include "random.h"
#include "driver/gpio.h"
#include <esp_task_wdt.h>
#include <esp32/rom/ets_sys.h>

uint32_t timeMs()
{
	return xTaskGetTickCount() * portTICK_PERIOD_MS;
}


void waitMS(unsigned int ms)
{
	TickType_t delay = (ms / portTICK_PERIOD_MS );
	vTaskDelay(delay);
}


void flashLeds(uint8_t led, int times, unsigned int delay)
{
	for(int i =0;i <= times; i++)
	{
		if(led == 0)
		{
			setLEDA(1);
			setLEDB(0);
		}
		else if(led == 1)
		{
			setLEDB(1);
			setLEDA(0);
		}
		else
		{
			setLEDA(1);
			setLEDB(1);
		}

		waitMS(delay);

		setLEDA(0);
		setLEDB(0);

		waitMS(delay);
	}
}

void startAnim()
{
	flashLeds(2, 5, 400);
}

void winnerAnim(uint8_t winner)
{
	flashLeds(winner, 5, 100);	
}


void app_main()
{
	initPins();


	while (1)
	{
		startAnim();

		setLEDA(0);
		setLEDB(0);

		int r = getRandomRange(1000, 5000);


		uint8_t winner =0;
		unsigned int startMS = timeMs();

		while(timeMs() - startMS < r)
		{

			if (isButtonBPressed())
			{
				winner = 1;
				break;
			}
			else if(isButtonAPressed())
			{
				winner =2;
				break;
			}
		}


		setLEDA(1);
		setLEDB(1);

		while(!winner)
		{
			
			if (isButtonBPressed())
			{
				winner = 2;
			}
			else if(isButtonAPressed())
			{
				winner =1;
			}

		}

		if(winner == 1) winnerAnim(0);
		else winnerAnim(1);
	}
}
 

