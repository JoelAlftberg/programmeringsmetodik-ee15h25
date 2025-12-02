#include <avr/io.h>

/*Include the correct header file */
#include <time.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "include/display.h"
#include "include/adc.h"
#include "include/p2_math.h"
#include "include/timer.h"

#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define PATCH_VERSION 3

int main(void)
{
    uint8_t startup_flag = 1;
    volatile ready_flag = 0;
    
    uint8_t digit_counter = 0;
    
    uint8_t current_mode = 255;
    uint8_t mode = 255;
    uint32_t mode_switch_counter = 0;
    uint32_t samples_sum = 0;
    uint16_t sample_counter = 0;
    
    /* Firmware version */
    display_buffer_update(MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, 0);
    
    /* Do some initiation */ 
    init_sys_timer();
    init_p2_gpio();
    sei();
    
    while(1){   

        /* Update display if flag is set by ISR (should be set every 16.6 ms) */
        if (display_update_flag){
            display_update_flag = 0;
            display_update(&digit_counter);
        }
        
        /* Startup sequence */
        if (sys_tick >= 50000 && startup_flag == 1){
            ready_flag = 1;
            startup_flag = 0;
        }
        
        /* Check if device is ready and we want to check what mode is selected */
        if (check_mode_flag && ready_flag){
            mode = check_mode();
            check_mode_flag = 0;
        }
        
        /* If we just switched mode, display will show the mode as (_ _ x) for mode x during 1.5 seconds */
        if (current_mode != mode){
            
            display_buffer_update(0, 0, mode, 3);
            
            mode_switch_counter = sys_tick;
            current_mode = mode;

            ready_flag = 0;
         
        }
        
        /* Check if 1 second has elapsed since we switched mode, toggle so that we are ready to measure */
        if (!ready_flag && (sys_tick - mode_switch_counter) >= 1500){
            ready_flag = true;
        }
               
        if (ready_flag){
            
            switch (mode){


                case 1:
                {
                    samples_sum += read_analog_adc(A1);
                    sample_counter++;
                    if (sample_counter == 256){
                        uint16_t average_reading = samples_sum >> 4;

                        uint16_t voltage_mv = calculate_millivolt(average_reading);
                        uint8_t factor = (gpio_digital_read(0) ? 7 : 1);
                        voltage_update_buffer(voltage_mv, factor);
                        sample_counter = 0;
                        samples_sum = 0;
                    }
                    break;
                }
                case 2:
                {
                    samples_sum += read_analog_adc(A1);
                    sample_counter++;
                    if (sample_counter == 256){
                        uint16_t average_reading = samples_sum >> 4;
                        
                        uint16_t voltage_mv = calculate_millivolt(average_reading);
                        uint32_t resistance = calculate_resistance(voltage_mv, 330);
                        resistance_update_buffer(resistance);
                        sample_counter = 0;
                        samples_sum = 0;
                    }
                    break;                   
                }
                case 3:
                {
                    samples_sum += read_analog_adc(A1);
                    sample_counter++;
                    if (sample_counter == 256){
                        uint16_t average_reading = samples_sum >> 4;
                        
                        uint16_t voltage_mv = calculate_millivolt(average_reading);
                        uint32_t resistance = calculate_resistance(voltage_mv, 33000);
                        resistance_update_buffer(resistance);
                        sample_counter = 0;
                        samples_sum = 0;
                    }
                    break;
                }
                case 4:
                {
                    display_buffer_update(4,4,4,3);
                }                                     
            }                 
        }
        
    }
        
}