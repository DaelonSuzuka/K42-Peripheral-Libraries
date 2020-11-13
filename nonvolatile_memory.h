#ifndef _NONVOLATILE_MEMORY_H_
#define _NONVOLATILE_MEMORY_H_

#include <stdbool.h>
#include <stdint.h>

/* ************************************************************************** */

extern void nonvolatile_memory_init(void);

/* ************************************************************************** */

/*  Notes on using EEPROM Memory operations:

    EEPROM can be read AND written as individual bytes, no block operations are
    needed.

    eeprom_read() is very fast, the read operation itself takes a single cycle.

    eeprom_write() can be quite a bit slower.  The write operation can take as
    long as 4ms to complete.  eeprom_write() does NOT wait for the write
    operation to complete, instead returning as soon as the write is engaged.
    In order to prevent conflict with multiple back-to-back writes, the relevant
    flag is checked at the beginning of the function.  If a previous write is
    still in process, it will wait until it completes before continuing with the
    new write operation.
*/

// Read one byte from EEPROM memory at (address)
extern uint8_t internal_eeprom_read(uint16_t address);

// Write one byte to EEPROM memory at (address)
extern void internal_eeprom_write(uint16_t address, uint8_t data);

/* ************************************************************************** */
// Flash configuration settings

#define FLASH_SIZE _ROMSIZE

// _FLASH_ERASE_SIZE is compiler-defined as the erase row size, in bytes
#define FLASH_ERASE_BLOCKSIZE _FLASH_ERASE_SIZE

// _FLASH_WRITE_SIZE is compiler-defined as the write row size, in bytes
#define FLASH_WRITE_BLOCKSIZE _FLASH_WRITE_SIZE

// The size of the array you need in order to do flash block operations
#define FLASH_BUFFER_SIZE FLASH_ERASE_BLOCKSIZE

#define FLASH_BLOCK_MASK ((FLASH_SIZE - 1) ^ (FLASH_ERASE_BLOCKSIZE - 1))
#define FLASH_ELEMENT_MASK (FLASH_ERASE_BLOCKSIZE - 1)

/* -------------------------------------------------------------------------- */

typedef __uint24 NVM_address_t;

// In order to print an NVM address, you have to cast it to a u32
// I've forgotten to do this cast one too many times, so now there's this macro
// to make sure we can't forget.
#define print_nvm_address(address) printf("address: %lu ", (uint32_t)address)
#define print_nvm_address_ln(address)                                          \
    printf("address: %lu \r\n", (uint32_t)address)

extern void print_flash_block(NVM_address_t address);
extern void print_flash_buffer(NVM_address_t address, uint8_t *buffer);

/* -------------------------------------------------------------------------- */

// Read one byte from Flash memory at (address)
extern uint8_t flash_read_byte(NVM_address_t address);

// Write one byte into flash memory at (address)
extern void flash_write_byte(NVM_address_t address, uint8_t data);

// Read an entire block of 64 bytes from Flash memory into the provided buffer
extern void flash_read_block(NVM_address_t address, uint8_t *readBuffer);

// Read an entire block of 64 bytes from Flash memory into the provided buffer
// Uses pointer to ROM instead of tableread instruction
extern void flash_read_block2(NVM_address_t address, uint8_t *readBuffer);

// Erase a block of Flash memory at (address)
extern void flash_block_erase(NVM_address_t address);

// Write the provided buffer into flash memory at (address)
extern void flash_block_write(NVM_address_t address, uint8_t *writeBuffer);

/* ************************************************************************** */

// read a single byte from the config area
extern uint8_t read_config_data(NVM_address_t address);

#endif // _NONVOLATILE_MEMORY_H_