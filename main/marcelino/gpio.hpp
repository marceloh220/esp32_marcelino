#ifndef _GPIO_HPP_
#define _GPIO_HPP_

#include "esp_intr_alloc.h"
#include "esp_rom_gpio.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"

#include "esp_attr.h"

class GPIO {

public:

    typedef enum state_e {
        LOW,
        HIGH,
    } state_t;

    typedef enum mode_e {
      INPUT = GPIO_MODE_INPUT,
      OUTPUT = GPIO_MODE_OUTPUT,
      INPUT_OUTPUT = GPIO_MODE_INPUT_OUTPUT,
      INPUT_PULLUP,
      INPUT_PULLDOWN,
    } mode_t;

    typedef enum interrupt_e {
        DISABLE      = GPIO_INTR_DISABLE,
        RISING_EDGE  = GPIO_INTR_POSEDGE,
        FALLING_EDGE = GPIO_INTR_NEGEDGE,
        ANY_EDGE     = GPIO_INTR_ANYEDGE,
        LOW_LEVEL    = GPIO_INTR_LOW_LEVEL,
        HIGH_LEVEL   = GPIO_INTR_HIGH_LEVEL,
    } interrupt_t;

    GPIO(gpio_num_t pin, mode_t mode)
    : _pin(pin), _mode(mode) {
        esp_rom_gpio_pad_select_gpio(pin);
        this->mode(mode);
    }

    ~GPIO() {
        gpio_reset_pin(_pin);
    }

    gpio_num_t pinName() {
        return _pin;
    }

    void mode(mode_t mode) {
        _mode = mode;
        switch (mode) {
            case INPUT:
            case OUTPUT:
            case INPUT_OUTPUT:
                gpio_set_direction(_pin, (gpio_mode_t)mode);
                break;
            case INPUT_PULLUP:
                gpio_set_direction(_pin, GPIO_MODE_INPUT);
                gpio_pulldown_dis(_pin);
                gpio_pullup_en(_pin);
                break;
            case INPUT_PULLDOWN:
                gpio_set_direction(_pin, GPIO_MODE_INPUT);
                gpio_pullup_dis(_pin);
                gpio_pulldown_en(_pin);
                break;
        }
    }

    void attach(void function(void*), interrupt_t mode, void* arg) {
        gpio_set_intr_type(_pin, (gpio_int_type_t)mode);
        gpio_install_isr_service(ESP_INTR_FLAG_LOWMED);
        gpio_isr_handler_add(_pin, function, arg);
    }

    void interruptDisable() {
        gpio_intr_disable(_pin);
    }

    void interruptEnable() {
        gpio_intr_enable(_pin);
    }

    inline bool read_raw() {
        return gpio_get_level(_pin);
    }

    virtual bool read() {
        bool state = read_raw();
        _state = _mode == INPUT_PULLUP ? !state : state;
        return _state;
    }

    inline void write(bool state) {
        _state = state;
        gpio_set_level(_pin, state);
    }

    inline void toggle(int state) {
        if(state) {
            _state ^= 1;
            write(_state);
        }
    }

    GPIO &operator=(GPIO &v) {
        this->write(v.read());
        return *this;
    }

    GPIO &operator=(int v) {
        this->write(v);
        return *this;
    }

    GPIO &operator^=(int v) {
        this->toggle(v);
        return *this;
    }

    [[nodiscard]] operator int() { return read(); }

private:
      const gpio_num_t _pin;
      mode_t          _mode;
      bool            _state;

};

#endif
