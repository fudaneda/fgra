#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[40][3] __attribute__((aligned(16))) = {
		{0x2022, 0x1e00, 0x0008},
		{0x0060, 0x001e, 0x0009},
		{0x0000, 0x0260, 0x000a},
		{0x2040, 0x0000, 0x000b},
		{0x2001, 0x1e00, 0x0010},
		{0x0060, 0x001e, 0x0011},
		{0x0000, 0x0460, 0x0012},
		{0x2040, 0x0000, 0x0013},
		{0x2021, 0x1e00, 0x0020},
		{0x0060, 0x001e, 0x0021},
		{0x0000, 0x0060, 0x0022},
		{0x2040, 0x0000, 0x0023},
		{0x2041, 0x1e00, 0x0028},
		{0x0060, 0x001e, 0x0029},
		{0x0000, 0x0260, 0x002a},
		{0x2040, 0x0000, 0x002b},
		{0x2020, 0x1e00, 0x0030},
		{0x0060, 0x001e, 0x0031},
		{0x0000, 0x0060, 0x0032},
		{0x2040, 0x0000, 0x0033},
		{0x2000, 0x0000, 0x0048},
		{0x2000, 0x0001, 0x0050},
		{0x0000, 0x0002, 0x0058},
		{0x0000, 0x0011, 0x0060},
		{0x0000, 0x0000, 0x0068},
		{0x9201, 0x0000, 0x00b1},
		{0x5101, 0x0000, 0x00b9},
		{0x1901, 0x0001, 0x00c1},
		{0x5001, 0x0000, 0x00d1},
		{0x0000, 0x0000, 0x00e8},
		{0x0000, 0x0000, 0x00f8},
		{0x0008, 0x0000, 0x0100},
		{0x0000, 0x0002, 0x0108},
		{0x0001, 0x0000, 0x0158},
		{0x0808, 0x0000, 0x0159},
		{0x0000, 0x0000, 0x0198},
		{0x2001, 0x1e00, 0x0208},
		{0x0060, 0x001e, 0x0209},
		{0x0000, 0x1060, 0x020a},
		{0x0000, 0x0000, 0x020b},
	};

	load_cfg((void*)cin, 0xc000, 240, 0, 0);
	load_data(din_addr[0], 0x0, 4092, 1, 0, 0, 1, 0);
	load_data(din_addr[0], 0x1000, 4092, 0, 0, 0, 1, 0);
	config(0x0, 40, 0, 0);
	execute(0xbb, 0, 0);
	store(dout_addr[0], 0x6000, 3836, 0, 0, 0, 0, 0);
}
// #define N 8
 #define _PB_N 32
int A[_PB_N][_PB_N]__attribute__((aligned(16)));
int B[_PB_N][_PB_N]__attribute__((aligned(16)));
int B_i[_PB_N][_PB_N]__attribute__((aligned(16)));
   //kernel 23
void stencil() { 
    for (int i = 1; i < _PB_N - 1; i++)
          for (int j = 1; j < _PB_N - 1; j++)
            B_i[i][j] = 2 * (A[i][j] + A[i][j-1] + A[i][1+j] + A[1+i][j] + A[i-1][j]);

}

void result_check()
{
  int i, j;


    for (int i = 1; i < _PB_N - 1; i++)
	    for (int j = 1; j < _PB_N - 1; j++)
	// if(i == 8) continue;
    		if (B_i[i][j] != B[i][j]) printf("There is an error in location (%d)[%d, %d]\n", i*32+j, B_i[i][j], B[i][j]);


}


int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

    for (int i = 0; i < _PB_N - 1; i++){
	    for (int j = 0; j < _PB_N - 1; j++){
			A[i][j] = i+j;
			B_i[i][j] = 0;
			B[i][j] = 0;
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
  
  printf("CPU add finished!\n");
  start = rdcycle();
  /* Run kernel. */
  stencil();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
  void* cgra_din_addr[1] = {A};
  void* cgra_dout_addr[1] = {(void*)B+128};
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
