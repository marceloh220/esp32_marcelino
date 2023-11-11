#include "marcelino/marcelino.hpp"

MutexRecursive mutex;

void blink_callback(arg_t arg);

Task blink_task(blink_callback, "Blink LED G", 1);

extern "C" void app_main() {

    while (1)
    {
    
        milliseconds t = time<milliseconds>();
        microseconds u = t;

        printf("Time: %lld\n", duration_cast<seconds>(u));

        delay(1s);
    
    }

}

void blink_callback(arg_t arg) {

    Output *led_g = new Output(LED_G);

    while(1) {

        *led_g ^= 1;
        delay(500ms);
    
    }

}