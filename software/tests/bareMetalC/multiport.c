#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[54][3] __attribute__((aligned(16))) = {
		{0x4000, 0x4000, 0x0008},
		{0xf100, 0x008f, 0x0009},
		{0x0000, 0x1000, 0x000a},
		{0x1000, 0x0002, 0x000b},
		{0x4002, 0x4000, 0x0018},
		{0xf100, 0x008f, 0x0019},
		{0x0000, 0x1000, 0x001a},
		{0x1000, 0x0002, 0x001b},
		{0x4001, 0x4000, 0x0020},
		{0xf100, 0x008f, 0x0021},
		{0x0000, 0x1000, 0x0022},
		{0x1000, 0x0002, 0x0023},
		{0x0000, 0x0000, 0x0048},
		{0x8000, 0x0001, 0x0050},
		{0x0000, 0x0000, 0x0058},
		{0x0000, 0x0600, 0x00f0},
		{0x0000, 0x0600, 0x00f8},
		{0x0000, 0x0600, 0x0100},
		{0x0000, 0x0600, 0x0198},
		{0x0300, 0x0000, 0x01a0},
		{0x0300, 0x0000, 0x01a8},
		{0x0006, 0x0000, 0x0210},
		{0x0001, 0x0001, 0x0212},
		{0x0005, 0x0000, 0x0218},
		{0x0001, 0x0001, 0x021a},
		{0x0000, 0x00c0, 0x0240},
		{0x0000, 0x0280, 0x0248},
		{0x0200, 0x0200, 0x0250},
		{0x0007, 0x0000, 0x02c0},
		{0x0001, 0x0001, 0x02c2},
		{0x0000, 0x0600, 0x02f0},
		{0x0000, 0x0600, 0x02f8},
		{0x0000, 0x0000, 0x0300},
		{0x0000, 0x0600, 0x0398},
		{0x0000, 0x0600, 0x03a0},
		{0x0000, 0x0600, 0x03a8},
		{0x8000, 0x0001, 0x0440},
		{0x0210, 0x0000, 0x0448},
		{0x0020, 0x0000, 0x0450},
		{0x4002, 0x4000, 0x04b0},
		{0xf100, 0x008f, 0x04b1},
		{0x0000, 0x9000, 0x04b2},
		{0x0802, 0x0000, 0x04b3},
		{0x0010, 0x0000, 0x04b4},
		{0x4001, 0x4000, 0x04b8},
		{0xf100, 0x008f, 0x04b9},
		{0x0000, 0x1000, 0x04ba},
		{0x0804, 0x0040, 0x04bb},
		{0x0000, 0x0000, 0x04bc},
		{0x4000, 0x4000, 0x04c0},
		{0xf100, 0x008f, 0x04c1},
		{0x0000, 0x1000, 0x04c2},
		{0x0804, 0x0040, 0x04c3},
		{0x0000, 0x0000, 0x04c4},
	};

	load_cfg((void*)cin, 0x18000, 324, 0, 0);
	load_data(din_addr[0], 0x0, 132, 1, 0, 0, 2, 0);
	load_data(din_addr[0], 0x2000, 132, 1, 0, 0, 2, 0);
	load_data(din_addr[0], 0x4000, 132, 1, 0, 0, 2, 0);
	load_data(din_addr[0], 0x6000, 132, 0, 0, 0, 2, 0);
	config(0x0, 54, 0, 0);
	execute(0x70d, 0, 0);
	store(dout_addr[0], 0x10000, 132, 1, 0, 0, 1, 0);
	store(dout_addr[0], 0x12000, 132, 0, 0, 0, 1, 0);
}

#define N 8
#define SIZE N*N


int A[SIZE]__attribute__((aligned(16)));
int B[SIZE]__attribute__((aligned(16)));
int P[SIZE]__attribute__((aligned(16)));
void matmul() {
    // for(int k = 0; k < N; k++) {
    for(int k = 0; k < N; k++) {
         for (int i = 0; i < 2*N; i++) {
            //  if((i+k) > 1 && ((i+k)) < 8){
            //     A[i] = B[i + 2] + 5;
            //  }else if(((i+k)) > 9 && ((i+k)) < 13){
            //     A[i + 1] = B[2*i + 1] + 6;
            //  }else{
            //     A[i + k] = B[2*i] + 7;
            //  }
                P[2*i + 2] = B[2*i + 2] + 5;
                P[2*i + 1] = B[2*i + 1] + 6;
                P[2*i] = B[2*i] + 7;
         }
    }
    // }
}

void result_check()
{
  int i, j;


  for (i = 0; i < 33; i++)
  {
	// if(i == 8) continue;
    if (A[i] != P[i]) printf("There is an error in location (%d)[%d, %d]\n", i, A[i], P[i]);

  }
}

int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

  for (i=0;i<64; i++){
      A[i] = 0 ;
      P[i] = 0 ;
      B[i] = i ;
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
  matmul();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[1] = {B};
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
    
//   printf("Checking results!\n");
//   result_check();
//   printf("Done!\n");

return 0;

}
