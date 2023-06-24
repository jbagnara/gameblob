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

void LDR_16(uint16_t *dst, uint16_t *src)
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

void STR_16(uint16_t *dst, uint16_t src)
{
    *dst = src;
}

/*==================================
 * INC:
 *  Increment reg by 1
 =================================*/
void INC_8(uint8_t *reg, flags f)
{
    uint8_t res = *reg + 1;
    f.z = res == 0;
    f.n = 0;
    f.h = (0x10 & (*reg & 0xf + 0x1)) >> 4;
    *reg = res;
}

void INC_16(uint8_t *reg)
{
    uint16_t res = *reg + 1;
    *reg = res;
}
