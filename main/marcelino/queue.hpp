#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "chrono.hpp"

template<typename type>
class Queue {

public:

    Queue(uint32_t length) {
        _handle = xQueueCreate(length, sizeof(type));
    }

    ~Queue() {
        vQueueDelete(_handle);
    }

    BaseType_t send(type *data) {
        return xQueueSend(_handle, (void*)data, portMAX_DELAY);
    }

    BaseType_t send(type *data, milliseconds timeout) {
        return xQueueSend(_handle, (void*)data, CHRONO_TO_TICK(timeout));
    }

    BaseType_t sendToBack(type *data) {
        return xQueueSendToBack(_handle, (void*)data, portMAX_DELAY);
    }

    BaseType_t sendToBack(type *data, milliseconds timeout) {
        return xQueueSendToBack(_handle, (void*)data, CHRONO_TO_TICK(timeout));
    }

    BaseType_t sendToFont(type *data) {
        return xQueueSendToFront(_handle, (void*)data, portMAX_DELAY);
    }

    BaseType_t sendToFont(type *data, milliseconds timeout) {
        return xQueueSendToFront(_handle, (void*)data, CHRONO_TO_TICK(timeout));
    }

    BaseType_t sendFromISR(type *data) {
        return xQueueSendFromISR(_handle, (void*)data, NULL);
    }

    BaseType_t sendToBackFromISR(type *data) {
        return xQueueSendToBackFromISR(_handle, (void*)data, NULL);
    }

    BaseType_t sendToFrontFromISR(type *data) {
        return xQueueSendToFrontFromISR(_handle, (void*)data, NULL);
    }

    BaseType_t receive(type *data) {
        return xQueueReceive(_handle, (void*)data, portMAX_DELAY);
    }

    BaseType_t receive(type *data, milliseconds timeout) {
        return xQueueReceive(_handle, (void*)data, CHRONO_TO_TICK(timeout));
    }

    UBaseType_t messagesWaiting() {
        return uxQueueMessagesWaiting(_handle);
    }

    UBaseType_t messagesWaitingFromISR() {
        return uxQueueMessagesWaitingFromISR(_handle);
    }

    UBaseType_t spacesAvaliable() {
        return uxQueueSpacesAvailable(_handle);
    }

    BaseType_t reset() {
        return xQueueReset(_handle);
    }

private:

    QueueHandle_t _handle;

};

#endif
