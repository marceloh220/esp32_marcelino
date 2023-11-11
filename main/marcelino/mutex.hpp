#ifndef _MUTEX_HPP_
#define _MUTEX_HPP_

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "chrono.hpp"

class Mutex {
public:
    Mutex() {
        *_handle = xSemaphoreCreateMutex();
    }

    ~Mutex() {
        vSemaphoreDelete(*_handle);
        delete _handle;
    }

    inline BaseType_t take() {
        return xSemaphoreTake(*_handle, portMAX_DELAY);
    }

    inline BaseType_t take(milliseconds timeout) {
        return xSemaphoreTake(*_handle, CHRONO_TO_TICK(timeout));
    }

    inline BaseType_t give() {
        return xSemaphoreGive(*_handle);
    }

private:
    SemaphoreHandle_t *_handle = new SemaphoreHandle_t;
};


class MutexRecursive {
public:
    MutexRecursive() {
        *_handle = xSemaphoreCreateRecursiveMutex();
    }

    ~MutexRecursive() {
        vSemaphoreDelete(*_handle);
        delete _handle;
    }

    inline BaseType_t take() {
        return xSemaphoreTakeRecursive(*_handle, portMAX_DELAY);
    }

    inline BaseType_t take(milliseconds timeout) {
        return xSemaphoreTakeRecursive(*_handle, CHRONO_TO_TICK(timeout));
    }

    inline BaseType_t give() {
        return xSemaphoreGiveRecursive(*_handle);
    }

private:
    SemaphoreHandle_t *_handle = new SemaphoreHandle_t;
};

#endif
