/*
 * dashboard.c
 *
 * Created: 2025-09-26 15:58:40
 *  Author: joela
 
 */

#include <stdint.h>
#include "dashboard.h"
 

Output parse_input(uint8_t *buffer){
	
	Output parsed_values = {0, 0, 0};
	uint8_t index = 0;
	uint8_t counter = 1;
	uint8_t *p = buffer;
	char temp_value[6] = {};
	
	
	while(*p){
		
		if(*p == ';' || *p == '\0'){
			temp_value[index] = '\0';
			if (counter <= 3 && index > 0){
				switch(counter){
					case 1:
						parsed_values.rpm = strtol(temp_value, 0, 10);
						break;
					case 2:
						parsed_values.gear = strtol(temp_value, 0, 10);
						break;
					case 3:
						parsed_values.speed = strtol(temp_value, 0, 10);
						break;
				}
			}
			
			counter++;
			index = 0;
		}
		else{
			if (index < sizeof(temp_value) - 1){
				
				temp_value[index++] = *p;
			}
		}
		
		p++;
	}
	return parsed_values;
}