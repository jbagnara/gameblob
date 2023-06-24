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

int exec(regs* r, uint8_t* mem)
{
    uint8_t op = mem[r->PC++];

#define IMM_16 (mem[(r->PC)++] | mem[(r->PC)++] << 8)
#define IMM_8 (mem[(r->PC)++])

    switch(op){
        case 0x00:                                      break;
        case 0x01: MOV_16(&r->BC, IMM_16);              break;
        case 0x02: STR_8(&mem[r->BC], r->A);            break;
        case 0x03: INC_16(&r->BC);                      break;
        case 0x04: INC_8(&r->B, &r->F);                 break;
        case 0x05: DEC_8(&r->B, &r->F);                 break;
        case 0x06: MOV_8(&r->B, IMM_8);                 break;
        case 0x07: RLCA_8(&r->A, &r->F);                break;
        case 0x08: STR_16(&mem[IMM_16], r->SP);         break;
        case 0x09: ADD_16(&r->HL, &r->BC, &r->F);       break;
        case 0x0a: LDR_8(&r->A, &mem[r->BC]);           break;
        case 0x0b: DEC_16(&r->BC);                      break;
        case 0x0c: INC_8(&r->C, &r->F);                 break;
        case 0x0d: DEC_8(&r->C, &r->F);                 break;
        case 0x0e: MOV_8(&r->C, IMM_8);                 break;
        case 0x0f: RRCA(&r->A, &r->F);                  break;

        case 0x10: break; //TODO low power standby mode
        case 0x11: MOV_16(&r->DE, IMM_16);              break;
        case 0x12: STR_8(&mem[r->DE], r->A);            break;
        case 0x13: INC_16(&r->DE);                      break;
        case 0x14: INC_8(&r->D, &r->F);                 break;
        case 0x15: DEC_8(&r->D, &r->F);                 break;
        case 0x16: MOV_8(&r->D, IMM_8);                 break;
        case 0x17: RLA_8(&r->A, &r->F);                 break;
        case 0x18: JR(&r->PC, IMM_8, 0x00, r->F);       break;
        case 0x19: ADD_16(&r->HL, &r->DE, &r->F);       break;
        case 0x1a: LDR_8(&r->A, &mem[r->DE]);           break;
        case 0x1b: DEC_16(&r->DE);                      break;
        case 0x1c: INC_8(&r->E, &r->F);                 break;
        case 0x1d: DEC_8(&r->E, &r->F);                 break;
        case 0x1e: MOV_8(&r->E, IMM_8);                 break;
        case 0x0f: RRA(&r->A, &r->F);                  break;
    }
    return 0;
}
