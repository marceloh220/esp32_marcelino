#ifndef _OLED_H_
#define _OLED_H_

#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"

#include "map.h"
#include "driver/i2c.h"
#include "esp_lcd_panel_io.h"

void oled_init() {
    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER, // I2C LCD is a master node
        .sda_io_num = SDA_OLED,
        .scl_io_num = SCL_OLED,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100E3,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_1, &i2c_conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_1, I2C_MODE_MASTER, 0, 0, 0));

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = OLED_ADDR,
        .control_phase_bytes = 1, // refer to LCD spec
        .dc_bit_offset = 6,       // refer to LCD spec
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)1, &io_config, &io_handle));
}

#endif
