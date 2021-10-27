#include <driver/i2c.h>
#include <stdio.h>
#include <driver/gpio.h>

#include "esp_pm.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "i2cUtility.h"
#include "I2CUtil.h"
#include "accelerometer.h"
#include "circular_buffer.h"

//sampling fq 10hz chosen because the fq of running is 3hz and he nyquist fq is 6hz
//10 was just a nice number 

#define TASK_PRIORITY 20
#define SAMPLING_PERIOD 100
#define BUFF_SIZE 10

struct circularBuffer buff;

static void sampling_task(void*arg)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    int16_t valx = 0;
    int16_t valy = 0;
    int16_t valz = 0;

    accelInit();

    while(1)
    {
        valx = accelReadX(); 
        printf("xval %d, ",valx);
        valy = accelReadY(); 
        printf("yval %d, ",valy);
        valz = accelReadZ(); 
        printf("zval %d\n",valz);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(SAMPLING_PERIOD));
    }
}

void app_main() {

    int *data = (int*)malloc(BUFF_SIZE * sizeof(int));
    initCircularBuffer( &buff,data,BUFF_SIZE, 0 );

    esp_pm_config_esp32_t conf = {
        .light_sleep_enable =   1,
        .max_freq_mhz =         80,
        .min_freq_mhz =         20
    };
	ESP_ERROR_CHECK(esp_pm_configure(&conf));

    xTaskCreate(sampling_task, "sampling", 2048, NULL, TASK_PRIORITY, NULL);
}
