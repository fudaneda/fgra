#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"



__attribute__((noinline))
void cgra_execute(void** dout_addr)
{
	static unsigned short cin[29][3] __attribute__((aligned(16))) = {
		{0x0000, 0x2000, 0x0018},
		{0x0080, 0x1000, 0x0019},
		{0x0000, 0xa000, 0x001a},
		{0x0002, 0x0000, 0x001b},
		{0x0001, 0x0000, 0x001c},
		{0x1001, 0x0000, 0x0058},
		{0x0000, 0x00c0, 0x0080},
		{0x0800, 0x0000, 0x0088},
		{0xc80c, 0x000a, 0x00c2},
		{0x0400, 0x0000, 0x00c3},
		{0x1db7, 0x04c1, 0x00c8},
		{0x4006, 0x0001, 0x00ca},
		{0x1100, 0x0000, 0x00f8},
		{0x0000, 0x0000, 0x0100},
		{0x0001, 0x0000, 0x0108},
		{0x0000, 0x0000, 0x0129},
		{0x0000, 0x0000, 0x0160},
		{0xc00e, 0x0000, 0x0162},
		{0x80a0, 0x000a, 0x016a},
		{0x4000, 0x0200, 0x016c},
		{0x0040, 0x0100, 0x016d},
		{0x0001, 0x0000, 0x0170},
		{0x0007, 0x0001, 0x0172},
		{0x0004, 0x0000, 0x01a8},
		{0x0000, 0x0100, 0x0210},
		{0x0021, 0x0000, 0x0212},
		{0x0000, 0x0000, 0x0213},
		{0x0000, 0x0002, 0x0214},
		{0x0800, 0x6001, 0x0215},
	};

	load_cfg((void*)cin, 0x18000, 174, 0, 0);
	config(0x0, 29, 0, 0);
	execute(0x4, 0, 0);
	store(dout_addr[0], 0x0, 1024, 0, 0);
}


#define POLYNOMIAL 0x04c11db7L

int crc_table[256]__attribute__((aligned(16)));
int crc_table_i[256]__attribute__((aligned(16)));
unsigned int test[256]__attribute__((aligned(16)));

/* generate the table of CRC remainders for all possible bytes */
void gen_crc_table()
{ 
  int i, j;  
  int crc_accum;
  
  for (i = 0;  i < 256;  i++)
    { 
      crc_accum = ((int) i << 24);
      for (j = 0;  j < 8;  j++)
	{ 
	  if (crc_accum & 0x80000000L)
	    crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
	  else
	    crc_accum = (crc_accum << 1); 
	}
      crc_table_i[i] = crc_accum; 
    }
  return; 
}


void result_check()
{
  int i, j;

  for (i = 0; i < 256; i++)
  {
    if (crc_table_i[i] != crc_table[i]) printf("There is an error in location (%d)[%d, %d]\n", i, crc_table_i[i], crc_table[i]);
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
    
  for(int i=0; i< 256; i++){
      crc_table[i] = 0;
	//   crc_table_i[i] = 0;
	//   test[i] = 0;
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
//   gen_crc_table();
//   end = rdcycle();
//   printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_dout_addr[1] = {crc_table};
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
