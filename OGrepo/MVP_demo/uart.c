#include "uart.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// Audio driver reset pin (change PB0 if needed)
#define AUDIO_RST_DDR   DDRB
#define AUDIO_RST_PORT  PORTB
#define AUDIO_RST_PIN   PB0

void uart_init(uint32_t baud)
{
    uint16_t ubrr = (F_CPU / (16UL * baud)) - 1;

    // Set baud rate
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;

    // TX (PD1) output, RX (PD0) input
    DDRD |= (1 << PD1);
    DDRD &= ~(1 << PD0);

    // Enable TX & RX
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Frame: 8 data, no parity, 1 stop
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)));   // wait for buffer empty
    UDR0 = data;
}

void uart_print(const char *str)
{
    while (*str)
    {
        uart_tx(*str++);
    }
}

uint8_t uart_rx_ready(void)
{
    return (UCSR0A & (1 << RXC0));
}

uint8_t uart_rx(void)
{
    while (!uart_rx_ready());
    return UDR0;
}

void audio_reset(void)
{
    AUDIO_RST_DDR |= (1 << AUDIO_RST_PIN);    // set pin as output
    AUDIO_RST_PORT &= ~(1 << AUDIO_RST_PIN);  // pull low
    _delay_ms(10);

    AUDIO_RST_PORT |= (1 << AUDIO_RST_PIN);   // release
    _delay_ms(250);                            // allow audio board to boot
}
