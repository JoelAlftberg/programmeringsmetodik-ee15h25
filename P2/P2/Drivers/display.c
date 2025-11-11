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

#include "../include/display.h"
#include <stdint.h>
#include <stdbool.h>
#include "../include/p2_math.h"
#include <avr/delay.h>

digit_pos_t digit_pins[3] = {digit_1_pin, digit_2_pin, digit_3_pin};
uint16_t display_buffer[4] = {0, 0, 0, 0};

void display_digit(uint8_t digit, digit_pos_t digit_pos, uint8_t decimal_point){
    
    for(uint8_t i = 0; i < 3; i++){
        if (digit_pins[i] == digit_pos){
            digital_out(digit_pins[i], false);
        }
        else{
            digital_out(digit_pins[i], true);
        }
    }    
    
    digital_out(2, digit & 0x01);
    digital_out(3, digit & 0x02);
    digital_out(4, digit & 0x04);
    digital_out(5, digit & 0x08);
    digital_out(6, decimal_point);
    
}

void code_update_buffer(display_code_t code){
    
    if(code == error){
        
    }
    
}

/*

Takes a positive integer as an input (value between 0 - 100000) and updates the display_buffer[]
array with the value rounded and converted to a suitable format for a 3-digit display

*/


/*

Send the data present in the buffer to the 3 digit 7-segment display
Use the HAL functions for outputting digits found in the drivers.c file

TODO: write drivers first for sending a number to a specific digit ex.
display_digit(uint8_t number, uint8_t digit, uint8_t decimal_point);
display_codes(uint8_t mode);

*/

void display_buffer_send(digit_pos_t digit_to_display){
/*

Make an array of length 4 instead of three for the buffer
pos 1 = first digit to show
pos 2 = second digit to show
pos 3 = third digit to show
pos 4 = which position to place decimal point, 0 means no decimal point 
*/
    
    
}