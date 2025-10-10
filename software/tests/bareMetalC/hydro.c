#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[62][3] __attribute__((aligned(16))) = {
		{0x2004, 0xfd00, 0x0008},
		{0x0000, 0x0000, 0x0009},
		{0x0000, 0x0120, 0x000a},
		{0x0104, 0x0000, 0x000b},
		{0x2003, 0xfd00, 0x0010},
		{0x0000, 0x0000, 0x0011},
		{0x0000, 0x0020, 0x0012},
		{0x0104, 0x0000, 0x0013},
		{0x2002, 0xfd00, 0x0018},
		{0x0000, 0x0000, 0x0019},
		{0x0000, 0x0020, 0x001a},
		{0x0104, 0x0000, 0x001b},
		{0x2003, 0xfd00, 0x0020},
		{0x0000, 0x0000, 0x0021},
		{0x0000, 0x0120, 0x0022},
		{0x0104, 0x0000, 0x0023},
		{0x2000, 0xfd00, 0x0028},
		{0x0000, 0x0000, 0x0029},
		{0x0000, 0x0120, 0x002a},
		{0x0104, 0x0000, 0x002b},
		{0x0000, 0x0000, 0x0040},
		{0x0000, 0x0000, 0x0048},
		{0x0800, 0x0000, 0x0058},
		{0x0000, 0x0000, 0x0060},
		{0x0003, 0x0000, 0x00b0},
		{0x1007, 0x0000, 0x00b1},
		{0x9821, 0x0000, 0x00b9},
		{0x9a03, 0x0000, 0x00c1},
		{0x0005, 0x0000, 0x00c8},
		{0x0803, 0x0000, 0x00c9},
		{0x0005, 0x0000, 0x00d0},
		{0x0803, 0x0000, 0x00d1},
		{0x0008, 0x0000, 0x00e8},
		{0x0200, 0x0010, 0x00f0},
		{0x1800, 0x0020, 0x00f8},
		{0x4080, 0x0000, 0x0100},
		{0x0000, 0x0000, 0x0110},
		{0x0003, 0x0000, 0x0158},
		{0x0807, 0x0000, 0x0159},
		{0x5203, 0x0000, 0x0161},
		{0x000f, 0x0000, 0x0168},
		{0x4001, 0x0000, 0x0169},
		{0x0801, 0x0001, 0x0171},
		{0x000f, 0x0000, 0x0178},
		{0x1801, 0x0000, 0x0179},
		{0x0000, 0x0000, 0x0190},
		{0x0000, 0x0000, 0x01a0},
		{0x0000, 0x0001, 0x01a8},
		{0x000a, 0x0000, 0x01b0},
		{0x1000, 0x0000, 0x01b8},
		{0x2001, 0xfd00, 0x0200},
		{0x0000, 0x0000, 0x0201},
		{0x0000, 0x0120, 0x0202},
		{0x0104, 0x0000, 0x0203},
		{0x2000, 0xfd00, 0x0218},
		{0x0000, 0x0000, 0x0219},
		{0x0000, 0x0720, 0x021a},
		{0x0004, 0x0000, 0x021b},
		{0x2001, 0xfd00, 0x0228},
		{0x0000, 0x0000, 0x0229},
		{0x0000, 0x0920, 0x022a},
		{0x0004, 0x0000, 0x022b},
	};

	load_cfg((void*)cin, 0xc000, 372, 0, 0);
	load_data(din_addr[0], 0x4000, 4048, 1, 0, 0, 1, 0);
	load_data(din_addr[0], 0x5000, 4048, 0, 0, 0, 1, 0);
	load_data(din_addr[1], 0x0, 4052, 1, 0, 0, 1, 0);
	load_data(din_addr[1], 0x1000, 4052, 0, 0, 0, 1, 0);
	config(0x0, 62, 0, 0);
	execute(0xa5f, 0, 0);
	store(dout_addr[0], 0x8000, 4048, 1, 0, 0, 1, 0);
	store(dout_addr[0], 0x9000, 4048, 0, 0, 0, 1, 0);
}
// #define N 8
	 #define size 1024
    int x[size]__attribute__((aligned(16)));
    int x_i[size]__attribute__((aligned(16)));
    int y[size]__attribute__((aligned(16)));
    int z[size]__attribute__((aligned(16)));
   //kernel 23
void hydro() { 
      
    int q = 15;
    int r = 5;
    int t = 8;
    for ( int k=0 ; k<1012 ; k++ ) {
            x_i[k] = q + y[k]*( r*z[k+10] + t*z[k+11] );
    } 
                 

}

void result_check()
{
  int i, j;    
    for ( int k=0 ; k<1012 ; k++ ) {
    		if (x_i[k] != x[k]) printf("There is an error in location (%d)[%d, %d]\n", k, x[k], x_i[k]);
        } 
	// if(i == 8) continue;


}


int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

    for (int i = 0; i < size ; i++){
	    x_i[i] = 0;
		x[i] = 0;
		y[i] = i;
		z[i] = i;

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
  hydro();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
  void* cgra_din_addr[2] = {y, (void*)z+40};
  void* cgra_dout_addr[1] = {x};
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
