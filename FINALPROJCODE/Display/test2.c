#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ST7735.h"
#include "LCD_GFX.h"

#define BUTTON PC1

int main() {
    lcd_init();
    _delay_ms(100);
    LCD_brightness(200);
    DDRC &= ~(1 << BUTTON);

    uint8_t face = 0;

    display_happy_face();
            LCD_drawString(90, 60, "45 deg", WHITE, BLACK);
            LCD_drawString(90, 80, "2 L", WHITE, BLACK);

    while (1) {
            
        
        if (PINC & (1 << BUTTON)) {
            face = (face + 1) % 5;
            switch (face) {
                case 0: display_happy_face(); break;
                case 1: display_sad_face(); break;
                case 2: display_angry_face(); break;
                case 3: display_wink_face(); break;
                case 4: display_idle_face(); break;
            }
            
        LCD_drawString(90, 60, "45 deg", WHITE, BLACK);
        LCD_drawString(90, 80, "2 L", WHITE, BLACK);
           
                        
            _delay_ms(300);
            while (PINC & (1 << BUTTON)); 
        }
    }
}
