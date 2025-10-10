#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"



__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[60][3] __attribute__((aligned(16))) = {
		{0x2000, 0x0000, 0x0010},
		{0x0088, 0x004f, 0x0011},
		{0x0000, 0x0800, 0x0012},
		{0x0200, 0x0000, 0x0013},
		{0x2000, 0x0000, 0x0030},
		{0x0088, 0x0040, 0x0031},
		{0x0000, 0x0800, 0x0032},
		{0x0004, 0x0000, 0x0033},
		{0x8000, 0x0000, 0x0048},
		{0x0030, 0x0000, 0x0068},
		{0x0c00, 0x0000, 0x00f0},
		{0x0000, 0x0008, 0x0110},
		{0x0060, 0x0000, 0x0120},
		{0x0100, 0x0000, 0x0129},
		{0x0000, 0x0002, 0x0131},
		{0x0000, 0x0080, 0x0138},
		{0x0000, 0x0000, 0x0160},
		{0x0007, 0x0008, 0x0162},
		{0x0001, 0x0000, 0x0168},
		{0x8001, 0x0002, 0x016a},
		{0x0000, 0x0000, 0x0170},
		{0x0186, 0x0002, 0x0172},
		{0x0000, 0x0000, 0x0173},
		{0x0004, 0x0000, 0x0174},
		{0x0806, 0x0012, 0x017a},
		{0x0180, 0x0000, 0x017b},
		{0x0008, 0x0000, 0x017c},
		{0x0000, 0x0040, 0x01a0},
		{0x1030, 0x0080, 0x01a8},
		{0x0020, 0x0000, 0x01b0},
		{0x0000, 0x0000, 0x01c8},
		{0x0000, 0x0400, 0x01d0},
		{0x0000, 0x00c0, 0x01e1},
		{0x0000, 0x0002, 0x01e8},
		{0x0000, 0x0000, 0x0208},
		{0x8186, 0x0001, 0x020a},
		{0x0000, 0x0000, 0x020b},
		{0x0004, 0x0000, 0x020c},
		{0x0001, 0x0000, 0x0210},
		{0x8004, 0x0101, 0x0212},
		{0x0000, 0x0000, 0x0213},
		{0x0260, 0x0000, 0x0214},
		{0x0001, 0x0000, 0x0218},
		{0x0011, 0x0000, 0x021a},
		{0x0000, 0x0000, 0x021c},
		{0x0000, 0x0040, 0x021d},
		{0x0040, 0xc002, 0x021e},
		{0x0100, 0x0000, 0x0250},
		{0x0000, 0x0030, 0x0280},
		{0x0001, 0x0000, 0x02b8},
		{0x0011, 0x0000, 0x02ba},
		{0x0000, 0x0000, 0x02bc},
		{0x2000, 0x0000, 0x02bd},
		{0x2000, 0xc008, 0x02be},
		{0xffff, 0xffff, 0x02c0},
		{0x000a, 0x0001, 0x02c2},
		{0x0100, 0x0000, 0x02f0},
		{0x0000, 0x0000, 0x0329},
		{0x0100, 0x0000, 0x0360},
		{0x0004, 0x0001, 0x0362},
	};

	load_cfg((void*)cin, 0x18000, 360, 0, 0);
	load_data(din_addr[0], 0x0, 2048, 0, 0, 0);
	config(0x0, 60, 0, 0);
	execute(0x22, 0, 0);
	store(dout_addr[0], 0x8000, 8192, 0, 0);
}


#define NUM_BEAMS 4 
#define NUM_POST_DEC_2 512
#define TARGET_BEAM 1
#define TARGET_SAMPLE 256
int data[512]__attribute__((aligned(16)));
int output [4][512]__attribute__((aligned(16)));
int output_i [4][512]__attribute__((aligned(16)));

void Detector()
{
  int sample;
  /* Should be exactly NUM_POST_DEC_2 samples. */
  // loop_begin();
  for (int i = 0; i < NUM_BEAMS; i++){
    for (sample = 0; sample < NUM_POST_DEC_2; sample++)
    {
      int outputVal;
      if (i == TARGET_BEAM && sample == TARGET_SAMPLE) {
        if (data[sample] >= 1)
          outputVal = i+1;
        else
          outputVal = 0;
      } else {
        if (data[sample] >= 1)
          outputVal = -(i+1);
        else
          outputVal = 0;
      }
      // outputVal = data[sample]; // @xcgao
      output_i[i][sample]= outputVal;
    }
  }
  // loop_end();
}


void result_check()
{
  int i, j;

  for (i = 0; i < 4; i++)
  {
    for(j=0; j < 512; j++){
      if (output_i[i][j] != output[i][j]) printf("There is an error in location (%d, %d)[%d, %d]\n", i, j, output_i[i], output[i]);
    }
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
    
  for(int i=0; i< 512; i++){
      data[i] = i;
  }
//   for(int i=0; i< Ncb; i++){
//       W[i] = 0;
//       W_i[i] = 0;
//   }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
//   printf("~~Initialization finished!\n");
  
//   // printf("CPU add finished!\n");
//   start = rdcycle();
//   /* Run kernel. */
//   Detector();
//   end = rdcycle();
//   printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[1] = {data};
  void* cgra_dout_addr[1] = {output};
//   void* cgra_din_addr[1] = {test};
//   cgra_execute(cgra_dout_addr);
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
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
