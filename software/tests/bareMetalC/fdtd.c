#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[39][3] __attribute__((aligned(16))) = {
		{0x1001, 0x0f80, 0x0008},
		{0x8020, 0x000f, 0x0009},
		{0x0000, 0x0020, 0x000a},
		{0x0418, 0x0000, 0x000b},
		{0x1000, 0x0f80, 0x0010},
		{0x8020, 0x000f, 0x0011},
		{0x0000, 0x0020, 0x0012},
		{0x0418, 0x0000, 0x0013},
		{0x1020, 0x0f80, 0x0018},
		{0x8020, 0x000f, 0x0019},
		{0x0000, 0x0020, 0x001a},
		{0x0550, 0x0000, 0x001b},
		{0x1000, 0x0f80, 0x0020},
		{0x8020, 0x000f, 0x0021},
		{0x0000, 0x0020, 0x0022},
		{0x0550, 0x0000, 0x0023},
		{0x0000, 0x0000, 0x0038},
		{0x0000, 0x0000, 0x0040},
		{0x0000, 0x0000, 0x0048},
		{0x8802, 0x0000, 0x0081},
		{0x9901, 0x0000, 0x0089},
		{0x9a02, 0x0000, 0x0091},
		{0x0000, 0x0000, 0x00b0},
		{0x0100, 0x0000, 0x00b8},
		{0xfff9, 0xffff, 0x0108},
		{0x0803, 0x0000, 0x0109},
		{0x0000, 0x0200, 0x0130},
		{0x2000, 0x0000, 0x01a8},
		{0xd201, 0x0000, 0x01f1},
		{0x0040, 0x0000, 0x0218},
		{0x0000, 0x0000, 0x0220},
		{0x1000, 0x0f80, 0x0260},
		{0x8020, 0x000f, 0x0261},
		{0x0000, 0x0220, 0x0262},
		{0x0400, 0x0000, 0x0263},
		{0x1000, 0x0f80, 0x0270},
		{0x8020, 0x000f, 0x0271},
		{0x0000, 0x0720, 0x0272},
		{0x0000, 0x0000, 0x0273},
	};

	load_cfg((void*)cin, 0x8000, 234, 0, 0);
	load_data(din_addr[0], 0x2000, 3968, 1, 0, 0, 1, 0);
	load_data(din_addr[0], 0x3000, 3968, 0, 0, 0, 1, 0);
	load_data(din_addr[1], 0x0, 4092, 1, 0, 0, 1, 5);
	load_data(din_addr[1], 0x1000, 4092, 0, 0, 0, 1, 5);
	load_data(din_addr[2], 0x4000, 3964, 0, 0, 0, 0, 0);
	config(0x0, 39, 0, 0);
	execute(0x5f, 0, 0);
	store(dout_addr[0], 0x4000, 3964, 0, 0, 0, 0, 0);
}

// #define N 8
#define size 32
#define _PB_NX 32
#define _PB_NY 32
int hz_i[size][size]__attribute__((aligned(16)));
int hz[size][size]__attribute__((aligned(16)));
int ex[size][size]__attribute__((aligned(16)));
int ey[size][size]__attribute__((aligned(16)));
   //kernel 23
void fdtd() { 
    for (int i = 0; i < _PB_NX - 1; i++)
	    for (int j = 0; j < _PB_NY - 1; j++)
	        hz_i[i][j] = hz_i[i][j] - 7*  (ex[i][j+1] - ex[i][j] +
				       ey[i+1][j] - ey[i][j]);

}

void result_check()
{
  int i, j;


    for (int i = 0; i < _PB_NX - 1; i++)
	    for (int j = 0; j < _PB_NY - 1; j++)
	// if(i == 8) continue;
    		if (hz_i[i][j] != hz[i][j]) printf("There is an error in location (%d)[%d, %d]\n", i*32+j, hz_i[i][j], hz[i][j]);


}


int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

    for (int i = 0; i < _PB_NX - 1; i++){
	    for (int j = 0; j < _PB_NY - 1; j++){
			hz[i][j] = 20 + 500*(i+j);
			hz_i[i][j] = 20 + 500*(i+j);
			ex[i][j] = i + j;
			ey[i][j] = i + j;
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
  fdtd();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
  void* cgra_din_addr[3] = {ex, ey, hz};
  void* cgra_dout_addr[1] = {hz};
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
