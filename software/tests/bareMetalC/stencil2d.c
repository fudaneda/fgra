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

#define TYPE int
#define col_size 64
#define row_size 64
#define f_size 9

TYPE orig[row_size * col_size] __attribute__((aligned(16)));
TYPE sol[row_size * col_size] __attribute__((aligned(16)));
TYPE filter[f_size] __attribute__((aligned(16)));
TYPE res[row_size * col_size] __attribute__((aligned(16)));

void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[44][5] __attribute__((aligned(16))) = {
		{0x3000, 0x3010, 0x0200, 0x1f7f, 0x0002},
		{0xf830, 0x80fb, 0x0000, 0x0000, 0x0003},
		{0x1000, 0x3000, 0x0200, 0x1f00, 0x0008},
		{0x0030, 0x80f8, 0x4049, 0x0000, 0x0009},
		{0xc000, 0x3000, 0xf400, 0x1f7f, 0x000c},
		{0xffa0, 0x80fb, 0x0000, 0x0000, 0x000d},
		{0xf001, 0x3000, 0xf400, 0x1f7f, 0x0010},
		{0xffa0, 0x80fb, 0x0000, 0x0000, 0x0011},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0016},
		{0x8000, 0x0000, 0x0000, 0x0000, 0x0018},
		{0x0000, 0x0002, 0x0000, 0x0000, 0x001a},
		{0x0001, 0x0002, 0x0000, 0x0000, 0x001c},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x001e},
		{0x0000, 0x0010, 0x0000, 0x0000, 0x0022},
		{0x0000, 0x0000, 0x1083, 0x0001, 0x0028},
		{0x0000, 0x0000, 0x4011, 0x0000, 0x002c},
		{0x0000, 0x0004, 0x0064, 0x3c10, 0x002d},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x003c},
		{0x0000, 0x0040, 0x0000, 0x0000, 0x003e},
		{0x0800, 0x0000, 0x0000, 0x0000, 0x0040},
		{0x3000, 0x0000, 0x0000, 0x0000, 0x0042},
		{0x0000, 0x0004, 0x0000, 0x0000, 0x0044},
		{0x0000, 0x0600, 0x0000, 0x0000, 0x0046},
		{0x0000, 0x0000, 0x1001, 0x0002, 0x004e},
		{0x0000, 0x0000, 0xa041, 0x0000, 0x0052},
		{0x0008, 0x0000, 0x0000, 0x0000, 0x0062},
		{0x0000, 0x0003, 0x0000, 0x0000, 0x0064},
		{0x0000, 0x0003, 0x0000, 0x0000, 0x0066},
		{0x0000, 0x0004, 0x0000, 0x0000, 0x0068},
		{0x8000, 0x0000, 0x0000, 0x0000, 0x006a},
		{0x0000, 0x0000, 0x3003, 0x0001, 0x007a},
		{0x0000, 0x0100, 0x0000, 0x0000, 0x0088},
		{0x0000, 0x0080, 0x0000, 0x0000, 0x008a},
		{0x0020, 0x0000, 0x0000, 0x0000, 0x008c},
		{0x0000, 0x0000, 0x3003, 0x0002, 0x009e},
		{0x0000, 0x0004, 0x0000, 0x0000, 0x00ac},
		{0x0010, 0x0000, 0x0000, 0x0000, 0x00b0},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x00b2},
		{0x3001, 0x3010, 0x0200, 0x1f7f, 0x00bc},
		{0xf830, 0x80fb, 0x0000, 0x0000, 0x00bd},
		{0x2002, 0x3010, 0x0200, 0x1f7f, 0x00c0},
		{0xf830, 0x80fb, 0x0000, 0x0000, 0x00c1},
		{0xd002, 0x3000, 0xf400, 0x1f7f, 0x00c4},
		{0xffa0, 0x80fb, 0x0000, 0x0000, 0x00c5},
	};

	load_cfg((void*)cin, 0x40340, 440, 6, 0);
	load_data(din_addr[0], 0x10000, 36, 1, 6, 0);
	load_data(din_addr[1], 0x1c000, 36, 1, 6, 0);
	load_data(din_addr[2], 0x34000, 36, 0, 6, 0);
	load_data(din_addr[3], 0xc000, 16384, 1, 6, 0);
	load_data(din_addr[4], 0x2c000, 16384, 1, 6, 0);
	load_data(din_addr[5], 0x38000, 16384, 0, 6, 0);
	config(0x34, 44, 6, 0);
	execute(0xa8a9, 6, 0);
	store(dout_addr[0], 0x4000, 15864, 6, 0);
}


/* Array initialization. */
void init_array()
{
  	int i, j;

  	for (i = 0; i < f_size; i++)
    {
      	filter[i] = i;
    }
	for (i = 0; i < row_size * col_size; i++)
	{
		orig[i] = i;
	}
}

__attribute__((noinline))
void stencil2d (){
    int r, c, k1, k2;
    TYPE temp, mul;

    for (r=0; r<row_size-2; r++) {
        for (c=0; c<col_size-2; c++) {
            temp = (TYPE)0;
            for (k1=0;k1<3;k1++){
                #pragma unroll
                for (k2=0;k2<3;k2++){
                    mul = filter[k1*3 + k2] * orig[(r+k1)*col_size + c+k2];
                    temp += mul;
                }
            }
            res[(r*col_size) + c] = temp;
        }
    }
}


void result_check()
{
  	int i, j, r, c;

    for (r=0; r<row_size-2; r++) {
        for (c=0; c<col_size-2; c++) {
            i = r*col_size + c;
    		if (res[i] != sol[i]) printf("There is an error in location (%d)[%d, %d]\n", i, res[i], sol[i]);
  		}
	}
}


int main(int argc, char** argv)
{
  long long unsigned start;
  long long unsigned end;
  init_array();
  printf("Initialization finished!\n");

  start = rdcycle();
  stencil2d();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[6] = {filter, filter, filter, orig, orig, orig};
  void* cgra_dout_addr[1] = {sol};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}