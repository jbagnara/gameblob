#include <cpu.h>
#include <op.h>
#include <stdio.h>

/*================================== 
 * Implements Sharp LR35902
 * instruction set
 * 
 * NOTE - I've separated the
 * different LD mneumonics into
 * separate op names MOV, LRD,
 * and STR.
 *=================================*/

#define IMM_16 (mem[(r->PC)++] | mem[(r->PC)++] << 8)
#define IMM_8 (mem[(r->PC)++])
#define MASK_Z  0x80
#define MASK_C  0x10
#define MASK_NZ 0xc0
#define MASK_NC 0x50
#define NONE    0x00

#define PRINT_REGS \
    printf("AF: 0x%.4x\n", r->AF); \
    printf("BC: 0x%.4x\n", r->BC); \
    printf("DE: 0x%.4x\n", r->DE); \
    printf("HL: 0x%.4x\n", r->HL); \
    printf("SP: 0x%.4x\n", r->SP); \
    printf("PC: 0x%.4x\n", r->PC); \
    printf("(HL): 0x%.4x\n", mem[r->HL]);

int exec(regs* r, uint8_t* mem)
{
    uint8_t op = mem[r->PC++];

    switch(op){
        case 0x00:                                                              break;
        case 0x01: MOV_16(&r->BC, IMM_16);                                      break;
        case 0x02: STR_8(&mem[r->BC], r->A);                                    break;
        case 0x03: INC_16(&r->BC);                                              break;
        case 0x04: INC_8(&r->B, &r->F);                                         break;
        case 0x05: DEC_8(&r->B, &r->F);                                         break;
        case 0x06: MOV_8(&r->B, IMM_8);                                         break;
        case 0x07: RLCA_8(&r->A, &r->F);                                        break;
        case 0x08: STR_16(&mem[IMM_16], r->SP);                                 break;
        case 0x09: ADD_16(&r->HL, &r->BC, &r->F);                               break;
        case 0x0a: LDR_8(&r->A, &mem[r->BC]);                                   break;
        case 0x0b: DEC_16(&r->BC);                                              break;
        case 0x0c: INC_8(&r->C, &r->F);                                         break;
        case 0x0d: DEC_8(&r->C, &r->F);                                         break;
        case 0x0e: MOV_8(&r->C, IMM_8);                                         break;
        case 0x0f: RRCA_8(&r->A, &r->F);                                        break;

        case 0x10: break;                                                       //TODO low power standby mode
        case 0x11: MOV_16(&r->DE, IMM_16);                                      break;
        case 0x12: STR_8(&mem[r->DE], r->A);                                    break;
        case 0x13: INC_16(&r->DE);                                              break;
        case 0x14: INC_8(&r->D, &r->F);                                         break;
        case 0x15: DEC_8(&r->D, &r->F);                                         break;
        case 0x16: MOV_8(&r->D, IMM_8);                                         break;
        case 0x17: RLA_8(&r->A, &r->F);                                         break;
        case 0x18: JR(&r->PC, IMM_8, NONE, &r->F);                              break;
        case 0x19: ADD_16(&r->HL, &r->DE, &r->F);                               break;
        case 0x1a: LDR_8(&r->A, &mem[r->DE]);                                   break;
        case 0x1b: DEC_16(&r->DE);                                              break;
        case 0x1c: INC_8(&r->E, &r->F);                                         break;
        case 0x1d: DEC_8(&r->E, &r->F);                                         break;
        case 0x1e: MOV_8(&r->E, IMM_8);                                         break;
        case 0x1f: RRA_8(&r->A, &r->F);                                         break;

        case 0x20: JR(&r->PC, IMM_8, MASK_NZ, &r->F);                           break;
        case 0x21: MOV_16(&r->HL, IMM_16);                                      break;
        case 0x22: STR_8(&mem[r->HL++], r->A);                                  break;
        case 0x23: INC_16(&r->HL);                                              break;
        case 0x24: INC_8(&r->H, &r->F);                                         break;
        case 0x25: DEC_8(&r->H, &r->F);                                         break;
        case 0x26: MOV_8(&r->H, IMM_8);                                         break;
        case 0x27: DAA(&r->A, &r->F);                                           break;
        case 0x28: JR(&r->PC, IMM_8, MASK_Z, &r->F);                            break;
        case 0x29: ADD_16(&r->HL, &r->HL, &r->F);                               break;
        case 0x2a: LDR_8(&r->A, &mem[r->HL++]);                                 break;
        case 0x2b: DEC_16(&r->HL);                                              break;
        case 0x2c: INC_8(&r->L, &r->F);                                         break;
        case 0x2d: DEC_8(&r->L, &r->F);                                         break;
        case 0x2e: MOV_8(&r->L, IMM_8);                                         break;
        case 0x2f: CPL(&r->A, &r->F);                                           break;

        case 0x30: JR(&r->PC, IMM_8, MASK_NC, &r->F);                           break;
        case 0x31: MOV_16(&r->SP, IMM_16);                                      break;
        case 0x32: STR_8(&mem[r->HL--], r->A);                                  break;
        case 0x33: INC_16(&r->SP);                                              break;
        case 0x34: INC_8(&mem[r->HL], &r->F);                                   break;
        case 0x35: DEC_8(&mem[r->HL], &r->F);                                   break;
        case 0x36: MOV_8(&mem[r->HL], IMM_8);                                   break;
        case 0x37: SCF(&r->F);                                                  break;
        case 0x38: JR(&r->PC, IMM_8, MASK_C, &r->F);                            break;
        case 0x39: ADD_16(&r->HL, &r->SP, &r->F);                               break;
        case 0x3a: LDR_8(&r->A, &mem[r->HL--]);                                 break;
        case 0x3b: DEC_16(&r->SP);                                              break;
        case 0x3c: INC_8(&r->A, &r->F);                                         break;
        case 0x3d: DEC_8(&r->A, &r->F);                                         break;
        case 0x3e: MOV_8(&r->A, IMM_8);                                         break;
        case 0x3f: CPL(&r->A, &r->F);                                           break;

        case 0x40: MOV_8(&r->B, r->B);                                          break;
        case 0x41: MOV_8(&r->B, r->C);                                          break;
        case 0x42: MOV_8(&r->B, r->D);                                          break;
        case 0x43: MOV_8(&r->B, r->E);                                          break;
        case 0x44: MOV_8(&r->B, r->H);                                          break;
        case 0x45: MOV_8(&r->B, r->L);                                          break;
        case 0x46: LDR_8(&r->B, &mem[r->HL]);                                   break;
        case 0x47: MOV_8(&r->B, r->A);                                          break;
        case 0x48: MOV_8(&r->C, r->B);                                          break;
        case 0x49: MOV_8(&r->C, r->C);                                          break;
        case 0x4a: MOV_8(&r->C, r->D);                                          break;
        case 0x4b: MOV_8(&r->C, r->E);                                          break;
        case 0x4c: MOV_8(&r->C, r->H);                                          break;
        case 0x4d: MOV_8(&r->C, r->L);                                          break;
        case 0x4e: LDR_8(&r->C, &mem[r->HL]);                                   break;
        case 0x4f: MOV_8(&r->C, r->A);                                          break;

        case 0x50: MOV_8(&r->D, r->B);                                          break;
        case 0x51: MOV_8(&r->D, r->C);                                          break;
        case 0x52: MOV_8(&r->D, r->D);                                          break;
        case 0x53: MOV_8(&r->D, r->E);                                          break;
        case 0x54: MOV_8(&r->D, r->H);                                          break;
        case 0x55: MOV_8(&r->D, r->L);                                          break;
        case 0x56: LDR_8(&r->D, &mem[r->HL]);                                   break;
        case 0x57: MOV_8(&r->D, r->A);                                          break;
        case 0x58: MOV_8(&r->E, r->B);                                          break;
        case 0x59: MOV_8(&r->E, r->C);                                          break;
        case 0x5a: MOV_8(&r->E, r->D);                                          break;
        case 0x5b: MOV_8(&r->E, r->E);                                          break;
        case 0x5c: MOV_8(&r->E, r->H);                                          break;
        case 0x5d: MOV_8(&r->E, r->L);                                          break;
        case 0x5e: LDR_8(&r->E, &mem[r->HL]);                                   break;
        case 0x5f: MOV_8(&r->E, r->A);                                          break;

        case 0x60: MOV_8(&r->H, r->B);                                          break;
        case 0x61: MOV_8(&r->H, r->C);                                          break;
        case 0x62: MOV_8(&r->H, r->D);                                          break;
        case 0x63: MOV_8(&r->H, r->E);                                          break;
        case 0x64: MOV_8(&r->H, r->H);                                          break;
        case 0x65: MOV_8(&r->H, r->L);                                          break;
        case 0x66: LDR_8(&r->H, &mem[r->HL]);                                   break;
        case 0x67: MOV_8(&r->H, r->A);                                          break;
        case 0x68: MOV_8(&r->L, r->B);                                          break;
        case 0x69: MOV_8(&r->L, r->C);                                          break;
        case 0x6a: MOV_8(&r->L, r->D);                                          break;
        case 0x6b: MOV_8(&r->L, r->E);                                          break;
        case 0x6c: MOV_8(&r->L, r->H);                                          break;
        case 0x6d: MOV_8(&r->L, r->L);                                          break;
        case 0x6e: LDR_8(&r->L, &mem[r->HL]);                                   break;
        case 0x6f: MOV_8(&r->L, r->A);                                          break;

        case 0x70: STR_8(&mem[r->HL], r->B);                                    break;
        case 0x71: STR_8(&mem[r->HL], r->C);                                    break;
        case 0x72: STR_8(&mem[r->HL], r->D);                                    break;
        case 0x73: STR_8(&mem[r->HL], r->E);                                    break;
        case 0x74: STR_8(&mem[r->HL], r->H);                                    break;
        case 0x75: STR_8(&mem[r->HL], r->L);                                    break;
        case 0x76: break;                                                       //TODO HALT
        case 0x77: STR_8(&mem[r->HL], r->A);                                    break;
        case 0x78: MOV_8(&r->A, r->B);                                          break;
        case 0x79: MOV_8(&r->A, r->C);                                          break;
        case 0x7a: MOV_8(&r->A, r->D);                                          break;
        case 0x7b: MOV_8(&r->A, r->E);                                          break;
        case 0x7c: MOV_8(&r->A, r->H);                                          break;
        case 0x7d: MOV_8(&r->A, r->L);                                          break;
        case 0x7e: LDR_8(&r->A, &mem[r->HL]);                                   break;
        case 0x7f: MOV_8(&r->A, r->A);                                          break;

        case 0x80: ADD_8(&r->A, &r->B, &r->F);                                  break;
        case 0x81: ADD_8(&r->A, &r->C, &r->F);                                  break;
        case 0x82: ADD_8(&r->A, &r->D, &r->F);                                  break;
        case 0x83: ADD_8(&r->A, &r->E, &r->F);                                  break;
        case 0x84: ADD_8(&r->A, &r->H, &r->F);                                  break;
        case 0x85: ADD_8(&r->A, &r->L, &r->F);                                  break;
        case 0x86: ADD_8(&r->A, &mem[r->HL], &r->F);                            break;
        case 0x87: ADD_8(&r->A, &r->A, &r->F);                                  break;
        case 0x88: ADC_8(&r->A, &r->B, &r->F);                                  break;
        case 0x89: ADC_8(&r->A, &r->C, &r->F);                                  break;
        case 0x8a: ADC_8(&r->A, &r->D, &r->F);                                  break;
        case 0x8b: ADC_8(&r->A, &r->E, &r->F);                                  break;
        case 0x8c: ADC_8(&r->A, &r->H, &r->F);                                  break;
        case 0x8d: ADC_8(&r->A, &r->L, &r->F);                                  break;
        case 0x8e: ADC_8(&r->A, &mem[r->HL], &r->F);                            break;
        case 0x8f: ADC_8(&r->A, &r->A, &r->F);                                  break;

        case 0x90: SUB_8(&r->A, &r->B, &r->F);                                  break;
        case 0x91: SUB_8(&r->A, &r->C, &r->F);                                  break;
        case 0x92: SUB_8(&r->A, &r->D, &r->F);                                  break;
        case 0x93: SUB_8(&r->A, &r->E, &r->F);                                  break;
        case 0x94: SUB_8(&r->A, &r->H, &r->F);                                  break;
        case 0x95: SUB_8(&r->A, &r->L, &r->F);                                  break;
        case 0x96: SUB_8(&r->A, &mem[r->HL], &r->F);                            break;
        case 0x97: SUB_8(&r->A, &r->A, &r->F);                                  break;
        case 0x98: SBC_8(&r->A, &r->B, &r->F);                                  break;
        case 0x99: SBC_8(&r->A, &r->C, &r->F);                                  break;
        case 0x9a: SBC_8(&r->A, &r->D, &r->F);                                  break;
        case 0x9b: SBC_8(&r->A, &r->E, &r->F);                                  break;
        case 0x9c: SBC_8(&r->A, &r->H, &r->F);                                  break;
        case 0x9d: SBC_8(&r->A, &r->L, &r->F);                                  break;
        case 0x9e: SBC_8(&r->A, &mem[r->HL], &r->F);                            break;
        case 0x9f: SBC_8(&r->A, &r->A, &r->F);                                  break;

        case 0xa0: AND_8(&r->A, &r->B, &r->F);                                  break;
        case 0xa1: AND_8(&r->A, &r->C, &r->F);                                  break;
        case 0xa2: AND_8(&r->A, &r->D, &r->F);                                  break;
        case 0xa3: AND_8(&r->A, &r->E, &r->F);                                  break;
        case 0xa4: AND_8(&r->A, &r->H, &r->F);                                  break;
        case 0xa5: AND_8(&r->A, &r->L, &r->F);                                  break;
        case 0xa6: AND_8(&r->A, &mem[r->HL], &r->F);                            break;
        case 0xa7: AND_8(&r->A, &r->A, &r->F);                                  break;
        case 0xa8: XOR_8(&r->A, &r->B, &r->F);                                  break;
        case 0xa9: XOR_8(&r->A, &r->C, &r->F);                                  break;
        case 0xaa: XOR_8(&r->A, &r->D, &r->F);                                  break;
        case 0xab: XOR_8(&r->A, &r->E, &r->F);                                  break;
        case 0xac: XOR_8(&r->A, &r->H, &r->F);                                  break;
        case 0xad: XOR_8(&r->A, &r->L, &r->F);                                  break;
        case 0xae: XOR_8(&r->A, &mem[r->HL], &r->F);                            break;
        case 0xaf: XOR_8(&r->A, &r->A, &r->F);                                  break;

        case 0xb0: OR_8(&r->A, &r->B, &r->F);                                   break;
        case 0xb1: OR_8(&r->A, &r->C, &r->F);                                   break;
        case 0xb2: OR_8(&r->A, &r->D, &r->F);                                   break;
        case 0xb3: OR_8(&r->A, &r->E, &r->F);                                   break;
        case 0xb4: OR_8(&r->A, &r->H, &r->F);                                   break;
        case 0xb5: OR_8(&r->A, &r->L, &r->F);                                   break;
        case 0xb6: OR_8(&r->A, &mem[r->HL], &r->F);                             break;
        case 0xb7: OR_8(&r->A, &r->A, &r->F);                                   break;
        case 0xb8: CP_8(&r->A, &r->B, &r->F);                                   break;
        case 0xb9: CP_8(&r->A, &r->C, &r->F);                                   break;
        case 0xba: CP_8(&r->A, &r->D, &r->F);                                   break;
        case 0xbb: CP_8(&r->A, &r->E, &r->F);                                   break;
        case 0xbc: CP_8(&r->A, &r->H, &r->F);                                   break;
        case 0xbd: CP_8(&r->A, &r->L, &r->F);                                   break;
        case 0xbe: CP_8(&r->A, &mem[r->HL], &r->F);                             break;
        case 0xbf: CP_8(&r->A, &r->A, &r->F);                                   break;

        case 0xc0: RET(&r->PC, &r->SP, MASK_NZ, &r->F);                         break;
        case 0xc1: POP_16(&r->BC, &mem[r->SP], &r->SP);                         break;
        case 0xc2: JP(&r->PC, IMM_16, MASK_NZ, &r->F);                          break;
        case 0xc3: JP(&r->PC, IMM_16, NONE, &r->F);                             break;
        case 0xc4: CALL(&r->PC, &r->SP, &mem[r->SP], IMM_16, MASK_NZ, &r->F);   break;
        case 0xc5: PUSH_16(&r->BC, &mem[r->SP], &r->SP);                        break;
        case 0xc6: ADD_8(&r->A, &IMM_8, &r->F);                                 break;
        case 0xc7: RST(&r->PC, &r->SP, &mem[r->SP], 0x00);                      break;
        case 0xc8: RET(&r->PC, &r->SP, MASK_Z, &r->F);                          break;
        case 0xc9: RET(&r->PC, &r->SP, NONE, &r->F);                            break;
        case 0xca: JP(&r->PC, IMM_16, MASK_Z, &r->F);                           break;
        case 0xcb: goto prefix_cb;                                              break;
        case 0xcc: CALL(&r->PC, &r->SP, &mem[r->SP], IMM_16, MASK_Z, &r->F);    break;
        case 0xcd: CALL(&r->PC, &r->SP, &mem[r->SP], IMM_16, NONE, &r->F);      break;
        case 0xce: ADC_8(&r->A, &IMM_8, &r->F);                                 break;
        case 0xcf: RST(&r->PC, &r->SP, &mem[r->SP], 0x08);                      break;

        case 0xd0: RET(&r->PC, &r->SP, MASK_NC, &r->F);                         break;
        case 0xd1: POP_16(&r->DE, &mem[r->SP], &r->SP);                         break;
        case 0xd2: JP(&r->PC, IMM_16, MASK_NC, &r->F);                          break;
        case 0xd3: goto trap;                                                   break;
        case 0xd4: CALL(&r->PC, &r->SP, &mem[r->SP], IMM_16, MASK_NC, &r->F);   break;
        case 0xd5: PUSH_16(&r->DE, &mem[r->SP], &r->SP);                        break;
        case 0xd6: SUB_8(&r->A, &IMM_8, &r->F);                                 break;
        case 0xd7: RST(&r->PC, &r->SP, &mem[r->SP], 0x10);                      break;
        case 0xd8: RET(&r->PC, &r->SP, MASK_C, &r->F);                          break;
        case 0xd9: RETI(&r->PC, &r->SP, &r->IME);                               break;
        case 0xda: JP(&r->PC, IMM_16, MASK_C, &r->F);                           break;
        case 0xdb: goto trap;                                                   break;
        case 0xdc: CALL(&r->PC, &r->SP, &mem[r->SP], IMM_16, MASK_C, &r->F);    break;
        case 0xdd: goto trap;                                                   break;
        case 0xde: SBC_8(&r->A, &IMM_8, &r->F);                                 break;
        case 0xdf: RST(&r->PC, &r->SP, &mem[r->SP], 0x18);                      break;

        case 0xe0: STR_8(&mem[ IMM_8 + 0xff00 ], &r->A);                        break;
        case 0xe1: POP_16(&r->HL, &mem[r->SP], &r->SP);                         break;
        case 0xe2: STR_8(&mem[r->C], &r->A);                                    break;
        case 0xe3: goto trap;                                                   break;
        case 0xe4: goto trap;                                                   break;
        case 0xe5: PUSH_16(&r->HL, &mem[r->SP], &r->SP);                        break;
        case 0xe6: AND_8(&r->A, &IMM_8, &r->F);                                 break;
        case 0xe7: RST(&r->PC, &r->SP, &mem[r->SP], 0x20);                      break;
        case 0xe8: ADD_16(&r->SP, &IMM_8, &r->F);                               break;
        case 0xe9: JP(&r->PC, &mem[r->HL], NONE, &r->F);                        break;
        case 0xea: STR_8(&mem[IMM_16], &r->A);                                  break;
        case 0xeb: goto trap;                                                   break;
        case 0xec: goto trap;                                                   break;
        case 0xed: goto trap;                                                   break;
        case 0xee: XOR_8(&r->A, &IMM_8, &r->F);                                 break;
        case 0xef: RST(&r->PC, &r->SP, &mem[r->SP], 0x38);                      break;
    }
    return 0;

    prefix_cb: 
    op = mem[r->PC++];
    switch(op) {
        case 0x00: RLC_8(&r->B, &r->F);                                         break;
        case 0x01: RLC_8(&r->C, &r->F);                                         break;
        case 0x02: RLC_8(&r->D, &r->F);                                         break;
        case 0x03: RLC_8(&r->E, &r->F);                                         break;
        case 0x04: RLC_8(&r->H, &r->F);                                         break;
        case 0x05: RLC_8(&r->L, &r->F);                                         break;
        case 0x06: RLC_8(&mem[r->HL], &r->F);                                   break;
        case 0x07: RLC_8(&r->A, &r->F);                                         break;
        case 0x08: RRC_8(&r->B, &r->F);                                         break;
        case 0x09: RRC_8(&r->C, &r->F);                                         break;
        case 0x0a: RRC_8(&r->D, &r->F);                                         break;
        case 0x0b: RRC_8(&r->E, &r->F);                                         break;
        case 0x0c: RRC_8(&r->H, &r->F);                                         break;
        case 0x0d: RRC_8(&r->L, &r->F);                                         break;
        case 0x0e: RRC_8(&mem[r->HL], &r->F);                                   break;
        case 0x0f: RRC_8(&r->A, &r->F);                                         break;

        case 0x10: RL_8(&r->B, &r->F);                                          break;
        case 0x11: RL_8(&r->C, &r->F);                                          break;
        case 0x12: RL_8(&r->D, &r->F);                                          break;
        case 0x13: RL_8(&r->E, &r->F);                                          break;
        case 0x14: RL_8(&r->H, &r->F);                                          break;
        case 0x15: RL_8(&r->L, &r->F);                                          break;
        case 0x16: RL_8(&mem[r->HL], &r->F);                                    break;
        case 0x17: RL_8(&r->A, &r->F);                                          break;
        case 0x18: RR_8(&r->B, &r->F);                                          break;
        case 0x19: RR_8(&r->C, &r->F);                                          break;
        case 0x1a: RR_8(&r->D, &r->F);                                          break;
        case 0x1b: RR_8(&r->E, &r->F);                                          break;
        case 0x1c: RR_8(&r->H, &r->F);                                          break;
        case 0x1d: RR_8(&r->L, &r->F);                                          break;
        case 0x1e: RR_8(&mem[r->HL], &r->F);                                    break;
        case 0x1f: RR_8(&r->A, &r->F);                                          break;

        case 0x20: SLA_8(&r->B, &r->F);                                         break;
        case 0x21: SLA_8(&r->C, &r->F);                                         break;
        case 0x22: SLA_8(&r->D, &r->F);                                         break;
        case 0x23: SLA_8(&r->E, &r->F);                                         break;
        case 0x24: SLA_8(&r->H, &r->F);                                         break;
        case 0x25: SLA_8(&r->L, &r->F);                                         break;
        case 0x26: SLA_8(&mem[r->HL], &r->F);                                   break;
        case 0x27: SLA_8(&r->A, &r->F);                                         break;
        case 0x28: SRA_8(&r->B, &r->F);                                         break;
        case 0x29: SRA_8(&r->C, &r->F);                                         break;
        case 0x2a: SRA_8(&r->D, &r->F);                                         break;
        case 0x2b: SRA_8(&r->E, &r->F);                                         break;
        case 0x2c: SRA_8(&r->H, &r->F);                                         break;
        case 0x2d: SRA_8(&r->L, &r->F);                                         break;
        case 0x2e: SRA_8(&mem[r->HL], &r->F);                                   break;
        case 0x2f: SRA_8(&r->A, &r->F);                                         break;

        case 0x30: SWAP_8(&r->B, &r->F);                                        break;
        case 0x31: SWAP_8(&r->C, &r->F);                                        break;
        case 0x32: SWAP_8(&r->D, &r->F);                                        break;
        case 0x33: SWAP_8(&r->E, &r->F);                                        break;
        case 0x34: SWAP_8(&r->H, &r->F);                                        break;
        case 0x35: SWAP_8(&r->L, &r->F);                                        break;
        case 0x36: SWAP_8(&mem[r->HL], &r->F);                                  break;
        case 0x37: SWAP_8(&r->A, &r->F);                                        break;
        case 0x38: SRL_8(&r->B, &r->F);                                         break;
        case 0x39: SRL_8(&r->C, &r->F);                                         break;
        case 0x3a: SRL_8(&r->D, &r->F);                                         break;
        case 0x3b: SRL_8(&r->E, &r->F);                                         break;
        case 0x3c: SRL_8(&r->H, &r->F);                                         break;
        case 0x3d: SRL_8(&r->L, &r->F);                                         break;
        case 0x3e: SRL_8(&mem[r->HL], &r->F);                                   break;
        case 0x3f: SRL_8(&r->A, &r->F);                                         break;

        case 0x40: BIT(&r->B, 0, &r->F);                                        break;
        case 0x41: BIT(&r->C, 0, &r->F);                                        break;
        case 0x42: BIT(&r->D, 0, &r->F);                                        break;
        case 0x43: BIT(&r->E, 0, &r->F);                                        break;
        case 0x44: BIT(&r->H, 0, &r->F);                                        break;
        case 0x45: BIT(&r->L, 0, &r->F);                                        break;
        case 0x46: BIT(&mem[r->HL], 0, &r->F);                                  break;
        case 0x47: BIT(&r->A, 0, &r->F);                                        break;
        case 0x48: BIT(&r->B, 1, &r->F);                                        break;
        case 0x49: BIT(&r->C, 1, &r->F);                                        break;
        case 0x4a: BIT(&r->D, 1, &r->F);                                        break;
        case 0x4b: BIT(&r->E, 1, &r->F);                                        break;
        case 0x4c: BIT(&r->H, 1, &r->F);                                        break;
        case 0x4d: BIT(&r->L, 1, &r->F);                                        break;
        case 0x4e: BIT(&mem[r->HL], 1, &r->F);                                  break;
        case 0x4f: BIT(&r->A, 1, &r->F);                                        break;

        case 0x50: BIT(&r->B, 2, &r->F);                                        break;
        case 0x51: BIT(&r->C, 2, &r->F);                                        break;
        case 0x52: BIT(&r->D, 2, &r->F);                                        break;
        case 0x53: BIT(&r->E, 2, &r->F);                                        break;
        case 0x54: BIT(&r->H, 2, &r->F);                                        break;
        case 0x55: BIT(&r->L, 2, &r->F);                                        break;
        case 0x56: BIT(&mem[r->HL], 2, &r->F);                                  break;
        case 0x57: BIT(&r->A, 2, &r->F);                                        break;
        case 0x58: BIT(&r->B, 3, &r->F);                                        break;
        case 0x59: BIT(&r->C, 3, &r->F);                                        break;
        case 0x5a: BIT(&r->D, 3, &r->F);                                        break;
        case 0x5b: BIT(&r->E, 3, &r->F);                                        break;
        case 0x5c: BIT(&r->H, 3, &r->F);                                        break;
        case 0x5d: BIT(&r->L, 3, &r->F);                                        break;
        case 0x5e: BIT(&mem[r->HL], 3, &r->F);                                  break;
        case 0x5f: BIT(&r->A, 3, &r->F);                                        break;

        case 0x60: BIT(&r->B, 4, &r->F);                                        break;
        case 0x61: BIT(&r->C, 4, &r->F);                                        break;
        case 0x62: BIT(&r->D, 4, &r->F);                                        break;
        case 0x63: BIT(&r->E, 4, &r->F);                                        break;
        case 0x64: BIT(&r->H, 4, &r->F);                                        break;
        case 0x65: BIT(&r->L, 4, &r->F);                                        break;
        case 0x66: BIT(&mem[r->HL], 4, &r->F);                                  break;
        case 0x67: BIT(&r->A, 4, &r->F);                                        break;
        case 0x68: BIT(&r->B, 5, &r->F);                                        break;
        case 0x69: BIT(&r->C, 5, &r->F);                                        break;
        case 0x6a: BIT(&r->D, 5, &r->F);                                        break;
        case 0x6b: BIT(&r->E, 5, &r->F);                                        break;
        case 0x6c: BIT(&r->H, 5, &r->F);                                        break;
        case 0x6d: BIT(&r->L, 5, &r->F);                                        break;
        case 0x6e: BIT(&mem[r->HL], 5, &r->F);                                  break;
        case 0x6f: BIT(&r->A, 5, &r->F);                                        break;

        case 0x70: BIT(&r->B, 6, &r->F);                                        break;
        case 0x71: BIT(&r->C, 6, &r->F);                                        break;
        case 0x72: BIT(&r->D, 6, &r->F);                                        break;
        case 0x73: BIT(&r->E, 6, &r->F);                                        break;
        case 0x74: BIT(&r->H, 6, &r->F);                                        break;
        case 0x75: BIT(&r->L, 6, &r->F);                                        break;
        case 0x76: BIT(&mem[r->HL], 6, &r->F);                                  break;
        case 0x77: BIT(&r->A, 6, &r->F);                                        break;
        case 0x78: BIT(&r->B, 7, &r->F);                                        break;
        case 0x79: BIT(&r->C, 7, &r->F);                                        break;
        case 0x7a: BIT(&r->D, 7, &r->F);                                        break;
        case 0x7b: BIT(&r->E, 7, &r->F);                                        break;
        case 0x7c: BIT(&r->H, 7, &r->F);                                        break;
        case 0x7d: BIT(&r->L, 7, &r->F);                                        break;
        case 0x7e: BIT(&mem[r->HL], 7, &r->F);                                  break;
        case 0x7f: BIT(&r->A, 7, &r->F);                                        break;

        case 0x80: RES(&r->B, 0);                                               break;
        case 0x81: RES(&r->C, 0);                                               break;
        case 0x82: RES(&r->D, 0);                                               break;
        case 0x83: RES(&r->E, 0);                                               break;
        case 0x84: RES(&r->H, 0);                                               break;
        case 0x85: RES(&r->L, 0);                                               break;
        case 0x86: RES(&mem[r->HL], 0);                                         break;
        case 0x87: RES(&r->A, 0);                                               break;
        case 0x88: RES(&r->B, 1);                                               break;
        case 0x89: RES(&r->C, 1);                                               break;
        case 0x8a: RES(&r->D, 1);                                               break;
        case 0x8b: RES(&r->E, 1);                                               break;
        case 0x8c: RES(&r->H, 1);                                               break;
        case 0x8d: RES(&r->L, 1);                                               break;
        case 0x8e: RES(&mem[r->HL], 1);                                         break;
        case 0x8f: RES(&r->A, 1);                                               break;

        case 0x90: RES(&r->B, 2);                                               break;
        case 0x91: RES(&r->C, 2);                                               break;
        case 0x92: RES(&r->D, 2);                                               break;
        case 0x93: RES(&r->E, 2);                                               break;
        case 0x94: RES(&r->H, 2);                                               break;
        case 0x95: RES(&r->L, 2);                                               break;
        case 0x96: RES(&mem[r->HL], 2);                                         break;
        case 0x97: RES(&r->A, 2);                                               break;
        case 0x98: RES(&r->B, 3);                                               break;
        case 0x99: RES(&r->C, 3);                                               break;
        case 0x9a: RES(&r->D, 3);                                               break;
        case 0x9b: RES(&r->E, 3);                                               break;
        case 0x9c: RES(&r->H, 3);                                               break;
        case 0x9d: RES(&r->L, 3);                                               break;
        case 0x9e: RES(&mem[r->HL], 3);                                         break;
        case 0x9f: RES(&r->A, 3);                                               break;

        case 0xa0: RES(&r->B, 4);                                               break;
        case 0xa1: RES(&r->C, 4);                                               break;
        case 0xa2: RES(&r->D, 4);                                               break;
        case 0xa3: RES(&r->E, 4);                                               break;
        case 0xa4: RES(&r->H, 4);                                               break;
        case 0xa5: RES(&r->L, 4);                                               break;
        case 0xa6: RES(&mem[r->HL], 4);                                         break;
        case 0xa7: RES(&r->A, 4);                                               break;
        case 0xa8: RES(&r->B, 5);                                               break;
        case 0xa9: RES(&r->C, 5);                                               break;
        case 0xaa: RES(&r->D, 5);                                               break;
        case 0xab: RES(&r->E, 5);                                               break;
        case 0xac: RES(&r->H, 5);                                               break;
        case 0xad: RES(&r->L, 5);                                               break;
        case 0xae: RES(&mem[r->HL], 5);                                         break;
        case 0xaf: RES(&r->A, 5);                                               break;

        case 0xb0: RES(&r->B, 6);                                               break;
        case 0xb1: RES(&r->C, 6);                                               break;
        case 0xb2: RES(&r->D, 6);                                               break;
        case 0xb3: RES(&r->E, 6);                                               break;
        case 0xb4: RES(&r->H, 6);                                               break;
        case 0xb5: RES(&r->L, 6);                                               break;
        case 0xb6: RES(&mem[r->HL], 6);                                         break;
        case 0xb7: RES(&r->A, 6);                                               break;
        case 0xb8: RES(&r->B, 7);                                               break;
        case 0xb9: RES(&r->C, 7);                                               break;
        case 0xba: RES(&r->D, 7);                                               break;
        case 0xbb: RES(&r->E, 7);                                               break;
        case 0xbc: RES(&r->H, 7);                                               break;
        case 0xbd: RES(&r->L, 7);                                               break;
        case 0xbe: RES(&mem[r->HL], 7);                                         break;
        case 0xbf: RES(&r->A, 7);                                               break;

        case 0xc0: SET(&r->B, 0);                                               break;
        case 0xc1: SET(&r->C, 0);                                               break;
        case 0xc2: SET(&r->D, 0);                                               break;
        case 0xc3: SET(&r->E, 0);                                               break;
        case 0xc4: SET(&r->H, 0);                                               break;
        case 0xc5: SET(&r->L, 0);                                               break;
        case 0xc6: SET(&mem[r->HL], 0);                                         break;
        case 0xc7: SET(&r->A, 0);                                               break;
        case 0xc8: SET(&r->B, 1);                                               break;
        case 0xc9: SET(&r->C, 1);                                               break;
        case 0xca: SET(&r->D, 1);                                               break;
        case 0xcb: SET(&r->E, 1);                                               break;
        case 0xcc: SET(&r->H, 1);                                               break;
        case 0xcd: SET(&r->L, 1);                                               break;
        case 0xce: SET(&mem[r->HL], 1);                                         break;
        case 0xcf: SET(&r->A, 1);                                               break;

        case 0xd0: SET(&r->B, 2);                                               break;
        case 0xd1: SET(&r->C, 2);                                               break;
        case 0xd2: SET(&r->D, 2);                                               break;
        case 0xd3: SET(&r->E, 2);                                               break;
        case 0xd4: SET(&r->H, 2);                                               break;
        case 0xd5: SET(&r->L, 2);                                               break;
        case 0xd6: SET(&mem[r->HL], 2);                                         break;
        case 0xd7: SET(&r->A, 2);                                               break;
        case 0xd8: SET(&r->B, 3);                                               break;
        case 0xd9: SET(&r->C, 3);                                               break;
        case 0xda: SET(&r->D, 3);                                               break;
        case 0xdb: SET(&r->E, 3);                                               break;
        case 0xdc: SET(&r->H, 3);                                               break;
        case 0xdd: SET(&r->L, 3);                                               break;
        case 0xde: SET(&mem[r->HL], 3);                                         break;
        case 0xdf: SET(&r->A, 3);                                               break;

        case 0xe0: SET(&r->B, 4);                                               break;
        case 0xe1: SET(&r->C, 4);                                               break;
        case 0xe2: SET(&r->D, 4);                                               break;
        case 0xe3: SET(&r->E, 4);                                               break;
        case 0xe4: SET(&r->H, 4);                                               break;
        case 0xe5: SET(&r->L, 4);                                               break;
        case 0xe6: SET(&mem[r->HL], 4);                                         break;
        case 0xe7: SET(&r->A, 4);                                               break;
        case 0xe8: SET(&r->B, 5);                                               break;
        case 0xe9: SET(&r->C, 5);                                               break;
        case 0xea: SET(&r->D, 5);                                               break;
        case 0xeb: SET(&r->E, 5);                                               break;
        case 0xec: SET(&r->H, 5);                                               break;
        case 0xed: SET(&r->L, 5);                                               break;
        case 0xee: SET(&mem[r->HL], 5);                                         break;
        case 0xef: SET(&r->A, 5);                                               break;

        case 0xf0: SET(&r->B, 6);                                               break;
        case 0xf1: SET(&r->C, 6);                                               break;
        case 0xf2: SET(&r->D, 6);                                               break;
        case 0xf3: SET(&r->E, 6);                                               break;
        case 0xf4: SET(&r->H, 6);                                               break;
        case 0xf5: SET(&r->L, 6);                                               break;
        case 0xf6: SET(&mem[r->HL], 6);                                         break;
        case 0xf7: SET(&r->A, 6);                                               break;
        case 0xf8: SET(&r->B, 7);                                               break;
        case 0xf9: SET(&r->C, 7);                                               break;
        case 0xfa: SET(&r->D, 7);                                               break;
        case 0xfb: SET(&r->E, 7);                                               break;
        case 0xfc: SET(&r->H, 7);                                               break;
        case 0xfd: SET(&r->L, 7);                                               break;
        case 0xfe: SET(&mem[r->HL], 7);                                         break;
        case 0xff: SET(&r->A, 7);                                               break;
    }
    return 0;

    trap: 
    return 1;
}
