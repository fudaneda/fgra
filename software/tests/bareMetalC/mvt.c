#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
//#include "include/polybench.h"

/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#include "include/encoding.h"
#include "include/ISA.h"

//#define POLYBENCH_USE_SCALAR_LB
#define N 64
#define _PB_N N

int n = N;
int alpha;
int beta;

int A[N][N] __attribute__((aligned(16)));
int x1[N] __attribute__((aligned(16)));
int x2[N] __attribute__((aligned(16)));
int x10[N] __attribute__((aligned(16)));
int x20[N] __attribute__((aligned(16)));
int y_1[N] __attribute__((aligned(16)));
int y_2[N] __attribute__((aligned(16)));

void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[44][5] __attribute__((aligned(16))) = {
		{0x4000, 0x0000, 0x8204, 0x207f, 0x0008},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0009},
		{0x3000, 0x0010, 0x8204, 0x2060, 0x000e},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000f},
		{0x4000, 0x0000, 0x8204, 0x207f, 0x0010},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0011},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x001c},
		{0x0200, 0x0000, 0x0000, 0x0000, 0x001e},
		{0x0000, 0x0030, 0x0000, 0x0000, 0x0020},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0022},
		{0x0000, 0x0000, 0x4011, 0x0000, 0x002c},
		{0x0000, 0x8004, 0x0802, 0x0100, 0x002d},
		{0x0000, 0x0000, 0x1003, 0x0001, 0x0030},
		{0x0000, 0x0000, 0x3011, 0x0000, 0x0032},
		{0x0000, 0x0004, 0x0802, 0x0100, 0x0033},
		{0x0000, 0x0200, 0x0000, 0x0000, 0x003e},
		{0x0002, 0x0000, 0x0000, 0x0000, 0x0040},
		{0x0000, 0x0001, 0x0000, 0x0000, 0x0042},
		{0x2000, 0x0000, 0x0000, 0x0000, 0x0044},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0046},
		{0x0000, 0x0000, 0x2003, 0x0002, 0x0054},
		{0x0c00, 0x0000, 0x0000, 0x0000, 0x0062},
		{0x000c, 0x0000, 0x0000, 0x0000, 0x0068},
		{0x0c00, 0x0000, 0x0000, 0x0000, 0x006a},
		{0x0000, 0x0000, 0xc0c1, 0x0000, 0x0074},
		{0x0000, 0x0000, 0xb041, 0x0000, 0x007c},
		{0x0000, 0x0200, 0x0000, 0x0000, 0x0086},
		{0x0003, 0x0000, 0x0000, 0x0000, 0x0088},
		{0x0000, 0x0820, 0x0000, 0x0000, 0x008c},
		{0x0030, 0x0000, 0x0000, 0x0000, 0x008e},
		{0x0300, 0x0000, 0x0000, 0x0000, 0x00aa},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x00ac},
		{0x2000, 0x0000, 0x0000, 0x0000, 0x00b0},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x00b2},
		{0x0000, 0x0000, 0x0204, 0x2000, 0x00bc},
		{0x0000, 0x8000, 0x0047, 0x0000, 0x00bd},
		{0x2000, 0x0000, 0x0204, 0x2000, 0x00be},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00bf},
		{0x0000, 0x0000, 0x0204, 0x2000, 0x00c0},
		{0x0000, 0x8000, 0x4047, 0x0000, 0x00c1},
		{0x5000, 0x0000, 0x0204, 0x2000, 0x00c2},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00c3},
		{0x3000, 0x0000, 0x0204, 0x2000, 0x00c4},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00c5},
	};

	load_cfg((void*)cin, 0x40000, 440, 4, 0);
	load_data(din_addr[0], 0x34000, 16384, 1, 4, 0);
	load_data(din_addr[1], 0x1c000, 16384, 0, 4, 0);
	load_data(din_addr[2], 0x38000, 256, 0, 4, 0);
	load_data(din_addr[3], 0x3c000, 256, 0, 4, 0);
	load_data(din_addr[4], 0x0, 256, 0, 4, 0);
	load_data(din_addr[5], 0x10000, 256, 0, 4, 3);
	config(0x0, 44, 4, 0);
	execute(0xf8c8, 4, 0);
	store(dout_addr[0], 0x20000, 256, 4, 0);
	store(dout_addr[1], 0x30000, 256, 4, 0);
}



/* Array initialization. */
void init_array()
{
  int i, j;

  for (i = 0; i < n; i++)
    {
      x1[i] = (int) (i % n); // / n;
      x2[i] = (int) (i % n); // / n;
      x10[i] = (int) (i % n); // / n;
      x20[i] = (int) (i % n); // / n;
      y_1[i] = (int) ((i + 3) % n); // / n;
      y_2[i] = (int) ((i + 4) % n); // / n;
      for (j = 0; j < n; j++)
	    A[i][j] = (int) (i*j % n); // / n;
      }
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
__attribute__((noinline))
void kernel_mvt()
{
  int i, j ,s1, s2;

  for (i = 0; i < _PB_N; i++)
  {
    s1 = 0;
    s2 = 0;
    for (j = 0; j < _PB_N; j++)
    {
        s1 += A[i][j] * y_1[j];
        s2 += A[j][i] * y_2[j];
    }
    x10[i] += s1;
    x20[i] += s2;
  }
}


void result_check()
{
  int i, j;

  for (i = 0; i < _PB_N; i++)
  {
    if (x1[i] != x10[i] || x2[i] != x20[i]) printf("There is an error in location (%d)\n", i);
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
  kernel_mvt();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

//  void* cgra_din_addr[9] = {A, y_1, A, y_1, (void*)A+8, (void*)y_1+8, (void*)A+8, (void*)y_1+8, x1};
//  void* cgra_dout_addr[1] = {x1};
  void* cgra_din_addr[6] = {A, A, x1, x2, y_2, y_1};
  void* cgra_dout_addr[2] = {x1, x2};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}