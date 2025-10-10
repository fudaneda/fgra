#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"



__attribute__((noinline))
void cgra_execute(void** dout_addr)
{
	static unsigned short cin[78][3] __attribute__((aligned(16))) = {
		{0x4000, 0x0000, 0x0028},
		{0x0108, 0x00ce, 0x0029},
		{0x3804, 0x9003, 0x002a},
		{0x4402, 0x5000, 0x002b},
		{0x0200, 0x0000, 0x0030},
		{0x0008, 0x00c0, 0x0031},
		{0x0000, 0x1003, 0x0032},
		{0x8403, 0x0000, 0x0033},
		{0x6000, 0x0000, 0x0060},
		{0x0022, 0x0000, 0x0068},
		{0x0000, 0x0004, 0x0098},
		{0x0023, 0x0000, 0x00a0},
		{0x0000, 0x0008, 0x0108},
		{0x0000, 0x0008, 0x0110},
		{0xc000, 0x0000, 0x0141},
		{0x1800, 0x0000, 0x0149},
		{0x8003, 0x0016, 0x016a},
		{0x0003, 0x0012, 0x0172},
		{0x0000, 0x0000, 0x0178},
		{0x0002, 0x0010, 0x017a},
		{0x3000, 0x0800, 0x01a0},
		{0x0001, 0x0000, 0x01a8},
		{0x0000, 0x0000, 0x01b0},
		{0x0000, 0x0c00, 0x01d9},
		{0x0000, 0x0006, 0x01e1},
		{0x0000, 0x0030, 0x01e9},
		{0xc000, 0x0000, 0x01f1},
		{0x0001, 0x0000, 0x0208},
		{0x8001, 0x0001, 0x020a},
		{0x0001, 0x0000, 0x0210},
		{0x0011, 0x0000, 0x0212},
		{0x0000, 0x0000, 0x0214},
		{0x4000, 0x0000, 0x0215},
		{0x2000, 0xc120, 0x0216},
		{0x0001, 0x0000, 0x0218},
		{0x0011, 0x0000, 0x021a},
		{0x0000, 0x0000, 0x021c},
		{0x0000, 0x0200, 0x021d},
		{0x00c0, 0xc002, 0x021e},
		{0x0020, 0x0000, 0x0238},
		{0x0000, 0x0000, 0x0240},
		{0x0100, 0x0600, 0x0248},
		{0x0100, 0x0000, 0x0250},
		{0x0000, 0xc000, 0x0280},
		{0x0000, 0x00c0, 0x0289},
		{0x0000, 0x00e0, 0x0291},
		{0x8000, 0x0000, 0x0299},
		{0x0100, 0x0000, 0x02b8},
		{0x0004, 0x0101, 0x02ba},
		{0x0000, 0x0002, 0x02bb},
		{0x0320, 0x0000, 0x02bc},
		{0x0001, 0x0000, 0x02c0},
		{0x0004, 0x00e1, 0x02c2},
		{0x0000, 0x0000, 0x02c3},
		{0x0260, 0x0000, 0x02c4},
		{0x0010, 0x0000, 0x02e0},
		{0x2000, 0x0000, 0x02f0},
		{0x0000, 0x0030, 0x0321},
		{0x0000, 0x0c01, 0x0329},
		{0x0000, 0x0000, 0x0330},
		{0x0000, 0x0001, 0x0331},
		{0xffff, 0xffff, 0x0358},
		{0x800a, 0x0001, 0x035a},
		{0x0010, 0x0000, 0x0388},
		{0x0000, 0x0200, 0x0390},
		{0x0000, 0x0005, 0x03c9},
		{0x0000, 0x0028, 0x03d1},
		{0x0020, 0x0000, 0x0438},
		{0x0400, 0x0000, 0x0470},
		{0x0400, 0x0000, 0x0478},
		{0x0201, 0x0000, 0x04a0},
		{0x0008, 0x00c0, 0x04a1},
		{0x0000, 0x9003, 0x04a2},
		{0x0403, 0x4020, 0x04a3},
		{0x4001, 0x0000, 0x04a8},
		{0x0108, 0x00ce, 0x04a9},
		{0x3804, 0x1003, 0x04aa},
		{0x0403, 0x4010, 0x04ab},
	};

	load_cfg((void*)cin, 0x18000, 468, 0, 0);
	config(0x0, 78, 0, 0);
	execute(0xf0, 0, 0);
	store(dout_addr[0], 0x8000, 4096, 0, 0);
}



#define NUM_CHANNELS 12
#define n 512
#define TARGET_BEAM 1
#define TARGET_SAMPLE 256
int inputs[1024]__attribute__((aligned(16)));
int inputs_i[1024]__attribute__((aligned(16)));

// void InputGenerate()
void InputGenerate()// @xcgao
{
  int i,j,k; 
  for (i = 0; i < NUM_CHANNELS; i++) {
   for (j = 0; j < NUM_CHANNELS; j++){
    for (k = 0; k < n; k++)
     {
      if (i == TARGET_BEAM && k == TARGET_SAMPLE) // @xcgao
      {
        inputs_i[2*k] = (i*k)*(k*i);
        inputs_i[2*k+1] = (k*i)*(k*i)+1;
      } else {
        int root = (i*k)*(k*i);
        inputs_i[2*k] = -root;
        inputs_i[2*k+1] = -(root+1);
      }
    }
    }
  }
}


void result_check()
{
  int i, j;

  for (i = 0; i < 1024; i++)
  {
    if (inputs_i[i] != inputs[i]) printf("There is an error in location (%d)[%d, %d]\n", i, inputs_i[i], inputs[i]);
  }
}

int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

  // for (i=0;i<SIZE; i++){
  //     A[i] = i * 2 + 5;
  //     B[i] = i * 3;
  //     C[i] = 0;
  //     D[i] = 0;
  //   }
    
  for(int i=0; i< 1024; i++){
    // inputs_i[i] = 0;
	  inputs[i] = 0;
  }
//   for(int i=0; i< Ncb; i++){
//       W[i] = 0;
//       W_i[i] = 0;
//   }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
//   printf("~~Initialization finished!\n");
  
  // printf("CPU add finished!\n");
//   start = rdcycle();
//   /* Run kernel. */
//   InputGenerate();
//   end = rdcycle();
//   printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_dout_addr[1] = {inputs};
//   void* cgra_din_addr[1] = {test};
//   cgra_execute(cgra_dout_addr);
  start = rdcycle();
  cgra_execute(cgra_dout_addr);
//   cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
  printf("CGRA comput finished!\n");
//   result = fence(1);

//   for (i=0;i<16; i++) {
// 	printf("%d\\", crc_table[i]);
// 	// printf("%d", sizeof(C[i]));
// 	// printf("%s", ",,");
// 	// printf("%d\n", i);
//   }
    
//   result_check();
  printf("Done!\n");

return 0;

}
