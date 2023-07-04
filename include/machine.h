#include <stdint.h>
#include <display.h>
#include <cpu.h>

typedef struct machine_t {
    uint8_t             mem[0x10000];
    cpu_t               cpu; 
    display_t           display;
} machine_t;
