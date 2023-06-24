#include <cpu.h>

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
void LDR_8(uint8_t *dst, uint8_t src)
{
    *dst = src;
}

void LDR_16(uint16_t *dst, uint16_t src)
{
    *dst = src;
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
    f->h = (0x10 & (*reg & 0xf + 0x1)) >> 4;
    *reg = res;
}

void INC_16(uint8_t *reg)
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
    f->h = (0x10 & (*reg & 0xf - 0x1)) >> 4;
    *reg = res;
}

void DEC_16(uint8_t *reg)
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
 * ADD:
 *  r1 = r1 + r2
 =================================*/
void ADD_8(uint8_t *r1, uint8_t *r2, flags *f)
{
    uint8_t res = *r1 + *r2;
    f->z = res == 0x00;
    f->n = 0;
    f->h = (0x10 & (*r1 & 0xf + *r2 & 0xf)) >> 4;
    f->c = res < r1;
    *r1 = res;
}

void ADD_16(uint16_t *r1, uint16_t *r2, flags *f)
{
    uint16_t res = *r1 + *r2;
    f->n = 0;
    f->h = (0x10 & (*r1 & 0xf + *r2 & 0xf)) >> 4;
    f->c = res < r1;
    r1 = res;
}

/*==================================
 * JR:
 *  Conditional Relative jump
 *  If mask NXOR flags; do
 *  PC = PC + imm
 *
 * NOTE - mask[0:3] unused
 =================================*/
void JR(uint16_t *PC, uint8_t imm, uint8_t mask, uint8_t f){
    if(~mask | f){
        *PC = *PC + (int8_t)imm;
    }
}
