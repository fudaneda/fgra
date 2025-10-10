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


#define SIZE 4096

int acc_vector[SIZE];
int res_vector[SIZE];
int acceleration_x[SIZE] __attribute__((aligned(16)));
int acceleration_y[SIZE] __attribute__((aligned(16)));
int acceleration_z[SIZE] __attribute__((aligned(16)));
int acc_avg_x[SIZE] __attribute__((aligned(16)));
int acc_avg_y[SIZE] __attribute__((aligned(16)));
int acc_avg_z[SIZE] __attribute__((aligned(16)));

__attribute__((noinline))
void pedometer(){//(int input[], int output[], int coefficients[])
	for(int i=0;i<SIZE;i++){
	    int sub_x = acceleration_x[i]- acc_avg_x[i];
        int sub_y = acceleration_y[i]- acc_avg_y[i];
        int sub_z = acceleration_z[i]-acc_avg_z[i];
        res_vector[i] = sub_x * sub_x+  sub_y * sub_y+ sub_z * sub_z;
//		res_vector[i] = (acceleration_x[i]- acc_avg_x[i]) * (acceleration_x[i]- acc_avg_x[i])+
//		(acceleration_y[i]- acc_avg_y[i]) * (acceleration_y[i]- acc_avg_y[i])+
//		(acceleration_z[i]-acc_avg_z[i]) * (acceleration_z[i]-acc_avg_z[i]) ;
	}
}


void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[70][5] __attribute__((aligned(16))) = {
		{0x0000, 0x0000, 0x0204, 0x2000, 0x0002},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0003},
		{0x2000, 0x0000, 0x0204, 0x2000, 0x0004},
		{0x0000, 0x8000, 0x4047, 0x0000, 0x0005},
		{0x1000, 0x0000, 0x0204, 0x2000, 0x0006},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0007},
		{0x3000, 0x0000, 0x0204, 0x2000, 0x0008},
		{0x0000, 0x8000, 0x4048, 0x0000, 0x0009},
		{0x4000, 0x0000, 0x0100, 0x0000, 0x000a},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000b},
		{0x6000, 0x0000, 0x0100, 0x0000, 0x000c},
		{0x0000, 0x8000, 0x0048, 0x0000, 0x000d},
		{0x5000, 0x0000, 0x0100, 0x0000, 0x000e},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000f},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0016},
		{0x0001, 0x0000, 0x0000, 0x0000, 0x0018},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x001a},
		{0x0001, 0x0000, 0x0000, 0x0000, 0x001c},
		{0x0030, 0x0000, 0x0000, 0x0000, 0x001e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0020},
		{0x0000, 0x0000, 0x10c1, 0x0002, 0x0028},
		{0x0000, 0x0000, 0x9101, 0x0001, 0x002c},
		{0x0000, 0x0000, 0xa002, 0x0000, 0x0030},
		{0x0000, 0x0000, 0xb003, 0x0001, 0x0032},
		{0x000c, 0x0000, 0x0000, 0x0000, 0x003c},
		{0x00c0, 0x0000, 0x0000, 0x0000, 0x003e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0042},
		{0x1100, 0x0000, 0x0000, 0x0000, 0x0044},
		{0x0000, 0x0000, 0x2041, 0x0002, 0x0054},
		{0x0000, 0x0000, 0x1001, 0x0002, 0x0056},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0060},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0062},
		{0x0004, 0x0000, 0x0000, 0x0000, 0x0068},
		{0x0004, 0x0000, 0x0000, 0x0000, 0x006a},
		{0x0000, 0x0000, 0x4011, 0x0000, 0x0072},
		{0x0000, 0x8004, 0x0802, 0x0100, 0x0073},
		{0x0000, 0x0000, 0x4011, 0x0000, 0x0074},
		{0x0000, 0x8004, 0x0802, 0x0100, 0x0075},
		{0x0000, 0x0000, 0x4003, 0x0002, 0x0078},
		{0x0000, 0x0000, 0xb003, 0x0001, 0x007a},
		{0x0001, 0x0000, 0x0000, 0x0000, 0x0086},
		{0x0001, 0x0000, 0x0000, 0x0000, 0x0088},
		{0x0050, 0x0000, 0x0000, 0x0000, 0x008c},
		{0x0000, 0x0000, 0xc043, 0x0001, 0x0096},
		{0x0000, 0x0000, 0x3043, 0x0002, 0x0098},
		{0x0000, 0x0000, 0x3002, 0x0002, 0x009c},
		{0x0000, 0x0000, 0xc082, 0x0001, 0x009e},
		{0x0000, 0x0010, 0x0000, 0x0000, 0x00a6},
		{0x0080, 0x0010, 0x0000, 0x0000, 0x00a8},
		{0x0010, 0x0020, 0x0000, 0x0000, 0x00aa},
		{0x0008, 0x0020, 0x0000, 0x0000, 0x00ac},
		{0x0010, 0x0021, 0x0000, 0x0000, 0x00ae},
		{0x0080, 0x0000, 0x0000, 0x0000, 0x00b0},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x00b2},
		{0x4000, 0x0000, 0x0204, 0x2000, 0x00b6},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00b7},
		{0x7000, 0x0000, 0x0100, 0x0000, 0x00b8},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00b9},
		{0x6000, 0x0000, 0x8204, 0x207f, 0x00ba},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00bb},
		{0x5000, 0x0000, 0x8204, 0x207f, 0x00bc},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00bd},
		{0x6000, 0x0000, 0x0100, 0x0000, 0x00be},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00bf},
		{0x0000, 0x0010, 0x8204, 0x2060, 0x00c0},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00c1},
		{0x5000, 0x0000, 0x0100, 0x0000, 0x00c2},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00c3},
		{0x7000, 0x0000, 0x0100, 0x0000, 0x00c4},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00c5},
	};

	load_cfg((void*)cin, 0x40000, 700, 0, 0);
	load_data(din_addr[0], 0x20000, 16384, 1, 0, 0);
	load_data(din_addr[1], 0x30000, 16384, 0, 0, 0);
	load_data(din_addr[2], 0x0, 256, 0, 0, 0);
	load_data(din_addr[3], 0x4000, 256, 0, 0, 0);
	load_data(din_addr[4], 0x24000, 256, 0, 0, 0);
	load_data(din_addr[5], 0x28000, 256, 0, 0, 0);
	load_data(din_addr[6], 0x34000, 16384, 0, 0, 0);
	load_data(din_addr[7], 0x10000, 16384, 0, 0, 0);
	load_data(din_addr[8], 0x2c000, 16384, 0, 0, 0);
	load_data(din_addr[9], 0x38000, 16384, 0, 0, 0);
	load_data(din_addr[10], 0x14000, 16384, 0, 0, 0);
	load_data(din_addr[11], 0x3c000, 16384, 0, 0, 0);
	config(0x0, 70, 0, 0);
	execute(0xff7f, 0, 0);
	store(dout_addr[0], 0x8000, 256, 0, 0);
	store(dout_addr[1], 0xc000, 256, 0, 0);
	store(dout_addr[2], 0x18000, 16384, 0, 0);
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
  for(int i=0;i<SIZE;i++){
    acceleration_x[i] = 3*i;
    acceleration_y[i] = 3*i+1;
    acceleration_z[i] = 3*i+2;

    acc_avg_x[i] = i;
    acc_avg_y[i] = i;
    acc_avg_z[i] = i;
  }
}




void result_check()
{
  int i, j;

  for (i = 0; i < _PB_N; i++)
  {
    if (x1[i] != x10[i] || x2[i] != x20[i]) printf("There is an error in location (%d)\n", i);
  }
  for (i = 0; i < SIZE; i++)
  {
    if (acc_vector[i] != res_vector[i]) printf("There is an error in location (%d)[%d, %d]\n", i, acc_vector[i], res_vector[i]);
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
  pedometer();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[12] = {A, A, x1, x2, y_1, y_2, acc_avg_x, acc_avg_y, acc_avg_z, acceleration_x, acceleration_y, acceleration_z};
  void* cgra_dout_addr[3] = {x1, x2, acc_vector};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}