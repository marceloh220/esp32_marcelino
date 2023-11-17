#ifndef _OLED_H_
#define _OLED_H_

#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"

#include "map.h"

#include "esp_lcd_panel_vendor.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"

class Oled {

public:

    Oled() {

    }

    ~Oled() {
        ssd1306_delete(_device);
    }

    void begin() {

        i2c_config_t conf_master = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = SDA_OLED,
            .scl_io_num = SCL_OLED,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
        };

        conf_master.master.clk_speed = 400000;
        conf_master.clk_flags = 0;

        esp_err_t ret = i2c_param_config(I2C_NUM_0, &conf_master);
        ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

        ret = i2c_driver_install(I2C_NUM_0, conf_master.mode, 0, 0, 0);
        ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

        _device = ssd1306_create(I2C_NUM_0, SSD1306_I2C_ADDRESS);

        if(_device == NULL) {
            ESP_LOGE("oled.h", "Create device fail.");
            return;
        }

        ret = ssd1306_refresh_gram(_device);
        ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

        ssd1306_clear_screen(_device, 0xFF);

        ssd1306_draw_string(_device, 0, 52, (const uint8_t *)"MUSIC", 12, 0);
        ssd1306_refresh_gram(_device);

    }

    void printf() {

    }



private:

    ssd1306_handle_t _device = NULL;

};

#endif
