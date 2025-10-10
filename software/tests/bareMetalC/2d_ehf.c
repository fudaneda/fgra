#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

// __attribute__((noinline))
// void cgra_execute(void** din_addr, void** dout_addr)
// {
// 	static unsigned short cin[91][3] __attribute__((aligned(16))) = {
// 		{0x3001, 0x6300, 0x0010},
// 		{0x0040, 0x0005, 0x0011},
// 		{0x0000, 0x0020, 0x0012},
// 		{0x0008, 0x0000, 0x0013},
// 		{0x2801, 0x6300, 0x0018},
// 		{0x0040, 0x0005, 0x0019},
// 		{0x0000, 0x0020, 0x001a},
// 		{0x0008, 0x0000, 0x001b},
// 		{0x3400, 0x6300, 0x0020},
// 		{0x0040, 0x0005, 0x0021},
// 		{0x0000, 0x0020, 0x0022},
// 		{0x0008, 0x0000, 0x0023},
// 		{0x2c00, 0x6300, 0x0028},
// 		{0x0040, 0x0005, 0x0029},
// 		{0x0000, 0x0020, 0x002a},
// 		{0x0008, 0x0000, 0x002b},
// 		{0x3801, 0x6300, 0x0030},
// 		{0x0040, 0x0005, 0x0031},
// 		{0x0000, 0x1c20, 0x0032},
// 		{0x0000, 0x0000, 0x0033},
// 		{0x2464, 0x6300, 0x0038},
// 		{0x0040, 0x0005, 0x0039},
// 		{0x0000, 0x0020, 0x003a},
// 		{0x0008, 0x0000, 0x003b},
// 		{0x2001, 0x6300, 0x0040},
// 		{0x0040, 0x0005, 0x0041},
// 		{0x0000, 0x0020, 0x0042},
// 		{0x0008, 0x0000, 0x0043},
// 		{0x0000, 0x0000, 0x0058},
// 		{0x0400, 0x0000, 0x0060},
// 		{0xa800, 0x0000, 0x0068},
// 		{0x6000, 0x0001, 0x0070},
// 		{0x0110, 0x0000, 0x0078},
// 		{0x9800, 0x0000, 0x0080},
// 		{0x8000, 0x0001, 0x0088},
// 		{0xa402, 0x0000, 0x00e9},
// 		{0xc201, 0x0000, 0x00f1},
// 		{0xa001, 0x0000, 0x00f9},
// 		{0x4410, 0x0001, 0x0101},
// 		{0xb042, 0x0000, 0x0109},
// 		{0xb202, 0x0001, 0x0111},
// 		{0xc001, 0x0000, 0x0119},
// 		{0x2000, 0x0010, 0x0130},
// 		{0x0200, 0x0001, 0x0138},
// 		{0x0002, 0x0030, 0x0140},
// 		{0x0000, 0x0026, 0x0148},
// 		{0x8011, 0x0020, 0x0150},
// 		{0x5000, 0x0242, 0x0158},
// 		{0x0b00, 0x0000, 0x0160},
// 		{0x0008, 0x0000, 0x0168},
// 		{0x2402, 0x0001, 0x01b9},
// 		{0xc043, 0x0000, 0x01c9},
// 		{0x3410, 0x0001, 0x01d1},
// 		{0x4001, 0x0002, 0x01d9},
// 		{0xa481, 0x0001, 0x01e1},
// 		{0xa043, 0x0000, 0x01e9},
// 		{0x9201, 0x0000, 0x01f1},
// 		{0x2000, 0x0000, 0x0210},
// 		{0x0001, 0x0000, 0x0218},
// 		{0x9800, 0x0000, 0x0220},
// 		{0x1800, 0x0000, 0x0228},
// 		{0x1000, 0x0000, 0x0230},
// 		{0x0000, 0x0000, 0x0240},
// 		{0x3401, 0x6300, 0x0298},
// 		{0x0040, 0x0005, 0x0299},
// 		{0x0000, 0x0020, 0x029a},
// 		{0x0008, 0x0000, 0x029b},
// 		{0x3801, 0x6300, 0x02a0},
// 		{0x0040, 0x0005, 0x02a1},
// 		{0x0000, 0x1a20, 0x02a2},
// 		{0x0000, 0x0004, 0x02a3},
// 		{0x2800, 0x6300, 0x02a8},
// 		{0x0040, 0x0005, 0x02a9},
// 		{0x0000, 0x0020, 0x02aa},
// 		{0x0008, 0x0000, 0x02ab},
// 		{0x2c64, 0x6300, 0x02b0},
// 		{0x0040, 0x0005, 0x02b1},
// 		{0x0000, 0x0020, 0x02b2},
// 		{0x0008, 0x0000, 0x02b3},
// 		{0x3064, 0x6300, 0x02b8},
// 		{0x0040, 0x0005, 0x02b9},
// 		{0x0000, 0x0020, 0x02ba},
// 		{0x0008, 0x0000, 0x02bb},
// 		{0x2464, 0x6300, 0x02c0},
// 		{0x0040, 0x0005, 0x02c1},
// 		{0x0000, 0x0020, 0x02c2},
// 		{0x0008, 0x0000, 0x02c3},
// 		{0x2065, 0x6300, 0x02c8},
// 		{0x0040, 0x0005, 0x02c9},
// 		{0x0000, 0x0020, 0x02ca},
// 		{0x0008, 0x0000, 0x02cb},
// 	};

// 	load_cfg((void*)cin, 0x10000, 546, 0, 0);
// 	load_data(din_addr[0], 0xa000, 2396, 1, 0, 0);
// 	load_data(din_addr[1], 0x1000, 2396, 1, 0, 0);
// 	load_data(din_addr[2], 0x2000, 2396, 0, 0, 0);
// 	load_data(din_addr[3], 0xb000, 2396, 1, 0, 0);
// 	load_data(din_addr[4], 0x3000, 2396, 1, 0, 0);
// 	load_data(din_addr[5], 0x4000, 2396, 0, 0, 0);
// 	load_data(din_addr[6], 0xc000, 2396, 1, 0, 0);
// 	load_data(din_addr[7], 0x5000, 2396, 1, 0, 0);
// 	load_data(din_addr[8], 0xd000, 2396, 0, 0, 0);
// 	load_data(din_addr[9], 0x8000, 2400, 1, 0, 0);
// 	load_data(din_addr[10], 0x9000, 2400, 1, 0, 0);
// 	load_data(din_addr[11], 0x0, 2400, 0, 0, 0);
// 	config(0x0, 91, 0, 0);
// 	execute(0xfefe, 0, 0);
// 	store(dout_addr[0], 0x6000, 2000, 0, 0);
// 	store(dout_addr[1], 0xe000, 2000, 0, 0);
// }


int zp[7][100]__attribute__((aligned(16)));
int za[7][100]__attribute__((aligned(16)));
// int za_i[7][100]__attribute__((aligned(16)));
int zq[7][100]__attribute__((aligned(16)));
int zr[7][100]__attribute__((aligned(16)));
int zm[7][100]__attribute__((aligned(16)));
int zb[7][100]__attribute__((aligned(16)));
int zb_i[7][100]__attribute__((aligned(16)));
   //kernel 18
// void kernel() { 
//     int kn = 6;
//     int jn = 100;
//     for ( int k=1 ; k<kn ; k++ ) {
//        for ( int j=1 ; j<jn ; j++ ) {
//            za_i[k][j] = ( zp[k+1][j-1] +zq[k+1][j-1] -zp[k][j-1] -zq[k][j-1] )*
//                       ( zr[k][j] +zr[k][j-1] ) / ( zm[k][j-1] +zm[k+1][j-1]);
//            zb_i[k][j] = ( zp[k][j-1] +zq[k][j-1] -zp[k][j] -zq[k][j] ) *
//                       ( zr[k][j] +zr[k-1][j] ) / ( zm[k][j] +zm[k][j-1]);
//        }
//      }
// }

// void result_check()
// {
//   int kn = 6;
//   int jn = 100;
//   for ( int k=1 ; k<kn ; k++ ) {
//     for ( int j=1 ; j<jn ; j++ ) {
//       if (za_i[k][j] != za[k][j]) printf("There is an za error in location (%d)[%d, %d]\n", k*jn + j, za_i[k][j], za[k][j]);    
//       // if (zb_i[k][j] != zb[k][j]) printf("There is an zb error in location (%d)[%d, %d]\n", k*jn + j, zb_i[k][j], zb[k][j]);    
//     }
//   }


// //   for (i = 0; i < SIZE; i++)
// //   {
// // 	// if(i == 8) continue;
// //     if (x_i[i] != x[i]) printf("There is an error in location (%d)[%d, %d]\n", i, x_i[i], x[i]);

// //   }
// }

int main(){

  int i,j;
  long long unsigned start;
  long long unsigned end;

  for (i=0;i<7; i++){
    for(j=0; j< 100; j++){
      zp[i][j] = i;
      // za[i][j] = i;
      // za_i[i][j] = i;
      zq[i][j] = i;
      zr[i][j] = i;
      zb[i][j] = i;
      zb_i[i][j] = i;
      zm[i][j] = i;
    }
  }
  // for(int j = 0; j< 4; j++){
  //   for(int i=0; i< 512; i++){
  //     output[j][i] = 0;
  //   }
  // }
//   for(int i=0; i< Ncb; i++){
//       W[i] = 0;
//       W_i[i] = 0;
//   }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
  
  // printf("CPU add finished!\n");
  // start = rdcycle();
  // /* Run kernel. */
  // kernel();
  // end = rdcycle();
  // printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
//   void* cgra_din_addr[12] = {(void*)zm+400, (void*)zm+400, (void*)zm+400, (void*)zp+400, (void*)zp+400, (void*)zp+400, (void*)zq+400, (void*)zq+400, (void*)zq+400, zr, zr, zr};
//   void* cgra_dout_addr[2] = {(void*)za+400, (void*)zb+400};
//   start = rdcycle();
//   cgra_execute(cgra_din_addr, cgra_dout_addr);
//   volatile int result = fence(1);
//   end = rdcycle();
//   printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
//   printf("CGRA comput finished!\n");
//   result = fence(1);

//   for (i=0;i<32; i++) {
// 	printf("%d\\", X[i]);
// 	// printf("%d", sizeof(C[i]));
// 	// printf("%s", ",,");
// 	// printf("%d\n", i);
//   }
    
  // printf("Checking results!\n");
  // result_check();
  printf("Done!\n");

return 0;

}
