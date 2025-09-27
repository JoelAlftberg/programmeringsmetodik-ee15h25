/*
 * bcd_counter.c
 *
 * Created: 2025-09-18 10:13:45
 *  Author: joela
 */ 

#include "../P0/p0.h"
#include "bcd_counter.h"
#include <stdint.h>

const uint8_t digit_pins[4] = { DISP_DIGIT_1_PIN, DISP_DIGIT_2_PIN, DISP_DIGIT_3_PIN, DISP_DIGIT_4_PIN};

void bcd_generate_pulses(uint8_t pulses, uint8_t pin){
	while(pulses){
		digital_out(pin,1);
		wait_micro(1);
		digital_out(pin,0);
		wait_micro(1);
		pulses--;
	}
}

void select_digit_pos(uint8_t digit_pos){
	
	if (digit_pos < 0 || digit_pos > 4){
		return 0;
	}
	uint8_t digit_index = digit_pos - 1;
	
	/* Set all digits low */
	for(int i = 0; i < 4; i++){
		digital_out(digit_pins[i], 1);
	}
	
	/* Set selected digit low to enable digit */
	digital_out(digit_pins[digit_index], 0);
	
}

void display_digit(uint8_t digit, uint8_t digit_pos){
	
	/* Reset the counter */
	bcd_generate_pulses(1, DISP_RESET_PIN);
	
	/* generate the digit with pulses*/
	bcd_generate_pulses(digit, DISP_CLOCK_PIN);
	
	select_digit_pos(digit_pos);
	
}

/* WIP */
void display_number(uint16_t number){
	
	uint8_t digit1 = number % 10;
	
	if (number > 10){
		number /= 10;
	}
	else{
		display_digit(digit1, 1);
		return;
	}
	
	uint8_t digit2 = number % 10;
	
}

