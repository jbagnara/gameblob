#include <cpu.h>
#include <op.h>

/*================================== 
 * Implements Sharp LR35902
 * instruction set
 * 
 * NOTE - I've separated the
 * different LD mneumonics into
 * separate op names MOV, LRD,
 * and STR.
 *=================================*/

uint8_t imm_16(uint8_t* mem, uint16_t PC) {
    return mem[PC++] | mem[PC++] << 8;
}

uint8_t imm_8(uint8_t* mem, uint16_t PC) {
    return mem[PC++];
}

int exec(cpu r, uint8_t* mem)
{
    op = mem[regs.PC++]

    switch(op){
        case 0x00: break;
        case 0x01: MOV_16(&r.BC, imm_16(mem, r.PC));
        case 0x02: STR_16(&mem[r.BC], r.A);
        case 0x03: INC_16(&r.BC);
    }
}
