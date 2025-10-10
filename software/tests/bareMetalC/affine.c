#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

#define NI 16
#define NJ 16
#define ASIZE (2*NI)
#define BSIZE (NI+NJ)
#define CSIZE (NJ*NJ)
int A[ASIZE];
int B[BSIZE];
int C[CSIZE];
int D[NI][NJ];
int E[NI][NJ];
int F[NI];
int E1[NI][NJ];
int F1[NI];

void test(){
  for (int i=0; i<NI; i++){
    int sum = 0;
    for (int j=NJ-1; j>=0; j--){
   	  #ifdef CGRA_COMPILER
      please_map_me();
      #endif
   	  E1[i][j] = A[i*2] + B[i+j] + D[i][j];
   	  if(j>NJ/2)
   	    sum += C[j*j] * D[i][j];
   	}
   	F1[i] = sum;
  }
}

void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[54][3] __attribute__((aligned(8))) = {
		{0x1000, 0x4000, 0x0008},
		{0x0040, 0x0080, 0x0009},
		{0x0000, 0x9300, 0x000a},
		{0x0800, 0x0000, 0x000b},
		{0xe80f, 0x43ff, 0x0010},
		{0x07c0, 0x0080, 0x0011},
		{0x0000, 0x8b00, 0x0012},
		{0x0000, 0x0000, 0x0013},
		{0xe00f, 0x43ff, 0x0018},
		{0x07c0, 0x0080, 0x0019},
		{0x0000, 0x0100, 0x001a},
		{0x0000, 0x0000, 0x001b},
		{0x00c0, 0x0000, 0x0038},
		{0x4000, 0x1004, 0x0040},
		{0x0c21, 0x0011, 0x0061},
		{0x0000, 0x0100, 0x0062},
		{0x4080, 0x0400, 0x0063},
		{0x0000, 0x0000, 0x0064},
		{0x8803, 0x0005, 0x0069},
		{0x0000, 0x0000, 0x0088},
		{0x00c0, 0x0020, 0x0090},
		{0x8201, 0x0009, 0x00b1},
		{0x0008, 0x0000, 0x00b8},
		{0x000a, 0x0010, 0x00b9},
		{0x00c0, 0x0000, 0x00d8},
		{0x0000, 0x2000, 0x00e0},
		{0x0000, 0x0000, 0x00e8},
		{0xffff, 0xffff, 0x0110},
		{0x0011, 0x0f00, 0x0111},
		{0x0000, 0x0100, 0x0112},
		{0x4000, 0x0400, 0x0113},
		{0x0004, 0x0000, 0x0114},
		{0x0000, 0x0000, 0x0128},
		{0x0000, 0x2000, 0x0130},
		{0x0000, 0x0000, 0x0138},
		{0x8001, 0x0011, 0x0151},
		{0x0003, 0x0009, 0x0159},
		{0x0004, 0x0000, 0x0160},
		{0x8003, 0x0001, 0x0161},
		{0x0040, 0x0000, 0x0178},
		{0x0004, 0x0000, 0x0180},
		{0x0000, 0x0000, 0x0188},
		{0xe80f, 0x43ff, 0x0198},
		{0x0400, 0x0080, 0x0199},
		{0x0000, 0x0100, 0x019a},
		{0x0000, 0x0000, 0x019b},
		{0x0000, 0x4000, 0x01a0},
		{0x0080, 0x0080, 0x01a1},
		{0x0000, 0x0100, 0x01a2},
		{0x0000, 0x0000, 0x01a3},
		{0x1000, 0x0000, 0x01a8},
		{0x0004, 0x0000, 0x01a9},
		{0x0000, 0x0700, 0x01aa},
		{0x0801, 0x0000, 0x01ab},
	};

	load_cfg((void*)cin, 0x10000, 324, 0, 0);
	load_data(din_addr[0], 0x8000, 124, 0, 0, 0);
	load_data(din_addr[1], 0xa000, 124, 0, 0, 0);
	load_data(din_addr[2], 0xc000, 1024, 0, 0, 0);
	load_data(din_addr[3], 0x0, 1024, 0, 0, 0);
	config(0x0, 54, 0, 0);
	execute(0x77, 0, 0);
	store(dout_addr[0], 0x2000, 1024, 0, 0);
	store(dout_addr[1], 0x4000, 64, 0, 0);
}


int main(){
  long long unsigned start;
  long long unsigned end;

  for (int i=0; i<ASIZE; i++){
    A[i] = i * 2 + 5;
  }
  for (int i=0; i<BSIZE; i++){
    B[i] = i * 3;
  }
  for (int i=0; i<CSIZE; i++){
    C[i] = i;
  }
  for (int i=0; i<NI; i++){
    for(int j=0; j<NJ; j++)
      D[i][j] = i+j;
  }

  start = rdcycle();
  /* Run kernel. */
  test();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[4] = {A, B, C, D};
  void* cgra_dout_addr[2] = {E, F};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  for (int i=0; i<NI; i++){
    for(int j = 0; j < NJ; j++){
        if(E[i][j] != E1[i][j])
            printf("E[%d][%d]: %d != %d\n", i, j, E[i][j], E1[i][j]);
    }
  }

   for (int i=0; i<NI; i++){
      if(F[i] != F1[i])
        printf("F[%d]: %d != %d\n", i, F[i], F1[i]);
   }
   printf("Done!\n");

  return 0;

}
