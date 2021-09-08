#include "esp_system.h"

int getRandomRange(int min, int max)
{
	int random = esp_random() % max;

	if(random > min)
	{
		return random;
	}
	else
	{
		return min;
	}
}
