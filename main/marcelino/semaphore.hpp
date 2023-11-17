#ifndef _SEMAPHORE_HPP_
#define _SEMAPHORE_HPP_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "chrono.hpp"

class Semaphore {
public:
    Semaphore(int count = 1, int initialValue = 0) {
        if(count > 1)   _handle = xSemaphoreCreateCounting(count, initialValue);
        else            _handle = xSemaphoreCreateBinary();
    }

    ~Semaphore() {
        vSemaphoreDelete(_handle);
    }

    inline BaseType_t take() {
        return xSemaphoreTake(_handle, portMAX_DELAY);
    }

    inline BaseType_t take(milliseconds timeout) {
        return xSemaphoreTake(_handle, CHRONO_TO_TICK(timeout));
    }

    inline BaseType_t give() {
        return xSemaphoreGive(_handle);
    }

    inline BaseType_t giveFromISR() {
        return xSemaphoreGiveFromISR(_handle, NULL);
    }

private:
    SemaphoreHandle_t _handle;
};

#endif
