/*
 * timer_and_isr_exercise.c
 *
 * Created: 2025-10-02 10:56:39
 * Author : joela
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void init_timer(){

	TCNT0 = 0x00;			/* Set starting counter to 0 */
	TCCR0A = (1 << WGM01);	/* CTC Mode */
	TCCR0B = (1 << CS02);	/* Set pre-scaler to 256 */
	OCR0A = 0x7D; /* Set Output Compare Register to 124 */
}

int main(void)
{

	DDRB |= (1<<PORTB2); /* Enable output on pin d2 */
	
	/* OCF0A Flag getting set when counter reaches 0x7D */
	init_timer();

    /* Replace with your application code */
    while (1) 
    {
		uint8_t counter_flag = TIFR0 & (1 << OCF0A);
		
	
		
    }
}

