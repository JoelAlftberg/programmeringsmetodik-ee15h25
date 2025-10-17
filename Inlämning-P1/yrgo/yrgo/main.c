#include <avr/io.h>

#include "p1/P1.h"
#include <util/delay.h>

int main(void)
{

    uint8_t led_number = 1;
    uint16_t led_timer = 0;
    uint16_t pot_timer = 0;
    uint8_t duty_cycle = 0;
    uint16_t delay = 0;
    uint16_t intensity = 0;

    setup_p1();
    
    while (1){

        led_timer++;
        pot_timer++;
        
        if (pot_timer >= 1500){

            delay = 50 * read_pot1();
            intensity = read_pot2() / 10;

            /* Clamp intensity so that duty cycle never goes over 100% */
            if (intensity > 100){
                intensity = 100;
            }

            pot_timer = 0;

        }
        
        if (!sw3()){
            
            /* PWM */
            duty_cycle < intensity ? led(led_number, true) : led(led_number, false);
            duty_cycle++;
            
            if (duty_cycle >= 100){
                duty_cycle = 0;
            }
            
        }

        /* LED cycling */
        if (!sw1() && led_timer >= delay){
            
            led(0, false);

            sw2() ? led_number-- : led_number++;

            if (led_number > 3){
                led_number = 1;
            }
            else if (led_number < 1){
                led_number = 3;
            }

            led_timer = 0;
            
        }
        
        _delay_us(20);
        
    }
}
