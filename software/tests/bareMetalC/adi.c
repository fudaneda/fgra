#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[47][3] __attribute__((aligned(16))) = {
		{0x1000, 0x0f80, 0x0028},
		{0x0020, 0x0010, 0x0029},
		{0x0000, 0x0720, 0x002a},
		{0x2004, 0x0000, 0x002b},
		{0x1001, 0x0f80, 0x0030},
		{0x0020, 0x0010, 0x0031},
		{0x0000, 0x0020, 0x0032},
		{0x0104, 0x0000, 0x0033},
		{0x2000, 0x0000, 0x0058},
		{0x2820, 0x0000, 0x0060},
		{0x0100, 0x0000, 0x0068},
		{0x0000, 0x0000, 0x0070},
		{0x9842, 0x0000, 0x00c1},
		{0xe003, 0x0000, 0x00c9},
		{0x1803, 0x0001, 0x00d1},
		{0x5822, 0x0000, 0x00d9},
		{0x0030, 0x0000, 0x00f8},
		{0x0040, 0x0200, 0x0100},
		{0xc010, 0x0000, 0x0108},
		{0x0034, 0x0000, 0x0110},
		{0x0000, 0x0000, 0x0118},
		{0x2003, 0x0001, 0x0171},
		{0x1803, 0x0001, 0x0179},
		{0x2000, 0x0000, 0x01a0},
		{0x0200, 0x0000, 0x01a8},
		{0x0004, 0x0000, 0x01b0},
		{0x0000, 0x0000, 0x01b8},
		{0x1000, 0x0f80, 0x0208},
		{0x0020, 0x0010, 0x0209},
		{0x0000, 0x0020, 0x020a},
		{0x0104, 0x0000, 0x020b},
		{0x1000, 0x0f80, 0x0210},
		{0x0020, 0x0010, 0x0211},
		{0x0000, 0x0720, 0x0212},
		{0x2006, 0x0080, 0x0213},
		{0x1000, 0x0f80, 0x0218},
		{0x0020, 0x0010, 0x0219},
		{0x0000, 0x0020, 0x021a},
		{0x0100, 0x0000, 0x021b},
		{0x1001, 0x0f80, 0x0220},
		{0x0020, 0x0010, 0x0221},
		{0x0000, 0x0020, 0x0222},
		{0x0106, 0x0000, 0x0223},
		{0x1000, 0x0f80, 0x0228},
		{0x0020, 0x0010, 0x0229},
		{0x0000, 0x0020, 0x022a},
		{0x0106, 0x0000, 0x022b},
	};

	load_cfg((void*)cin, 0xc000, 282, 0, 0);
	load_data(din_addr[0], 0x8000, 4092, 1, 0, 0, 1, 10);
	load_data(din_addr[0], 0x9000, 4092, 0, 0, 0, 1, 10);
	load_data(din_addr[1], 0xa000, 4096, 1, 0, 0, 1, 0);
	load_data(din_addr[1], 0xb000, 4096, 0, 0, 0, 1, 0);
	load_data(din_addr[2], 0x4000, 4096, 1, 0, 0, 1, 0);
	load_data(din_addr[2], 0x5000, 4096, 0, 0, 0, 1, 0);
	config(0x0, 47, 0, 0);
	execute(0xfb0, 0, 0);
	store(dout_addr[0], 0x4000, 4096, 1, 0, 0, 1, 0);
	store(dout_addr[0], 0x5000, 4096, 0, 0, 0, 1, 0);
	store(dout_addr[1], 0xa000, 4096, 1, 0, 0, 1, 0);
	store(dout_addr[1], 0xb000, 4096, 0, 0, 0, 1, 0);
}
// #define N 8
#define NUM 32
  int A[NUM][NUM]__attribute__((aligned(16)));
  int B[NUM][NUM]__attribute__((aligned(16)));
  int X[NUM][NUM]__attribute__((aligned(16)));
  int B_i[NUM][NUM]__attribute__((aligned(16)));
  int X_i[NUM][NUM]__attribute__((aligned(16)));
   //kernel 23
void adi() { 
    for (int i1=0 ; i1 < NUM ; i1++) {
        for (int i2=0 ; i2 < NUM-1 ; i2++){
	    	X_i[i1][i2] = X_i[i1][i2] - X_i[i1][i2+1] * A[i1][i2] * B_i[i1][i2+1];
	    	B_i[i1][i2] = B_i[i1][i2] - A[i1][i2] * A[i1][i2] * B_i[i1][i2+1];
 		} 
 	}
}

void result_check()
{
  for (int i=0 ; i < NUM ; i++) {
          for (int j=0 ; j < NUM-1 ; j++){
    		if (X_i[i][j] != X[i][j]) printf("There is an error in location (%d)[%d, %d]\n", i*NUM+j, X_i[i][j], X[i][j]);
        } 
  }
	// if(i == 8) continue;


}


int main(){

//   int i,j;
  long long unsigned start;
  long long unsigned end;

   for (int i=0 ; i < NUM ; i++) {
          for (int j=0 ; j < NUM ; j++){
    		A[i][j] = i + j;
			B[i][j] = i + j;
			X[i][j] = i + j;
			B_i[i][j] = i + j;
			X_i[i][j] = i + j;
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
  adi();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
  void* cgra_din_addr[3] = {A, B, X};
  void* cgra_dout_addr[2] = {X, B};
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
