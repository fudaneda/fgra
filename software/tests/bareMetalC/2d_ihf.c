#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

// __attribute__((noinline))
// void cgra_execute(void** din_addr, void** dout_addr)
// {
// 	static unsigned short cin[42][3] __attribute__((aligned(16))) = {
// 		{0x4001, 0xd000, 0x0010},
// 		{0x0007, 0x0000, 0x0011},
// 		{0x0000, 0x1000, 0x0012},
// 		{0x0800, 0x0002, 0x0013},
// 		{0x4002, 0xd000, 0x0018},
// 		{0x0007, 0x0000, 0x0019},
// 		{0x0000, 0x1000, 0x001a},
// 		{0x0800, 0x0002, 0x001b},
// 		{0x4000, 0xd000, 0x0028},
// 		{0x0007, 0x0000, 0x0029},
// 		{0x0000, 0x1000, 0x002a},
// 		{0x1000, 0x0002, 0x002b},
// 		{0x4002, 0xd000, 0x0030},
// 		{0x0007, 0x0000, 0x0031},
// 		{0x0000, 0x1000, 0x0032},
// 		{0x1000, 0x0002, 0x0033},
// 		{0x0000, 0x0000, 0x0050},
// 		{0x0800, 0x0000, 0x0058},
// 		{0x0800, 0x0000, 0x0060},
// 		{0x0000, 0x0000, 0x0068},
// 		{0x6003, 0x0002, 0x00ca},
// 		{0x6083, 0x0002, 0x00d2},
// 		{0x0100, 0x0000, 0x0108},
// 		{0x4401, 0x0002, 0x017a},
// 		{0x0000, 0x0800, 0x01a0},
// 		{0x0000, 0x0003, 0x01a8},
// 		{0x0000, 0x0000, 0x01b0},
// 		{0x0000, 0x0600, 0x0248},
// 		{0x0000, 0x0600, 0x02f0},
// 		{0x8000, 0x0000, 0x0398},
// 		{0xa182, 0x0003, 0x0402},
// 		{0x0000, 0x0000, 0x0438},
// 		{0x0001, 0x0000, 0x0440},
// 		{0x2001, 0xd000, 0x04a0},
// 		{0x0007, 0x0000, 0x04a1},
// 		{0x0000, 0x9000, 0x04a2},
// 		{0x1004, 0x0040, 0x04a3},
// 		{0x0100, 0x0000, 0x04a4},
// 		{0x4001, 0xd000, 0x04a8},
// 		{0x0007, 0x0000, 0x04a9},
// 		{0x0000, 0x1000, 0x04aa},
// 		{0x1001, 0x0002, 0x04ab},
// 	};

// 	load_cfg((void*)cin, 0x18000, 252, 0, 0);
// 	load_data(din_addr[0], 0x0, 4004, 1, 0, 0, 1, 0);
// 	load_data(din_addr[0], 0x2000, 4004, 0, 0, 0, 1, 0);
// 	load_data(din_addr[1], 0x8000, 4004, 1, 0, 0, 2, 0);
// 	load_data(din_addr[1], 0xa000, 4004, 1, 0, 0, 2, 0);
// 	load_data(din_addr[1], 0xc000, 4004, 1, 0, 0, 2, 0);
// 	load_data(din_addr[1], 0xe000, 4004, 0, 0, 0, 2, 0);
// 	config(0x0, 42, 0, 0);
// 	execute(0xf6, 0, 0);
// 	store(dout_addr[0], 0x8000, 4004, 1, 0, 0, 2, 0);
// 	store(dout_addr[0], 0xa000, 4004, 1, 0, 0, 2, 0);
// 	store(dout_addr[0], 0xc000, 4004, 1, 0, 0, 2, 0);
// 	store(dout_addr[0], 0xe000, 4004, 0, 0, 0, 2, 0);
// }


volatile int zz[7][101];
volatile int za[7][101];
volatile int za_i[7][101];
volatile int zv[7][101];
volatile int zr[7][101];
volatile int zb[7][101];
volatile int zu[7][101];
   //kernel 23
   void kernel() { 
       int kn = 6;
       int n = 100;
       int qa = 0;
        for ( int j=1 ; j<6 ; j++ ) {
            for ( int k=1 ; k<n ; k++ ) {
                qa = za_i[j+1][k]*zr[j][k] + za_i[j-1][k]*zb[j][k] +
                     za_i[j][k+1]*zu[j][k] + za_i[j][k-1]*zv[j][k] + zz[j][k];
                za_i[j][k] += 2*( qa - za_i[j][k] );
            }
        }
   }

void result_check()
{
  int i, j;


//   for (i = 0; i < SIZE; i++)
//   {
// 	// if(i == 8) continue;
//     if (x_i[i] != x[i]) printf("There is an error in location (%d)[%d, %d]\n", i, x_i[i], x[i]);

//   }
}

int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

  for (i=0;i<7; i++){
    for(j=0; j< 101; j ++){
      zz[i][j] = i + j;
      za[i][j] = i + j;
      za_i[i][j] = i + j;
      zv[i][j] = i + j;
      zr[i][j] = i + j;
      zb[i][j] = i + j;
      zu[i][j] = i + j;
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
  kernel();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
//   void* cgra_din_addr[2] = {v, x};
//   void* cgra_dout_addr[1] = {x};
//   start = rdcycle();
//   cgra_execute(cgra_din_addr, cgra_dout_addr);
//   volatile int result = fence(1);
//   end = rdcycle();
//   printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
//   printf("CGRA comput finished!\n");
//   result = fence(1);

//   for (i=0;i<32; i++) {
// 	printf("%d\\", X[i]);
// 	// printf("%d", sizeof(C[i]));
// 	// printf("%s", ",,");
// 	// printf("%d\n", i);
//   }
    
//   printf("Checking results!\n");
//   result_check();
  printf("Done!\n");

return 0;

}
