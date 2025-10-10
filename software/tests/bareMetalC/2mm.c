#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[69][3] __attribute__((aligned(16))) = {
		{0x0000, 0x0200, 0x0010},
		{0x0010, 0x1008, 0x0011},
		{0x0800, 0x0c10, 0x0012},
		{0x0000, 0x0000, 0x0013},
		{0x4002, 0x0200, 0x0028},
		{0x7f40, 0x4008, 0x0029},
		{0x0800, 0x0010, 0x002a},
		{0x0108, 0x0000, 0x002b},
		{0x4000, 0x0200, 0x0030},
		{0x7f40, 0x4008, 0x0031},
		{0x0800, 0x0010, 0x0032},
		{0x0108, 0x0000, 0x0033},
		{0x0210, 0x0000, 0x0048},
		{0x6000, 0x0000, 0x0050},
		{0x0100, 0x0000, 0x0058},
		{0x0000, 0x0000, 0x0068},
		{0x1011, 0x0000, 0x00b1},
		{0x0000, 0x0040, 0x00b2},
		{0x2058, 0x0000, 0x00b3},
		{0x0001, 0x0000, 0x00b4},
		{0xe041, 0x0000, 0x00b9},
		{0xe041, 0x0000, 0x00c1},
		{0x6021, 0x0000, 0x00c9},
		{0x0029, 0x0000, 0x00d0},
		{0x1023, 0x0000, 0x00d1},
		{0x0029, 0x0000, 0x00d8},
		{0x0803, 0x0000, 0x00d9},
		{0x0040, 0x0010, 0x00f0},
		{0x00c1, 0x0090, 0x00f8},
		{0xc080, 0x00c0, 0x0100},
		{0x4081, 0x0000, 0x0108},
		{0x4000, 0x0000, 0x0110},
		{0x0029, 0x0000, 0x0158},
		{0x0003, 0x0001, 0x0159},
		{0x0029, 0x0000, 0x0160},
		{0x0003, 0x0001, 0x0161},
		{0x0903, 0x0001, 0x0169},
		{0x0903, 0x0001, 0x0171},
		{0x4a43, 0x0000, 0x0179},
		{0x5823, 0x0000, 0x0181},
		{0x6000, 0x0000, 0x0198},
		{0x7000, 0x0000, 0x01a0},
		{0x7000, 0x0000, 0x01a8},
		{0x8802, 0x0000, 0x01b0},
		{0x0808, 0x0000, 0x01b8},
		{0x4003, 0x0200, 0x0200},
		{0x7f40, 0x4008, 0x0201},
		{0x0800, 0x0010, 0x0202},
		{0x0108, 0x0000, 0x0203},
		{0x4001, 0x0200, 0x0208},
		{0x7f40, 0x4008, 0x0209},
		{0x0800, 0x0010, 0x020a},
		{0x0108, 0x0000, 0x020b},
		{0x0030, 0x0204, 0x0210},
		{0x7410, 0x1008, 0x0211},
		{0x0873, 0x0010, 0x0212},
		{0x0148, 0x0000, 0x0213},
		{0x0020, 0x0204, 0x0218},
		{0x7410, 0x1008, 0x0219},
		{0x0873, 0x0010, 0x021a},
		{0x0148, 0x0000, 0x021b},
		{0x0000, 0x0204, 0x0220},
		{0x7410, 0x1008, 0x0221},
		{0x0873, 0x0110, 0x0222},
		{0x0148, 0x0000, 0x0223},
		{0x0010, 0x0204, 0x0228},
		{0x7410, 0x1008, 0x0229},
		{0x0873, 0x0010, 0x022a},
		{0x0148, 0x0000, 0x022b},
	};

	load_cfg((void*)cin, 0xc000, 414, 0, 0);
	load_data(din_addr[0], 0x4000, 1024, 1, 0, 0, 2, 0);
	load_data(din_addr[0], 0x5000, 1024, 1, 0, 0, 2, 0);
	load_data(din_addr[0], 0x6000, 1024, 1, 0, 0, 2, 0);
	load_data(din_addr[0], 0x7000, 1024, 0, 0, 0, 2, 0);
	load_data(din_addr[1], 0x8000, 1024, 1, 0, 0, 2, 4);
	load_data(din_addr[1], 0x9000, 1024, 1, 0, 0, 2, 4);
	load_data(din_addr[1], 0xa000, 1024, 1, 0, 0, 2, 4);
	load_data(din_addr[1], 0xb000, 1024, 0, 0, 0, 2, 4);
	config(0x0, 69, 0, 0);
	execute(0xff2, 0, 0);
	store(dout_addr[0], 0x0, 1024, 0, 0, 0, 0, 0);
}

#define _PB_LENGTH 15
int A[_PB_LENGTH+1][_PB_LENGTH+1]__attribute__((aligned(16)));
int B[_PB_LENGTH+1][_PB_LENGTH+1]__attribute__((aligned(16)));
int C[_PB_LENGTH+1][_PB_LENGTH+1]__attribute__((aligned(16)));
int C_i[_PB_LENGTH+1][_PB_LENGTH+1]__attribute__((aligned(16)));
   //kernel 23
void kernel() { 
     int alpha = 41;
     for (int i = 0; i <= _PB_LENGTH ; i++)
        {
          for (int j = 0; j <= _PB_LENGTH ; j++)
          {
            //#pragma unroll 2
            int temp = 0;
            //#pragma unroll 4
            for (int k = 0; k <= _PB_LENGTH; k++){
	      		temp += alpha * A[i][k] * B[k][j];
	    }
	    C_i[i][j] = temp;
          }
        }
}

void result_check()
{
  for (int i=0 ; i < 16 ; i++) {
          for (int j=0 ; j < 16 ; j++){
    		if (C_i[i][j] != C[i][j]) printf("There is an error in location (%d)[%d, %d]\n", i*16+j, C_i[i][j], C[i][j]);
        } 
  }
}

int main(){

//   int i,j;
  long long unsigned start;
  long long unsigned end;

   for (int i=0 ; i < 16 ; i++) {
          for (int j=0 ; j < 16 ; j++){
    		A[i][j] = i + j;
    		B[i][j] = i + j;
    		C[i][j] = 0;
    		C_i[i][j] = 0;
			// a_i[i][j] = i + j;
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
  kernel();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
  void* cgra_din_addr[2] = {A, B};
  void* cgra_dout_addr[1] = {C};
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
