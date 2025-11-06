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
    
    digit_1 = 11,
    digit_2 = 12,
    digit_3 = 13
    
    } digit_pos_t;


typedef enum{
    
    error = 1
    
    } display_code_t;


extern digit_pos_t digit_pins[3];
extern uint8_t display_buffer[4];

void display_digit(uint8_t digit, digit_pos_t digit_pos, uint8_t decimal_point);
void display_buffer_send(digit_pos_t digit_to_display);
void display_buffer_update(float number);


#endif /* DISPLAY_H_ */