/*
 * display.c
 *
 * Created: 2025-10-27 12:58:09
 *  Author: Joel Alftberg
 */ 


/*
11 digit 1
12 digit 2
13 digit 3

2 BCD A
3 BCD B
4 BCD C
5 BCD D
6 BCD DP

*/
#include <avr/delay.h>
#include <stdint.h>
#include <stdbool.h>

#include "../include/display.h"
#include "../include/p2_math.h"
#include "../include/gpio.h"


digit_pos_t digit_pins[3] = {digit_1_pin, digit_2_pin, digit_3_pin};
uint8_t display_buffer[4] = {0, 0, 0, 0};


void display_digit_driver(uint8_t digit, uint8_t digit_pos, uint8_t decimal_point){
    
    for(uint8_t i = 0; i < 3; i++){
        
        if (i == digit_pos){
            gpio_digital_write(digit_pins[i], LOW);
        }
        else{
            gpio_digital_write(digit_pins[i], HIGH);
        }
        
    }    
    
    gpio_digital_write(2, digit & 0x01);
    gpio_digital_write(3, (digit >> 1) & 0x01);
    gpio_digital_write(4, (digit >> 2) & 0x01);
    gpio_digital_write(5, (digit >> 3) & 0x01);
    gpio_digital_write(6, decimal_point);
    
}

void display_buffer_code(display_code_t code){
    
    if(code == error){
        
    }
    
}

/*

Send the data present in the buffer to the 3 digit 7-segment display
Use the HAL functions for outputting digits found in the drivers.c file

TODO: write drivers first for sending a number to a specific digit ex.
display_codes(uint8_t mode);

*/
void display_update(uint8_t *digit_counter){
    
    display_digit_driver(display_buffer[*digit_counter], *digit_counter, (display_buffer[3] == *digit_counter) ? 1 : 0);
    (*digit_counter)++;
    if (*digit_counter > 2){
        *digit_counter = 0;
    }
    
}

void display_buffer_update(uint8_t digit_1, uint8_t digit_2, uint8_t digit_3, uint8_t decimal_point){
    
    display_buffer[0] = digit_1;
    display_buffer[1] = digit_2;
    display_buffer[2] = digit_3;
    display_buffer[3] = decimal_point;
    
}
