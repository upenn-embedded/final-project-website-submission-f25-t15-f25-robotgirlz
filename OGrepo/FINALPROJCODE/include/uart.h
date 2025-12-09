#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdint.h>

void uart_init(uint32_t baud);
void uart_tx(uint8_t data);
void uart_print(const char *str);
uint8_t uart_rx_ready(void);
uint8_t uart_rx(void);

// Audio driver reset control
void audio_reset(void);

#endif
