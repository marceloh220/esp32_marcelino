#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#include "chrono.hpp"

class Timer {

public:

    Timer(TimerCallbackFunction_t callback, const char *name, milliseconds time, bool repetitive = true) :
    _name(name) {
        _handle = new TimerHandle_t;
        _id = (void*)_handle;
        *_handle = xTimerCreate(name, CHRONO_TO_TICK(time), repetitive, _id, callback);
    }

    ~Timer() {
        xTimerDelete(*_handle, portMAX_DELAY);
        delete _handle;
    }

    bool verifyID(TimerHandle_t timer) {
        return pvTimerGetTimerID(timer) == _id ? true : false;
    }

    const char* name() { return _name; }

    BaseType_t start() {
        return xTimerStart(*_handle, portMAX_DELAY);
    }

    BaseType_t start(milliseconds timeout) {
        return xTimerStart(*_handle, CHRONO_TO_TICK(timeout));
    }

    BaseType_t startFromISR() {
        return xTimerStartFromISR(*_handle, NULL);
    }

    BaseType_t stop() {
        return xTimerStop(*_handle, portMAX_DELAY);
    }

    BaseType_t stop(milliseconds timeout) {
        return xTimerStop(*_handle, CHRONO_TO_TICK(timeout));
    }

    BaseType_t stopFromISR() {
        return xTimerStopFromISR(*_handle, NULL);
    }

    BaseType_t reset() {
        return xTimerReset(*_handle, portMAX_DELAY);
    }

    BaseType_t reset(milliseconds timeout) {
        return xTimerReset(*_handle, CHRONO_TO_TICK(timeout));
    }

private:

    const char* _name;
    void* _id;
    TimerHandle_t *_handle;

};

#endif
