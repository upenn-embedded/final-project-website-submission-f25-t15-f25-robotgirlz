
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ST7735.h"
#include "LCD_GFX.h"

static void hardware_init(void){
    lcd_init();  
    _delay_ms(100);  
    LCD_brightness(200);
}

int main(void) {
    hardware_init();
    
    uint8_t current_face = 0; 
    
    while (1) {
        switch(current_face) {
            case 0: 
                display_happy_face(); break; 
            case 1: 
                display_sad_face(); break;  
            case 2: 
                display_angry_face(); break;
            case 3: 
                display_wink_face(); break;
            case 4: 
                display_idle_face(); break;
        }
        
       
        _delay_ms(3000);
        
        
        current_face = (current_face + 1) % 5;
    }
    
    return 0;
}