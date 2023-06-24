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
    e_PC = 0x00;
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
/*===========================
 * TEST 0x01
 *=========================*/
    test_case = 0x01;

    reset(m);
    m.mem[0] = 0x01;
    m.mem[1] = 0x0a;
    m.mem[2] = 0x0b;
    m.cpu.PC = 0x0;
    exec(&m.cpu, m.mem);
    
    e_B = 0x0b;
    e_C = 0x0a;
    e_PC = 0x3;
    e_mem[0] = 0x01;
    e_mem[1] = 0x0a;
    e_mem[2] = 0x0b;
    check();

/*===========================
 * TEST 0x02
 *=========================*/
    test_case = 0x02;

    reset(m);
    m.mem[0] = 0x02;
    m.cpu.A = 0xbe;
    m.cpu.BC = 0xca15;
    exec(&m.cpu, m.mem);

    e_A = 0xbe;
    e_B = 0xca;
    e_C = 0x15;
    e_PC = 0x1;
    e_mem[0x0] = 0x02;
    e_mem[0xca15] = 0xbe;
    check();

/*===========================
 * TEST 0x03
 *=========================*/
    test_case = 0x03;

    reset(m);
    m.mem[0] = 0x03;
    m.cpu.BC = 0xca15;
    exec(&m.cpu, m.mem);

    e_B = 0xca;
    e_C = 0x16;
    e_PC = 0x1;
    e_mem[0x0] = 0x03;
    check();

/*===========================
 * TEST 0x04
 *=========================*/
    test_case = 0x04;

    reset(m);
    m.mem[0] = 0x04;
    m.cpu.B = 0x46;
    exec(&m.cpu, m.mem);

    e_B = 0x47;
    e_PC = 0x1;
    e_mem[0x0] = 0x04;
    check();

/*===========================
 * TEST 0x08
 *=========================*/
    test_case = 0x08;

    reset(m);
    m.mem[0] = 0x08;
    m.mem[1] = 0x15;
    m.mem[2] = 0xca;
    m.cpu.SP = 0xbeef;
    exec(&m.cpu, m.mem);

    e_mem[0] = 
    e_PC = 0x3;
    e_SP = 0xbeef;
    e_mem[0] = 0x08;
    e_mem[1] = 0x15;
    e_mem[2] = 0xca;
    e_mem[0xca15] = 0xef;
    e_mem[0xca16] = 0xbe;
    check();
}


