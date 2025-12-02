/*
 * p2_math.c
 *
 * Created: 2025-10-28 08:51:18
 *  Author: joela
 */ 
#include <stdint.h>
#include <stdbool.h>
#include "../include/p2_math.h"
#include "../include/display.h"

bool factor_flag = false;

/*

*/
uint16_t round_integer(uint16_t number){
    
        
    uint8_t remainder = number % 10;
    
    if (remainder > 5){
        number += (10 - remainder);
    }
    else if (remainder < 5 && remainder != 0){
        number -= remainder;
    }

    return number / 10;
}

/*

*/
void cascading_rounding(uint8_t *digit_1, uint8_t *digit_2, uint8_t *digit_3, uint8_t *decimal_point){
    
    *digit_3 = round_integer(*digit_3);
    
    if (*digit_3 == 10){
        *digit_3 = 0;
        (*digit_2)++;
    }
    if (*digit_2 == 10){
        *digit_2 = 0;
        (*digit_1)++;
    }
    if (*digit_1 == 10){
        *digit_1 = 1;
        *decimal_point = (*decimal_point == 3) ? *decimal_point - 2 : *decimal_point + 1;
    }
    
}

/*
    
*/
uint32_t calculate_millivolt(uint32_t adc_value){
    
    uint8_t v_ref = 5;
    uint32_t adc_max = 16383;
    /* Scales up with 1000 to get millivolt*/
    return (uint32_t) ( adc_value * v_ref * 1000) / adc_max;
    
}

/*
Takes an input voltage and calculates the resistance of the measured resistor
Output will be 100 times the resistance so that for example 6.734 ohm will be output as 673
*/
uint32_t calculate_resistance(uint16_t voltage_mv, uint16_t reference_resistor_ohm){
    
    uint16_t v_ref_mv = 5000;
    uint8_t factor = 10;

    /* Guard against zero-division*/
    if (voltage_mv >= v_ref_mv - 1 ){
        return UINT16_MAX;
    }

    if (voltage_mv < 147 && reference_resistor_ohm != REF_RESISTOR_HIGH){
        factor = 100;
        factor_flag = true;
    }
    else{
        factor_flag = false;
    }

    return (((uint32_t) reference_resistor_ohm * voltage_mv * factor) / (v_ref_mv - voltage_mv));
    
}

/*
Takes the calculated voltage and formats it so that it can be output on 3-digit 7-segment display
*/
void voltage_update_buffer(uint16_t voltage_mv, uint8_t divider_factor){

    /*1599 mv -> 1.60 V */
    /*19253 mv -> 19.3V */
    uint8_t digit_1 = 0;
    uint8_t digit_2 = 0;
    uint8_t digit_3 = 0;
    uint8_t decimal_point = 0;

    voltage_mv *= divider_factor;
    
    if (voltage_mv > 10000){
        digit_1 = voltage_mv / 10000;
        digit_2 = (voltage_mv / 1000) % 10;
        digit_3 = (voltage_mv % 1000) / 100;
        decimal_point = 1;
    }
    else{
        digit_1 = (voltage_mv / 1000);
        digit_2 = (voltage_mv / 100) % 10;
        digit_3 = (voltage_mv % 100) / 10; 
        decimal_point = 0;
    }
    
    //cascading_rounding(&digit_1, &digit_2, &digit_3, &decimal_point);
    display_buffer_update(digit_1, digit_2, digit_3, decimal_point);
    
}

/*  
Takes the calculated resistance and formats it so that it can be output on 3-digit 7-segment display
Handles rounding and placement of the decimal point
*/
void resistance_update_buffer(uint32_t resistance){
    
    uint32_t factor_1 = 1;
    uint32_t factor_2 = 1;
    uint32_t denominator = 1;
    uint8_t decimal_point = 0;

    uint8_t digit_1 = 0;
    uint8_t digit_2 = 0;
    uint8_t digit_3 = 0;

    bool rounding = true;

    /* If resistance is out of bounds, display 0 for all digits */
    if (resistance == 0 || resistance > 1000000){
        display_buffer_update(0, 0, 0, 3);
        return;
    }
    
    /* If we are measuring resistances of 0 - 100 ohm, use a larger factor to get more precision */
    if (factor_flag){
        /* 0-10 ohm */
        if (resistance < 1000){
            factor_1 = 100;
            rounding = false;
            decimal_point = 1;
        }
        /* 10-100 ohm */
        else if (resistance < 10000){
            factor_1 = 100;
            decimal_point = 2;
        }
        else {
            display_buffer_update(0, 0, 0, 3);
            return;
        }
    }
    else{
        /* 0-100 ohm */
        if (resistance < 1000){
            factor_1 = 10;
            rounding = false;
            decimal_point = 1;
        }
        /* 100-1k ohm */
        else if (resistance < 10000){
            factor_1 = 1000;
            decimal_point = 3;  
        }
        /* 1k-10k ohm */
        else if (resistance < 100000){
            factor_1 = 10000;
            decimal_point = 0;
        }
        /* 10-100k ohm */
        else if (resistance < 1000000){
            factor_1 = 100000;
            decimal_point = 1;
        }
    }

    /* Calculate factors to use for formatting the number */
    factor_2 = factor_1 / 10;
    denominator = (factor_1 == 100) ? 1 : factor_1 / 1000;
    
    /* Do final calculations for each digit*/
    digit_1 = resistance / factor_1;
    digit_2 = (resistance % factor_1) / factor_2;
    digit_3 = (resistance % factor_2) / denominator;
    
    /* Perform cascading rounding */
    if (rounding == true){
        cascading_rounding(&digit_1, &digit_2, &digit_3, &decimal_point);
    }

    /* Update display buffer */
    display_buffer_update(digit_1, digit_2, digit_3, decimal_point);

}

