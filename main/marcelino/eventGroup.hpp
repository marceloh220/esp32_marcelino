#ifndef _EVENT_GROUP_HPP_
#define _EVENT_GROUP_HPP_

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include "chrono.hpp"

class EventGroup {

public:

    EventGroup() {
        *_handle = xEventGroupCreate();
    }

    ~EventGroup() {
        vEventGroupDelete(*_handle);
        delete _handle;
    }

    inline EventBits_t set(const EventBits_t flags) {
        return xEventGroupSetBits(*_handle, flags);
    }

    inline EventBits_t setFromISR(const EventBits_t flags) {
        return xEventGroupSetBitsFromISR(*_handle, flags, NULL);
    }

    inline EventBits_t clear(const EventBits_t flags) {
        return xEventGroupClearBits(*_handle, flags);
    }

    inline EventBits_t clearFromISR(const EventBits_t flags) {
        return xEventGroupClearBitsFromISR(*_handle, flags);
    }

    inline EventBits_t get() {
        return xEventGroupGetBits(*_handle);
    }

    inline EventBits_t getFromISR() {
        return xEventGroupGetBitsFromISR(*_handle);
    }

    inline EventBits_t wait(const EventBits_t flags, bool clearFlags, bool allFlags) {
        return xEventGroupWaitBits(*_handle, flags, clearFlags, allFlags, portMAX_DELAY);
    }

    inline EventBits_t wait(const EventBits_t flags, bool clearFlags, bool allFlags, milliseconds timeout) {
        return xEventGroupWaitBits(*_handle, flags, clearFlags, allFlags, CHRONO_TO_TICK(timeout));
    }

private:

    EventGroupHandle_t *_handle = new EventGroupHandle_t;

};

#endif
