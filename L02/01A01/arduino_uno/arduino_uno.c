#define F_CPU 16000000UL // 16 MHz klockfrekvens.

#include <avr/io.h>
#include <util/delay.h>

void setup(void) {
    /*s�tt bit 5 i register DDRB till h�g, detta g�r att utg�ng 5 p� port B hanteras som en utg�ng*/
    DDRB = (1 << 5);
}

/************************************************************************/
/* Function Name: wait(int ms)                                          */
/* parameter: int ms, milliseconds to wait                              */
/* Return: void                                                         */
/* Description:                                                         */
/* The program waits xxxx of milliseconds                               */
/************************************************************************/
void wait(int milliseconds) {
    for (int i = 0;i<milliseconds;i++) {
        _delay_ms(1);
    }
}



/************************************************************************/
/* Function Name: led_on                                                */
/* parameter: void                                                      */
/* Return: void                                                         */
/* Description:                                                         */
/* Turn on the internal led on the arduino uno                          */
/************************************************************************/
void led_on(void) {
    PORTB |= (1 << 5);
}



/************************************************************************/
/* Function Name: led_off                                               */
/* parameter: void                                                      */
/* Return: void                                                         */
/* Description:                                                         */
/* Turn off the internal led on the arduino uno                         */
/************************************************************************/
void led_off(void) {
    PORTB &= ~(1 << 5);
}


