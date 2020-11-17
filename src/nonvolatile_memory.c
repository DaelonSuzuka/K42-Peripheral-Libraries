#include "nonvolatile_memory.h"
#include "interrupt.h"
#include "os/logging.h"
#include "pic_family.h"
#include "pic_header.h"
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

// NVM internal utility macros
#define SELECT_EEPROM() NVMCON1bits.REG = 0
#define SELECT_CONFIG() NVMCON1bits.REG = 1
#define SELECT_FLASH() NVMCON1bits.REG = 2

#define NVM_WRITE_MODE() NVMCON1bits.FREE = 0
#define NVM_ERASE_MODE() NVMCON1bits.FREE = 1

// NVM operations
#define NVM_READ 0b000
#define NVM_READ_POST_INC 0b001
#define NVM_READ_PAGE 0b010
#define NVM_WRITE 0b011
#define NVM_WRITE_POST_INC 0b100
#define NVM_WRITE_PAGE 0b101
#define NVM_ERASE_PAGE 0b111

/* ************************************************************************** */
/*  nvm_write() is the 'engage' button for writing to both types of nonvolatile
    memory.

    This function is the smallest unit that needs to be marked critical.
*/

void nvm_write(void) {
    begin_critical_section();
#if FAMILY_Q43 || FAMILY_Q84
    // Magic Sequence - Do Not Change
    NVMLOCK = 0x55;
    NVMLOCK = 0xAA;
    NVMCON0bits.GO = 1;
#else
    NVMCON1bits.WREN = 1; // Enable NVM writes

    // Magic Sequence - Do Not Change
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;

    NVMCON1bits.WREN = 0; // Disable NVM writes
#endif
    end_critical_section();
}

/* ************************************************************************** */

#define EEPROM_BASE_ADDRESS 0x380000

uint8_t internal_eeprom_read(uint16_t address) {
    LOG_TRACE({ println("eeprom_read"); });
#if FAMILY_Q43 || FAMILY_Q84
    // set address, including EEPROM offset
    NVMADR = EEPROM_BASE_ADDRESS + address;

    // set operation
    NVMCON1bits.NVMCMD = NVM_READ;

    // engage
    NVMCON0bits.GO = 1;

    return NVMDAT;
#else
    NVMADRH = address >> 8;
    NVMADRL = address;

    SELECT_EEPROM();

    // Initiate read operation
    NVMCON1bits.RD = 1;

    // Return the value
    return NVMDAT;
#endif
}

void internal_eeprom_write(uint16_t address, uint8_t data) {
    LOG_TRACE({ println("eeprom_write"); });
#if FAMILY_Q43 || FAMILY_Q84
    // Wait for possible previous write to complete
    if (NVMCON0bits.GO) {
        while (NVMCON0bits.GO) {
        }
    }

    // set address, including EEPROM offset
    NVMADR = EEPROM_BASE_ADDRESS + address;

    // set operation
    NVMCON1bits.NVMCMD = NVM_WRITE;

    // put data in
    NVMDATL = data;

    nvm_write();
#else
    // Wait for possible previous write to complete
    if (NVMCON1bits.WR) {
        LOG_DEBUG({ println("previous write not finished"); });
        while (NVMCON1bits.WR) {
        }
    }

    NVMADRH = address >> 8;
    NVMADRL = address;

    // Load data into register
    NVMDAT = data;

    // Engage
    SELECT_EEPROM();
    NVM_WRITE_MODE();
    nvm_write();
#endif
}

/* ************************************************************************** */

void print_flash_block(NVM_address_t address) {
    // uint8_t element = address & FLASH_ELEMENT_MASK;
    // NVM_address_t blockAddress = address & FLASH_BLOCK_MASK;
    // uint16_t blockNumber = blockAddress / 128;

    // println("-----------------------------------------------------");
    // println("|  address  |  blockAddress  |  block#  |  element  |");
    // printf("|  %-7lu  |  %-12lu  |  %-6u  |  %-7u  |\r\n", (uint32_t)address,
    //        (uint32_t)blockAddress, blockNumber, element);
    // println("-----------------------------------------------------");

    // // create a pointer to the first byte of the selected block
    // const char *blockPointer = (const char *)blockAddress;

    // print("|  "); // start of first row
    // for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
    //     char tempChar = *blockPointer++;
    //     if (i == element) {
    //         printf("\033[7m%02x\033[0;37;40m ", tempChar);
    //     } else {
    //         printf("%02x ", tempChar);
    //     }
    //     if (((i + 1) % 16) == 0) {
    //         println(" |"); // end of current row
    //         if (i < FLASH_BUFFER_SIZE - 1) {
    //             print("|  "); // start of next row
    //         }
    //     }
    // }
    // println("-----------------------------------------------------");
}

void print_flash_buffer(NVM_address_t address, uint8_t *buffer) {
    // uint8_t element = address & FLASH_ELEMENT_MASK;
    // NVM_address_t blockAddress = address & FLASH_BLOCK_MASK;

    // println("");
    // printf("address: %lu ", (uint32_t)address);
    // printf("blockAddress: %lu ", (uint32_t)blockAddress);
    // printf("element: %d\r\n", element);

    // for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
    //     if (i == element) {
    //         printf("\033[7m%02x\033[0;37;40m ", buffer[i]);
    //     } else {
    //         printf("%02x ", buffer[i]);
    //     }
    //     if (((i + 1) % 16) == 0) {
    //         println("");
    //     }
    // }
    // println("");
}

/* ************************************************************************** */

// Write one byte into flash memory at (address)
void flash_write_byte(NVM_address_t address, uint8_t data) {
    // LOG_TRACE({ println("flash_write_byte"); });
    // SELECT_FLASH();

    // // if existingData is already what we want, then we're done
    // uint8_t existingData = flash_read_byte(address);
    // if (existingData == data) {
    //     return;
    // }

    // // compare the two datas bit-by-bit, checking for 0->1 transitions
    // bool mustErase = false;
    // for (uint8_t i = 0; i < 8; i++) {
    //     if (((existingData & (1 << i)) == 0) && ((data & (1 << i)) == 1)) {
    //         mustErase = true;
    //     }
    // }

    // // Read existing block into buffer
    // uint8_t buffer[FLASH_BUFFER_SIZE];
    // flash_read_block(address, buffer);

    // // write the new data into the buffer
    // buffer[address & FLASH_ELEMENT_MASK] = data;

    // // only erase if we require a 0 -> 1 transition
    // if (mustErase) {
    //     flash_block_erase(address);
    // }

    // // Write the modified buffer back into flash
    // flash_block_write(address, buffer);
}

/* -------------------------------------------------------------------------- */

// Read one byte from Flash memory at (address)
uint8_t flash_read_byte(NVM_address_t address) {
    // LOG_TRACE({ println("flash_read_byte"); });

    // TBLPTR = address;

    // // Read one byte from flash to TABLAT
    // SELECT_FLASH();
    // asm("TBLRD");
    // return TABLAT;
    return 0;
}

// Read an entire block of 64 bytes from Flash memory into the provided buffer
void flash_read_block(NVM_address_t address, uint8_t *readBuffer) {
    // LOG_TRACE({ println("flash_read_block"); });

    // TBLPTR = (address & FLASH_BLOCK_MASK);

    // // copy TABLAT into readBuffer
    // SELECT_FLASH();
    // for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
    //     asm("TBLRDPOSTINC");
    //     readBuffer[i] = TABLAT;
    // }
}

// Read an entire block of 64 bytes from Flash memory into the provided buffer
// Uses pointer to ROM instead of tableread instruction
void flash_read_block2(NVM_address_t address, uint8_t *readBuffer) {
    // LOG_TRACE({ println("flash_read_block"); });

    // NVM_address_t blockAddress = (address & FLASH_BLOCK_MASK);
    // const char *blockPointer = (const char *)blockAddress;

    // for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
    //     readBuffer[i] = *blockPointer++;
    // }
}

// Erase a block of Flash memory at (address)
void flash_block_erase(NVM_address_t address) {
    // LOG_TRACE({ println("flash_block_erase"); });

    // TBLPTR = address;

    // // Engage
    // SELECT_FLASH();
    // NVM_ERASE_MODE();
    // nvm_write();
}

// Write the provided buffer into flash memory at (address)
void flash_block_write(NVM_address_t address, uint8_t *writeBuffer) {
    // LOG_TRACE({ println("flash_block_write"); });

    // TBLPTR = (address & FLASH_BLOCK_MASK);

    // // copy writeBuffer into TABLAT
    // for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
    //     TABLAT = writeBuffer[i]; // Load data byte
    //     if (i == (FLASH_BUFFER_SIZE - 1)) {
    //         asm("TBLWT");
    //     } else {
    //         asm("TBLWTPOSTINC");
    //     }
    // }

    // // Engage
    // SELECT_FLASH();
    // NVM_WRITE_MODE();
    // nvm_write();
}

/* ************************************************************************** */

// read a single byte from the config area
uint8_t read_config_data(NVM_address_t address) {
    LOG_TRACE({ println("read_config_data"); });
#if FAMILY_Q43 || FAMILY_Q84
    NVMADR = address;

    // set operation
    NVMCON1bits.NVMCMD = NVM_READ;

    // engage
    NVMCON0bits.GO = 1;

    return NVMDAT;
#else
    TBLPTR = address;

    // Read one byte from config to TABLAT
    SELECT_CONFIG();
    asm("TBLRD");
    return TABLAT;
#endif
}