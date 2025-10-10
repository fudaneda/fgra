#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[45][3] __attribute__((aligned(16))) = {
		{0x1000, 0x0780, 0x0028},
		{0x8120, 0x0002, 0x0029},
		{0x0000, 0x0070, 0x002a},
		{0x0178, 0x0000, 0x002b},
		{0x3800, 0x0000, 0x0050},
		{0x0100, 0x0000, 0x0058},
		{0x8000, 0x0000, 0x0060},
		{0xa023, 0x0000, 0x00b1},
		{0x0004, 0x0000, 0x00b8},
		{0x1803, 0x0000, 0x00b9},
		{0x2001, 0x0001, 0x00c1},
		{0x6041, 0x0000, 0x00c9},
		{0x0000, 0x0000, 0x00f0},
		{0x0000, 0x0002, 0x00f8},
		{0x0000, 0x0000, 0x0100},
		{0x0001, 0x0040, 0x0108},
		{0x4000, 0x0100, 0x0110},
		{0x0001, 0x0000, 0x0160},
		{0x0011, 0x0000, 0x0161},
		{0x0000, 0x1a40, 0x0162},
		{0x2800, 0x0100, 0x0163},
		{0x0060, 0x0000, 0x0164},
		{0x0005, 0x0000, 0x0168},
		{0x0001, 0x0001, 0x0169},
		{0xa003, 0x0000, 0x0171},
		{0x0080, 0x0000, 0x0180},
		{0x0011, 0x0000, 0x0181},
		{0x0000, 0x01c0, 0x0182},
		{0x7808, 0x0500, 0x0183},
		{0x0060, 0x0000, 0x0184},
		{0x0120, 0x0000, 0x01a8},
		{0x2000, 0x0000, 0x01b0},
		{0x0200, 0x0000, 0x01b8},
		{0x0001, 0x0782, 0x0210},
		{0xe410, 0x0002, 0x0211},
		{0x0000, 0x0070, 0x0212},
		{0x2104, 0x0080, 0x0213},
		{0x0000, 0x2580, 0x0218},
		{0x0000, 0x0000, 0x0219},
		{0x0000, 0x0670, 0x021a},
		{0x4804, 0x0100, 0x021b},
		{0x0000, 0x0782, 0x0220},
		{0xe410, 0x0002, 0x0221},
		{0x0000, 0x0070, 0x0222},
		{0x0104, 0x0080, 0x0223},
	};

	load_cfg((void*)cin, 0xc000, 270, 0, 0);
	load_data(din_addr[0], 0x4000, 572, 1, 0, 0, 2, 7);
	load_data(din_addr[0], 0x5000, 572, 1, 0, 0, 2, 7);
	load_data(din_addr[0], 0x6000, 572, 1, 0, 0, 2, 7);
	load_data(din_addr[0], 0x7000, 572, 0, 0, 0, 2, 7);
	load_data(din_addr[1], 0x8000, 2048, 1, 0, 0, 1, 0);
	load_data(din_addr[1], 0x9000, 2048, 0, 0, 0, 1, 0);
	config(0x0, 45, 0, 0);
	execute(0x710, 0, 0);
	store(dout_addr[0], 0x8000, 2048, 1, 0, 0, 1, 0);
	store(dout_addr[0], 0x9000, 2048, 0, 0, 0, 1, 0);
}
// #define N 8
#define NUM 16
  int A[NUM][2*NUM]__attribute__((aligned(16)));
  int B[NUM][2*NUM]__attribute__((aligned(16)));
  int X[NUM][2*NUM]__attribute__((aligned(16)));
  int X_i[NUM][2*NUM]__attribute__((aligned(16)));
  int A_i[NUM][2*NUM]__attribute__((aligned(16)));
   //kernel 23
void test_bank_share() { 
    for (int i1=0 ; i1 < 5 ; i1++) {
        for (int i2=0 ; i2 < NUM-1 ; i2++){
            X_i[i2][i1*i1] = B[i1][i2] * X_i[i2][i1] + X_i[i2][i1+1] + 5;
 		} 
 	}
}

void result_check()
{
  for (int i=0 ; i < 5 ; i++) {
          for (int j=0 ; j < NUM-1 ; j++){
			// printf("A[%d]: %d \n", i*NUM+j, A_i[i][j]);
    		if (X_i[j][i*i] != X[j][i*i]) printf("There is an error in location (%d)[%d, %d]\n", i*NUM+j, X_i[j][i*i], X[j][i*i]);
        } 
  }
	// if(i == 8) continue;


}


int main(){

//   int i,j;
  long long unsigned start;
  long long unsigned end;

   for (int i=0 ; i < NUM ; i++) {
          for (int j=0 ; j < 2*NUM ; j++){
    		A[i][j] = i + j;
			B[i][j] = i + j;
			X[i][j] = i + j;
			X_i[i][j] = i + j;
			A_i[i][j] = i + j;
        } 
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
  
//   printf("CPU add finished!\n");
  start = rdcycle();
  /* Run kernel. */
  test_bank_share();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
  void* cgra_din_addr[2] = {B, X};
  void* cgra_dout_addr[1] = {X};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
  printf("CGRA comput finished!\n");
  result = fence(1);

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
