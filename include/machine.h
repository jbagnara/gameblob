#include <stdint.h>
#include <cpu.h>

typedef struct machine {
    uint8_t             mem[0x10000];
    regs                cpu; 
} machine;
