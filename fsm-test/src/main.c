#include "pins.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include <esp_task_wdt.h>
#include <esp32/rom/ets_sys.h>
//states 
//  moving 
//  idle 
//  loading 
//  unloading 
//
//events
//  push button on lower 
//  push external button on upper
//  done loading
//  done unloading
//  arrive to floor 
#define MOVING_STATE 1
#define IDLE_STATE   2
#define BTN_PRESS_EVENT 0
#define BTN_RELEASE_EVENT 1

int idle(int val)
{
    printf("state = idle\n");
    if(val == BTN_PRESS_EVENT)
        return MOVING_STATE;
    return IDLE_STATE;
}

int moving(int val)
{
    printf("state = moving\n");
    if(val == BTN_RELEASE_EVENT)
        return IDLE_STATE;
    return MOVING_STATE;
}

int pollEvent()
{
    if(isButtonAPressed())
        return BTN_PRESS_EVENT;
    else return BTN_RELEASE_EVENT;
}

void sleep_ms(uint32_t ms)
{
    TickType_t delay = ms / portTICK_PERIOD_MS;
    vTaskDelay(delay);
}

void app_main()
{
    initPins();
    int (*stateTable[])(int) = {idle, moving};
    int (*funcPtr)(int);

    funcPtr = idle;
    int event = 0;
    int nextState;

    while(1)
    {
        nextState = funcPtr(event);
        funcPtr = stateTable[nextState -1];
        event = pollEvent();
        sleep_ms(200);
    }
}
