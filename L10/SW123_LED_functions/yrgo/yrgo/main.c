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

    setup_p1();
    
    uint16_t led_blink_time_counter = 0;
    uint16_t led_blink_period = 5000;
    
    uint8_t led_dimmer_period = 50;
    uint16_t led_dimmer_time_counter = 0;
    uint8_t led_dimmer_duty_cycle = 0; 
    uint8_t led_dimmer_counter = 0;
    int8_t led_dimmer_direction = 1;   /* +1 is dimming up, -1 is dimming down */
    
    while(1) {
        
        /* Toggle LED1 periodically depending on when it was last toggled and status of SW1*/
        led_blink_time_counter++;
        if(sw1() && (led_blink_time_counter >= led_blink_period)){
                led_blink_time_counter = 0;
                led1_toggle();                                  
        }
        else if (!sw1()){
            led1(false);
        }
            
        led_dimmer_time_counter++;
        /* Increment a counter and change duty cycle to match*/
        if(sw2() && (led_dimmer_time_counter >= led_dimmer_period)){
            
                led_dimmer_time_counter= 0;
                   
                /* Raise or lower duty cycle with 1 depending on direction */
                led_dimmer_duty_cycle += led_dimmer_direction; 
                    
                if (led_dimmer_duty_cycle == 100){
                    led_dimmer_direction = -1;
                }
                else if (led_dimmer_duty_cycle == 0){
                    led_dimmer_direction = 1;
                }                                            
        }
        else if (!sw2()){
            led_dimmer_duty_cycle = 0;
            led_dimmer_direction = 1;
        }
                
        /* Run PWM (dimmer) */
        led_dimmer_counter++;
        if (led_dimmer_counter >= 100){
            led_dimmer_counter = 0;
        }
        led_dimmer_counter < led_dimmer_duty_cycle ? led2(true) : led2(false);
        
        /* Freeze all execution if SW3 is pressed
           Keep same PWM output going when frozen*/
        while(sw3()); 
            
        _delay_us(100);
    }
}       
