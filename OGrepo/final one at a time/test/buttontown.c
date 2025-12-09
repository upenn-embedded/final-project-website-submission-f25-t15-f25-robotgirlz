// /*
// * part_b.c
// * Interrupt-based LED control using Input Capture (ICP1, PB0)
// */
// #include <avr/io.h>
// #include <avr/interrupt.h>
// int main(void) {
// // --- Configure LED pin (on-board LED on PB5, Arduino "D13") as output
// DDRB |= (1 << PB5); // PB5 = output
// // --- Configure PB0 as input (ICP1)
// DDRB &= ~(1 << PB0); // PB0 = input
// PORTB |= (1 << PB0); // Enable internal pull-up
// // --- Configure Timer1 for Input Captur
// // --- Enable global interrupts

// while (1) {
//  if( PINB & (1<< PB0)){
//     PORTB |= (1<< PB5);
//  }
//  else{
//     PORTB &= ~(1<<PB5);
//  }


// }
// return 0;
// }
// // Input Capture Interrupt Service Routine
