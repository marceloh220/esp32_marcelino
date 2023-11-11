#ifndef _BUTTOM_HPP_
#define _BUTTOM_HPP_

#include "freertos/projdefs.h"
#include "input.hpp"

#include "chrono.hpp"

class Button : public Input {

public:

    Button(uint32_t pin, milliseconds debounce, INPUT_MODE_t mode = pulldown) :
    Input(pin, mode), _debounce(debounce) {

    }

    ~Button() {
        gpio_reset_pin((gpio_num_t)pin);
    }

    [[nodiscard]] int read() {
        int state = _read();
        if (state && !_lock) {
            _lock = true;
            return true;
        } else if(!state && _lock) {
            delay(_debounce);
            if(!_read()) {
                _lock = false;
            }
        }
        return false;
    }

private:
    bool _lock = false;
    milliseconds _debounce;

    [[nodiscard]] int _read() {
        int state = gpio_get_level((gpio_num_t)pin);
        return mode == pullup ? !state : state;
    }

};

#endif
