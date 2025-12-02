/*
 * timer.c
 *
 * Created: 2025-11-18 08:40:08
 *  Author: joela
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t sys_tick = 0;
volatile uint8_t frame_update_tick = 0;
volatile uint16_t check_mode_tick = 0;

volatile uint8_t display_update_flag = 1;
volatile uint8_t check_mode_flag = 1;

ISR(TIMER1_COMPA_vect){

    sys_tick++;
    
    frame_update_tick++;
    
    check_mode_tick++;
    
    // 166 * 100 microseconds = 16.6 ms
    if (frame_update_tick >= 55) {
        frame_update_tick = 0;
        display_update_flag = 1;
    }
    
    if (check_mode_tick >= 10){
        check_mode_tick = 0;
        check_mode_flag = 1;
    }
    
}

void init_sys_timer(){
    
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12);   
    
    OCR1A = 199; // 1 tick = 0.5 microseconds -> 200 ticks = 100 microseconds
    
    TCCR1B |= (1 << CS11); // pre-scaler 8
    
    TIMSK1 |= (1 << OCIE1A); // Enable timer interrupt
    
}

void init_real_time_clock(){
    
}
