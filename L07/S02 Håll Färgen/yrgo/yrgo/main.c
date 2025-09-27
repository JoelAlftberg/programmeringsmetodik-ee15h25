#include <avr/io.h>

/*Include the correct header file */
#include "p0/P0.h"
#include "p1/P1.h"
#include <time.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void blink_led(uint8_t led_number, uint8_t blink_times, uint16_t wait_ms){
	
	led(0, false);
	
	for(uint8_t i = 0; i < blink_times; i++){
		led(led_number, true);
		wait(wait_ms);
		led(led_number, false);
		wait(wait_ms);
	}
	
}

bool wait_input(uint16_t ms_to_wait, bool (*button)(void)){
	
	for(uint16_t i = 0; i < ms_to_wait; i++){
		
		if(button()){
			return true;
		}
		wait(1);
	}
	
	return false;
	
}

uint8_t game_wait_for_player(void){
	
	while (1){
		
		for(uint8_t i = 1; i < 4; i++){
			
			led(i, true);
			
			if(wait_input(500, sw1)){
				return i;
			}
			
			led(i, false);
			wait(500);
			
			}		
	}
}

void game_wait_start(uint8_t player_selected_led){
	
	// Wait for player input to start game, light all three LEDs
		wait(500);
		while(1){
			led(0, false);
			if(wait_input(300, sw3)){
				break;
			}
			led(player_selected_led, true);
			if(wait_input(300, sw3)){
				break;
			}
			led(player_selected_led, false);
			if(wait_input(300, sw3)){
				break;
			}
			led(0, true);
			if(wait_input(500, sw3)){
				break;
			}
		}
		
		// Player started game, blink all LEDs
		for(int i = 0; i < 3; i++){
			led(0, false);
			wait(200);
			led(0, true);
			wait(200);
		}
	
}

void game_loop(uint8_t player_selected_led){
	
	
	uint16_t difficulty_levels[10] = {800, 600, 500, 400, 300, 200, 175, 150, 125, 100};
		
	srand(time(0));
	
	wait(500);
	
	led(0, false);
	
	for(uint8_t curr_level = 0; curr_level < 10; curr_level++)
	{			
		while(1){

			// blink one of the three LEDs
			int random_led = (rand() % 3) + 1;
			led(random_led, true);
			
			// give player time according to difficulty to select the LED
			if(wait_input(difficulty_levels[curr_level], sw1)){
				if(random_led != player_selected_led){
					blink_led(1, 3, 300);
					return;
				}
				else{
					blink_led(2, 3, 300);
					break;
				}
			}
			
			led(random_led, false);
			if(wait_input(difficulty_levels[curr_level], sw1)){
				if(random_led != player_selected_led){
					blink_led(1, 3, 150);
					return;
				}
				else{
					blink_led(2, 3, 150);
					break;
				}
			}
		}
	}
	
	//victory!
	for (uint8_t i = 0; i < 3; i++){
		for(uint8_t j = 1; j < 4; j++){
			led(0,false);
			blink_led(j, 1, 300);
		}
		for(uint8_t k = 3; k > 0; k--){
			led(0,false);
			blink_led(k, 1, 300);
		}
	}
}

int main(void)
{
    /*Use either setup_p0 OR setup_p1*/
    //setup_p0();
    setup_p1();
    while(1) {
		
		uint8_t selected_led = game_wait_for_player();
		game_wait_start(selected_led);
		game_loop(selected_led);
		
		
    }
}

// run color selector
// if button is pressed -> start game and check what color was pressed
//