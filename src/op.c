#include <cpu.h>
#include <stdint.h>

#define printh(A) printf("0x%x\n", A)

/*==================================
 * MOV:
 *  Move src into dst
 =================================*/
void MOV_8(uint8_t *dst, uint8_t src)
{
    *dst = src;
}

void MOV_16(uint16_t *dst, uint16_t src)
{
    *dst = src;
}

/*==================================
 * LDR:
 *  load value at addr src
 *  into dst
 =================================*/
void LDR_8(uint8_t *dst, uint8_t *src)
{
    *dst = *src;
}

void LDR_16(uint16_t *dst, uint16_t *src)
{
    *dst = *src;
}

void POP_16(uint16_t *dst, uint16_t *src, uint16_t* SP)
{
    *dst = *src;
    *SP = *SP + 2;
}

void PUSH_16(uint16_t *src, uint16_t *dst, uint16_t* SP)
{
    *dst = *src;
    *SP = *SP - 2;
}

/*==================================
 * STR:
 *  store value at addr src 
 *  into dst
 =================================*/
void STR_8(uint8_t *dst, uint8_t src)
{
    *dst = src;
}

void STR_16(uint8_t *dst, uint16_t src)
{
    *((uint16_t*)dst) = src;
}

/*==================================
 * INC:
 *  Increment reg by 1
 =================================*/
void INC_8(uint8_t *reg, flags *f)
{
    uint8_t res = *reg + 1;
    f->z = res == 0;
    f->n = 0;
    f->h = (0x10 & ((*reg & 0xf) + 0x1)) >> 4;
    *reg = res;
}

void INC_16(uint16_t *reg)
{
    uint16_t res = *reg + 1;
    *reg = res;
}

/*==================================
 * DEC:
 *  decrement reg by 1
 =================================*/
void DEC_8(uint8_t *reg, flags *f)
{
    uint8_t res = *reg - 1;
    f->z = res == 0;
    f->n = 1;
    f->h = (0x10 & ((*reg & 0xf) - 0x1)) >> 4;
    *reg = res;
}

void DEC_16(uint16_t *reg)
{
    uint16_t res = *reg - 1;
    *reg = res;
}


/*==================================
 * RLCA:
 *  Rotate Left
 =================================*/
void RLCA_8(uint8_t *reg, flags *f)
{
    uint8_t res = *reg << 1 | *reg >> 7;
    f->c = *reg >> 7;
    *reg = res;
}

/*==================================
 * RLA:
 *  Rotate Left through carry
 =================================*/
void RLA_8(uint8_t *reg, flags *f)
{
    uint8_t res = *reg << 1 | f->c;
    f->c = *reg >> 7;
    *reg = res;
}

/*==================================
 * RRCA:
 *  Rotate Right
 =================================*/
void RRCA_8(uint8_t *reg, flags *f)
{
    uint8_t res = *reg >> 1 | *reg << 7;
    f->c = *reg & 0x1;
    *reg = res;
}

/*==================================
 * RRA:
 *  Rotate Reft through carry
 =================================*/
void RRA_8(uint8_t *reg, flags *f)
{
    uint8_t res = *reg >> 1 | f->c << 7;
    f->c = *reg & 0x1;
    *reg = res;
}

/*==================================
 CPL:
 *  bitwise negate
 =================================*/
void CPL(uint8_t *reg, flags *f)
{
    *reg = ~*reg;
    f->n = 1;
    f->h = 1;
}

/*==================================
 * ADD:
 *  r1 = r1 + r2
 =================================*/
void ADD_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 + *r2;
    f->z = res == 0x00;
    f->n = 0;
    f->h = (0x10 & ((*r1 & 0xf) + (*r2 & 0xf))) >> 4;
    f->c = res < *r1;
    *r1 = res;
}

void ADD_16(uint16_t *r1, uint16_t *r2, flags *f)
{
    uint16_t res = *r1 + *r2;
    f->n = 0;
    f->h = (0x10 & ((*r1 & 0xf) + (*r2 & 0xf))) >> 4;
    f->c = res < *r1;
    *r1 = res;
}

/*==================================
 * ADC:
 *  r1 = r1 + r2 + c
 =================================*/
void ADC_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 + *r2 + f->c;
    f->z = res == 0x00;
    f->n = 0;
    f->h = (0x10 & ((*r1 & 0xf) + (*r2 & 0xf) + f->c)) >> 4;
    f->c = res < *r1;
    *r1 = res;
}

void ADC_16(uint16_t *r1, uint16_t *r2, flags *f)
{
    uint16_t res = *r1 + *r2 + f->c;
    f->n = 0;
    f->h = (0x10 & ((*r1 & 0xf) + (*r2 & 0xf) + f->c)) >> 4;
    f->c = res < *r1;
    *r1 = res;
}

/*==================================
 * SUB:
 *  r1 = r1 - r2
 =================================*/
void SUB_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 - *r2;
    f->z = res == 0x00;
    f->n = 1;
    f->h = (0x10 & ((*r1 & 0xf) - (*r2 & 0xf))) >> 4;
    f->c = res > *r1;
    *r1 = res;
}

void SUB_16(uint16_t *r1, uint16_t *r2, flags *f)
{
    uint16_t res = *r1 - *r2;
    f->n = 1;
    f->h = (0x10 & ((*r1 & 0xf) - (*r2 & 0xf))) >> 4;
    f->c = res > *r1;
    *r1 = res;
}

void SBC_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 - *r2 - f->c;
    f->z = res == 0x00;
    f->n = 1;
    f->h = (0x10 & ((*r1 & 0xf) - (*r2 & 0xf) - f->c)) >> 4;
    f->c = res > *r1;
    *r1 = res;
}

void SBC_16(uint16_t *r1, uint16_t *r2, flags *f)
{
    uint16_t res = *r1 - *r2 - f->c;
    f->n = 1;
    f->h = (0x10 & ((*r1 & 0xf) - (*r2 & 0xf) - f->c)) >> 4;
    f->c = res > *r1;
    *r1 = res;
}

void CP_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 - *r2;
    f->z = res == 0x00;
    f->n = 1;
    f->h = (0x10 & ((*r1 & 0xf) - (*r2 & 0xf))) >> 4;
    f->c = res > *r1;
}

void AND_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 & *r2;
    f->z = res == 0x00;
    f->n = 0;
    f->h = 1;
    f->c = 0;
    *r1 = res;
}

void XOR_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 ^ *r2;
    f->z = res == 0x00;
    f->n = 0;
    f->h = 0;
    f->c = 0;
    *r1 = res;
}

void OR_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 | *r2;
    f->z = res == 0x00;
    f->n = 0;
    f->h = 0;
    f->c = 0;
    *r1 = res;
}

/*==================================
 * JP:
 *  Conditional jump
 *
 =================================*/
void JP(uint16_t *PC, uint16_t imm, uint8_t mask, flags *f)
{
    if(~mask | *((uint8_t*)f)){
        *PC = imm;
    }
}

/*==================================
 * CALL:
 *  Conditional call
 *
 =================================*/
void CALL(uint16_t *PC, uint16_t *SP, uint16_t *stack, uint16_t imm, uint8_t mask, flags *f)
{
    if(~mask | *((uint8_t*)f)){
        *SP = *SP - 2;
        *stack = *PC;
        *PC = imm;
    }
}

void RST(uint16_t *PC, uint16_t *SP, uint16_t *stack, uint16_t imm)
{
    *SP = *SP - 2;
    *stack = *PC;
    *PC = imm;
}

/*==================================
 * JR:
 *  Conditional Relative jump
 *
 * NOTE - mask[0:3] unused
 =================================*/
void JR(uint16_t *PC, uint8_t imm, uint8_t mask, flags *f)
{
    if(~mask | *((uint8_t*)f)){
        *PC = *PC + (int8_t)imm;
    }
}

/*==================================
 * RET:
 *  Conditional return
 *
 * NOTE - mask[0:3] unused
 =================================*/
void RET(uint16_t *PC, uint16_t *SP, uint8_t mask, flags *f)
{
    if(~mask | *((uint8_t*)f)){
        *PC = *SP;
        *SP = *SP + 2;
    }
}

void RETI(uint16_t *PC, uint16_t *SP, uint8_t *IME)
{
    *PC = *SP;
    *SP = *SP + 2;
    *IME = 1;
}

/*==================================
 * DDA:
 *  BCD Decimal Adjust
 *  Retroactively converts previous
 *  ADD/SUB op into BCD ADD/SUB
 *  using N, H, C flags
 *================================*/
void DAA(uint8_t *reg, flags *f)
{
    uint8_t res = *reg;
    if(f->n){
        if(f->c) res -= 0x60; 
        if(f->h) res -= 0x6;
        if((res & 0xf) > 0x9) res -= 0x6;
        if(res > 0x99) res += 0xa0;

        f->c |= res > *reg;
    } else {
        if(f->c) res += 0x60; 
        if(f->h) res += 0x6;
        if((res & 0xf) > 0x9) res += 0x6;
        if(res > 0x99) res -= 0xa0;

        f->c |= res < *reg;
    }
    *reg = res;
    f->z = res == 0;
    f->h = 0;
}

/*==================================
 * SCF:
 *  set carry flag
 =================================*/
void SCF(flags *f)
{
    f->c = 1;
    f->h = 0;
    f->n = 0;
}

/*==================================
 CCF:
 *  flip carry flag
 =================================*/
void CCF(flags *f)
{
    f->c = ~(f->c);
    f->h = 0;
    f->n = 0;
}
