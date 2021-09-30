#include <SoundGen.h>
#include <driver/dac.h>
#include <driver/gpio.h>

int startSound(int freq)
{
    dac_cw_config_t conf;
    conf.freq = freq;
    conf.offset = 1;
    conf.phase = DAC_CW_PHASE_0;
    conf.scale = DAC_CW_SCALE_1;
    conf.en_ch = DAC_CHANNEL_1;

    esp_err_t err = dac_cw_generator_config(&conf);
    if(err == ESP_OK)
    {
        printf("config OK \n");
        err = dac_cw_generator_enable();
        if(err == ESP_OK)
        {
            dac_output_enable(DAC_CHANNEL_1);
        }
    }

    return (freq/130)*130;
}

void stopSound()
{
    ESP_ERROR_CHECK(dac_cw_generator_disable());
}
