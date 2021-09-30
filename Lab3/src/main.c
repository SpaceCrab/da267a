#include <stdio.h>
#include <stdlib.h>

#include <driver/adc.h>
#include <esp32/rom/ets_sys.h>
#include <esp_task_wdt.h>

#include "pins.h"
#include "SoundGen.h"
#include "sampler.h"
#include "random.h"

void blinkLED(int ms, int times)
{
    for (int i = 0; i < times; i++)
    {
        setLEDA(1); 
        vTaskDelay(pdMS_TO_TICKS(ms));
        setLEDA(0);
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
}

float absval(float a)
{
    return a > 0 ? a :-a;
}

void app_main() 
{
    initPins();
    while(1)
    {
        printf("starting game!!! \n");

        blinkLED(50,20);

        int randFq = getRandomRange(200, 700);
        int actualFq = startSound(randFq);

        vTaskDelay(pdMS_TO_TICKS(3000));
        stopSound();
        startSampling(4000);
        vTaskDelay(pdMS_TO_TICKS(1000));
        stopSampling();

        float playerFq = getFreq();

        printf("player fq = %.2f target fq = %d\n", playerFq, actualFq);

        if(absval(playerFq - (float)actualFq) < 50)
        {
            printf("------player wins------\n");
            blinkLED(100,20);
        }
        else
        {
            printf("------player looses------\n");
            blinkLED(1000, 2);
        }

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

