#ifndef _NONVOLATILE_MEMORY_H_
#define _NONVOLATILE_MEMORY_H_

#include <stdint.h>

/* ************************************************************************** */

extern void nonvolatile_memory_init(void);

/* ************************************************************************** */

// standard datatype for flash addresses
typedef uint24_t NVM_address_t;

enum nvm_operations {
    NVM_READ = 0b000,
    NVM_READ_POST_INC = 0b001,
    NVM_READ_PAGE = 0b010,
    NVM_WRITE = 0b011,
    NVM_WRITE_POST_INC = 0b100,
    NVM_WRITE_PAGE = 0b101,
    NVM_ERASE_PAGE = 0b110,
};

// Active the nvm peripheral
void nvm_activate(NVM_address_t address, enum nvm_operations operation);

/* ************************************************************************** */

// EEPROM addresses are mapped into memory starting at 0x380000
#define EEPROM_BASE_ADDRESS 0x380000

// Read one byte from EEPROM at address
extern uint8_t internal_eeprom_read(NVM_address_t address);

// Write one byte to EEPROM at address
extern void internal_eeprom_write(NVM_address_t address, uint8_t data);

/* ************************************************************************** */
// Flash configuration settings

#define FLASH_SIZE _ROMSIZE

// _FLASH_ERASE_SIZE is compiler-defined as the erase row size, in words
#define FLASH_ERASE_BLOCKSIZE _FLASH_ERASE_SIZE * 2

// _FLASH_WRITE_SIZE is compiler-defined as the write row size, in words
#define FLASH_WRITE_BLOCKSIZE _FLASH_WRITE_SIZE 

// The size of the array you need in order to do flash block operations
#define FLASH_BUFFER_SIZE FLASH_ERASE_BLOCKSIZE

#define FLASH_BLOCK_MASK ((FLASH_SIZE - 1) ^ (FLASH_ERASE_BLOCKSIZE - 1))
#define FLASH_ELEMENT_MASK (FLASH_ERASE_BLOCKSIZE - 1)

/* -------------------------------------------------------------------------- */

// In order to print an NVM address, you have to cast it to a u32
// I've forgotten to do this cast one too many times, so now there's this macro
// to make sure we can't forget.
#define print_nvm_address(address) printf("address: %lu ", (uint32_t)address)
#define print_nvm_address_ln(address)                                          \
    printf("address: %lu \r\n", (uint32_t)address)

extern void print_flash_block(NVM_address_t address);
extern void print_flash_buffer(NVM_address_t address, uint8_t *buffer);

/* ************************************************************************** */

extern uint8_t flashBuffer[FLASH_BUFFER_SIZE];

//
extern void flash_page_read(NVM_address_t address);

//
extern void flash_page_erase(NVM_address_t address);

//
extern void flash_page_write(NVM_address_t address);

// 
extern void flash_read_block(NVM_address_t address, uint8_t *destination);

// 
extern void flash_block_erase(NVM_address_t address);

// 
extern void flash_block_write(NVM_address_t address, uint8_t *source);

/* ************************************************************************** */

// Read a single byte of flash
extern uint8_t flash_read_byte(NVM_address_t address);

// Write a single byte of flash
extern void flash_write_byte(NVM_address_t address, uint8_t data);

// Read a word of flash
extern uint16_t flash_read_word(NVM_address_t address);

// Write a word of flash
extern void flash_write_word(NVM_address_t address, uint16_t data);

/* ************************************************************************** */

#endif // _NONVOLATILE_MEMORY_H_