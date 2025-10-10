#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"


#define E 1792
#define KL 350
#define KH 360
#define Ncb  660
int W[Ncb]__attribute__((aligned(16)));
int W_i[Ncb]__attribute__((aligned(16)));
int fint[E]__attribute__((aligned(16)));

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[80][3] __attribute__((aligned(16))) = {
		{0x0000, 0x0c00, 0x0020},
		{0x0080, 0x2940, 0x0021},
		{0x0000, 0x0800, 0x0022},
		{0x0006, 0x0000, 0x0023},
		{0x0030, 0x0000, 0x0058},
		{0x0000, 0x0020, 0x0100},
		{0x0000, 0x0002, 0x0141},
		{0x0000, 0x0004, 0x0149},
		{0x000a, 0x0000, 0x0170},
		{0x8005, 0x0002, 0x0172},
		{0x0000, 0x0008, 0x01a8},
		{0x0000, 0x0000, 0x01b0},
		{0x0000, 0x0180, 0x01d9},
		{0x0000, 0x8000, 0x01e0},
		{0x3000, 0x00c0, 0x01e9},
		{0x1000, 0x0020, 0x01f1},
		{0x0002, 0x0000, 0x0210},
		{0x800d, 0x0002, 0x0212},
		{0x0001, 0x0000, 0x0218},
		{0x0011, 0x0080, 0x021a},
		{0x0000, 0x0002, 0x021b},
		{0x01a0, 0x0000, 0x021c},
		{0x6000, 0x0000, 0x021d},
		{0x2940, 0xc002, 0x021e},
		{0xfea2, 0xffff, 0x0220},
		{0x0001, 0x0002, 0x0222},
		{0x0000, 0x0200, 0x0250},
		{0x0000, 0x0000, 0x0258},
		{0x0000, 0x00a8, 0x0281},
		{0x0000, 0x8000, 0x0288},
		{0x0000, 0x0c03, 0x0289},
		{0x10c0, 0x0002, 0x0291},
		{0x1000, 0x0000, 0x0299},
		{0x070a, 0x0000, 0x02b0},
		{0x8005, 0x0002, 0x02b2},
		{0x028a, 0x0000, 0x02b8},
		{0x0011, 0x0000, 0x02ba},
		{0x0000, 0x0000, 0x02bc},
		{0x2000, 0x0000, 0x02bd},
		{0x0030, 0xc528, 0x02be},
		{0x0081, 0x0000, 0x02c0},
		{0x8041, 0x1f02, 0x02c2},
		{0x0204, 0xf084, 0x02c3},
		{0x15a0, 0x0000, 0x02c4},
		{0x2000, 0x2400, 0x02c5},
		{0x0030, 0x0528, 0x02c6},
		{0x0167, 0x0000, 0x02c8},
		{0x0005, 0x0008, 0x02ca},
		{0x0100, 0x0000, 0x02f0},
		{0x8300, 0x0000, 0x02f8},
		{0x0000, 0x0000, 0x0300},
		{0x0000, 0x0000, 0x0329},
		{0x000e, 0x0000, 0x0331},
		{0x0400, 0x0000, 0x0338},
		{0x0001, 0x000d, 0x0362},
		{0x015e, 0x0000, 0x0368},
		{0x0005, 0x0801, 0x036a},
		{0x1000, 0x0000, 0x036b},
		{0x0960, 0x0000, 0x036c},
		{0x0206, 0x0012, 0x0372},
		{0x0300, 0x0000, 0x0373},
		{0x0008, 0x0000, 0x0374},
		{0x0000, 0x0100, 0x0398},
		{0x0000, 0x0080, 0x03a0},
		{0x00b0, 0x0000, 0x03a8},
		{0x0000, 0x0030, 0x03d1},
		{0x0400, 0x0010, 0x03d9},
		{0x0000, 0x0000, 0x03e0},
		{0x2000, 0x0000, 0x0440},
		{0x2000, 0x0000, 0x0450},
		{0x0400, 0x0000, 0x0478},
		{0x0060, 0x0000, 0x0480},
		{0x5ff6, 0x0c51, 0x04a8},
		{0x7680, 0x294d, 0x04a9},
		{0x0000, 0x8800, 0x04aa},
		{0x0602, 0x4000, 0x04ab},
		{0x4000, 0x0c51, 0x04b8},
		{0x7680, 0x294d, 0x04b9},
		{0x0000, 0x0800, 0x04ba},
		{0x0601, 0x0000, 0x04bb},
	};

	load_cfg((void*)cin, 0x18000, 480, 0, 0);
	load_data(din_addr[0], 0x10000, 7880, 1, 0, 0);
	load_data(din_addr[1], 0x8000, 7880, 0, 0, 0);
	config(0x0, 80, 0, 0);
	execute(0x288, 0, 0);
	store(dout_addr[0], 0x0, 2640, 0, 0);
}

// void array_add(){
//    for (int i=0;i<SIZE; i++){
//       #ifdef CGRA_COMPILER
//       please_map_me();
//       #endif
//       D[i] = A[i]+B[i];
//    }
// }

// void matching(){
//     int Kn = 8;
//     int step = 2;
//     for(int i = 0; i < 64; i++){
//     	int sum = 0;
//     	for(int j = 0; j < 5; j++){
//     	    // #ifdef CGRA_COMPILER
//             //     please_map_me();
//             // #endif
//     		int idx = i+j*56;
//     		if(i < 8){
//     			sum += fint[idx];
//     		}else if(i >= 16 && idx-8 < 256){
//     			sum += fint[idx-Kn];
//    		    }else if(i >= 8 && i < 16){
//    		 	    sum = 0x81;
//     		}
//     	}
//     	W_i[i] = sum >> step; // round(sum >> step)
//     }
// }

void matching(){
    int Kn = KH-KL;
    int Wn = Ncb-Kn;
    int maxCnt = (E+Wn-1)/Wn;
    int step = 2;
    for(int i = 0; i < Ncb; i++){
    	int sum = 0;
    	for(int j = 0; j < maxCnt; j++){
    		int idx = i+j*Wn;
    		if(i < KL){
    			sum += fint[idx];
    		}else if(i >= KH && idx-Kn < E){
    			sum += fint[idx-Kn];
   		    }else if(i >= KL && i < KH){
   		 	    sum = 0x81;
    		}
    	}
    	W_i[i] = sum >> step; // round(sum >> step)
    }
}


void result_check()
{
  int i, j;

  for (i = 0; i < Ncb; i++)
  {
    if (W[i] != W_i[i]) printf("There is an error in location (%d)[%d, %d]\n", i, W_i[i], W[i]);
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
    
  for(int i=0; i< E; i++){
      fint[i] = i + 1;
  }
  for(int i=0; i< Ncb; i++){
      W[i] = 0;
    //   W_i[i] = 0;
  }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
  
  // printf("CPU add finished!\n");
//   start = rdcycle();
//   /* Run kernel. */
//   matching();
//   end = rdcycle();
//   printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[2] = {fint, fint};
  void* cgra_dout_addr[1] = {W};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
  printf("CGRA comput finished!\n");
//   result = fence(1);

//   for (i=0;i<Ncb; i++) {
// 	printf("%d\\", W[i]);
// 	// printf("%d", sizeof(C[i]));
// 	// printf("%s", ",,");
// 	// printf("%d\n", i);
//   }
    
//   result_check();
  printf("Done!\n");

return 0;

}
