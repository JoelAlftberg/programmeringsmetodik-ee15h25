/*
 * dmm_mode.c
 *
 * Created: 2025-10-28 10:18:08
 *  Author: joela
 */ 
#include "../include/adc.h"
#include <stdint.h>

float voltage_mode_upper_range(void){
    
    float input_voltage = 0;
    
    for(uint8_t i = 0; i < 16; i++){
        input_voltage += read_analog_adc(A0);
    }
    input_voltage = input_voltage / 16.0f;
    
    return (input_voltage * (5.0f/1023.0f) * 7.0f);
    
}