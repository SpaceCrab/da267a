#include<esp_task_wdt.h>
#include "driver/gpio.h"

#define BUTTON_PIN 12
#define ESP_INTR_FLAG_DEFAULT 0
#define PUSH_TIME_US 100000

static volatile int counter = 0;
static volatile uint64_t lastPush = -PUSH_TIME_US;

static void ISR_handler(void *arg)
{
    uint64_t now = esp_timer_get_time();

    if((now -lastPush) > PUSH_TIME_US)
    {
        lastPush = now;
        counter ++;
    }
}

static void waitMs(unsigned int millis)
{
    TickType_t delay = millis /portTICK_PERIOD_MS;
    vTaskDelay(delay);
}

void app_main() 
{
    gpio_config_t config;
    config.pin_bit_mask = (uint64_t) 1<<BUTTON_PIN;
    config.mode = GPIO_MODE_DEF_INPUT;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.pull_up_en = GPIO_PULLUP_ENABLE;
    config.intr_type = GPIO_INTR_NEGEDGE;

    esp_err_t res = gpio_config(&config);
    if(res != ESP_OK)
    {
        printf("cannot init pin %s\n", esp_err_to_name(res));
    }

    res = gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    if(res != ESP_OK)
    {
        printf("cannot init interrupts %s\n", esp_err_to_name(res));
    }

    res = gpio_isr_handler_add(BUTTON_PIN, ISR_handler, NULL);


    if(res != ESP_OK)
    {
        printf("cannot init interrupts %s\n", esp_err_to_name(res));
    }

    while(1)
    {
        printf("counter is %d\n", counter);
        printf("busy waiting .......");
        waitMs(100);
        printf("done waiting\n");
    }

}
