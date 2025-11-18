/*
 * p2_math.h
 *
 * Created: 2025-10-28 08:53:28
 *  Author: joela
 */ 


#ifndef P2_MATH_H_
#define P2_MATH_H_


#define REF_RESISTOR_LOW 330U
#define REF_RESISTOR_HIGH 33000U
#define HIGH_VOLTAGE_DIVIDER 7

uint16_t round_integer(uint16_t number);
void cascading_rounding(uint8_t *digit_1, uint8_t *digit_2, uint8_t *digit_3, uint8_t *decimal_point);
uint16_t calculate_millivolt(uint16_t adc_value);
uint32_t calculate_resistance(uint16_t voltage_mv, uint16_t reference_resistor_ohm);
void voltage_update_buffer(uint16_t voltage_mv, uint8_t divider_factor);
void resistance_update_buffer(uint32_t resistance);


#endif /* P2_MATH_H_ */