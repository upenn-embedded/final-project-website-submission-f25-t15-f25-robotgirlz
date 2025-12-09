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
void ERROR(void);

// ======== I²C Initialization ========
void I2C1_init(uint32_t scl_freq_hz);
// ======== START Condition ========
void I2C1_start(void);

// ======== Repeated START ========
void I2C1_repeated_start(void);

// ======== STOP Condition ========
void I2C1_stop(void);

// ======== Write a Byte to Bus ========
void I2C1_write_byte(uint8_t addr, uint8_t data);

// ======== Write (SLA+W) and Bytes ========
void I2C1_write_bytes(uint8_t addr, uint8_t *data, uint8_t length);
// ======== Read One Byte with ACK or NACK ========
uint8_t I2C1_read_byte(uint8_t ack);

// ======== Read (SLA+R) and Multiple Bytes ========
void I2C1_read_bytesNACKEND(uint8_t addr, uint8_t *data, uint8_t length);
 // function to rad from the 16 bit registers in the temp sensor
void I2C1_readfromregister(uint8_t deviceaddr, uint16_t regaddr, uint8_t *data,uint8_t datalength);
void I2C1_writetoregister(uint8_t deviceaddr, uint16_t regaddr, uint8_t *data,uint8_t datalength);

void I2C1_read_bytesACKEND(uint8_t addr, uint8_t *data, uint8_t length);

    

