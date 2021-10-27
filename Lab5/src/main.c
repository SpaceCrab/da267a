#include <driver/i2c.h>
#include <stdio.h>
#include "i2cUtility.h"
#include "I2CUtil.h"
#include "accelerometer.h"


void app_main() {
    int16_t val = 0; 
       printf("val %d, \n",val);
    accelInit();
    while (1) {
       val = accelReadX(); 
       printf("xval %d, ",val);
       val = accelReadY(); 
       printf("yval %d, ",val);
       val = accelReadZ(); 
       printf("zval %d\n",val);


       vTaskDelay(pdMS_TO_TICKS(250));
    }
}
