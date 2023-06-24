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

uint16_t imm_16(uint8_t *mem, uint16_t *PC) {
    return mem[(*PC)++] | mem[(*PC)++] << 8;
}

uint8_t imm_8(uint8_t* mem, uint16_t *PC) {
    return mem[(*PC)++];
}

int exec(regs* r, uint8_t* mem)
{
    uint8_t op = mem[r->PC++];

    switch(op){
        case 0x00:                                              break;
        case 0x01: MOV_16(&r->BC, imm_16(mem, &r->PC));         break;
        case 0x02: STR_8(&mem[r->BC], r->A);                    break;
        case 0x03: INC_16(&r->BC);                              break;
        case 0x04: INC_8(&r->B, &r->F);                         break;
        case 0x05: DEC_8(&r->B, &r->F);                         break;
        case 0x06: MOV_8(&r->B, imm_8(mem, &r->PC));            break;
        case 0x07: RLCA_8(&r->A, &r->F);                        break;
        case 0x08: STR_16(&mem[imm_16(mem, &r->PC)], r->SP);    break;
    }
    return 0;
}
