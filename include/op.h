#include <cpu.h>
#include <stdint.h>

void MOV_8(uint8_t *dst, uint8_t src);
void MOV_16(uint16_t *dst, uint16_t src);
void LDR_8(uint8_t *dst, uint8_t *src);
void LDR_16(uint16_t *dst, uint16_t* src);
void POP_16(uint16_t *dst, uint16_t *src, uint16_t* SP);
void PUSH_16(uint16_t *src, uint16_t *dst, uint16_t* SP);
void STR_8(uint8_t *dst, uint8_t src);
void STR_16(uint8_t *dst, uint16_t src);
void INC_8(uint8_t *reg, cpuflags_t *f);
void INC_16(uint16_t *reg);
void DEC_8(uint8_t *reg, cpuflags_t *f);
void DEC_16(uint16_t *reg);
void RLCA_8(uint8_t *reg, cpuflags_t *f);
void RLA_8(uint8_t *reg, cpuflags_t *f);
void RRCA_8(uint8_t *reg, cpuflags_t *f);
void RRA_8(uint8_t *reg, cpuflags_t *f);
void CPL(uint8_t *reg, cpuflags_t *f);
void ADD_8(uint8_t *r1, uint8_t *r2, cpuflags_t *f);
void ADD_16(uint16_t *r1, uint16_t *r2, cpuflags_t *f);
void ADC_8(uint8_t *r1, uint8_t *r2, cpuflags_t *f);
void ADC_16(uint16_t *r1, uint16_t *r2, cpuflags_t *f);
void SUB_8(uint8_t *r1, uint8_t *r2, cpuflags_t *f);
void SUB_16(uint16_t *r1, uint16_t *r2, cpuflags_t *f);
void SBC_8(uint8_t *r1, uint8_t *r2, cpuflags_t *f);
void SBC_16(uint16_t *r1, uint16_t *r2, cpuflags_t *f);
void CP_8(uint8_t *r1, uint8_t *r2, cpuflags_t *f);
void AND_8(uint8_t *r1, uint8_t *r2, cpuflags_t *f);
void XOR_8(uint8_t *r1, uint8_t *r2, cpuflags_t *f);
void OR_8(uint8_t *r1, uint8_t *r2, cpuflags_t *f);
void CALL(uint16_t *PC, uint16_t *SP, uint16_t *stack, uint16_t imm, uint8_t mask, cpuflags_t *f);
void RST(uint16_t *PC, uint16_t *SP, uint16_t *stack, uint16_t imm);
void JR(uint16_t *PC, uint16_t imm, uint8_t mask, cpuflags_t *f);
void RET(uint16_t *PC, uint16_t *SP, uint8_t mask, cpuflags_t *f);
void DAA(uint8_t *reg, cpuflags_t *f);
void SCF(cpuflags_t *f);
void CCF(cpuflags_t *f);
