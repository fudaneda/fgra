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

#define height_size 16
#define col_size 8
#define row_size 8
//Data Bounds
#define TYPE int
#define MAX 1000
#define MIN 1
//Convenience Macros
#define SIZE (row_size * col_size * height_size)
#define INDX(_row_size,_col_size,_i,_j,_k) ((_i)+_row_size*((_j)+_col_size*(_k)))

TYPE C[2] __attribute__((aligned(16)));
TYPE orig[SIZE] __attribute__((aligned(16)));
TYPE sol[SIZE] __attribute__((aligned(16)));
// TYPE res[SIZE] __attribute__((aligned(16)));

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[67][3] __attribute__((aligned(16))) = {
		{0x0441, 0x00c0, 0x0010},
		{0xc00c, 0x4c00, 0x0011},
		{0x01c0, 0x0090, 0x0012},
		{0x0258, 0x0000, 0x0013},
		{0x0449, 0x00c0, 0x0018},
		{0xc00c, 0x4c00, 0x0019},
		{0x01c0, 0x0090, 0x001a},
		{0x0258, 0x0000, 0x001b},
		{0x0481, 0x00c0, 0x0020},
		{0xc00c, 0x4c00, 0x0021},
		{0x01c0, 0x0050, 0x0022},
		{0x0258, 0x0000, 0x0023},
		{0x0439, 0x00c0, 0x0028},
		{0xc00c, 0x4c00, 0x0029},
		{0x01c0, 0x0050, 0x002a},
		{0x0258, 0x0000, 0x002b},
		{0x0401, 0x00c0, 0x0030},
		{0xc00c, 0x4c00, 0x0031},
		{0x01c0, 0x0010, 0x0032},
		{0x0258, 0x0000, 0x0033},
		{0x0442, 0x00c0, 0x0038},
		{0xc00c, 0x4c00, 0x0039},
		{0x01c0, 0x00d0, 0x003a},
		{0x0258, 0x0000, 0x003b},
		{0x0440, 0x00c0, 0x0040},
		{0xc00c, 0x4c00, 0x0041},
		{0x01c0, 0x00d0, 0x0042},
		{0x0258, 0x0000, 0x0043},
		{0x8000, 0x0000, 0x0058},
		{0x8000, 0x0000, 0x0060},
		{0x8000, 0x0000, 0x0068},
		{0x8200, 0x0000, 0x0070},
		{0x0000, 0x0000, 0x0078},
		{0x8400, 0x0000, 0x0080},
		{0x0000, 0x0000, 0x0088},
		{0x4401, 0x0002, 0x00f1},
		{0xa001, 0x0001, 0x00f9},
		{0xa081, 0x0001, 0x0101},
		{0x2081, 0x0002, 0x0109},
		{0x0000, 0x0030, 0x0130},
		{0x0200, 0x00b0, 0x0138},
		{0x0000, 0x0030, 0x0140},
		{0x2400, 0x0000, 0x0148},
		{0x0000, 0x0000, 0x0150},
		{0x0000, 0x0000, 0x0158},
		{0xc483, 0x0000, 0x01c9},
		{0x4083, 0x0001, 0x01d1},
		{0x9601, 0x0000, 0x01d9},
		{0x3401, 0x0001, 0x01e1},
		{0x0020, 0x0000, 0x0210},
		{0x0001, 0x0000, 0x0218},
		{0x1800, 0x0000, 0x0220},
		{0x1800, 0x0000, 0x0228},
		{0x1800, 0x0000, 0x0230},
		{0x0800, 0x0000, 0x0238},
		{0x0501, 0x00c0, 0x02a0},
		{0xc00c, 0x4c00, 0x02a1},
		{0x01c0, 0x0310, 0x02a2},
		{0x0000, 0x0000, 0x02a3},
		{0x0001, 0x00c0, 0x02b0},
		{0xc000, 0x0000, 0x02b1},
		{0x01c0, 0x0150, 0x02b2},
		{0x0208, 0x0000, 0x02b3},
		{0x0000, 0x00c0, 0x02c8},
		{0xc000, 0x0000, 0x02c9},
		{0x01c0, 0x0050, 0x02ca},
		{0x0208, 0x0000, 0x02cb},
	};

	load_cfg((void*)cin, 0x2000, 402, 0, 0);
	load_data(din_addr[0], 0x1000, 8, 1, 0, 0, 1, 0);
	load_data(din_addr[0], 0x1200, 8, 0, 0, 0, 1, 0);
	load_data(din_addr[1], 0x0, 4028, 1, 0, 0, 3, 1);
	load_data(din_addr[1], 0x200, 4028, 1, 0, 0, 3, 1);
	load_data(din_addr[1], 0x400, 4028, 1, 0, 0, 3, 1);
	load_data(din_addr[1], 0x600, 4028, 1, 0, 0, 3, 1);
	load_data(din_addr[1], 0x800, 4028, 1, 0, 0, 3, 1);
	load_data(din_addr[1], 0xa00, 4028, 1, 0, 0, 3, 1);
	load_data(din_addr[1], 0xc00, 4028, 1, 0, 0, 3, 1);
	load_data(din_addr[1], 0xe00, 4028, 0, 0, 0, 3, 1);
	config(0x0, 67, 0, 0);
	execute(0x94fe, 0, 0);
	store(dout_addr[0], 0x1400, 3516, 0, 0, 0, 0, 0);
}



/* Array initialization. */
static
void init_array()
{
    for(int i = 0; i < SIZE; i++){
        orig[i] = i;
    }
	C[0] = 1;
	C[1] = 2;
}

// __attribute__((noinline))
// void stencil3d (){
//     int i,j,k;
// 	int sum0, sum1, mul0, mul1;

// 	for(i = 1; i < height_size - 1; i++){
//         for(j = 1; j < col_size - 1; j++){
//             for(k = 1; k < row_size - 1; k++){
            
//                 sum0 = orig[INDX(row_size, col_size, k, j, i)];
//                 sum1 = orig[INDX(row_size, col_size, k, j, i + 1)] +
//                        orig[INDX(row_size, col_size, k, j, i - 1)] +
//                        orig[INDX(row_size, col_size, k, j + 1, i)] +
//                        orig[INDX(row_size, col_size, k, j - 1, i)] +
//                        orig[INDX(row_size, col_size, k + 1, j, i)] +
//                        orig[INDX(row_size, col_size, k - 1, j, i)];
//                 mul0 = sum0 * C[0];
//                 mul1 = sum1 * C[1];
//                 res[INDX(row_size, col_size, k, j, i)] = mul0 + mul1;
//             }
//         }
//     }
// }


// static
// void result_check()
// {
//   	int i, j, k, r, c;
// 	for(i = 1; i < height_size - 1; i++){
//         for(j = 1; j < col_size - 1; j++){
//             for(k = 1; k < row_size - 1; k++){
//             int idx = INDX(row_size, col_size, k, j, i);
//     		if (res[idx] != sol[idx]) printf("There is an error in location (%d)[%d, %d]\n", idx, res[idx], sol[idx]);
//   			}
// 		}
// 	}
// }


int main(int argc, char** argv)
{
  long long unsigned start;
  long long unsigned end;
  init_array();
  printf("Initialization finished!\n");

//  start = rdcycle();
//  stencil3d();
//  end = rdcycle();
//  printf("It takes %d cycles for CPU to finish the task.\n\n", end - start);

  void* cgra_din_addr[2] = {C, (void*)orig+32};
  void* cgra_dout_addr[1] = {(void*)sol+288};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

//   start = rdcycle();
//   stencil3d();
//   end = rdcycle();
//   printf("It takes %d cycles for CPU to finish the task.\n", end - start);

//   result_check();
  printf("Done!\n");

  return 0;
}