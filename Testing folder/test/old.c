// #define F_CPU 16000000UL
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdio.h>
// #include <avr/interrupt.h>
// #include "ST7735.h"
// #include "LCD_GFX.h"
// #include "../include/i2cdriver.h"
// #include "../include/tempi2c.h"
// #include "wlLfuncction.h"

// #define BUTTON PC1

// #define TRIGGER1 PD1
// #define TRIGGER2 PD3
// #define TRIGGER3 PD4
// #define TRIGGER4 PD5

// uint8_t current_face = 0;
// int water_level_ml = 0;
// int temp = 0.0;
// int count = 0; 
// int PERIOD = 10;
// int newface = 0; // flag for if we change perosnalitie s

// void gpio_init(void)
// {
//     DDRC &= ~(1 << BUTTON);
    
//     // Speaker triggers
//     DDRD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);
//     PORTD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);
// }

// void timerinit(){
// TCCR3A |= 0x00;
// TCCR3B |= 0x00; // overflow interrupt enable
// TIMSK3 |= (1 << OCIE3A);    // clear the counter
// TCNT3 =0 ;  // scaler /8    f=16M/scaler/256/2 maybe change 
// TCCR3B |= (1 << CS32);
// }

// void play_audio(uint8_t track)
// {
//     if (track == 0) return; // DND in idle
    
//     switch (track)
//     {
//         case 1: PORTD &= ~(1 << TRIGGER1); break;
//         case 2: PORTD &= ~(1 << TRIGGER2); break;
//         case 3: PORTD &= ~(1 << TRIGGER3); break;
//         case 4: PORTD &= ~(1 << TRIGGER4); break;
//         default: return;
//     }
//     _delay_ms(2000);
//     PORTD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);
// }

// void show_face(void)
// {
//     switch(current_face)
//     {
//         case 0: display_happy_face(); break;
//         case 1: display_sad_face(); break;
//         case 2: display_angry_face(); break;
//         case 3: display_wink_face(); break;
//         case 4: display_idle_face(); break;
//     }
// }

// void display_info(void)
// {
//     char water_str[15];
//        char tmp[8];
//           sprintf(tmp, "%d deg", temp);
//     LCD_drawString(90, 60, tmp, WHITE, BLACK); // temp sensor not yet added
    
//     // Display water level from sensor
//     sprintf(water_str, "%d mL", water_level_ml);
//     LCD_drawString(90, 80, water_str, WHITE, BLACK);
// }
// ISR(TIMER3_OVF){
//     count+=1 ;
//     if(count > PERIOD){
//         count = 0 ;
//     }
// }
//  ISR(PCINT23_VECT){ 
//    current_face = (current_face +1) % 5;
// newface = 1;
   
// }

// int main(void)
// {
//     gpio_init();
//  timerinit();
//     adc_init(); // Initialize ADC for water level sensor
    
//     lcd_init();
//     _delay_ms(100);
//     LCD_brightness(200);

     
    
//     show_face();
//     display_info();
    

//     //I2C1_init(1);
// //tempint();
// _delay_ms(25);

    
//     while (1)
//     {
//         //cli();
//        //temp = (int)gettemp();
//        if(newface == 1){
//         show_face();
//         newface = 0;
//        }
//          if(count == PERIOD ){
            
//              if (current_face < 4) {
//                 play_audio(current_face + 1);

                  
//                            }
//              }
//              else{
//                  water_level_ml = mLWL(); 
      
//        //cli();
//         display_info(); 
//         //sei();

//              }
//              _delay_ms(100);

       
//         // if (PINC & (1 << BUTTON))
//         // {
//         //     current_face = (current_face + 1) % 5;
            
//         //     show_face();
//         //     display_info();
            
//         //     if (current_face < 4) {
//         //         play_audio(current_face + 1);
//         //     }
            
//         //     // _delay_ms(300);
//         //     // while (PINC & (1 << BUTTON));
//         // }
        
//         _delay_ms(100); // Small delay between readings
//     }
    
//     return 0;
// }