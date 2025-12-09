//include headers and whatnot 

#include <../Display/LCD_GFX.c>
#include <../Display/ST7735.h> 
#include <../lib/functions.h>
#include "../include/i2cdriver.h"
#include <../include/tempi2c.h>
#include "../include/wlLfuncction.h"

#define BUTTON PC1

#define TRIGGER1 PD0
#define TRIGGER2 PD1
#define TRIGGER3 PD2
#define TRIGGER4 PD3

//VARIABLE DECS 
/*int deg = 70 ;
int wL0 = 0 ;
int wL = 0 ;
int CAP = 20000;
int refillcount = 0;
int wtot1 = (refillcount*CAP)+(CAP-wL); // weird and silly 
int wtot0= 0; */

int PERIOD = 1000; 
//time between reminders determined by timer set up frequency and clock overflow rate 

//GPIO initializaiton 

void gpio_init(void)
{
    // Button input
    DDRC &= ~(1 << BUTTON);
    
    // Speaker triggers as outputs
    DDRD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);
    PORTD |= (1 << TRIGGER1) | (1 << TRIGGER2) | (1 << TRIGGER3) | (1 << TRIGGER4);
}
//DDRC &= ~(1<<DDC0);//set PC0 input change audio button 
 


//I2C initialization in I2c driver file run I2C int in main file for initialization process 
//I2C pin iniitalizations are set when teh TWEN is set 
 


//timer initialization
//Timer3--Normal mode
void timerinit(){
TCCR3A |= 0x00;
TCCR3B |= 0x00; // overflow interrupt enable
TIMSK3 |= (1 << OCIE3A);    // clear the counter
TCNT3 =0 ;  // scaler /8    f=16M/scaler/256/2 maybe change 
TCCR3B |= (1 << CS32);
}

//timer overflow counter 
 
ISR(TIMER3_OVF){
    count+=1 
    if(count > PERIOD){
        count = 0 
    }
}
ISR(PCINT8){
    //personality change 
    // change face displayed at reminder 
    //change audio file 
}
ISR(PCINT9){
    // DND no yell mode turn off the reminders 
    // set yell flag off 
}
//Audio driver initialization 

// DATA RECEIVE FUNCTIONS in their sensors respective header file 




//ACCUATOR FUNCTIONS 
void display_info(float temp,int wl)
{    char tmp[16];
    char ml[16];
    sprintf(tmp,"deg: %.2f\r\n", temp);
    sprintf(ml,"ml: %d\r\n", ml);
    LCD_drawString(90, 60, tmp, WHITE, BLACK); //temp sensor not yet added
    LCD_drawString(90, 80, ml, WHITE, BLACK); //water level sensor not yet added
}

void yell(){
   // cases : 
    
}

int main(){
    gpio_init();
    timerinit();
    I2C0_init(10000);
     tempint();
    adc_init();
    while (1){
        cli();
        gettemp();
        mLWL();
        sei();
        display_info(gettemp(),display(mLWL))
      /* int cli(); // usuage guide said the quick timing means we shgfjfvnjmku,il hb nt.b,hmy.kmkn,lko colors time 
        LEDupdate();*/
      
        if(count == PERIOD ){
            if (0< wtot0-wtot1< 250){
                //=========play the audio file pls ===
                  PORTB &= ~(1 << PORTB0);   // Set trigger LOW play sound 
         _delay_ms(1500);  // Wait for it to play 
    
         PORTB |= (1 << PORTB0);  // Reset trigger High stop playing sound 
                face();
                blink(); // dont do if hard
            }
            else if (wtot0-wtot1> 250){//nohting no rmeider 
                }
                
            else if(wtot0- wtot1 < 0 ) {
                refil ++

            }
            else {}
}
       // drawchar (getttemp) //replace with functions that actually display the numbers 
        drawwL();
        
    }
}









