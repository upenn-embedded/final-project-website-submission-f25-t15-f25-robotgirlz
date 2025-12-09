
#define F_CPU 16000000UL // frequency 
#include <avr/io.h>
#include <util/delay.h>


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
void I2C1_init(uint32_t scl_freq_hz) {
   
    TWSR1 = 0x00; // Prescaler = 1
    TWBR1 = ((F_CPU / scl_freq_hz) - 16) / 2; // From datasheet
    TWCR1 = (1 << TWEN); // Enable TWI
}

// ======== START Condition ========
void I2C1_start(void) {
    TWCR1 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != START){
        ERROR();}
}

// ======== Repeated START ========
void I2C1_repeated_start(void) {
    TWCR1 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != REP_START){
        ERROR();
    }
}

// ======== STOP Condition ========
void I2C1_stop(void) {
    TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    // No need to check status; STOP doesn?t update TWSR
}

// ======== Write a Byte to Bus ========
void I2C1_write_byte(uint8_t addr, uint8_t data) {
    TWDR1 = (addr << 1) | 0;  // Write mode
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    TWDR1 = data;
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != MT_DATA_ACK)
        ERROR();
   
}
void I2C1_write(uint8_t byte)
{
    TWDR1 = byte;
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    
}

// ======== Write (SLA+W) and Bytes ========
void I2C1_write_bytes(uint8_t addr, uint8_t *data, uint8_t length) {
    // Send START
    I2C1_start();

    // Send SLA+W
    TWDR1 = (addr << 1) | 0;  // Write mode
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR1 & 0xF8) != MT_SLA_ACK)
        ERROR();

    // Send all data bytes
    for (uint8_t i = 0; i < length; i++) {
        TWDR1 = data[i];
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
        TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // ACK for when you want to keep going / reading multiplle bytes
    } else {
        // Send NACK (last byte)
        TWCR1 = (1 << TWINT) | (1 << TWEN);
    }

    while (!(TWCR1 & (1 << TWINT)));

    return TWDR1;
    
}

// ======== Read (SLA+R) and Multiple Bytes ========
void I2C1_read_bytesNACKEND(uint8_t addr, uint8_t *data, uint8_t length) {
    I2C1_start();   

    // Send SLA+R
    TWDR1 = (addr << 1) | 1;  // Read mode address of the periph + 1 
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
//  void I2C0_readfromregister(uint8_t deviceaddr, uint16_t regaddr, uint8_t *data, uint8_t datalen)
// {
//     uint8_t reg_MSB = (regaddr >> 8) & 0xFF;
//     uint8_t reg_LSB = regaddr & 0xFF;

//     // START
//     I2C0_start();

//     // Send SLA+W
//     TWDR0 = (deviceaddr << 1) | 0;
//     TWCR0 = (1 << TWINT) | (1 << TWEN);
//     while (!(TWCR0 & (1 << TWINT)));

//     // Write register MSB
//     TWDR0 = reg_MSB;
//     TWCR0 = (1 << TWINT) | (1 << TWEN);
//     while (!(TWCR0 & (1 << TWINT)));

//     // Write register LSB
//     TWDR0 = reg_LSB;
//     TWCR0 = (1 << TWINT) | (1 << TWEN);
//     while (!(TWCR0 & (1 << TWINT)));

//     // REPEATED START
//    // I2C0_start();

//     // Send SLA+R
//     TWDR0 = (deviceaddr << 1) | 1;
//     TWCR0 = (1 << TWINT) | (1 << TWEN);
//     while (!(TWCR0 & (1 << TWINT)));

//     // READ bytes
//     for (uint8_t i = 0; i < datalen; i++)
//     {
//         if (i == datalen - 1)
//             data[i] = I2C0_read_byte(0);  // NACK last byte
//         else
//             data[i] = I2C0_read_byte(1);  // ACK intermediate bytes
//     }

//     // STOP
//     I2C0_stop();
// }
// function to rad from the 16 bit registers in the temp sensor
void I2C1_readfromregister(uint8_t deviceaddr, uint16_t regaddr, uint8_t *data, uint8_t datalen)
{
    uint8_t reg_MSB = (regaddr >> 8) & 0xFF;
    uint8_t reg_LSB = regaddr & 0xFF;

    // START
    I2C1_start();

    // SLA+W
    I2C1_write((deviceaddr << 1) | 0);

    // Send register MSB
    I2C1_write(reg_MSB);

    // Send register LSB
    I2C1_write(reg_LSB);

    // REPEATED START
    //I2C0_start();
    TWCR1 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));


    // SLA+R
    I2C1_write((deviceaddr << 1) | 1);

    // Read bytes
    for (uint8_t i = 0; i < datalen; i++)
    {
        if (i == datalen - 1)
            data[i] = I2C1_read_byte(0);  // NACK last byte
        else
            data[i] = I2C1_read_byte(1);  // ACK
    }

    // STOP
    I2C1_stop();
}
/*void I2C0_readfromregister(uint8_t deviceaddr, uint16_t regaddr, uint8_t *data,uint8_t datalength){
    uint8_t regaddrl = regaddr & 0xFF;
    uint8_t regaddrm = (regaddr >>8) & 0xFF;
    I2C0_start();   
    I2C0_write_byte(deviceaddr,regaddrm);
    I2C0_write_byte(deviceaddr,regaddrl);
    TWDR0 = (deviceaddr << 1) | 1;  // Read mode  now
    TWCR0 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR0 & (1 << TWINT)));
    if ((TWSR0 & 0xF8) != MR_SLA_ACK)
        ERROR();
     // Read (length - 1) bytes with ACK
    for (uint8_t i = 0; i < (datalength - 1); i++) {
        data[i] = I2C0_read_byte(1); // ACK after each
    }
    // Read last byte with NACK
    data[datalength - 1] = I2C0_read_byte(0);

    // Send STOP
    I2C0_stop();

}*/

void I2C1_writetoregister(uint8_t deviceaddr, uint16_t regaddr, uint8_t *data,uint8_t datalength){ // only lengthv 2
    uint8_t regaddrl = regaddr & 0xFF;
    uint8_t regaddrm = (regaddr >>8) & 0xFF;
    uint8_t togetwrote[] = {regaddrm, regaddrl, data[0],data[1]};
    //I2C0_start();   
   I2C1_write_bytes(deviceaddr,togetwrote,4);
   // I2C0_stop();

}


void I2C1_read_bytesACKEND(uint8_t addr, uint8_t *data, uint8_t length) {
    

    // Send SLA+R
    TWDR1 = (addr << 1) | 1;  // Read mode address of the periph + 1 
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
    if ((TWSR0 & 0xF8) != MR_SLA_ACK)
        ERROR();

    // Read (length - 1) bytes with ACK
    for (uint8_t i = 0; i < (length); i++) {
        data[i] = I2C1_read_byte(1); // ACK after each
    }

    
}
