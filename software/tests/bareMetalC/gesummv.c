#include "include/encoding.h"
#include "include/ISA.h"

#define DATA_TYPE int
#define N 64
#define _PB_N N

DATA_TYPE A[N][N] __attribute__((aligned(16)));
DATA_TYPE B[N][N] __attribute__((aligned(16)));
DATA_TYPE x[N] __attribute__((aligned(16)));
DATA_TYPE y[N] __attribute__((aligned(16)));
DATA_TYPE yy[N] __attribute__((aligned(16)));


/* Array initialization. */
void init_array ()
{
  int i, j;

  for (i = 0; i < _PB_N; i++)
  {
    x[i] = i;
    for (j = 0; j < _PB_N; j++)
    {
      A[i][j] = i+j;
      B[i][j] = i+2*j;
    }
  }
}

__attribute__((noinline))
void gesummv()
{
  int i, j;
  DATA_TYPE alpha = 3;
  DATA_TYPE beta = 2;

  for (i = 0; i < _PB_N; i++)
  {
    DATA_TYPE sum0 = 0;
    DATA_TYPE sum1 = 0;
    for (j = 0; j < _PB_N; j++)
    {
//      please_map_me();
      sum0 += A[i][j] * x[j];
      sum1 += B[i][j] * x[j];
    }
    yy[i] = alpha * sum0 + beta * sum1;
  }

}

void result_check()
{
  int i, j;

  for (i = 0; i < _PB_N; i++)
  {
      if (y[i] != yy[i]) printf("There is an error in location (%d)[%d, %d]\n", i, y[i], yy[i]);
  }
}


void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[30][5] __attribute__((aligned(16))) = {
		{0x4000, 0x0000, 0x0204, 0x2000, 0x0006},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0007},
		{0x0000, 0x0000, 0x0204, 0x2000, 0x000a},
		{0x0000, 0x8000, 0x4048, 0x0000, 0x000b},
		{0x7000, 0x0000, 0x8204, 0x207f, 0x000e},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000f},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x001a},
		{0x2000, 0x0000, 0x0000, 0x0000, 0x001c},
		{0x0003, 0x0002, 0x0000, 0x0000, 0x001e},
		{0x0000, 0x0010, 0x0000, 0x0000, 0x0020},
		{0x0000, 0x0000, 0xa203, 0x0000, 0x002c},
		{0x0000, 0x0000, 0x4011, 0x0000, 0x0030},
		{0x0000, 0x8004, 0x0802, 0x0100, 0x0031},
		{0x0001, 0x0000, 0x3007, 0x0000, 0x0032},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x003e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0042},
		{0x0c00, 0x0000, 0x0000, 0x0000, 0x0044},
		{0x0000, 0x0000, 0x2011, 0x0000, 0x004e},
		{0x0000, 0x8004, 0x0802, 0x0100, 0x004f},
		{0x0000, 0x0000, 0xa001, 0x0001, 0x0054},
		{0x0000, 0x0000, 0xc203, 0x0000, 0x0056},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0062},
		{0x0000, 0x0040, 0x0000, 0x0000, 0x0064},
		{0x0080, 0x0000, 0x0000, 0x0000, 0x0066},
		{0x0003, 0x0000, 0x0000, 0x0000, 0x006a},
		{0x0003, 0x0000, 0x1003, 0x0000, 0x0074},
		{0x0000, 0x0020, 0x0000, 0x0000, 0x008e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x00b2},
		{0x5000, 0x0000, 0x0204, 0x2000, 0x00c4},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00c5},
	};

	load_cfg((void*)cin, 0x402e0, 300, 2, 0);
	load_data(din_addr[0], 0x0, 16384, 0, 2, 0);
	load_data(din_addr[1], 0x34000, 16384, 0, 2, 0);
	load_data(din_addr[2], 0x1c000, 256, 0, 2, 0);
	config(0x2e, 30, 2, 0);
	execute(0x8054, 2, 0);
	store(dout_addr[0], 0x10000, 256, 2, 0);
}



int main(int argc, char** argv)
{
  long long unsigned start;
  long long unsigned end;
//  printf("The number of N is %d", N);
  init_array();
  printf("Initialization finished!\n");
  start = rdcycle();
  /* Run kernel. */
  gesummv();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[3] = {A, B, x};
  void* cgra_dout_addr[1] = {y};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}