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
    
    return ((reference_resistor_ohm * voltage_mv * 100) / (5000 - voltage_mv));
    
}

uint32_t resistance_update_buffer(uint32_t resistance){
    
    /* Resistance is less than 10 */
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
    */
    else if (resistance > 1000 && resistance < 10000){
        display_buffer[0] = resistance / 1000;
        display_buffer[1] = (resistance % 1000) / 100;
        display_buffer[2] = round_integer(resistance % 100) / 10;
        display_buffer[3] = 1;
    }  
    /* Resistance is between 100 and 1000 */
    /* 16253 / 10000 = 1
       16253 / 1000 = 16, 16 % 10 = 6
       16253 % 1000 = 253, round 253, 300, 300 / 100 = 3
    */
    else if (resistance > 10000 && resistance < 100000){
        display_buffer[0] = resistance / 10000;
        display_buffer[1] = (resistance / 1000) % 10;
        display_buffer[2] = round_integer(resistance % 100) / 100;
        display_buffer[3] = 0;
    }
    
    /* Resistance is between 1k and 10k */
    else if (resistance > 100000 && resistance < 1000000){
        
    }

    /* Resistance is between 10k and 100k */
    else if (resistance > 1000000 && resistance < 10000000){
        
    }
}

