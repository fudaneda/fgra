#include "include/encoding.h"
#include "include/ISA.h"

#define TYPE int
#define N 64
#define _PB_N N

TYPE A[N][N] __attribute__((aligned(16)));
TYPE B[N][N] __attribute__((aligned(16)));
TYPE x[N] __attribute__((aligned(16)));
TYPE y[N] __attribute__((aligned(16)));
TYPE yy[N] __attribute__((aligned(16)));

#define height_size 16
#define col_size 16
#define row_size 16

//Convenience Macros
#define SIZE (row_size * col_size * height_size)
#define INDX(_row_size,_col_size,_i,_j,_k) ((_i)+_row_size*((_j)+_col_size*(_k)))

TYPE C[2] __attribute__((aligned(16)));
TYPE orig[SIZE] __attribute__((aligned(16)));
TYPE sol[SIZE] __attribute__((aligned(16)));
TYPE res[SIZE] __attribute__((aligned(16)));

__attribute__((noinline))
void gesummv()
{
  int i, j;
  TYPE alpha = 3;
  TYPE beta = 2;

  for (i = 0; i < _PB_N; i++)
  {
    TYPE sum0 = 0;
    TYPE sum1 = 0;
    for (j = 0; j < _PB_N; j++)
    {
//      please_map_me();
      sum0 += A[i][j] * x[j];
      sum1 += B[i][j] * x[j];
    }
    yy[i] = alpha * sum0 + beta * sum1;
  }

}

__attribute__((noinline))
void stencil3d (){
    int i,j,k;
	int sum0, sum1, mul0, mul1;

	for(i = 1; i < height_size - 1; i++){
        for(j = 1; j < col_size - 1; j++){
            for(k = 1; k < row_size - 1; k++){

                sum0 = orig[INDX(row_size, col_size, k, j, i)];
                sum1 = orig[INDX(row_size, col_size, k, j, i + 1)] +
                       orig[INDX(row_size, col_size, k, j, i - 1)] +
                       orig[INDX(row_size, col_size, k, j + 1, i)] +
                       orig[INDX(row_size, col_size, k, j - 1, i)] +
                       orig[INDX(row_size, col_size, k + 1, j, i)] +
                       orig[INDX(row_size, col_size, k - 1, j, i)];
                mul0 = sum0 * C[0];
                mul1 = sum1 * C[1];
                res[INDX(row_size, col_size, k, j, i)] = mul0 + mul1;
            }
        }
    }
}


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
  for(int i = 0; i < SIZE; i++){
      orig[i] = i;
  }
  C[0] = 1;
  C[1] = 2;
}



void result_check()
{
  int i, j, k;

  for (i = 0; i < _PB_N; i++)
  {
      if (y[i] != yy[i]) printf("There is an error in location (%d)[%d, %d]\n", i, y[i], yy[i]);
  }
  for(i = 1; i < height_size - 1; i++){
        for(j = 1; j < col_size - 1; j++){
            for(k = 1; k < row_size - 1; k++){
            int idx = INDX(row_size, col_size, k, j, i);
    		if (res[idx] != sol[idx]) printf("There is an error in location (%d)[%d, %d]\n", idx, res[idx], sol[idx]);
  			}
  	}
  }
}


void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[71][5] __attribute__((aligned(16))) = {
		{0x6100, 0xe000, 0x0600, 0x0700, 0x0002},
		{0x0230, 0x8038, 0x0000, 0x0000, 0x0003},
		{0x7001, 0xe000, 0x0600, 0x0700, 0x0004},
		{0x0230, 0x8038, 0x004a, 0x0000, 0x0005},
		{0x4000, 0x0000, 0x8204, 0x207f, 0x0006},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0007},
		{0x5111, 0xe000, 0x0600, 0x0700, 0x0008},
		{0x0230, 0x8038, 0x0000, 0x0000, 0x0009},
		{0x1001, 0xe000, 0x0000, 0x0700, 0x000a},
		{0x0000, 0x8038, 0x0001, 0x0000, 0x000b},
		{0x2000, 0x0000, 0x0204, 0x2000, 0x000c},
		{0x0000, 0x8000, 0x004a, 0x0000, 0x000d},
		{0x4000, 0x0000, 0x0204, 0x2000, 0x000e},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000f},
		{0x0030, 0x0000, 0x0000, 0x0000, 0x0016},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0018},
		{0x2000, 0x0010, 0x0000, 0x0000, 0x001a},
		{0x2000, 0x0000, 0x0000, 0x0000, 0x001c},
		{0x0030, 0x0002, 0x0000, 0x0000, 0x001e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0020},
		{0x0000, 0x0000, 0xa083, 0x0001, 0x0028},
		{0x0000, 0x0000, 0xa103, 0x0001, 0x002a},
		{0x0000, 0x0000, 0xa203, 0x0000, 0x002c},
		{0x0001, 0x0000, 0x3007, 0x0000, 0x0030},
		{0x00c0, 0x0600, 0x0000, 0x0000, 0x003a},
		{0x00c0, 0x0000, 0x0000, 0x0000, 0x003c},
		{0x8200, 0x0000, 0x0000, 0x0000, 0x003e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0040},
		{0x0110, 0x0000, 0x0000, 0x0000, 0x0042},
		{0x0000, 0x0000, 0x2601, 0x0002, 0x004c},
		{0x0000, 0x0000, 0x4001, 0x0001, 0x004e},
		{0x0000, 0x0000, 0x1011, 0x0000, 0x0050},
		{0x0000, 0x8004, 0x0803, 0x0100, 0x0051},
		{0x0000, 0x0000, 0x1011, 0x0000, 0x0052},
		{0x0000, 0x8004, 0x0802, 0x0100, 0x0053},
		{0x0000, 0x0000, 0x9081, 0x0001, 0x0054},
		{0x0c00, 0x0020, 0x0000, 0x0000, 0x005e},
		{0x0008, 0x0208, 0x0000, 0x0000, 0x0060},
		{0x0003, 0x0003, 0x0000, 0x0000, 0x0062},
		{0x0000, 0x0003, 0x0000, 0x0000, 0x0064},
		{0x0040, 0x0004, 0x0000, 0x0000, 0x0066},
		{0x0000, 0x0000, 0xc601, 0x0000, 0x0070},
		{0x0003, 0x0000, 0x1003, 0x0000, 0x0076},
		{0x0000, 0x0020, 0x0000, 0x0000, 0x0082},
		{0x2000, 0x0000, 0x0000, 0x0000, 0x0084},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0086},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x008a},
		{0x0000, 0x0000, 0xa401, 0x0001, 0x0094},
		{0x0000, 0x0000, 0x3401, 0x0002, 0x0096},
		{0x0000, 0x0000, 0x3001, 0x0002, 0x0098},
		{0x0000, 0x0000, 0x3003, 0x0002, 0x009c},
		{0x0040, 0x0000, 0x0000, 0x0000, 0x00a6},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x00a8},
		{0x0018, 0x0000, 0x0000, 0x0000, 0x00aa},
		{0x0004, 0x0003, 0x0000, 0x0000, 0x00ac},
		{0x0010, 0x0001, 0x0000, 0x0000, 0x00ae},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x00b0},
		{0x70f1, 0xe000, 0x0600, 0x0700, 0x00b6},
		{0x0230, 0x8038, 0x0000, 0x0000, 0x00b7},
		{0x4000, 0x0000, 0x0204, 0x2000, 0x00b8},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00b9},
		{0x6001, 0xe000, 0x0600, 0x0700, 0x00ba},
		{0x0230, 0x8038, 0x0000, 0x0000, 0x00bb},
		{0x5201, 0xe000, 0x0600, 0x0700, 0x00bc},
		{0x0230, 0x8038, 0x0000, 0x0000, 0x00bd},
		{0x0000, 0xe000, 0x0000, 0x0700, 0x00be},
		{0x0000, 0x8038, 0x0000, 0x0000, 0x00bf},
		{0x6102, 0xe000, 0x0600, 0x0700, 0x00c0},
		{0x0230, 0x8038, 0x0000, 0x0000, 0x00c1},
		{0x5101, 0xe000, 0x0600, 0x0700, 0x00c2},
		{0x0230, 0x8038, 0x0000, 0x0000, 0x00c3},
	};

	load_cfg((void*)cin, 0x40000, 710, 0, 0);
	load_data(din_addr[0], 0x20000, 16384, 0, 0, 0);
	load_data(din_addr[1], 0x10000, 16384, 0, 0, 0);
	load_data(din_addr[2], 0x0, 256, 0, 0, 0);
	load_data(din_addr[3], 0x30000, 8, 1, 0, 0);
	load_data(din_addr[4], 0x14000, 8, 0, 0, 0);
	load_data(din_addr[5], 0x34000, 16252, 1, 0, 0);
	load_data(din_addr[6], 0x24000, 16252, 1, 0, 0);
	load_data(din_addr[7], 0x28000, 16252, 1, 0, 0);
	load_data(din_addr[8], 0x4000, 16252, 1, 0, 0);
	load_data(din_addr[9], 0x2c000, 16252, 1, 0, 0);
	load_data(din_addr[10], 0x38000, 16252, 1, 0, 0);
	load_data(din_addr[11], 0x8000, 16252, 0, 0, 0);
	config(0x0, 71, 0, 0);
	execute(0x7f7f, 0, 0);
	store(dout_addr[0], 0x18000, 256, 0, 0);
	store(dout_addr[1], 0xc000, 14204, 0, 0);
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
  stencil3d();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[12] = {A, B, x, C, C, (void*)orig+64, (void*)orig+64, (void*)orig+64, (void*)orig+64, (void*)orig+64, (void*)orig+64, (void*)orig+64};
  void* cgra_dout_addr[2] = {y, (void*)sol+1088};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}