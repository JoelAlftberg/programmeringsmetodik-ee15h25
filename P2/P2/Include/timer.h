/*
 * timer.h
 *
 * Created: 2025-11-18 09:34:06
 *  Author: joela
 */ 


#ifndef TIMER_H_
#define TIMER_H_

extern volatile uint32_t sys_tick;
extern volatile uint8_t frame_update_tick;
extern volatile check_mode_tick;
extern volatile display_update_flag;
volatile uint8_t check_mode_flag;

void init_sys_timer();

#endif /* TIMER_H_ */