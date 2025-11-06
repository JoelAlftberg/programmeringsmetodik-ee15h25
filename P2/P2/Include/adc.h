/*
 * adc.h
 *
 * Created: 2025-10-28 10:39:40
 *  Author: joela
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef enum {
    A0, A1, A2, A3, A4, A5
} analog_pin_t;

uint16_t read_analog_adc(analog_pin_t pin);


#endif /* ADC_H_ */