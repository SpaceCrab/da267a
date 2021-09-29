#include <stdio.h>
#include <stdlib.h>

#include <driver/adc.h>
#include <esp32/rom/ets_sys.h>
#include <esp_task.h>

#include <SoundGen.h>

void app_main() 
{
    int freq = 390;
    startSound(freq);
    while(1)
    {
    }
}

