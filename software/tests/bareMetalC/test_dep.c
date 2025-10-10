#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[35][3] __attribute__((aligned(16))) = {
		{0xf00f, 0x07ff, 0x0008},
		{0x0000, 0x0000, 0x0009},
		{0x0000, 0x0040, 0x000a},
		{0x0300, 0x0200, 0x000b},
		{0xf00e, 0x07ff, 0x0010},
		{0x0000, 0x0000, 0x0011},
		{0x0000, 0x0040, 0x0012},
		{0x0105, 0x0000, 0x0013},
		{0x1001, 0x0780, 0x0018},
		{0x0000, 0x0000, 0x0019},
		{0x0000, 0x0040, 0x001a},
		{0x0105, 0x0000, 0x001b},
		{0x1001, 0x0780, 0x0020},
		{0x0000, 0x0000, 0x0021},
		{0x0000, 0x0640, 0x0022},
		{0x0400, 0x0000, 0x0023},
		{0x0000, 0x0000, 0x0040},
		{0x8000, 0x0000, 0x0048},
		{0x0000, 0x0000, 0x0050},
		{0x0030, 0x0000, 0x0058},
		{0x0001, 0x0000, 0x0080},
		{0x0800, 0x0000, 0x0088},
		{0x0000, 0x0000, 0x0090},
		{0xd021, 0x0000, 0x00b9},
		{0xd901, 0x0000, 0x00c1},
		{0x0000, 0x0000, 0x00e8},
		{0x0000, 0x0030, 0x00f0},
		{0x0000, 0x0040, 0x00f8},
		{0x0200, 0x0000, 0x0100},
		{0x4a03, 0x0000, 0x0171},
		{0x0000, 0x0000, 0x01a0},
		{0x1001, 0x0780, 0x0210},
		{0x0000, 0x0000, 0x0211},
		{0x0000, 0x0040, 0x0212},
		{0x0100, 0x0000, 0x0213},
	};

	load_cfg((void*)cin, 0xc000, 210, 0, 0);
	load_data(din_addr[0], 0x0, 64, 0, 0, 0, 0, 0);
	load_data(din_addr[1], 0x1000, 64, 1, 0, 0, 1, 0);
	load_data(din_addr[1], 0x2000, 64, 0, 0, 0, 1, 0);
	load_data(din_addr[2], 0x8000, 64, 0, 0, 0, 0, 0);
	config(0x0, 35, 0, 0);
	execute(0x10f, 0, 0);
	store(dout_addr[0], 0x0, 64, 0, 0, 0, 0, 0);
}
// #define N 8
#define size 16


int A[size]__attribute__((aligned(16)));
int A_i[size]__attribute__((aligned(16)));
int B[size]__attribute__((aligned(16)));
int C[size]__attribute__((aligned(16)));
void test(){ 
    for(int i = 1; i < size; i++){
        A_i[i] = (A_i[size - i] + B[i] + B[size - i - 1]) * C[i];
    }
  }

void result_check()
{
  int i, j;


  for (i = 1; i < size; i++)
  {
	// if(i == 8) continue;
    if (A_i[i] != A[i]) printf("There is an error in location (%d)[%d, %d]\n", i, A_i[i], A[i]);

  }
}

int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

  for (i=0;i<size; i++){
      A[i] = i ;
      A_i[i] = i ;
      B[i] = i ;
      C[i] = i ;
    }
  // for(int j = 0; j< 4; j++){
  //   for(int i=0; i< 512; i++){
  //     output[j][i] = 0;
  //   }
  // }
//   for(int i=0; i< Ncb; i++){
//       W[i] = 0;
//       W_i[i] = 0;
//   }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
  
  printf("CPU add finished!\n");
  start = rdcycle();
  /* Run kernel. */
  test();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
  void* cgra_din_addr[3] = {A, B, C};
  void* cgra_dout_addr[1] = {A};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
  printf("CGRA comput finished!\n");
//   result = fence(1);

//   for (i=0;i<32; i++) {
// 	printf("%d\\", X[i]);
// 	// printf("%d", sizeof(C[i]));
// 	// printf("%s", ",,");
// 	// printf("%d\n", i);
//   }
    
  printf("Checking results!\n");
  result_check();
  printf("Done!\n");

return 0;

}
