#ifndef _MAP_H_
#define _MAP_H_

#include "hal/gpio_types.h"

typedef enum map_e {
    LED_R       = GPIO_NUM_2,
    LED_Y       = GPIO_NUM_4,
    LED_G       = GPIO_NUM_5,
    BUTTON_R    = GPIO_NUM_16,
    BUTTON_Y    = GPIO_NUM_17,
    BUTTON_G    = GPIO_NUM_18,
    BUTTON_ENC  = GPIO_NUM_15,
    ENC_CLK     = GPIO_NUM_19,
    ENC_DT      = GPIO_NUM_23,
    SDA_OLED    = GPIO_NUM_21,
    SCL_OLED    = GPIO_NUM_22,
    BUZZER_DAC2 = GPIO_NUM_26,
    PWM_TCH7    = GPIO_NUM_27,
    OLED_ADDR   = (0x78 >> 1),
} map_t;


#endif
