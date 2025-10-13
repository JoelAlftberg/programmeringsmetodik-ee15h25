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
    /*Use either setup_p0 OR setup_p1*/
    //setup_p0();
    setup_p1();
    while(1) {
        
        uint16_t pot_values[5] = {};
        
        uint16_t sum = 0;
        
        for(uint8_t i = 0; i < 5; i++){
            pot_values[i] = read_pot1();
            wait(10);
        }
        
        for(uint8_t i = 0; i < 5; i++){
            
            sum += pot_values[i];
            
        }
        
        uint16_t average_val = sum / 5;
        
        uint16_t chosen_val  = 1023;
        
        if(average_val > (chosen_val - 10)){
            led(1, true);
            led(2, false);
            led(3, false);
        }
        else if (average_val < (chosen_val + 10)){
            led(1, false);
            led(2, true);
            led(3, false);
        }
        else{
            led(1, false);
            led(2, false);
            led(3, true);
        }
        
        wait(100);

    }
}




    