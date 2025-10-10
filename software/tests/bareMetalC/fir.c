
#include "include/encoding.h"
#include "include/ISA.h"

#define NDATA 4096
#define NTAPS 8

int input[NDATA] __attribute__((aligned(16)));
int output[NDATA] __attribute__((aligned(16)));
int output1[NDATA] __attribute__((aligned(16)));
int coefficients[NTAPS] __attribute__((aligned(16))) = {
025, 150, 375, -225, 050, 075, -300, 125};


void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[23][5] __attribute__((aligned(16))) = {
		{0xc000, 0x8fff, 0x1000, 0x0000, 0x0006},
		{0x0008, 0x8000, 0x0000, 0x0000, 0x0007},
		{0x4000, 0x8000, 0xf200, 0x007f, 0x000a},
		{0x0008, 0x8000, 0x0000, 0x0000, 0x000b},
		{0x1000, 0x8000, 0x0200, 0x0000, 0x0010},
		{0x0008, 0x8000, 0x0046, 0x0000, 0x0011},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x001a},
		{0x0000, 0x0008, 0x0000, 0x0000, 0x001c},
		{0x0800, 0x0000, 0x0000, 0x0000, 0x001e},
		{0x0010, 0x0000, 0x0000, 0x0000, 0x0022},
		{0x0000, 0x0000, 0x9043, 0x0000, 0x0030},
		{0x0000, 0x0000, 0xb421, 0x0001, 0x0032},
		{0x0000, 0x8004, 0x0102, 0x4000, 0x0033},
		{0x0040, 0x0000, 0x0000, 0x0000, 0x0044},
		{0x0000, 0x0000, 0x4006, 0x0000, 0x0054},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0068},
		{0x1000, 0x0000, 0x0000, 0x0000, 0x006a},
		{0x0000, 0x0000, 0x200a, 0x0002, 0x007a},
		{0x0001, 0x0000, 0x0011, 0x0000, 0x007c},
		{0x0000, 0x0020, 0x0000, 0x8006, 0x007d},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x008e},
		{0x0001, 0x0000, 0x0011, 0x0000, 0x00a0},
		{0x0000, 0x0004, 0x0100, 0xc000, 0x00a1},
	};

	load_cfg((void*)cin, 0x40000, 230, 0, 0);
	load_data(din_addr[0], 0x10000, 32, 0, 0, 0);
	load_data(din_addr[1], 0x0, 16384, 0, 0, 0);
	config(0x0, 23, 0, 0);
	execute(0x94, 0, 0);
	store(dout_addr[0], 0x14000, 16384, 0, 0);
}


/* Array initialization. */
void init_array()
{
  int i, j;

  for (i = 0; i < NDATA; i++)
    {
      input[i] = i;
//      output[i] = 0;
//      res[i] = 0;
    }
}


__attribute__((noinline))
void fir()//(int input[], int output[], int coefficients[])
/*   input :           input sample array */
/*   output:           output sample array */
/*   coefficient:      coefficient array */
{
   int i, j;

   for(j=0; j< NDATA; ++j) {
 	  int sum = 0;
    //#pragma unroll 4
    for (i = 0; i < NTAPS; ++i) {
      #ifdef CGRA_COMPILER
      please_map_me();
      #endif
      if(i<=j){
        sum += input[j-i] * coefficients[i];
      }
    }
    output1[j] = sum;
 }
}


void result_check()
{
  int i, j;

  for (i = 0; i < NDATA; i++)
  {
    if (output1[i] != output[i]) printf("There is an error in location (%d)[%d, %d]\n", i, output1[i], output[i]);
  }
}


int main(int argc, char** argv)
{
  long long unsigned start;
  long long unsigned end;
  init_array();
  printf("Initialization finished!\n");

  start = rdcycle();
  /* Run kernel. */
  fir();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

//  void* cgra_din_addr[9] = {coefficients, coefficients, coefficients, coefficients, input, input, input, input, output};
  void* cgra_din_addr[2] = {coefficients, input};
  void* cgra_dout_addr[1] = {output};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}