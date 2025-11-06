#include <avr/io.h>

#include "p1/P1.h"
#include <util/delay.h>

int main(void)
{

    /*Deklarerar statusvariabler som håller koll på knappens aktuella status*/

    setup_p1();
    
    bool switch1_pressed = false;
    bool switch1_toggle_status = false;
    bool switch2_pressed = false;
    bool switch2_toggle_status = false;
    bool switch3_pressed = false;
    bool switch3_toggle_status = false;
    uint8_t number = 0;

    while(1) {
        
        /*Hanterar toggelfunktion för switch 1*/
        if(sw1() && !switch1_pressed){
            /*Inverterar värdet på variabeln switch1_toggle_status */
            switch1_toggle_status = !switch1_toggle_status;
            switch1_pressed = true;
            number++;

        }
        else if(!sw1() && switch1_pressed){
            switch1_pressed = false;
        }

        /*Hanterar toggelfunktion för switch 2*/
        if(sw2() && !switch2_pressed){
            _delay_us(50);
            if(sw2()){
                /*Inverterar värdet på variabeln switch2_toggle_status */
                switch2_toggle_status = !switch2_toggle_status;
                switch2_pressed = true;
                number++;
            }
            else{
                _delay_us(50);
            }
        }
        else if(!sw2() && switch2_pressed){
            switch2_pressed = false;
            _delay_us(300);
        }

        if(sw3() && !switch3_pressed){
            _delay_us(50);
            /*Inverterar värdet på variabeln switch2_toggle_status */
            if(sw3()){
                switch3_toggle_status = !switch3_toggle_status;
                switch3_pressed = true;
                number++;   
            }
            else{
                _delay_us(50);  
            }            
        }
        else if(!sw3() && switch3_pressed){
            switch3_pressed = false;
            _delay_us(300);
        }
        
        /*Tänder LED varannan gång man trycker på sw1 och 2*/
        led1(switch1_toggle_status);
        led2(switch2_toggle_status);
        led3(switch3_toggle_status);
        set_number(number);
        if (number > 9){
            number = 0;
        }         

     
     }            

}
