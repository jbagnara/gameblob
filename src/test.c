#include <op.h>
#include <cpu.h>
#include <machine.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t e_A, e_F, e_B, e_C, e_D, e_E, e_H, e_L; uint16_t e_PC, e_SP;
uint8_t e_mem[0x10000];

uint16_t test_case = 0x00;
int failed = 0;

machine m;

void reset()
{
    // reset cpu
    m.cpu.AF = 0x0000;
    m.cpu.BC = 0x0000;
    m.cpu.DE = 0x0000;
    m.cpu.HL = 0x0000;
    m.cpu.SP = 0x0000;
    m.cpu.PC = 0x0000;

    for(size_t i=0; i<(sizeof(m.mem)/sizeof(m.mem[0])); i++) {
        m.mem[0] = 0x00;
        e_mem[0] = 0x00;
    }

    // reset expected values
    e_F = 0x00;
    e_A = 0x00;
    e_B = 0x00;
    e_C = 0x00;
    e_D = 0x00;
    e_E = 0x00;
    e_H = 0x00;
    e_L = 0x00;
    e_PC = 0x01;
    e_SP = 0x00;
}

int check()
{
    printf("\033[0;31m");
    regs r = m.cpu;
	if(e_A != r.A){
		printf("incorrect A reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.2x, got 0x%.2x\n", e_A, r.A); 
		failed = 1;
	}

	if(e_F != *((uint8_t*)&r.F)){
		printf("incorrect F reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.2x, got 0x%.2x\n", e_F, r.F); 
		failed = 1;
	}

	if(e_B != r.B){
		printf("incorrect B reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.2x, got 0x%.2x\n", e_B, r.B); 
		failed = 1;
	}

	if(e_C != r.C){
		printf("incorrect C reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.2x, got 0x%.2x\n", e_C, r.C); 
		failed = 1;
	}

	if(e_D != r.D){
		printf("incorrect D reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.2x, got 0x%.2x\n", e_D, r.D); 
		failed = 1;
	}

	if(e_E != r.E){
		printf("incorrect E reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.2x, got 0x%.2x\n", e_E, r.E); 
		failed = 1;
	}

	if(e_H != r.H){
		printf("incorrect H reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.2x, got 0x%.2x\n", e_H, r.H); 
		failed = 1;
	}

	if(e_L != r.L){
		printf("incorrect L reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.2x, got 0x%.2x\n", e_L, r.L); 
		failed = 1;
	}

	if(e_PC != r.PC){
		printf("incorrect PC reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.4x, got 0x%.4x\n", e_PC, r.PC); 
		failed = 1;
	}

	if(e_SP != r.SP){
		printf("incorrect SP reg in case 0x%.2x\n", test_case);
        printf(" - expected 0x%.4x, got 0x%.4x\n", e_SP, r.SP); 
		failed = 1;
	}

    for(size_t i=0; i<0x10000; i++){
        if(e_mem[i] != m.mem[i]){
            printf("incorrect value at address 0x%.4x\n", i);
            printf(" - expected 0x%.2x, got 0x%.2x\n", e_mem[i], m.mem[i]);
            failed = 1;
        }
    }

	if(failed == 0){
		printf("\033[0;32m");
		printf("0x%.2x case passed\n", test_case);
	}

    printf("\033[0m");
    if(failed == 1){
        exit(1);
    }
}

int main()
{
#define TEST(A) \
    reset(m); \
    test_case = 0x##A;

#define SET_REG(A, B) \
    m.cpu.A = B; \
    e_##A = B;

#define CHECK_REG(A, B) \
    e_##A = B;

#define SET_MEM(A, B) \
    m.mem[A] = B; \
    e_mem[A] = B;

#define CHECK_MEM(A, B) \
    e_mem[A] = B;

#define EXEC exec(&m.cpu, m.mem);

#define CHECK \
    check();

#define FOR(A, B, C) for(int FOR_ITR = A; FOR_ITR <= B; FOR_ITR++) C

    reset(m);
/*===========================
 * TEST 0x01
 *=========================*/
    TEST(01)

    SET_MEM(0, 0x01)
    SET_MEM(1, 0x0a)
    SET_MEM(2, 0x0b)
    CHECK_REG(B, 0x0b)
    CHECK_REG(C, 0x0a)
    CHECK_REG(PC, 0x3)

    EXEC
    CHECK

/*===========================
 * TEST 0x02
 *=========================*/
    TEST(02)

    SET_MEM(0, 0x02)
    SET_REG(A, 0xbe)
    SET_REG(B, 0xca)
    SET_REG(C, 0x15)
    CHECK_MEM(0, 0x02)
    CHECK_MEM(0xca15, 0xbe)

    EXEC
    CHECK
    

/*===========================
 * TEST 0x03
 *=========================*/
    TEST(03)

    SET_MEM(0, 0x03)
    SET_REG(B, 0xca)
    SET_REG(C, 0x15)
    CHECK_REG(C, 0x16)

    EXEC
    CHECK

/*===========================
 * TEST 0x04
 *=========================*/
    TEST(04)

    SET_MEM(0, 0x04)
    SET_REG(B, 0x46)
    CHECK_REG(B, 0x47)

    EXEC
    CHECK

/*===========================
 * TEST 0x08
 *=========================*/
    TEST(08)

    SET_MEM(0, 0x08)
    SET_MEM(1, 0x15)
    SET_MEM(2, 0xca)
    SET_REG(SP, 0xbeef)
    CHECK_REG(PC, 3)
    CHECK_MEM(0xca15, 0xef)
    CHECK_MEM(0xca16, 0xbe)

    EXEC
    CHECK

/*===========================
 * TEST 0x27a
 *=========================*/
    TEST(27a)

    SET_MEM(0, 0x80)
    SET_MEM(1, 0x27)
    SET_REG(A, 0x99)
    SET_REG(B, 0x99)
    CHECK_REG(A, 0x98)
    CHECK_REG(F, 0x10)
    CHECK_REG(PC, 0x2)

    EXEC
    EXEC
    CHECK

/*===========================
 * TEST 0x27b
 *=========================*/
    TEST(27b)

    SET_MEM(0, 0x80)
    SET_MEM(1, 0x27)
    SET_REG(A, 0x47)
    SET_REG(B, 0x25)
    CHECK_REG(A, 0x72)
    CHECK_REG(PC, 0x2)

    EXEC
    EXEC
    CHECK

/*===========================
 * TEST 0x27c
 *=========================*/
    TEST(27c)

    SET_MEM(0, 0x80)
    SET_MEM(1, 0x27)
    SET_REG(A, 0x47)
    SET_REG(B, 0x75)
    CHECK_REG(A, 0x22)
    CHECK_REG(F, 0x10)
    CHECK_REG(PC, 0x2)

    EXEC
    EXEC
    CHECK

/*===========================
 * TEST 0x27d
 *=========================*/
    TEST(27d)

    SET_MEM(0, 0x90)
    SET_MEM(1, 0x27)
    SET_REG(A, 0x98)
    SET_REG(B, 0x99)
    CHECK_REG(A, 0x99)
    CHECK_REG(B, 0x99)
    CHECK_REG(F, 0x50)
    CHECK_REG(PC, 0x2)

    EXEC
    EXEC
    CHECK

/*===========================
 * TEST 0x27e
 *=========================*/
    TEST(27e)

    SET_MEM(0, 0x90)
    SET_MEM(1, 0x27)
    SET_REG(A, 0x47)
    SET_REG(B, 0x25)
    CHECK_REG(A, 0x22)
    CHECK_REG(F, 0x40)
    CHECK_REG(PC, 0x2)

    EXEC
    EXEC
    CHECK

/*===========================
 * TEST 0x27f
 *=========================*/
    TEST(27f)

    SET_MEM(0, 0x90)
    SET_MEM(1, 0x27)
    SET_REG(A, 0x43)
    SET_REG(B, 0x25)
    CHECK_REG(A, 0x18)
    CHECK_REG(F, 0x40)
    CHECK_REG(PC, 0x2)

    EXEC
    EXEC
    CHECK

/*===========================
 * TEST 0x40-0x75, 0x77-0x7f
 *=========================*/
#define TEST_MOV(OP, A, B) \
    TEST(OP) \
    SET_MEM(0, 0x##OP) \
    SET_REG(A, 0x36) \
    SET_REG(B, 0x82) \
    CHECK_REG(A, 0x82) \
    EXEC \
    CHECK

#define TEST_LDR(OP, A, B, C) \
    TEST(OP) \
    SET_MEM(0, 0x##OP) \
    SET_MEM(0xba0c, 0x82) \
    SET_REG(B, 0xba) \
    SET_REG(C, 0x0c) \
    CHECK_REG(A, 0x82) \
    EXEC \
    CHECK

#define TEST_STR_D1(OP, A, B, C) \
    TEST(OP) \
    SET_MEM(0, 0x##OP) \
    SET_REG(A, 0xf1) \
    SET_REG(B, 0x29) \
    SET_REG(C, 0x82) \
    CHECK_MEM(0xf129, 0x82) \
    EXEC \
    CHECK

#define TEST_STR_D2(OP, A, B, C) \
    TEST(OP) \
    SET_MEM(0, 0x##OP) \
    SET_REG(A, 0x82) \
    SET_REG(B, 0x29) \
    SET_REG(C, 0x82) \
    CHECK_MEM(0x8229, 0x82) \
    EXEC \
    CHECK

#define TEST_STR_D3(OP, A, B, C) \
    TEST(OP) \
    SET_MEM(0, 0x##OP) \
    SET_REG(A, 0xf1) \
    SET_REG(B, 0x29) \
    SET_REG(C, 0x29) \
    CHECK_MEM(0xf129, 0x29) \
    EXEC \
    CHECK

#define TEST_MOV_GROUP(X, R) \
    TEST_MOV(X, R, B) \
    TEST_MOV(X+1, R, C) \
    TEST_MOV(X+2, R, D) \
    TEST_MOV(X+3, R, E) \
    TEST_MOV(X+4, R, H) \
    TEST_MOV(X+5, R, L) \
    TEST_LDR(X+6, R, H, L) \
    TEST_MOV(X+7, R, A)

    TEST_MOV_GROUP(40, B)
    TEST_MOV_GROUP(48, C)
    TEST_MOV_GROUP(50, D)
    TEST_MOV_GROUP(58, E)
    TEST_MOV_GROUP(60, H)
    TEST_MOV_GROUP(68, L)
    TEST_STR_D1(70, H, L, B)
    TEST_STR_D1(71, H, L, C)
    TEST_STR_D1(72, H, L, D)
    TEST_STR_D1(73, H, L, E)
    TEST_STR_D2(74, H, L, H)
    TEST_STR_D3(75, H, L, L)
    TEST_STR_D1(77, H, L, A)
    TEST_MOV_GROUP(78, A)

/*===========================
 * TEST 0x80-0x87
 *=========================*/
#define ADD_FLAGS(OP1, OP2) \
    (((uint8_t)(OP1 + OP2) < OP1) << 4 | \
    (((OP1 & 0xf) + (OP2 & 0xf)) & 0x10) << 1 | \
    ((uint8_t)(OP1 + OP2) == 0) << 7)
#define TEST_ADD(OP, OP1, OP2, REG1, REG2) \
    TEST(OP) \
    SET_MEM(0, 0x##OP) \
    SET_REG(REG1, OP1) \
    SET_REG(REG2, OP2) \
    CHECK_REG(REG1, OP1 + OP2) \
    CHECK_REG(F, ADD_FLAGS(OP1, OP2)) \
    EXEC \
    CHECK

    TEST_ADD(80, 0x32, 0x69, A, B)
    TEST_ADD(81, 0xf0, 0x31, A, C)
    TEST_ADD(82, 0x0b, 0x28, A, D)
    TEST_ADD(83, 0x99, 0x99, A, E)
    TEST_ADD(84, 0x00, 0x38, A, H)
    TEST_ADD(85, 0xff, 0x01, A, L)
}

