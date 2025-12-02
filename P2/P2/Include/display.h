/*
 * display.h
 *
 * Created: 2025-10-27 14:02:19
 *  Author: Joel Alftberg
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

typedef enum{
    
    digit_1_pin = 13,
    digit_2_pin = 12,
    digit_3_pin = 11
    
    } digit_pos_t;


typedef enum{
    
    error = 1
    
    } display_code_t;


extern digit_pos_t digit_pins[3];
extern uint8_t display_buffer[4];

void display_digit_driver(uint8_t digit, uint8_t digit_pos, uint8_t decimal_point);
void display_update();
void display_buffer_update(uint8_t digit_1, uint8_t digit_2, uint8_t digit_3, uint8_t decimal_point);


#endif /* DISPLAY_H_ */