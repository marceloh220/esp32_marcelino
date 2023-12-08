#include "marcelino/marcelino.hpp"

void ISR_blink(TimerHandle_t);
Timer *timer0 = new Timer(ISR_blink, "Timer 0", 250ms);
Timer *timer1 = new Timer(ISR_blink, "Timer 1", 500ms);

Semaphore *blinkSemaphore = new Semaphore;
Queue<char*> *msg = new Queue<char*>(10);

void blink_callback(arg_t arg);
void print_callback(arg_t arg);

Task *blink_task = new Task(blink_callback, "Blink LED G", 1);
Task *print_task = new Task(print_callback, "Print MSG", 1);

Oled *display = new Oled;

extern "C" void app_main() {

    char* msgToPrint = new char[40];

    timer0->start();
    timer1->start();

    display->begin();

    while (1) {

        int64_t seconds_time =  time<seconds>().count();

        struct tm timer_str;
        
        timer_str.tm_hour = (seconds_time / 3600) % 24;
        timer_str.tm_min = (seconds_time / 60) % 60;
        timer_str.tm_sec = seconds_time % 60;

        strftime(msgToPrint, 40, "%H:%M:%S\n", &timer_str);

        msg->send(&msgToPrint);
        
        blinkSemaphore->give();

        delay(1s);
    
    }

    delete msgToPrint;

}

void blink_callback(arg_t arg) {

    static Output led_g(LED_G);

    while(1) {

        blink_task->delayUntil(100ms);

        blinkSemaphore->take();
        led_g ^= 1;

    }

}

void print_callback(void* arg) {

    char* msgToPrint = new char[40];

    while (1) {

        print_task->delayUntil(100ms);

        if(msg->receive(&msgToPrint) == pdPASS) {
            printf("%s", msgToPrint);
        }

    }

    delete msgToPrint;

}

void ISR_blink(TimerHandle_t timer) {

    static Output *led_r = new Output(LED_R);
    static Output *led_y = new Output(LED_Y);

    if(timer0->verifyID(timer))
        led_r->toggle();

    if(timer1->verifyID(timer))
        led_y->toggle();

}
