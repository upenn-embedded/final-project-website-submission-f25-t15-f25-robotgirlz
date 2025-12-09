// #include <avr/io.h>
// #include <util/delay.h>
// #include "uart.h"     // You already have this
// #include "i2cdriver.h" // Change to your header file name

// void I2C0_scan_bus(void) {

//     for (uint8_t addr = 1; addr < 127; addr++) {

//         // Send START
//         TWCR0 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
//         while (!(TWCR0 & (1<<TWINT)));

//         // Load SLA+W
//         TWDR0 = (addr << 1);   // Write mode
//         TWCR0 = (1<<TWINT)|(1<<TWEN);
//         while (!(TWCR0 & (1<<TWINT)));

//         uint8_t status = TWSR0 & 0xF8;

//         // STOP
//         TWCR0 = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

//         // Check ACK
//         if (status == 0x18) {   // MT_SLA_ACK
//             uart_print("Found device at address: 0x");
//             uart_print("\r\n");
//         }
//     }

//     uart_print("Scan complete.\r\n");
// }

// int main(void) {
//     uart_init(9600);
//     I2C0_init(100000);  // 100kHz

//     _delay_ms(100);

//     I2C0_scan_bus();

//     while (1) {
//         // nothing
//     }
// }
// // 