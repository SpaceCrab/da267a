#include <sampler.h>

#include <driver/adc.h>
#include <esp_timer.h>
#include <driver/gpio.h>
#include <soc/adc_channel.h>

#define TRIGGER_LVL 1050

esp_timer_handle_t timerHandle;
uint32_t lastSample = 0;
uint32_t counter;
uint64_t startTime;
uint64_t stopTime;

void callback(void *args)
{
    //TODO count "crossings" of the averageand calculate frequency 
    uint32_t sample = adc1_get_raw(ADC1_CHANNEL_4);
    //printf("%d\n", sample);

    if(lastSample < TRIGGER_LVL && sample > TRIGGER_LVL )
        counter++;
    else if(lastSample > TRIGGER_LVL && sample < TRIGGER_LVL)
        counter++;
    lastSample = sample;
}

void startSampling(int freq)
{
    //init adc
    lastSample = 0;
    counter = 0;
    adc_power_on();
    adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_4);
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);

    //init timer
    esp_timer_create_args_t timerArgs = {
        .arg = NULL,
        .callback = callback,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "timer",
        .skip_unhandled_events = 1
    };

    u_int64_t sampleFreq = (u_int64_t)(1000000. / ((double) freq));
    esp_err_t err = esp_timer_create(&timerArgs,&timerHandle);

    //start timer
    err = esp_timer_start_periodic(timerHandle, sampleFreq);
    startTime = esp_timer_get_time();
}

void stopSampling()
{
    esp_timer_stop(timerHandle);
    printf("amount of triggers %d\n", counter);
    stopTime = esp_timer_get_time();
}

float getFreq()
{
    return ((float)counter) / (2*(((float) stopTime) - ((float)startTime))/1000000.);
}
