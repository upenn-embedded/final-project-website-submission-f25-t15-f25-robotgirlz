#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

//
// === UART SETUP (PD0 = RX, PD1 = TX) ===
//
void uart_init(void)
{
    uint16_t ubrr = (F_CPU / (16UL * 9600UL)) - 1;

    //baud rate register
    UBRR0H = (ubrr >> 8); // high 8 bits (upper)
    UBRR0L = (ubrr & 0xFF); // low 8 bits (lower)

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);     // enable RX & TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // 8-bit, 1 stop, no parity
}

/* We send a character to the UART Data Register (UDR0) because:
- UDR0 is the only place the microcontroller checks for outgoing data
- Writing to UDR0 tells the UART hardware: “Send this byte out the TX pin.”
- The UART hardware then performs the entire serial transmission automatically
- Without writing to UDR0, nothing would be transmitted.*/
void uart_send_char(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // wait until UART data register is empty
    UDR0 = c; //send the character by putting it into the data register
}

// Used for sending the command telling the audio driver WHAT to play.
void uart_send_str(const char *s)
{
    while (*s)
        uart_send_char(*s++);
}

//
// === AUDIO DRIVER CONTROL ===
// PB0 is connected to the Audio Driver "RST" pin
//
#define AUDIO_RST_DDR   DDRB
#define AUDIO_RST_PORT  PORTB
#define AUDIO_RST_PIN   PB0

void audio_reset(void)
{
    AUDIO_RST_DDR |= (1 << AUDIO_RST_PIN);  // PB0 output

    // Active-low reset: pull low briefly
    AUDIO_RST_PORT &= ~(1 << AUDIO_RST_PIN);
    _delay_ms(10);

    AUDIO_RST_PORT |= (1 << AUDIO_RST_PIN); // release reset
    _delay_ms(250); // allow Audio Driver to boot
}

//
// === AUDIO PLAY FUNCTIONS ===
//

void audio_play_track(uint8_t n)
{
    // Format: #n\n
    uart_send_char('#'); // play by track number
    uart_send_char('0' + n); // the track number
    uart_send_char('\n'); //end of command
}

void audio_play_filename(const char* fname)
{
    uart_send_char('P');     // filename play command
    uart_send_str(fname);    // 8.3 filename without dot
    uart_send_char('\n');
}

//
// === MAIN ===
//
int main(void)
{
    uart_init();
    audio_reset();

    _delay_ms(500);

    // Play track 1 (001.WAV)
    audio_play_track(1);
    _delay_ms(3000);

    // Play a file by name (HELLO.WAV)
    audio_play_filename("HELLOWAV");
    _delay_ms(5000);

    // Loop example: alternating tracks
    while (1)
    {
        audio_play_track(2);
        _delay_ms(5000);

        audio_play_track(3);
        _delay_ms(5000);

        audio_play_filename(4); // play another file by name
        _delay_ms(5000);
    }
}
