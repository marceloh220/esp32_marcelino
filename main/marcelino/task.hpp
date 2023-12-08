#ifndef _TASK_HPP_
#define _TASK_HPP_

#include "esp_err.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"

#include "chrono.hpp"

typedef void * arg_t;

class Task {

public:

    typedef enum  pinCore {
        CORE_0,
        CORE_1,
        NO_AFINITY,
    } pinCore_t;

    Task(TaskFunction_t callback, const char* name, UBaseType_t priority = 0, uint32_t stackSize = 2048, pinCore_t core = NO_AFINITY, arg_t args = NULL) :
    _callback(callback), _name(name), _priority(priority), _stackSize(stackSize), _core(core), _args(args)
    {
        attach();
    }

    ~Task() {
        vTaskDelete(_handle);
    }

    inline void delayUntil(milliseconds time) {
        vTaskDelayUntil(&previousTime, CHRONO_TO_TICK(time));
    }

    inline BaseType_t abortDelay() {
        return xTaskAbortDelay(_handle);
    }

    inline void suspend() {
        vTaskSuspend(_handle);
    }

    inline void resume() {
        vTaskResume(_handle);
    }

    inline BaseType_t resumeFromISR() {
        return xTaskResumeFromISR(_handle);
    }

    inline const char* name() { return _name;}
    
    inline UBaseType_t priority() { return _priority;}
    inline void priority(UBaseType_t priority) { 
        _priority = priority;
        vTaskPrioritySet(_handle, priority);
    }

    inline uint32_t stackSize() { return _stackSize;}

    template<typename type>
    inline type args() { return static_cast<type>(_args);}

    template<typename type>
    inline void args(type args) { _args = static_cast<arg_t>(args);}

    inline BaseType_t core() {
        return _core;
    }

private:
    TaskFunction_t _callback;
    const char * _name;
    UBaseType_t  _priority;
    uint32_t     _stackSize;
    UBaseType_t  _core;
    arg_t        _args;
    TaskHandle_t _handle;
    bool         _created = false;
    TickType_t   previousTime = 0;

    inline void attach() {
        if(!_created) {
            esp_err_t error;
            if(_core == NO_AFINITY) {
                error = xTaskCreate(_callback, _name, _stackSize, _args, _priority, &_handle);
            } else error = xTaskCreatePinnedToCore(_callback, _name, _stackSize, _args, _priority, &_handle, _core);
            if(error == pdPASS) {
                ESP_LOGI(_name, "Task created");
                _created = true;
            } else {
                ESP_LOGE(_name, "Task faill in creation");
            }
        }
    }

};

#endif
