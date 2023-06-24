#include <stdint.h>;

typedef struct machine {
    uint8_t[0x10000]    mem;
    cpu                 cpu; 
} machine;
