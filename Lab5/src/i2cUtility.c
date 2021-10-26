#include <stdint.h>
#include <driver/i2c.h>
#include "i2cUtility.h"

#define TIMEOUT_MS 1000
/*
 * Initialises I2C bus, uses controller 0
 */
void initI2C(int sdapin, int sclpin)
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = sdapin;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = sclpin;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    esp_err_t res = i2c_param_config(I2C_NUM_0,&conf);
    ESP_ERROR_CHECK(res);
    res = i2c_driver_install(I2C_NUM_0, conf.mode, 0,0,0);
    ESP_ERROR_CHECK(res);
}

/*
 * Writes one byte into a register
 */
void writeI2C(uint8_t adress, uint8_t reg, uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    //set adress + write and check for ack 
    res = i2c_master_write_byte(cmd, adress << 1 | I2C_MASTER_WRITE,1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_write_byte(cmd, reg,1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_write_byte(cmd, data,1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, TIMEOUT_MS/portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
}

/*
 * Reads len bytes and places them into a buffer, buffer must be pre  allocated
 */
void readI2C(uint8_t adress, uint8_t reg, uint8_t *buffer, int len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    //set adress + write and check for ack 
    res = i2c_master_write_byte(cmd, adress << 1 | I2C_MASTER_WRITE,1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_write_byte(cmd, reg,1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, TIMEOUT_MS/portTICK_RATE_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);

    res = i2c_master_start(cmd);
    cmd = i2c_cmd_link_create();

    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    //set adress + write and check for ack 
    res = i2c_master_write_byte(cmd, adress << 1 | I2C_MASTER_READ,1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_read(cmd, buffer, len, I2C_MASTER_NACK);
    ESP_ERROR_CHECK(res);

    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);

    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, TIMEOUT_MS/portTICK_RATE_MS);
    ESP_ERROR_CHECK(res);

    i2c_cmd_link_delete(cmd);

}
