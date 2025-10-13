#include <avr/io.h>

#include "p1/P1.h"
#include <time.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    uint8_t led_number = 1;
    uint16_t led_timer = 0;
    uint8_t duty_cycle = 0;
    
    setup_p1();
    
    while(1) {
        
        uint16_t delay = 50 * read_pot1();
        uint16_t intensity = read_pot2() / 10;
        
        if (intensity > 100) intensity = 100; 
        
        led_timer++;
        
        if (!sw3())
        {                
            /* PWM */
            
            duty_cycle < intensity ? led(led_number, true) : led(led_number, false);
            
            duty_cycle++;
            
            if(duty_cycle >= 100) duty_cycle = 0;
            
        }

        if(!sw1() && led_timer >= delay){
            
            led(0, false);

            if (led_number > 3){
                led_number = 1;
            }            
            else if(led_number < 1) {
                led_number = 3;
            }            
            
            sw2() ? led_number-- : led_number++;
            led_timer = 0;
            duty_cycle = 0;
            
        }
        
        _delay_us(100);
        
    }
}