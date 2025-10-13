#include <avr/io.h>

/*Include the correct header file */
#include "p1/P1.h"
#include <time.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>


int main(void)
{

    setup_p1();
    
    while(1) {
        
        for(uint8_t i = 0 ; i < 10; i++){
            
            uint16_t delay_1 = read_pot1();
            uint16_t delay_2 = read_pot2();
            set_number(i);
            
            relay_toggle();
            led1_toggle();
            led2_toggle();
            led3_toggle();
            
            if(sw1()){
                led(0, false);
                led1_toggle();
                wait(delay_2);
            }
            else if(sw2()){
                led(0, false);
                led2_toggle();
                wait(delay_2);
            }
            
            while(sw3()){
                
                uint16_t temp = read_temperature() / 100;
                set_number(temp);
                led3_toggle();      
                wait(delay_2);
           
            }
            
            wait(delay_1);
            led(0, false);
            wait(delay_1);
            
        }     
    }
}