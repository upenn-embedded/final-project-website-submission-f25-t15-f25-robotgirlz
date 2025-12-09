
// #include <avr/io.h>
// #include <util/delay.h>
// #include "../include/tempi2c.h"
// #include "../include/uart.h"
// #include "../include/wlLfuncction.h"


// int main(void){
//    char tmp[64];
//     char str[64];
//     //DDRC &= ~((1 << PC5) | (1 << PC4));  // Inputs

//     //PORTC &= ~((1 << PC5) | (1 << PC4)); // No internal pull-ups
 

//     uart_init(9600);
//     I2C1_init(10000);
//     uint8_t cntrolregnumbe[2];
//      I2C1_readfromregister(Taddr,REG_CTRL,cntrolregnumbe,2);
//      _delay_ms(10);
//      tempint();
//  
//     //calibrate();
//     while(1){
//        
//     gettemp();
//      sprintf(tmp,"temp is %.2f\r\n",gettemp());
//      uart_print(tmp);
//      _delay_ms(500);
//     }
    
// }



