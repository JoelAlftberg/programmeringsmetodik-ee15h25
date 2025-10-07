#include <avr/io.h>

/*Include the correct header file */
#include "p0/P0.h"
#include "p1/P1.h"
#include <time.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
	
	uint8_t colors[6][3] = {
		{1, 0, 0}, // Red
		{1, 0, 1}, // Magenta
		{0, 0, 1}, // Blue
		{0, 1, 1}, // Cyan
		{1, 1, 0} // Yellow
	};

    setup_p1();
	
    while(1) {
		
		for(uint8_t i = 0; i < 6; i++){
			
	        for(uint8_t j = 0; j < 3; j++){
    	        led(j + 1, colors[i][j]);
	        }
			
			for(uint16_t delay_ms = 0; delay_ms < 1000; delay_ms++){
				while(sw1());
				wait(1);
			}	
            
		}
    }
}