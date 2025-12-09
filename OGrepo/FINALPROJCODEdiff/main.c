//include headers and whatnot 

#include <lib/LCD_GFX.h>
#include <lib/ST7735.h> 
#include <functions.h>


//VARIABLE DECS 
int deg = 70 ;
int wL0 = 0 ;
int wL = 0 ;
int CAP = 20000;
int refillcount = 0;
int wtot1 = (refillcount*CAP)+(CAP-wL); 
int wtot0= 0; 

int PERIOD = 1000; //time between reminders determined by timer set up frequency and clock overflow rate 

//GPIO initializaiton 
DDRC &= ~(1<<PORTC0);//set PC0 input change audio button 
DDRC &= ~(1<<PORTC1);//set PC1 in[ut dnd button 

//I2C initialization in I2c driver file run I2C int in main file for initialization process 
//I2C pin iniitalizations are set when teh TWEN is set 
// set PC4 temp i2c input 
//set PC5 temp 12C clock 
// 
//set PE0 wl i2c data                       // maybe these i2c pin initializatoins are in the header doesn't matter as long as theyre somewhere 
// set PE1 wl i2c clock

//set LED output pin PD3 -- may have to change for PWM reasons (or maybe we be silly and just pin toggle a signal )

// SPI INITIALIZATION 
 


//timer initialization
//Timer3--Normal mode
TCCR3A = 0x00;
TCCR3B = 0x00;

    // overflow interrupt enable
TIMSK3 |= (1 << TOIE1);

    // clear the counter
TCNT3 = 0;

    // scaler /8    f=16M/scaler/256/2 maybe change 
TCCR3B |= (1 << CS32);

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




//ACCUATOR FUNCTIONS in the functions header 


int main(){
    while (1){
        gettemp();
        int cli(); // usuage guide said the quick timing means we should not have iteruppts during the colors time 
        LEDupdate();
      
        if(count == PERIOD ){
            getwL()
            if (0< wtot0-wtot1< 250){ 
                yell();
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
        Drawtemp();
        drawwL();
        int sei;
    }
}









