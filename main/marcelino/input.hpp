#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "esp_rom_gpio.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "map.h"

typedef enum INPUT_MODE_e {
    floating,
    pullup,
    pulldown,
} INPUT_MODE_t;

class Input {
public:

    Input(uint32_t pin, INPUT_MODE_t mode = pulldown) : pin(pin), mode(mode) {
        esp_rom_gpio_pad_select_gpio(pin);
        gpio_set_direction((gpio_num_t)pin, GPIO_MODE_INPUT);
        if(mode == pullup) {
            gpio_pullup_en((gpio_num_t)pin);
        }
        else if(mode == pulldown) {
            gpio_pulldown_en((gpio_num_t)pin);
        }
    }

    ~Input() {
        gpio_reset_pin((gpio_num_t)pin);
    }

    [[nodiscard]] virtual int read() {
        int state = gpio_get_level((gpio_num_t)pin);
        return mode == pullup ? !state : state;
    }

    [[nodiscard]] operator int() { return read(); }

protected:
    const uint32_t pin;
    const INPUT_MODE_t mode;
};

#endif
