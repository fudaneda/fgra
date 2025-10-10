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

#define TYPE int32_t
#define N 494
#define L 8
int32_t nzval[N*L] __attribute__((aligned(16)));
int32_t cols[N*L] __attribute__((aligned(16)));
int32_t vec[N] __attribute__((aligned(16)));
int32_t out[N] __attribute__((aligned(16)));
int32_t res[N] __attribute__((aligned(16)));

void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[25][5] __attribute__((aligned(16))) = {
		{0x5000, 0x8000, 0x0200, 0xf700, 0x000a},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000b},
		{0x2000, 0x0000, 0x00f7, 0x0000, 0x000e},
		{0x0000, 0x8000, 0x4084, 0x0000, 0x000f},
		{0x4000, 0x8000, 0x0200, 0xf700, 0x0010},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0011},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x001e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0020},
		{0x0100, 0x0000, 0x0000, 0x0000, 0x0022},
		{0x0000, 0x0000, 0xa803, 0x0000, 0x0030},
		{0x0004, 0x0000, 0x1003, 0x0000, 0x0034},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0044},
		{0x0000, 0x0000, 0x1011, 0x0000, 0x0056},
		{0x0000, 0x0004, 0x0104, 0x07b8, 0x0057},
		{0xc000, 0x0000, 0x0000, 0x0000, 0x0062},
		{0x0000, 0x0003, 0x0000, 0x0000, 0x0064},
		{0x0000, 0x0003, 0x0000, 0x0000, 0x0066},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0068},
		{0x0000, 0x0000, 0x3101, 0x0001, 0x0072},
		{0x0030, 0x0200, 0x0000, 0x0000, 0x0084},
		{0x0300, 0x0004, 0x0000, 0x0000, 0x00a8},
		{0x0000, 0x8000, 0x0200, 0xf700, 0x00b8},
		{0x0000, 0x8000, 0x0003, 0x0000, 0x00b9},
		{0x1000, 0x8000, 0x0200, 0xf700, 0x00ba},
		{0x0000, 0x8000, 0x004c, 0x0000, 0x00bb},
	};

	load_cfg((void*)cin, 0x40000, 250, 0, 0);
	load_data(din_addr[0], 0x10000, 15808, 0, 0, 0);
	load_data(din_addr[1], 0x14000, 15808, 0, 0, 0);
	load_data(din_addr[2], 0x20000, 1976, 0, 0, 0);
	load_data(din_addr[3], 0x18000, 1976, 0, 0, 0);
	config(0x0, 25, 0, 0);
	execute(0x6d0, 0, 0);
	store(dout_addr[0], 0x24000, 1976, 0, 0);
}


/* Array initialization. */
void init_array()
{
	int j, cur_indx, i;
	for (i = 0; i < N; i++){
        vec[i] = i;
        cur_indx = 0;
        for(j=0; j < L; j++){
            cur_indx = (TYPE)(((double) i / N) * ((L-1) - cur_indx) + cur_indx);
//            printf("idx %d \n",cur_indx);
            if(cur_indx < L){
		        nzval[i*L + j] = i;
                cols[i*L +j] = cur_indx;
            }
        }
	}
	for (i=0; i<N; i++){
        res[i] = i;
        out[i] = i;
    }
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
__attribute__((noinline))
void ellpack()
{
    int i, j;
    TYPE Si;

    ellpack_1 : for (i=0; i<N; i++) {
        TYPE sum = 0;
        ellpack_2 : for (j=0; j<L; j++) {
//        please_map_me();
                Si = nzval[j + i*L] * vec[cols[j + i*L]];
                sum += Si;
        }
        res[i] += sum;
    }
}

void result_check()
{
  int i, j;

  for (i = 0; i < N; i++)
  {
    if (res[i] != out[i])
        printf("There is an error in location (%d)[%d, %d]\n", i, res[i], out[i]);
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
  ellpack();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[4] = {cols, nzval, out, vec};
  void* cgra_dout_addr[1] = {out};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}