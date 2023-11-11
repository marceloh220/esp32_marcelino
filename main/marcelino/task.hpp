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

    Task(TaskFunction_t callback, const char* name, UBaseType_t priority = 0, uint32_t stackSize = 2048, void* args = NULL) :
    _callback(callback), _name(name), _priority(priority), _stackSize(stackSize), _args(args) {
        _handle = new TaskHandle_t;
        attach();
    }

    ~Task() {
        vTaskDelete(*_handle);
        delete _handle;
    }

    inline void delayUntil(const TickType_t time) {
        vTaskDelayUntil(&previousTime, time);
    }

    inline BaseType_t abortDelay() {
        return xTaskAbortDelay(*_handle);
    }

    inline void suspend() {
        vTaskSuspend(*_handle);
    }

    inline void resume() {
        vTaskResume(*_handle);
    }

    inline BaseType_t resumeFromISR() {
        return xTaskResumeFromISR(*_handle);
    }

    inline const char* name() { return _name;}
    
    inline UBaseType_t priority() { return _priority;}
    inline void priority(UBaseType_t priority) { 
        _priority = priority;
        vTaskPrioritySet(*_handle, priority);
    }

    inline uint32_t stackSize() { return _stackSize;}

    template<typename type>
    inline type args() { return static_cast<type>(_args);}
    template<typename type>
    inline void args(type args) { _args = static_cast<void*>(args);}

    inline BaseType_t core() {
        return xPortGetCoreID();
    }

private:
    TaskFunction_t _callback;
    const char *_name;
    UBaseType_t _priority;
    uint32_t _stackSize;
    void* _args;
    TaskHandle_t *_handle;
    bool _created = false;
    TickType_t previousTime = 0;

    void attach() {
        if(!_created) {
            esp_err_t error = xTaskCreate(_callback, _name, _stackSize, _args, _priority, _handle);
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
