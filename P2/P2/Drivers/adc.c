/*
 * adc.c
 *
 * Created: 2025-10-28 10:19:46
 *  Author: joela
 */ 

#include "../include/adc.h"
#include <avr/io.h>

uint16_t read_analog_adc(analog_pin_t pin){
    ADMUX = ((1 << REFS0) | pin);
    ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
    while ((ADCSRA & (1 << ADIF)) == 0) ;
    ADCSRA |= (1 << ADIF);
    return ADC;
}