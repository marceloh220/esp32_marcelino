#ifndef _CHRONO_HPP_
#define _CHRONO_HPP_

#include <chrono>

#include "freertos/FreeRTOS.h"
#include "esp_timer.h"

using namespace std::literals::chrono_literals;

using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::hours;
using std::chrono::days;
using std::chrono::weeks;
using std::chrono::month;
using std::chrono::year;

#define CHRONO_TO_TICK(_time) (pdMS_TO_TICKS(_time.count())) 

template<typename t>
[[nodiscard]] int64_t duration_cast(microseconds time) {
    return std::chrono::duration_cast<t>(time).count();
}

template<typename t>
[[nodiscard]] int64_t duration_cast(milliseconds time) {
    return std::chrono::duration_cast<t>(time).count();
}

template<typename t>
[[nodiscard]] int64_t duration_cast(seconds time) {
    return std::chrono::duration_cast<t>(time).count();
}

template<typename t>
[[nodiscard]] int64_t duration_cast(minutes time) {
    return std::chrono::duration_cast<t>(time).count();
}

template<typename t>
[[nodiscard]] int64_t duration_cast(hours time) {
    return std::chrono::duration_cast<t>(time).count();
}

template<typename t>
[[nodiscard]] int64_t duration_cast(days time) {
    return std::chrono::duration_cast<t>(time).count();
}

template<typename t>
[[nodiscard]] int64_t duration_cast(weeks time) {
    return std::chrono::duration_cast<t>(time).count();
}

template<typename t>
[[nodiscard]] int64_t duration_cast(month time) {
    return std::chrono::duration_cast<t>(time).count();
}

template<typename t>
[[nodiscard]] int64_t duration_cast(year time) {
    return std::chrono::duration_cast<t>(time).count();
}

inline void delay(milliseconds time) {
    vTaskDelay(CHRONO_TO_TICK(time));
}

template <typename t>
[[nodiscard]] inline t time() {
    microseconds micros(esp_timer_get_time());
    return std::chrono::duration_cast<t>(micros);
}

#endif
