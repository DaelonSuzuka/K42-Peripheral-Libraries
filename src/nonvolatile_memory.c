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

#if FAMILY_K42

// NVM internal utility macros
#define SELECT_EEPROM() NVMCON1bits.REG = 0
#define SELECT_CONFIG() NVMCON1bits.REG = 1
#define SELECT_FLASH() NVMCON1bits.REG = 2

#define NVM_WRITE_MODE() NVMCON1bits.FREE = 0
#define NVM_ERASE_MODE() NVMCON1bits.FREE = 1

/* ************************************************************************** */
/*  nvm_write() is the 'engage' button for writing to both types of nonvolatile
    memory.

    This function is the smallest unit that needs to be marked critical.
*/

void nvm_write(void) {
    begin_critical_section();
    NVMCON1bits.WREN = 1; // Enable NVM writes

    // Magic Sequence - Do Not Change
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;

    NVMCON1bits.WREN = 0; // Disable NVM writes
    end_critical_section();
}

/*  Notes on PIC18's EEPROM Memory:

    EEPROM in PIC18 family MCUs is very straightforward.
    There is 256 or 1024 bytes of byte-addressable EEPROM.

    Both read and write operations follow the same basic sequence, with the
    major difference being time required.  Reading from EEPROM only takes one
    cycle after the operation is started.  Writing to EEPROM takes up to 4ms.
    Other user code could be executed during that time, but in this application
    we will choose to wait for it to finish.

    Read:
    1) Load the desired address into EEADR(and EEADRH)
    2) Set the RD bit of EECON1, to begin operation
    3) Read byte from EEDATA

    Write:
    1) Load the desired address into EEADR(and EEADRH)
    2) Load the byte to be written into EEDATA
    3) Set the WREN bit of EECON1, to enable writes
    4) Write the 'magic sequence' of 0x55, 0xAA to EECON2, to unlock writes
    5) Set the WR bit of EECON1, to begin operation
    6) Wait for WR bit to be cleared by hardware
*/

uint8_t internal_eeprom_read(NVM_address_t address) {
    LOG_TRACE({ println("eeprom_read"); });

    NVMADRH = address >> 8;
    NVMADRL = address;

    SELECT_EEPROM();

    // Initiate read operation
    NVMCON1bits.RD = 1;

    // Return the value
    return NVMDAT;
}

void internal_eeprom_write(NVM_address_t address, uint8_t data) {
    LOG_TRACE({ println("eeprom_write"); });
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
}

/* ************************************************************************** */

/*  Notes on PIC18's Flash memory:

    Flash memory can be read as individual bytes by loading a desired address
    into TBLPTR and executing a TBLRD asm instruction.  The result of the read
    operation is placed into the TABLAT register.

    Flash memory can only be erased in 128 byte blocks. The block erase
    operation automatically handles

    Flash memory can only be written in 128 byte blocks.  In order to write only
    one or two bytes to flash without corrupting surrounding values, the
    following steps are necessary:
        1) Declare a buffer to hold 128 bytes.
        2) Call flash_read_block() with the desired address and buffer.
        3) Modify the buffer's contents with the new values.
        4) If necessary, erase the existing flash block
        5) Call flash_write_block() to write the new buffer into the block.
        6) Verify that the block was written to correctly.

    Registers involved in Flash memory operations:

    NVMCON1: control bits for Flash operations
        REG:    Select between Flash/EEPROM/Configuration Bits
        n/a
        FREE:   Program Flash Memory Erase Enable bit (1)
                1 = Performs an erase operation on the next WR command
                0 = The next WR command performs a write operation
        WRERR:
        WREN:   Program/Erase Enable bit
        WR:     Write Control, set to initiate write
        RD:     Read Control, set to initiate read
    NVMCON2: receives the 'magic sequence' to allow flash writes

    TBLPTR: Table Pointer register
        A set of three registers, TBLPTRU, TBLPTRH, and TBLPTRL.
        The Microchip provided header file gives access to the three TBLPTR
        registers as a single 24 bit unsigned integer.
        These registers are used together to effectively create a 22 bit
        pointer to a byte in Program Flash Memory

    TABLAT: Table Latch register
        When reading, the memory location pointed to by the TBLPTR is copied
        into TABLAT.
        When writing, TABLAT functions as a 'shadow register' interface to
        the array of write latch holding registers. The holding registers
        are indexed by the least 7 bits of the TBLPTR.

    TBLWT and TBLRD instructions, and the POSTINC/POSTDEC/PREINC suffixes
        These instructions perform operations using the TBLPTR and TABLAT
        registers, the holding registers, and the Program Flash Memory itself.
        These operations are performed in hardware, initiated by a single
        assembly instruction. The following listings are a C-styled
        representation of the operations performed during each instruction.

        TABLAT = holdingRegister[(TBLPTR & 0x00007F)]; // "TBLRD*"
        TABLAT = holdingRegister[(TBLPTR++ & 0x00007F)]; // "TBLRD*+"
        TABLAT = holdingRegister[(TBLPTR-- & 0x00007F)]; // "TBLRD*-"
        TABLAT = holdingRegister[(++TBLPTR & 0x00007F)]; // "TBLRD+*"

        holdingRegister[(TBLPTR & 0x00007F)] = TABLAT; // "TBLWT*"
        holdingRegister[(TBLPTR++ & 0x00007F)] = TABLAT; // "TBLWT*+"
        holdingRegister[(TBLPTR-- & 0x00007F)] = TABLAT; // "TBLWT*-"
        holdingRegister[(++TBLPTR & 0x00007F)] = TABLAT; // "TBLWT+*"
*/

/* -------------------------------------------------------------------------- */

void print_flash_block(NVM_address_t address) {
    uint8_t element = address & FLASH_ELEMENT_MASK;
    NVM_address_t blockAddress = address & FLASH_BLOCK_MASK;
    uint16_t blockNumber = blockAddress / 128;

    println("-----------------------------------------------------");
    println("|  address  |  blockAddress  |  block#  |  element  |");
    printf("|  %-7lu  |  %-12lu  |  %-6u  |  %-7u  |\r\n", (uint32_t)address,
           (uint32_t)blockAddress, blockNumber, element);
    println("-----------------------------------------------------");

    // create a pointer to the first byte of the selected block
    const char *blockPointer = (const char *)blockAddress;

    print("|  "); // start of first row
    for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
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

    for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
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

static void set_TBLPTR(NVM_address_t address) {
    LOG_DEBUG({ print_nvm_address_ln(address); });
    TBLPTR = address;
    //! There should be a log statement here, but it causes a serious bug
}

/*  //! WARNING

    For some reason, sometimes printing the value of TBLPTR causes
    minicom on the servitor to lock up? This is very bizarre behavior.
    This seems to happen directly before starting a flash block write.

    Making a local copy of TBLPTR and printing that doesn't seem to help.

    Here's stuff I tried:

    This version tries to print the contents of TBLPTR directly but it actually
    produces gibberish because printf can't take unsigned 24 bit inputs.
        LOG_DEBUG({ printf("TBLPTR: %lu\r\n", TBLPTR); });

    This fixes the gibberish, but now it crashes minicom sometimes.
        LOG_DEBUG({ printf("TBLPTR: %lu\r\n", (uint32_t)TBLPTR); });

    This was a guess about printf behaving badly with a hardware register as an
    input? Minicom still crashes with this, so it didn't help.
        uint32_t copyOfTBLPTR = (uint32_t)TBLPTR;
        LOG_DEBUG({ printf("TBLPTR: %lu\r\n", copyOfTBLPTR); });
*/

/* -------------------------------------------------------------------------- */

// Write one byte into flash memory at (address)
void flash_write_byte(NVM_address_t address, uint8_t data) {
    LOG_TRACE({ println("flash_write_byte"); });
    SELECT_FLASH();

    // if existingData is already what we want, then we're done
    uint8_t existingData = flash_read_byte(address);
    if (existingData == data) {
        return;
    }

    // compare the two datas bit-by-bit, checking for 0->1 transitions
    bool mustErase = false;
    for (uint8_t i = 0; i < 8; i++) {
        if (((existingData & (1 << i)) == 0) && ((data & (1 << i)) == 1)) {
            mustErase = true;
        }
    }

    // Read existing block into buffer
    uint8_t buffer[FLASH_BUFFER_SIZE];
    flash_read_block(address, buffer);

    // write the new data into the buffer
    buffer[address & FLASH_ELEMENT_MASK] = data;

    // only erase if we require a 0 -> 1 transition
    if (mustErase) {
        flash_erase_block(address);
    }

    // Write the modified buffer back into flash
    flash_write_block(address, buffer);
}

/* -------------------------------------------------------------------------- */

// Read one byte from Flash memory at (address)
uint8_t flash_read_byte(NVM_address_t address) {
    LOG_TRACE({ println("flash_read_byte"); });

    set_TBLPTR(address);

    // Read one byte from flash to TABLAT
    SELECT_FLASH();
    asm("TBLRD");
    return TABLAT;
}

// Read an entire block of 64 bytes from Flash memory into the provided buffer
void flash_read_block(NVM_address_t address, uint8_t *readBuffer) {
    LOG_TRACE({ println("flash_read_block"); });

    set_TBLPTR(address & FLASH_BLOCK_MASK);

    // copy TABLAT into readBuffer
    SELECT_FLASH();
    for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
        asm("TBLRDPOSTINC");
        readBuffer[i] = TABLAT;
    }
}

// Read an entire block of 64 bytes from Flash memory into the provided buffer
// Uses pointer to ROM instead of tableread instruction
void flash_read_block2(NVM_address_t address, uint8_t *readBuffer) {
    LOG_TRACE({ println("flash_read_block"); });

    NVM_address_t blockAddress = (address & FLASH_BLOCK_MASK);
    const char *blockPointer = (const char *)blockAddress;

    for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
        readBuffer[i] = *blockPointer++;
    }
}

// Erase a block of Flash memory at (address)
void flash_erase_block(NVM_address_t address) {
    LOG_TRACE({ println("flash_erase_block"); });

    set_TBLPTR(address);

    // Engage
    SELECT_FLASH();
    NVM_ERASE_MODE();
    nvm_write();
}

// Write the provided buffer into flash memory at (address)
void flash_write_block(NVM_address_t address, uint8_t *writeBuffer) {
    LOG_TRACE({ println("flash_write_block"); });

    set_TBLPTR(address & FLASH_BLOCK_MASK);

    // copy writeBuffer into TABLAT
    for (uint8_t i = 0; i < FLASH_BUFFER_SIZE; i++) {
        TABLAT = writeBuffer[i]; // Load data byte
        if (i == (FLASH_BUFFER_SIZE - 1)) {
            asm("TBLWT");
        } else {
            asm("TBLWTPOSTINC");
        }
    }

    // Engage
    SELECT_FLASH();
    NVM_WRITE_MODE();
    nvm_write();
}

/* ************************************************************************** */

// read a single byte from the config area
uint8_t read_config_data(NVM_address_t address) {
    LOG_TRACE({ println("read_config_data"); });

    set_TBLPTR(address);

    // Read one byte from config to TABLAT
    SELECT_CONFIG();
    asm("TBLRD");
    return TABLAT;
}

#else

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

// TODO: this address has to change between chips
uint8_t flashBuffer[FLASH_BUFFER_SIZE] __at(0x2500);

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
void flash_erase_block(NVM_address_t address) {
    nvm_activate(address, NVM_ERASE_PAGE); //
}

// 
void flash_write_block(NVM_address_t address, uint8_t *source) {
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
        flash_erase_block(address);
    }

    flash_write_block(address, NULL);
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

#endif