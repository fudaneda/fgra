#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"



// __attribute__((noinline))

#define E 1024
#define P 45

int fin[E]__attribute__((aligned(16)));
int fint[E]__attribute__((aligned(16)));
int fintt[E]__attribute__((aligned(16)));

void deinterleaving(){
    int RNULL = 5; // number of NULL rows
    int CNULL = 4; // column index of the first NULL
    // P(P+1)/2 >= E > P(P-1)/2
    // RNULL(RNULL+1)/2 >= P(P+1)/2-E > RNULL(RNULL-1)/2
    // CNULL = RNULL(RNULL+1)/2 + E - P(P+1)/2
    int RN = P - RNULL + (CNULL>0); // valid row number: 11
    int idx = 0; // input index
    for(int j = 0; j < P; j++){
    	for(int i = 0; i < RN; i++){
    		if(j + i < P && (i < RN-1 || j < CNULL)){
    			fintt[i*P - i*(i-1)*1 + j] = fin[idx];
    			idx++;
    		}
    	}
    }
}
__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[78][3] __attribute__((aligned(16))) = {
		{0x0000, 0xd400, 0x0010},
		{0x001c, 0x0000, 0x0011},
		{0x0000, 0x8800, 0x0012},
		{0x1603, 0x4010, 0x0013},
		{0x0030, 0x0000, 0x0048},
		{0x0000, 0x0000, 0x0050},
		{0x0003, 0x0000, 0x0088},
		{0x0000, 0x0000, 0x00f0},
		{0x0000, 0x0600, 0x00f8},
		{0x1000, 0x0000, 0x0100},
		{0x0000, 0xc000, 0x0130},
		{0xc000, 0x0000, 0x0131},
		{0x1800, 0x0000, 0x0139},
		{0x0004, 0x0000, 0x0160},
		{0x0021, 0x0000, 0x0162},
		{0x0000, 0x1800, 0x0163},
		{0x0000, 0x0000, 0x0164},
		{0x2000, 0x1800, 0x0165},
		{0x7350, 0xc002, 0x0166},
		{0x8102, 0x0015, 0x016a},
		{0x8801, 0x0012, 0x0172},
		{0x002d, 0x0000, 0x0178},
		{0x0005, 0x0002, 0x017a},
		{0x0000, 0x0800, 0x0198},
		{0x0000, 0x0600, 0x01a0},
		{0x0048, 0x0000, 0x01a8},
		{0x0010, 0x0004, 0x01b0},
		{0x0000, 0x0006, 0x01d1},
		{0x0002, 0x0008, 0x01d9},
		{0xc000, 0x0018, 0x01e1},
		{0x0000, 0x0000, 0x01e9},
		{0x0001, 0x0000, 0x0210},
		{0x0011, 0x1c00, 0x0212},
		{0x2000, 0x0040, 0x0213},
		{0x0d40, 0x0000, 0x0214},
		{0x2000, 0x0005, 0x0215},
		{0x02d0, 0xc002, 0x0216},
		{0x8001, 0x0012, 0x021a},
		{0x002d, 0x0000, 0x0220},
		{0x0003, 0x0002, 0x0222},
		{0x0300, 0x0000, 0x0240},
		{0x0100, 0x0600, 0x0248},
		{0x0000, 0x0000, 0x0250},
		{0x0011, 0x0020, 0x0258},
		{0xa000, 0x0000, 0x0279},
		{0x0000, 0x000c, 0x0280},
		{0x0000, 0x0602, 0x0281},
		{0x0004, 0x0000, 0x02b0},
		{0x0003, 0x0001, 0x02b2},
		{0x0004, 0x0000, 0x02b8},
		{0x0005, 0x0001, 0x02ba},
		{0x0001, 0x0000, 0x02c0},
		{0x0011, 0x0000, 0x02c2},
		{0x0000, 0x0000, 0x02c4},
		{0x2000, 0x0000, 0x02c5},
		{0x0290, 0xc05a, 0x02c6},
		{0x0803, 0x0012, 0x02ca},
		{0x0000, 0x0200, 0x02e8},
		{0x0000, 0x0600, 0x02f0},
		{0x0100, 0x0000, 0x02f8},
		{0x0110, 0x0000, 0x0300},
		{0x0000, 0x0a00, 0x0329},
		{0x0028, 0x0000, 0x0360},
		{0x8005, 0x0001, 0x0362},
		{0xffff, 0xffff, 0x0368},
		{0x0001, 0x0001, 0x036a},
		{0x0001, 0x0000, 0x0370},
		{0x0003, 0x0001, 0x0372},
		{0x0000, 0x0600, 0x0390},
		{0x0000, 0x0600, 0x0398},
		{0x0000, 0x0028, 0x03d1},
		{0x8000, 0x0001, 0x0438},
		{0x0060, 0x0000, 0x0440},
		{0x0060, 0x0000, 0x0478},
		{0x0000, 0xd400, 0x04b0},
		{0x001c, 0x0000, 0x04b1},
		{0x0000, 0x0800, 0x04b2},
		{0x1406, 0x0054, 0x04b3},
	};

	load_cfg((void*)cin, 0x18000, 468, 0, 0);
	load_data(din_addr[0], 0x0, 4096, 0, 0, 0);
	config(0x0, 78, 0, 0);
	execute(0x102, 0, 0);
	store(dout_addr[0], 0x10000, 4096, 0, 0);
}

void result_check()
{
  int i, j;

  for (i = 0; i < 550; i++)
  {
    if (fint[i] != fintt[i]) printf("There is an error in location (%d)[%d, %d]\n", i, fintt[i], fint[i]);
  }
}

// void result_check(){
//     int RNULL = 5; // number of NULL rows
//     int CNULL = 4; // column index of the first NULL
//     int RN = P - RNULL + (CNULL>0); // valid row number: 11
//     int idx = 0; // input index
//     for(int j = 0; j < P; j++){
//     	for(int i = 0; i < RN; i++){
//     		if(j + i < P && (i < RN-1 || j < CNULL)){
// 				if(fintt[i*P - i*(i-1)/2 + j] != fint[i*P - i*(i-1)/2 + j]){
// 					printf("There is an error in location");
// 				}
//     		}
//     	}
//     }
// }


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
 
  for(int i=0; i<E; i++){
	fin[i] = i;
	fint[i] = 0;
	// fintt[i] = 0;
  }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
  
  // printf("CPU add finished!\n");
//   start = rdcycle();
//   /* Run kernel. */
//   deinterleaving();
// //   matching();
//   end = rdcycle();
//   printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[1] = {fin};
  void* cgra_dout_addr[1] = {fint};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
  printf("CGRA comput finished!\n");
//   result = fence(1);

//   for (i=100;i<200; i++) {
// 	printf("%d\\", fintt[i]);
// 	printf("%d\n", fint[i]);
// 	// printf("%d", sizeof(C[i]));
// 	// printf("%s", ",,");
// 	// printf("%d\n", i);
//   }
    
//   result_check();
  printf("Done!\n");

return 0;

}
