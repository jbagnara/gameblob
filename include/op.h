#include <cpu.h>

void MOV_8(uint8_t *dst, uint8_t src);
void MOV_16(uint16_t *dst, uint16_t src);
void LDR_8(uint8_t *dst, uint8_t *src);
void LDR_16(uint16_t *dst, uint16_t *src);
void STR_8(uint8_t *dst, uint8_t src);
void STR_16(uint16_t *dst, uint16_t src);
void INC_8(uint8_t *reg, flags *f);
void INC_16(uint16_t *reg);
