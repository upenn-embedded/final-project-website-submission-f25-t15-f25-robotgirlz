Chat I2C 


#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL // frequency 

// ======== I²C (TWI) Status Codes ========
#define START           0x08
#define REP_START       0x10
#define MT_SLA_ACK      0x18
#define MT_DATA_ACK     0x28
#define MR_SLA_ACK      0x40
#define MR_DATA_ACK     0x50
#define MR_DATA_NACK    0x58


// ======== Error Handler (simple) ========
void ERROR(void) {
    
    while (1); // its just a loop rn but itll be print
}

// ======== I²C Initialization ========
void I2C0_init(uint32_t scl_freq_hz) {
   
    TWSR0 = 0x00; // Prescaler = 1
    TWBR = ((F_CPU / scl_freq_hz) - 16) / 2; // From datasheet
    TWCR0 = (1 << TWEN); // Enable TWI
}

// ======== START Condition ========
void I2C0_start(void) {
    TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));
    if ((TWSR0 & 0xF8) != START)
        ERROR();
}

// ======== Repeated START ========
void I2C0_repeated_start(void) {
    TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));
    if ((TWSR0 & 0xF8) != REP_START)
        ERROR();
}

// ======== STOP Condition ========
void I2C0_stop(void) {
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    // No need to check status; STOP doesn’t update TWSR
}

// ======== Write a Byte to Bus ========
void I2C0_write_byte(uint8_t data) {
    TWDR = data;
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));
    if ((TWSR0 & 0xF8) != MT_DATA_ACK)
        ERROR();
}

// ======== Write (SLA+W) and Bytes ========
void I2C0_write_bytes(uint8_t addr, uint8_t *data, uint8_t length) {
    // Send START
    I2C0_start();

    // Send SLA+W
    TWDR = (addr << 1) | 0;  // Write mode
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));
    if ((TWSR0 & 0xF8) != MT_SLA_ACK)
        ERROR();

    // Send all data bytes
    for (uint8_t i = 0; i < length; i++) {
        TWDR = data[i];
        TWCR0 = (1 << TWINT) | (1 << TWEN);
        while (!(TWCR0 & (1 << TWINT)));
        if ((TWSR0 & 0xF8) != MT_DATA_ACK)
            ERROR();
    }

    // Send STOP
    I2C0_stop();
}

// ======== Read One Byte with ACK or NACK ========
uint8_t I2C0_read_byte(uint8_t ack) {
    if (ack) {
        // Send ACK after receive
        TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    } else {
        // Send NACK (last byte)
        TWCR0 = (1 << TWINT) | (1 << TWEN);
    }

    while (!(TWCR0 & (1 << TWINT)));

    return TWDR;
}

// ======== Read (SLA+R) and Multiple Bytes ========
void I2C0_read_bytes(uint8_t addr, uint8_t *data, uint8_t length) {
    // Send START
    I2C0_start();

    // Send SLA+R
    TWDR = (addr << 1) | 1;  // Read mode
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));
    if ((TWSR0 & 0xF8) != MR_SLA_ACK)
        ERROR();

    // Read (length - 1) bytes with ACK
    for (uint8_t i = 0; i < (length - 1); i++) {
        data[i] = I2C0_read_byte(1); // ACK after each
    }

    // Read last byte with NACK
    data[length - 1] = I2C0_read_byte(0);

    // Send STOP
    I2C0_stop();
}
void I2C1_init(uint32_t scl_freq_hz) {
    #define F_CPU 16000000UL
    TWSR1 = 0x00; // Prescaler = 1
    TWBR = ((F_CPU / scl_freq_hz) - 16) / 2; // From datasheet
    TWCR1 = (1 << TWEN); // Enable TWI
}

// ======== START Condition ========
void I2C1_start(void) {
    TWCR1 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != START)
        ERROR();
}

// ======== Repeated START ========
void I2C1_repeated_start(void) {
    TWCR1 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != REP_START)
        ERROR();
}

// ======== STOP Condition ========
void I2C1_stop(void) {
    TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    // No need to check status; STOP doesn’t update TWSR
}

// ======== Write a Byte to Bus ========
void I2C1_write_byte(uint8_t data) {
    TWDR = data;
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != MT_DATA_ACK)
        ERROR();
}

// ======== Write (SLA+W) and Bytes ========
void I2C1_write_bytes(uint8_t addr, uint8_t *data, uint8_t length) {
    // Send START
    I2C1_start();

    // Send SLA+W
    TWDR = (addr << 1) | 0;  // Write mode
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != MT_SLA_ACK)
        ERROR();

    // Send all data bytes
    for (uint8_t i = 0; i < length; i++) {
        TWDR = data[i];
        TWCR1 = (1 << TWINT) | (1 << TWEN);
        while (!(TWCR1 & (1 << TWINT)));
        if ((TWSR1 & 0xF8) != MT_DATA_ACK)
            ERROR();
    }

    // Send STOP
    I2C1_stop();
}

// ======== Read One Byte with ACK or NACK ========
uint8_t I2C1_read_byte(uint8_t ack) {
    if (ack) {
        // Send ACK after receive
        TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    } else {
        // Send NACK (last byte)
        TWCR1 = (1 << TWINT) | (1 << TWEN);
    }

    while (!(TWCR1 & (1 << TWINT)));

    return TWDR;
}

// ======== Read (SLA+R) and Multiple Bytes ========
void I2C1_read_bytes(uint8_t addr, uint8_t *data, uint8_t length) {
    // Send START
    I2C1_start();

    // Send SLA+R
    TWDR = (addr << 1) | 1;  // Read mode
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != MR_SLA_ACK)
        ERROR();

    // Read (length - 1) bytes with ACK
    for (uint8_t i = 0; i < (length - 1); i++) {
        data[i] = I2C1_read_byte(1); // ACK after each
    }

    // Read last byte with NACK
    data[length - 1] = I2C1_read_byte(0);

    // Send STOP
    I2C1_stop();
}









