/*
 * p2_logic.c
 *
 * Created: 2025-11-18 11:05:04
 *  Author: joela
 */ 

/*
input pins
7, 8, 9, 10
    
output pins
A  B  C  D  dp
2, 3, 4, 5, 6
d1  d2  d3
11, 12, 13 (display)
    
*/

#include <stdint.h>
#include "../include/gpio.h"
   
#define INPUT_PIN_AMOUNT 4
#define OUTPUT_PIN_AMOUNT 8
   
static uint8_t input_pins[INPUT_PIN_AMOUNT] = {7, 8, 9, 10 };
static uint8_t output_pins[OUTPUT_PIN_AMOUNT] = {2, 3, 4, 5, 6, 11, 12, 13};

uint8_t check_mode(){

    
    for (uint8_t i = 0; i < INPUT_PIN_AMOUNT; i++){
        if (gpio_digital_read(input_pins[i])){
            return (i + 1);
        }
    }
    
    /* If all pins are low, we are in mode 5 (timer mode)*/
    return 5;
    
}

void init_p2_gpio(){

    gpio_set_direction(0, INPUT);
    
    for (uint8_t i = 0; i < INPUT_PIN_AMOUNT; i++){
        gpio_set_direction(input_pins[i], INPUT);
    }
    
    for (uint8_t i = 0; i < OUTPUT_PIN_AMOUNT; i++){
        gpio_set_direction(output_pins[i], OUTPUT);
    }
    
}



