#include <driver/i2c.h>
#include <math.h>
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

#define COUNTING_PRIORITY 10
#define SAMPLING_PRIORITY 20
#define SAMPLING_PERIOD 100
#define COUNTING_PERIOD 500
#define BUFF_SIZE 30
#define MININUM_SD 10
#define MIN_INTR_STEP_TIME 250
#define K 1.5

struct circularBuffer buff;
int steps = 0;

static void counting_task(void*arg){
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        int length = buff.length;
        if (length == 0) continue;

        int head = buff.head;
        int mean = 0;
        for(int i = 0; i < length; i++)
        {
            mean = mean + buff.data[head];
            head = (head + 1) % buff.maxLength;
        }
        mean = mean / length;
        int sum = 0;
        head = buff.head;
        for(int i = 0; i < length; i++)
        {
            sum = sum + (buff.data[head] - mean) * (buff.data[head] - mean);
            head = (head + 1) % buff.maxLength;
        }
        int sd = sqrtf(sum / length);
        if (sd < MININUM_SD) sd = MININUM_SD;
        int lastStep = -MIN_INTR_STEP_TIME;
        int curStep  = 0;
        for (int i = 0; i < length; i++) {
            int value  = removeHead(&buff);
            curStep = i * MIN_INTR_STEP_TIME;
            if (value > ((double)sd * K + mean) && curStep - lastStep > MIN_INTR_STEP_TIME) {
                steps++;
                lastStep = curStep;
            }
        }
        printf("steps: %d, mean: %d, sd: %d, mean + sd: %d, size: %d\n", steps, mean, sd, mean + sd, length);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(COUNTING_PERIOD));
    }
   
}

static void sampling_task(void*arg)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    int16_t valx = 0;
    int16_t valy = 0;
    int16_t valz = 0;

    accelInit();

    while(1)
    {
        //get values from accelerometer and convert them into floating point 
        valx = accelReadX(); 
        valy = accelReadY(); 
        valz = accelReadZ(); 
        float xf = (float)valx;
        float yf = (float)valy;
        float zf = (float)valz;
        
        // calculate the magnitude of the values 
        float magnitude = sqrtf((xf * xf) + (yf * yf) + (zf * zf));

        //store the magnitude values in the buffer 
        addElement(&buff, (uint32_t)magnitude);
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

    xTaskCreate(sampling_task, "sampling", 2048, NULL, SAMPLING_PRIORITY, NULL);
    xTaskCreate(counting_task, "counting", 2048, NULL, COUNTING_PRIORITY, NULL);
}
