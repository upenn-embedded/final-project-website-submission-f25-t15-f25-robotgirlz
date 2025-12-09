
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <wlLfuncction.h>
// it will get the distnce and convert it to ml 

//ADC initialization -- stealing from lab 4 and adjusting 
// ====== ADC ======
void adc_init(void){
    ADMUX  = (1<<REFS0)|(1<<REFS1);   // use 1.1 refernce voltage   
    ADCSRA = (1<<ADEN) | 7;   //ADC enable and prescaler = 128
}

uint16_t adc_read(uint8_t ch){ // ch is the channel number 
    ADMUX  = (ADMUX & 0xF0) | (ch & 0x0F); // keep left side set the right side 
    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC));
    uint16_t v = ADC;
    return v;
}




int mLWL(){
    uint16_t lvl0;
    uint16_t lvl1;
    uint16_t lvl2;
    uint16_t lvl3;
    uint16_t lvl4;


    lvl0 = adc_read(0);
    lvl1 = adc_read(1);
    lvl2 = adc_read(2);
    lvl3 = adc_read(3);
    lvl4 = adc_read(4); 

    uint16_t lvltot = lvl0+lvl1+lvl2+lvl3+lvl4;

    float ml = .391*((float)lvltot); // scale the voltage with the water level 0 = 0 adn mmax adc read(5115) = 2000ml
if (ml < 0){
    ml = 0;
}
    return (int)ml;
    //updates variable wL0 
    //something like 
   //"stores" prvious wL as wL0 

    //I2C grabbing situation 
    //returns variable wL
    // 
} //read the waterlevel and convert to ml 