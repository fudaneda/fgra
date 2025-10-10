#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"


#define SIZE  1024
int A[SIZE] __attribute__((aligned(16)));
int B[SIZE] __attribute__((aligned(16)));
int C[SIZE] __attribute__((aligned(16)));
int D[SIZE] __attribute__((aligned(16)));

__attribute__((noinline))

void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[20][3] __attribute__((aligned(16))) = {
		{0x0000, 0x0001, 0x0020},
		{0x0004, 0x0000, 0x0021},
		{0x0000, 0x0144, 0x0022},
		{0x0000, 0x0000, 0x0023},
		{0x0030, 0x0000, 0x0058},
		{0x0000, 0x0020, 0x0100},
		{0x0000, 0x0020, 0x01a8},
		{0x0000, 0x0020, 0x0250},
		{0x0000, 0x0020, 0x02f8},
		{0x0000, 0x0000, 0x03a0},
		{0x0001, 0x0009, 0x0411},
		{0x0001, 0x0000, 0x0450},
		{0x1000, 0x0001, 0x04b8},
		{0x0004, 0x0000, 0x04b9},
		{0x0000, 0x0004, 0x04ba},
		{0x0001, 0x0000, 0x04bb},
		{0x0000, 0x0001, 0x04c0},
		{0x0004, 0x0000, 0x04c1},
		{0x0000, 0x0004, 0x04c2},
		{0x0001, 0x0000, 0x04c3},
	};

	load_cfg((void*)cin, 0x30000, 120, 0, 0);
	load_data(din_addr[0], 0x24000, 1024, 0, 0, 0);
	load_data(din_addr[1], 0x28000, 1024, 0, 0, 0);
	config(0x0, 20, 0, 0);
	execute(0x608, 0, 0);
	store(dout_addr[0], 0xc000, 1024, 0, 0);
}

// void cgra_execute(void** din_addr, void** dout_addr)
// {
// 	static unsigned short cin[16][5] __attribute__((aligned(16))) = {
// 		{0x4000, 0x0000, 0x0010, 0x0000, 0x0010},
// 		{0x0000, 0x8000, 0x2030, 0x0000, 0x0011},
// 		{0x4000, 0x0000, 0x0010, 0x0000, 0x001c},
// 		{0x0000, 0x8000, 0x0000, 0x0000, 0x001d},
// 		{0x2010, 0x0000, 0x0000, 0x0000, 0x0034},
// 		{0x0000, 0x0002, 0x0000, 0x0000, 0x0038},
// 		{0x0000, 0x0002, 0x0000, 0x0000, 0x003c},
// 		{0x0000, 0x0000, 0x0000, 0x0000, 0x0040},
// 		{0x0000, 0x0000, 0xa041, 0x0001, 0x0054},
// 		{0x0000, 0x0100, 0x0000, 0x0000, 0x0074},
// 		{0x0080, 0x0000, 0x0000, 0x0000, 0x0078},
// 		{0x0000, 0x0020, 0x0000, 0x0000, 0x00bc},
// 		{0x0000, 0x0020, 0x0000, 0x0000, 0x0104},
// 		{0x0000, 0x0004, 0x0000, 0x0000, 0x014c},
// 		{0x4000, 0x0000, 0x0010, 0x0000, 0x016c},
// 		{0x0000, 0x8000, 0x0000, 0x0000, 0x016d},
// 	};
// 	load_cfg((void*)cin, 0x40000, 160, 0, 0);
// 	printf("Load cfg finished!\n");
// 	load_data(din_addr[0], 0x20000, 1024, 0, 0, 0);
// 	printf("Load data finished!\n");
// 	load_data(din_addr[1], 0x10000, 1024, 0, 0, 0);
// 	printf("Load data finished!\n");
// 	config(0x0, 16, 0, 0);
// 	printf("COnfig finished!\n");
// 	execute(0x148, 0, 0);
// 	printf("Execute finished!\n");
// 	store(dout_addr[0], 0x0, 1024, 0, 0);
// 	printf("Store finished!\n");
// }

void array_add(){
   for (int i=0;i<SIZE; i++){
      #ifdef CGRA_COMPILER
      please_map_me();
      #endif
      D[i] = A[i]+B[i];
   }
}

void result_check()
{
  int i, j;

  for (i = 0; i < SIZE; i++)
  {
    if (C[i] != D[i]) printf("There is an error in location (%d)[%d, %d]\n", i, C[i], D[i]);
  }
}

int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

  for (i=0;i<SIZE; i++){
      A[i] = i * 2 + 5;
      B[i] = i * 3;
      C[i] = 0;
      D[i] = 0;
    }
    
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
// array_add();
// // printf("CPU add finished!\n");
  start = rdcycle();
  /* Run kernel. */
  array_add();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  // void* cgra_din_addr[2] = {A, B};
  // void* cgra_dout_addr[1] = {C};
  // start = rdcycle();
  // cgra_execute(cgra_din_addr, cgra_dout_addr);
  // volatile int result = fence(1);
  // end = rdcycle();
  // printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
  printf("CGRA comput finished!\n");
// volatile int result = fence(1);

  // for (i=0;i<16; i++) {
	// printf("%d", C[i]);
	// // printf("%d", sizeof(C[i]));
	// // printf("%s", ",,");
	// printf("%d\n", i);
  // }
    
  result_check();
  printf("Done!\n");

return 0;

}
