
#include "arduino_uno.h"
#include <stdint.h>
int main(void)
{
    
    setup();
    while(1)
    {
		led_on();
		wait(500);
		led_off();
		wait(500); 
    }
}