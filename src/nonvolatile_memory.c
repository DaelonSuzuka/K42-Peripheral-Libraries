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

// NVM operations
#define NVM_READ 0b000
#define NVM_READ_POST_INC 0b001
#define NVM_READ_PAGE 0b010
#define NVM_WRITE 0b011
#define NVM_WRITE_POST_INC 0b100
#define NVM_WRITE_PAGE 0b101
#define NVM_ERASE_PAGE 0b110

/* ************************************************************************** */
/*  nvm_write() is the 'engage' button for writing to both types of nonvolatile
    memory.

    This function is the smallest unit that needs to be marked critical.
*/

void nvm_write(void) {
    begin_critical_section();

    // Magic Sequence - Do Not Change
    NVMLOCK = 0x55;
    NVMLOCK = 0xAA;
    NVMCON0bits.GO = 1;

    end_critical_section();
}

/* ************************************************************************** */

#define EEPROM_BASE_ADDRESS 0x380000

uint8_t internal_eeprom_read(uint16_t address) {
    LOG_TRACE({ println("eeprom_read"); });

    // set address, including EEPROM offset
    NVMADR = EEPROM_BASE_ADDRESS + (uint24_t)address;

    // set operation
    NVMCON1bits.NVMCMD = NVM_READ;

    // engage
    NVMCON0bits.GO = 1;

    return NVMDATL;
}

void internal_eeprom_write(uint16_t address, uint8_t data) {
    LOG_TRACE({ printf("eeprom_write: %02x @ %u\r\n", data, address); });

    // Wait for possible previous write to complete
    while (NVMCON0bits.GO) {
        // empty
    }

    // set address, including EEPROM offset
    NVMADR = EEPROM_BASE_ADDRESS + (uint24_t)address;

    // put data in
    NVMDATL = data;

    // set operation
    NVMCON1bits.NVMCMD = NVM_WRITE;

    nvm_write();

    NVMCON1bits.NVMCMD = NVM_READ;
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
// flash page operations

uint8_t flashBuffer[256] @0x2500;

void flash_page_read(NVM_address_t address) {
    LOG_TRACE({ println("flash_page_read"); });

    NVMADR = address;

    NVMCON1bits.NVMCMD = NVM_READ_PAGE;

    NVMCON0bits.GO = 1;
    while (NVMCON0bits.GO)
        ;

    // reset to safe command
    NVMCON1bits.NVMCMD = NVM_READ;
}

void flash_page_erase(NVM_address_t address) {
    LOG_TRACE({ println("flash_page_erase"); });

    NVMADR = address;

    NVMCON1bits.NVMCMD = NVM_ERASE_PAGE;

    nvm_write();
    while (NVMCON0bits.GO)
        ;

    // reset to safe command
    NVMCON1bits.NVMCMD = NVM_READ;
}

void flash_page_write(NVM_address_t address) {
    LOG_TRACE({ println("flash_page_write"); });

    NVMADR = address;

    NVMCON1bits.NVMCMD = NVM_WRITE_PAGE;

    nvm_write();
    while (NVMCON0bits.GO)
        ;

    // reset to safe command
    NVMCON1bits.NVMCMD = NVM_READ;
}

/* ************************************************************************** */

// Write one byte into flash memory at (address)
void flash_write_byte(NVM_address_t address, uint8_t data) {
    LOG_TRACE({ println("flash_write_byte"); });

    // if existingData is already what we want, then we're done
    uint8_t existingData = flash_read_byte(address);

    LOG_DEBUG({ printf("existing: %02x new: %02x \r\n", existingData, data); });
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

    // Read existing block into buffer
    flash_page_read(address);

    // write the new data into the buffer
    flashBuffer[address & FLASH_ELEMENT_MASK] = data;

    // only erase if we require a 0 -> 1 transition
    if (mustErase) {
        flash_page_erase(address);
    }

    // Write the modified buffer back into flash
    flash_page_write(address);
}

/* -------------------------------------------------------------------------- */

// Read one byte from Flash memory at (address)
uint8_t flash_read_byte(NVM_address_t address) {
    LOG_TRACE({ println("flash_read_byte"); });

    flash_page_read(address);

    return flashBuffer[address & FLASH_ELEMENT_MASK];
}

/* ************************************************************************** */

// read a single byte from the config area
uint8_t read_config_data(NVM_address_t address) {
    LOG_TRACE({ println("read_config_data"); });

    NVMADR = address;

    // set operation
    NVMCON1bits.NVMCMD = NVM_READ;

    // engage
    NVMCON0bits.GO = 1;

    return NVMDAT;
}