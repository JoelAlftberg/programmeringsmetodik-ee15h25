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

uint16_t round_to_hundredth(uint16_t decimal_part);
uint16_t round_to_tenth(uint16_t decimal_part);


#endif /* P2_MATH_H_ */