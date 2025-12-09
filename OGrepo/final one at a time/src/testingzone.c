#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "ST7735.h"
#include "LCD_GFX.h"
#include "uart.h"
#include "wlLfuncction.h"
#include "i2cdriver.h"
#include "tempi2c.h"

#define BUTTON PD7
#define TRIGGER1 PD1
#define TRIGGER2 PD3
#define TRIGGER3 PD4
#define TRIGGER4 PD5
#define LED_BLUE PE2
#define LED_RED PE3

uint8_t current_face = 0;
int count = 0;
int countflag  = 0;
int PERIOD = 50;
int water_level_ml = 0;
float temperature_c = 0.0;

void gpio_init(void)
{    
    DDRD &= ~(1 << BUTTON);   
    PORTD |= (1 << BUTTON);   // Enable pull-up for button
    
    DDRD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);
    PORTD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);

    DDRE |= (1<<LED_BLUE) | (1<<LED_RED);
}
void timerinit(){
TCCR3A |= 0x00;
TCCR3B |= 0x00; // overflow interrupt enable
TIMSK3 |= (1 << TOIE3);    // clear the counter
TCNT3 =0 ;  // scaler /8    f=16M/scaler/256/2 maybe change 
TCCR3B |= (1 << CS32);
}

//timer overflow counter 
 
ISR(TIMER3_OVF_vect){
    count+=1;
}
void play_audio(uint8_t track)
{
    if (track == 0) return;
    switch (track)
    {
        case 1: PORTD &= ~(1 << TRIGGER1); break;
        case 2: PORTD &= ~(1 << TRIGGER2); break;
        case 3: PORTD &= ~(1 << TRIGGER3); break;
        case 4: PORTD &= ~(1 << TRIGGER4); break;
        default: return;
    }
    _delay_ms(2000);
    PORTD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);
}

void show_face(void)
{
    switch(current_face)
    {
        case 0: display_happy_face(); break;
        case 1: display_sad_face(); break;
        case 2: display_angry_face(); break;
        case 3: display_wink_face(); break;
        case 4: display_idle_face(); break;
    }
}

void display_info(void)
{
    char buffer[22];

    LCD_drawBlock(90, 60, 159, 90, BLACK);
    
    sprintf(buffer, "%.1f C", temperature_c);
    LCD_drawString(90, 60, buffer, WHITE, BLACK);
    
    sprintf(buffer, "%d mL", water_level_ml);
    LCD_drawString(90, 80, buffer, WHITE, BLACK);
}

int main(void)
{ 
//      char tmp[16];
//     char str[16];
//   char cnt[16];
 
    timerinit();
   //uart_init(9600);
    gpio_init();
    I2C1_init(10000);
    tempint();
    adc_init();
    
    lcd_init();
    _delay_ms(200);         
    LCD_brightness(200);
    
    show_face();
    display_info();
   sei();
   int wl0 = mLWL();
    
    while (1)
    {    cli();
        water_level_ml = mLWL();
        if((0 < (int)gettemp()) & ((int)gettemp() < 100)){
        temperature_c  = gettemp();
        }
        sei();
    //     sprintf(tmp,"temp is %.2f\r\n",gettemp());
    //      sprintf(str,"displayed %.2f\r\n",temperature_c);
    //   uart_print(tmp);
    //   uart_print(str);
        if (temperature_c > 30)
        {
            PORTE &= ~(1<< LED_BLUE);
            PORTE |= (1<< LED_RED);
        }   

        else
        {
            PORTE &= ~(1<< LED_RED);
            PORTE |= (1<<LED_BLUE);            
        }
    

        display_info();  
            //  sprintf(cnt,"count %d\r\n",count);
            //  uart_print(cnt);
        if(count > PERIOD){
        countflag = 1;
        count = 0 ;
    }
          if(countflag == 1){
            if ((water_level_ml > wl0 -250)){
            if (current_face < 4){
            play_audio(current_face + 1 );
            }
            _delay_us(20);
            countflag = 0;
            

        }
        wl0 = water_level_ml;
    }
        
       // if (!(PIND & (1 << BUTTON)))   
       // {
           // _delay_ms(40);     
            if (!(PIND & (1 << BUTTON)))
            {
                current_face = (current_face + 1) % 5;
                show_face();
                display_info();  
                
                // if (current_face < 4)
                //     play_audio(current_face + 1);
                
                while (!(PIND & (1 << BUTTON))); 
                _delay_ms(20);
            }
        //}
       
        //_delay_ms(200);  
        display_info();
    }
    return 0;
}