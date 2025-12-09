// #define F_CPU 16000000UL
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdint.h>

// //
// // === AUDIO FX TRIGGER PINS ===
// // PB0 → Trigger 1 (Track 1)
// // PB1 → Trigger 2 (Track 2)
// // PB2 → Trigger 3 (Track 3)
// // PB3 → Trigger 4 (Track 4)
// //
// #define TRIGGER_DDR  DDRD
// #define TRIGGER_PORT PORTD

// #define TRIGGER1 PD1
// #define TRIGGER2 PD3
// #define TRIGGER3 PD4
// #define TRIGGER4 PD5

// // Pulse duration for trigger in milliseconds
// #define TRIGGER_PULSE_MS 2000

// //void trigger_play(uint8_t pin)

   

// int main(void)
// {
//     // Set PB0–PB3 as outputs
//     TRIGGER_DDR |= (1 << DDD1) | (1 << DDD3)| (1 << DDD4) |(1 << DDD5);
//     TRIGGER_PORT |= (1 << PORTD1) | (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5); // Start High

//    // _delay_ms(500); // Optional startup delay

//     while (1)
//     {
//         // Play Track 1
//          TRIGGER_PORT &= ~(1 << PORTD1);   // Set trigger LOW
//          _delay_ms(TRIGGER_PULSE_MS);  // Wait for minimum pulse
//          TRIGGER_PORT |= (1 << PORTD1);  // Reset trigger High
//         _delay_ms(3000);
//         // Play Track 2
        
//     }
// }
