/*
 * p2_math.c
 *
 * Created: 2025-10-28 08:51:18
 *  Author: joela
 */ 
#include <stdint.h>
#include "include/p2_math.h"
#include "include/display.h"



uint16_t round_integer(uint16_t number){
    
    if (number < 100){
        
        uint8_t remainder = number % 10;
        
        if (remainder > 5){
            number += (10 - remainder);
        }
        else if (remainder < 5 && remainder != 0){
            number -= remainder;
        }
    }
    else if (number > 100){
        
        uint16_t remainder = number % 100;
        
        if (number > 50){
            number += (100 - remainder);
        }
        else if (remainder < 50 && remainder != 0){
            number -= remainder;
        }
    }
    
    return number;
}

uint16_t calculate_millivolt(uint16_t adc_value){
    
    return (adc_value * 5 * 1000) / 1023);
    
}

/*
Take an input voltage and calculate the resistance of the measured resistor
Output will be 100 times the resistance so that for example 6.734 ohm will be output as 673
*/

uint32_t calculate_resistance(uint16_t voltage_mv, uint16_t reference_resistor_ohm){
    
    uint8_t factor = 10;
    if (voltage_mv < 147 && reference_resistor_ohm != REF_RESISTOR_HIGH){
        factor = 100;
    }
    return ((reference_resistor_ohm * voltage_mv * 10) / (5000 - voltage_mv));
    
}

uint32_t resistance_update_buffer(uint32_t resistance){
    
    uint8_t rounding_carry = 0;
    
    /* Resistance is less than 10 */
    /*
    399 -> 3 9 9
    399 / 100 = 3
    399 % 100 / 10 = 9
    399 % 10 = 0
    */
    if (resistance > 0 && resistance < 1000){
        display_buffer[0] = resistance / 100;
        display_buffer[1] = (resistance % 100) / 10;
        display_buffer[2] = resistance % 10;
        display_buffer[3] = 1;  
    }
    
    /* Resistance is between 10 and 100 */
    /*      
    7922 / 1000 = 7
    (7922 % 1000) / 100 = 9
    (7922 % 100) = 22, round down to 20, divide by 10 and get 2
    7997 / 1000 = 7
    7997 % 1000 / 100= 9
    7997 % 100 = 97 -> ROUND UP TO 100 
    7 9 100 -> 7 10 0 -> 8 0 0
    */
    else if (resistance > 1000 && resistance < 10000){
 
        if (round_integer(resistance % 100) == 100){
            display_buffer[2] = 0;
            rounding_carry = 1;
        }
        else {
            display_buffer[2] = round_integer(resistance % 100) / 10;
            rounding_carry = 0;
        }
        
        uint8_t rounded_digit2 = (((resistance % 1000) / 100) + rounding_carry);
        
        if (rounded_digit2 == 10){
             display_buffer[1] = 0
             rounding_carry = 1;
        }
        else{
            display_buffer[1] = rounded_digit2;
            rounding_carry = 0;
        }
        
        display_buffer[0] = resistance / 1000 + rounding_carry;
        
        display_buffer[3] = 1;
        
    }  
    
    /* Resistance is between 100 and 1000 */
    /* 
        9996  (999.6) -> 9 9 96 -> 9 9 10 -> 9 10 0 -> 10 0 0 -> 1. 0 0 (if digit[0] == 10, digit_point = 1)
        5125  (512.5) -> 5 1 25 -> 5 1 3 
        6995  (699.5) -> 6 9 95 -> 6 9 10 -> 6 10 0 -> 7 0 0 -> 7 0 0
    */
    else if (resistance > 10000 && resistance < 100000){
        display_buffer[0] = resistance / 1000;
        display_buffer[1] = (resistance / 100) % 10;
        display_buffer[2] = round_integer(resistance % 100) / 10;
        display_buffer[3] = 0;
    }
    
    /* Resistance is between 1k and 10k */
    /*
        78396 (7839.6) -> 7 8 39 -> 7 8 4 -> 7. 8 4
        54999 (5499.9) -> 5 4 99 -> 5 4 10 -> 5. 5 0
        99969 (9996.9)  -> 9 9 96 -> 9 9 10 -> 9 10 0 -> 10 0 0 -> 1 0.      
    */
    else if (resistance > 100000 && resistance < 1000000){
        display_buffer[0] = resistance / 100000;
        display_buffer[1] = resistance / 10000 % 10;
        display_buffer[2] = round_integer(resistance) ;
    }

    /* Resistance is between 10k and 100k */
    /*
        783962 (78396.2) -> 7 8 39 -> 7 8 4 -> 7 8. 4
        549996 (54999.6) -> 5 4 99 -> 5 4 10 -> 5 5 0 -> 5 5. 0
        9996953 (99969.5)  -> 9 9 96 -> 9 9 10 -> 9 10 0 -> 10 0 0 -> 1 0 0    
    */
    else if (resistance > 1000000 && resistance < 10000000){
        
    }
}

