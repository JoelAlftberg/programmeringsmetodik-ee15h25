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

void display_code(display_code_t code){
    
    if(code == error){
        
    }
    
}

/*

Takes a positive integer as an input (value between 0 - 100000) and updates the display_buffer[]
array with the value rounded and converted to a suitable format for a 3-digit display

*/

void prepare_for_buffer(uint32_t number){
    
}

void display_buffer_update(uint32_t number){

    uint16_t num_decimal_part = 0;

    if (number < 0){
        // {404, 404, 3} in display buffer will evaluate to ERR
        display_buffer[0] = 404;
        display_buffer[1] = 404;
        display_buffer[2] = 3;
        return;
    }
    // 1k to 99.9k range
    if (number > 1000 && number < 100000){

        uint8_t num_thousands = number / 1000;
        num_decimal_part = number - (num_thousands * 1000);
        display_buffer[0] = num_thousands;
        
        if (num_thousands < 10){
            // example 7825 -> num_decimal = 825 (0.825), round to nearest hundreth 830 (0.830) and then do /= 10 so it becomes 83
            
            display_buffer[1] = round_to_hundredth(num_decimal_part);
            display_buffer[2] = 1;
        }
        else if (num_thousands > 10){
            // example 24789 -> num_decimal = 789 (0.789) round to nearest tenth so  789 -> 800 (0.800) then /= 100 so it becomes 8
            display_buffer[1] = round_to_tenth(num_decimal_part);
            display_buffer[2] = 2;
        }
    }
    // 0 to 999 range
    else if (number > 0 && number < 1000){
        
        uint16_t num_integer_part = (uint16_t) number;
        num_decimal_part = (number - num_integer_part) * 1000;

        // example 6.789123
        if (number < 10 && number > 0){
            display_buffer[1] = round_to_hundredth(num_decimal_part);
            display_buffer[2] = 1;
        }
        // example 48.14722
        else if (number > 10 && number < 100){
            display_buffer[1] = round_to_tenth(num_decimal_part);
            display_buffer[2] = 2;
        }
        // example 453.51452
        else if (number > 10 && number < 1000){
            
            if (num_decimal_part > 500){
                num_integer_part++;
            }
            
            display_buffer[1] = 0;
            display_buffer[2] = 3;
            
        }
        
        display_buffer[0] = num_integer_part;
        
    }
}

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