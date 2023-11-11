#ifndef _OUTPUT_HPP_
#define _OUTPUT_HPP_

#include "esp_rom_gpio.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"

#include "map.h"

class Output {
public:
    Output(uint32_t pin) : pin(pin) {
        esp_rom_gpio_pad_select_gpio(pin);
        gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT);
    }

    ~Output() {
        gpio_reset_pin((gpio_num_t)pin);
    }

    inline int read() {
        return state;
    }

    inline void write(bool level) {
        this->state = level;
        gpio_set_level((gpio_num_t)pin, level);
    }

    void toggle(int level) {
        if(level) {
            state ^= 1;
            write(state);
        }
    }

    Output &operator=(Output &v) {
        this->write(v.read());
        return *this;
    }

    Output &operator=(int v) {
        this->write(v);
        return *this;
    }

    Output &operator^=(int v) {
        this->toggle(v);
        return *this;
    }

    [[nodiscard]] operator int() { return read(); }

protected:
    const uint32_t pin;
    bool state = 0;
};

#endif
