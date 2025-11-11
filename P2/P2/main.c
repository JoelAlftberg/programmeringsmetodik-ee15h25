#include <avr/io.h>


/*Include the correct header file */
#include "p0/P0.h"
#include "p1/P1.h"
#include <time.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "include/display.h"
#include "include/dmm_mode.h"
#include "include/adc.h"

// display_buffer[0] = integer, display_buffer[1] = decimal, display_buffer[2] = decimal_point;

        
int main(void)
{
    setup_p0();
    
   /* 
   if d7 high -> Rset = 330 else if d8 -> high Rset = 33000
   
   Read from A0 - 16 samples with for loop (hope for some noise)
   average = divide A0 by 16
   voltage_read = average value * (5.0f / 1023.0f)
   R_measured = (voltage_read * R_set) / (5 - voltage_read);
   
   */
   
    uint16_t timer_counter = 0;
    uint8_t display_timer_counter = 0;
    uint8_t display_digit = 0;
    uint8_t number_iterator = 0;
    uint8_t mode = 1;
               
    while(1){
        
        if(timer_counter >= 2000){
            uint16_t raw = read_analog_adc(A0);
            display_buffer_update(raw);
            timer_counter = 0;  
        }
        
        // display send needs to be running continously on 5 ms timing (each digit will be updated once every 15ms)
        // iterate through digit_1, digit_2, digit_3
        if (display_timer_counter >= 5){
            display_buffer_send(digit_pins[display_digit]);
            display_digit++;
            if (display_digit > 2){
                display_digit = 0;
            }
        }
        
        timer_counter++;
        display_timer_counter++;
        _delay_us(100);
    }
        
        
        // if power just turned on, do some kind of starting sequence (init)
        // check the mode we are in
            // if mode has changed since last loop, display mode (ex U1 for low voltage, U2 for high voltage)
        
        // depending on mode, do appropriate math
        // handle number output by rounding and formatting
        // display number

}

