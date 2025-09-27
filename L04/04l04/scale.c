#include <stdio.h>
#include <stdint.h>
#include "scale.h"

/********************************************************
* Function name: scale_uint16 (uint16_t value, uint16_t min_in, uint16_t  max_in, uint16_t min_out, uint16_t  max_out)
* parameter 1: value, the value to be scaled
* parameter 2: min_in, the smallest possible input value
* parameter 3: max_in, the largest possible input value
* parameter 4: min_out, the smallest possible output value
* parameter 5: max_out, the largest possible output value
* Return: uint16_t
* Description:
* Scales the value in parameter 1 to fall into the range beetween min_out and max_out
* Returns the value 0 if the value of the min parameters are set above the max parameters
********************************************************/
uint16_t scale_uint16(uint16_t value, uint16_t min_in, uint16_t max_in, uint16_t min_out, uint16_t  max_out){

	/* Protects against cases where the min value is above the max value for both input and output*/

	if ( (min_in > max_in) || (min_out > max_out) || (value > max_in) ){
		return 0;
	}
	
	return value / (uint16_t) ((max_in - min_in) / (max_out - min_out));
	
}


int main(void){

	uint16_t scale_value = scale_uint16(239, 100, 500, 20, 9816);
	printf("Scaled value: %d\n", scale_value);
	
	return 0;
	
}