#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[27][3] __attribute__((aligned(16))) = {
		{0x1001, 0x0380, 0x0018},
		{0x7fa0, 0x2004, 0x0019},
		{0x0400, 0x0020, 0x001a},
		{0x0400, 0x0000, 0x001b},
		{0x8008, 0x0380, 0x0020},
		{0x7d10, 0x9004, 0x0021},
		{0x047c, 0x0120, 0x0022},
		{0x0400, 0x0000, 0x0023},
		{0x1001, 0x0380, 0x0028},
		{0x0020, 0x2004, 0x0029},
		{0x0400, 0x0920, 0x002a},
		{0x8000, 0x0200, 0x002b},
		{0x0000, 0x0380, 0x0030},
		{0x0080, 0x8004, 0x0031},
		{0x0400, 0x0220, 0x0032},
		{0x0400, 0x0000, 0x0033},
		{0x2200, 0x0000, 0x0058},
		{0x0100, 0x0000, 0x0060},
		{0x0001, 0x0000, 0x0068},
		{0x1011, 0x0000, 0x00c1},
		{0x0000, 0x0080, 0x00c2},
		{0xe020, 0x0000, 0x00c3},
		{0x0001, 0x0000, 0x00c4},
		{0x4821, 0x0000, 0x00c9},
		{0x5041, 0x0000, 0x00d1},
		{0x0000, 0x0000, 0x0110},
		{0x0004, 0x0000, 0x0118},
	};

	load_cfg((void*)cin, 0xc000, 162, 0, 0);
	load_data(din_addr[0], 0x0, 256, 0, 0, 0, 0, 0);
	load_data(din_addr[1], 0x4000, 2048, 0, 0, 0, 0, 0);
	config(0x0, 27, 0, 0);
	execute(0x3c, 0, 0);
	store(dout_addr[0], 0x4000, 2048, 0, 0, 0, 0, 0);
}
// #define N 8
  #define _PB_LENGTH 7
  int c[_PB_LENGTH+1][_PB_LENGTH+1]__attribute__((aligned(16)));
  int sum_c[_PB_LENGTH+1][_PB_LENGTH+1][_PB_LENGTH+1]__attribute__((aligned(16)));
  int sum_c_i[_PB_LENGTH+1][_PB_LENGTH+1][_PB_LENGTH+1]__attribute__((aligned(16)));
   //kernel 23
void dynprog() { 
    for (int i = 0; i <= _PB_LENGTH ; i++)
        {
          for (int j = 0; j <= _PB_LENGTH ; j++)
          {
            for (int k = 1; k <= _PB_LENGTH; k++)
              sum_c_i[i][j][k] = sum_c_i[i][j][k-1] + c[i][k] + c[k][j];
          }
        }

}

void result_check()
{
    for (int i = 0; i <= _PB_LENGTH ; i++)
        {
          for (int j = 0; j <= _PB_LENGTH ; j++)
          {
            for (int k = 1; k <= _PB_LENGTH; k++)
			if (sum_c_i[i][j][k] != sum_c[i][j][k]) printf("There is an error in location (%d)[%d, %d]\n", i*64 + j*8+k, sum_c_i[i][j][k], sum_c[i][j][k]);
          }
        }

}


int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

    
    for (int i = 0; i <= _PB_LENGTH ; i++)
        {
          for (int j = 0; j <= _PB_LENGTH ; j++)
          {
			c[i][j] = i + j;
            for (int k = 0; k <= _PB_LENGTH; k++){
			sum_c[i][j][k] = 0;
			// sum_c_i[i][j][k] = 0;
			}
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
  dynprog();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
  void* cgra_din_addr[1] = {c};
  void* cgra_dout_addr[1] = {sum_c};
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
    
  // printf("Checking results!\n");
  // result_check();
  printf("Done!\n");

return 0;

}
