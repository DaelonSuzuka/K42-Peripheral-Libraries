#include "nonvolatile_memory.h"
#include "interrupt.h"
#include "os/logging.h"
#include "pic_family.h"
#include "pic_header.h"
#include <stdbool.h>
static uint8_t LOG_LEVEL = L_SILENT;

/* ************************************************************************** */
// this prints all the relevant macros defined by the compiler, for debug
static void print_configuration_data(void) {
    println("");
    printf("_EEPROMSIZE: %u\r\n", _EEPROMSIZE);
    println("");
    printf("_ROMSIZE: %lu\r\n", _ROMSIZE);
    printf("_FLASH_ERASE_SIZE: %u\r\n", _FLASH_ERASE_SIZE);
    printf("_FLASH_WRITE_SIZE: %u\r\n", _FLASH_WRITE_SIZE);
    println("");
    printf("FLASH_ERASE_BLOCKSIZE: %u\r\n", FLASH_ERASE_BLOCKSIZE);
    printf("FLASH_WRITE_BLOCKSIZE: %u\r\n", FLASH_WRITE_BLOCKSIZE);
    printf("FLASH_BUFFER_SIZE: %u\r\n", FLASH_BUFFER_SIZE);
    printf("FLASH_BLOCK_MASK: %lu\r\n", FLASH_BLOCK_MASK);
    printf("FLASH_ELEMENT_MASK: %u\r\n", FLASH_ELEMENT_MASK);
}

void nonvolatile_memory_init(void) {
    //
    log_register();

    //
    LOG_DEBUG({ print_configuration_data(); });
}

/* ************************************************************************** */

void nvm_activate(NVM_address_t address, enum nvm_operations operation) {
    NVMCON1bits.NVMCMD = operation;

    NVMADR = address;

    if (operation >= NVM_WRITE) {
        begin_critical_section();

        // Magic Sequence - Do Not Change
        NVMLOCK = 0x55;
        NVMLOCK = 0xAA;
    }

    // engage
    NVMCON0bits.GO = 1;

    if (operation >= NVM_WRITE) {
        end_critical_section();
    }

    while (NVMCON0bits.GO) {
        // wait for the operation to finish
    }

    NVMCON1bits.NVMCMD = NVM_READ; // reset the operation for safety
}

/* ************************************************************************** */

uint8_t internal_eeprom_read(NVM_address_t address) {
    if (address < EEPROM_BASE_ADDRESS) {
        address += EEPROM_BASE_ADDRESS;
    }
    nvm_activate(address, NVM_READ);
    return NVMDATL;
}

void internal_eeprom_write(NVM_address_t address, uint8_t data) {
    if (address < EEPROM_BASE_ADDRESS) {
        address += EEPROM_BASE_ADDRESS;
    }
    NVMDATL = data;
    nvm_activate(address, NVM_WRITE);
}

/* ************************************************************************** */

void print_flash_block(NVM_address_t address) {
    uint8_t element = address & FLASH_ELEMENT_MASK;
    NVM_address_t blockAddress = address & FLASH_BLOCK_MASK;
    uint16_t blockNumber = blockAddress / FLASH_WRITE_BLOCKSIZE;

    println("-----------------------------------------------------");
    println("|  address  |  blockAddress  |  block#  |  element  |");
    printf("|  %-7lu  |  %-12lu  |  %-6u  |  %-7u  |\r\n", (uint32_t)address,
           (uint32_t)blockAddress, blockNumber, element);
    println("-----------------------------------------------------");

    // create a pointer to the first byte of the selected block
    const char *blockPointer = (const char *)blockAddress;

    print("|  "); // start of first row
    for (uint16_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
        char tempChar = *blockPointer++;
        if (i == element) {
            printf("\033[7m%02x\033[0;37;40m ", tempChar);
        } else {
            printf("%02x ", tempChar);
        }
        if (((i + 1) % 16) == 0) {
            println(" |"); // end of current row
            if (i < FLASH_BUFFER_SIZE - 1) {
                print("|  "); // start of next row
            }
        }
    }
    println("-----------------------------------------------------");
}

void print_flash_buffer(NVM_address_t address, uint8_t *buffer) {
    uint8_t element = address & FLASH_ELEMENT_MASK;
    NVM_address_t blockAddress = address & FLASH_BLOCK_MASK;

    println("");
    printf("address: %lu ", (uint32_t)address);
    printf("blockAddress: %lu ", (uint32_t)blockAddress);
    printf("element: %d\r\n", element);

    for (uint16_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
        if (i == element) {
            printf("\033[7m%02x\033[0;37;40m ", buffer[i]);
        } else {
            printf("%02x ", buffer[i]);
        }
        if (((i + 1) % 16) == 0) {
            println("");
        }
    }
    println("");
}

/* ************************************************************************** */

uint8_t flashBuffer[FLASH_BUFFER_SIZE] @0x2500;

// 
void flash_page_read(NVM_address_t address) {
    nvm_activate(address, NVM_READ_PAGE); //
}

// 
void flash_page_erase(NVM_address_t address) {
    nvm_activate(address, NVM_ERASE_PAGE); //
}

// 
void flash_page_write(NVM_address_t address) {
    nvm_activate(address, NVM_WRITE_PAGE); //
}

// 
void flash_read_block(NVM_address_t address, uint8_t *destination) {
    nvm_activate(address, NVM_READ_PAGE);

    if (destination && (destination != &flashBuffer)) {
        for (uint16_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
            destination[i] = flashBuffer[i];
        }
    }
}

// 
void flash_block_erase(NVM_address_t address) {
    nvm_activate(address, NVM_ERASE_PAGE); //
}

// 
void flash_block_write(NVM_address_t address, uint8_t *source) {
    if (source && (source != &flashBuffer)) {
        for (uint16_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
            flashBuffer[i] = source[i];
        }
    }

    nvm_activate(address, NVM_WRITE_PAGE);
}

/* ************************************************************************** */

// Read one byte from Flash memory at (address)
uint8_t flash_read_byte(NVM_address_t address) {
    flash_read_block(address, NULL);

    return flashBuffer[address & FLASH_ELEMENT_MASK];
}

// Write one byte into flash memory at (address)
void flash_write_byte(NVM_address_t address, uint8_t data) {
    uint8_t existingData = flash_read_byte(address);

    // if existingData is already what we want, then we're done
    if (existingData == data) {
        return;
    }

    // compare the two datas bit-by-bit, checking for 0->1 transitions
    bool mustErase = false;
    for (uint8_t i = 0; i < 8; i++) {
        if (!(existingData & (1 << i)) && (data & (1 << i))) {
            mustErase = true;
        }
    }

    flash_read_block(address, NULL);

    // write the new data into the buffer
    flashBuffer[address & FLASH_ELEMENT_MASK] = data;

    // only erase if we require a 0 -> 1 transition
    if (mustErase) {
        flash_block_erase(address);
    }

    flash_block_write(address, NULL);
}

/* -------------------------------------------------------------------------- */

// Read a word of flash
uint16_t flash_read_word(NVM_address_t address) {
    nvm_activate(address, NVM_READ);
    return NVMDAT;
}

// Write a word of flash
void flash_write_word(NVM_address_t address, uint16_t data) {
    NVMDAT = data;
    nvm_activate(address, NVM_WRITE);
}

/* ************************************************************************** */

// read a single byte from the config area
uint8_t read_config_data(NVM_address_t address) {
    NVMADR = address;

    // set operation
    NVMCON1bits.NVMCMD = NVM_READ;

    // engage
    NVMCON0bits.GO = 1;

    return NVMDAT;
}