#ifndef CPU_H
#define CPU_H

#include <stdint.h>
/*==================================
 *
 * CPU registers can be accessed
 * as either individual 16-bit
 * register pairs or as 8-bit
 * registers
 *
 =================================*/
typedef struct flags {
    uint8_t dnc:4;  // unused
    uint8_t c:1;    // carry
    uint8_t h:1;    // half carry
    uint8_t n:1;    // substraction
    uint8_t z:1;    // zero
} cpuflags_t;

#define PAIR(A, B, C) \
    union { \
        uint16_t A##B; \
        struct { \
            C B; \
            uint8_t A; \
        }; \
    };
#define REG_FLAG(A, B) PAIR(A, B, cpuflags_t);
#define REG_PAIR(A, B) PAIR(A, B, uint8_t)

typedef struct regs {
    REG_FLAG(A, F);
    REG_PAIR(B, C);
    REG_PAIR(D, E);
    REG_PAIR(H, L);
    uint16_t SP;
    uint16_t PC;
    uint8_t IME;
} cpu_t;
#endif
