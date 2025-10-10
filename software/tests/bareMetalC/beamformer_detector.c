#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"


#define NUM_BEAMS 4 
#define NUM_POST_DEC_2 512
#define TARGET_BEAM 1
#define TARGET_SAMPLE 256
int data[512]__attribute__((aligned(16)));
int output [4][512]__attribute__((aligned(16)));

void Detector()
{
  int sample;
  /* Should be exactly NUM_POST_DEC_2 samples. */
for (int i = 0; i < NUM_BEAMS; i++){
  for (sample = 0; sample < NUM_POST_DEC_2; sample++)
  {
    float outputVal;
    if (i == TARGET_BEAM && sample == TARGET_SAMPLE) {
      if (data[sample] >= 1)
        outputVal = i+1;
      else
        outputVal = 0;
    } else {
      if (data[sample] >= 1)
        outputVal = -(i+1);
      else
        outputVal = 0;
    }
    outputVal = data[sample];
    output[i][sample]= outputVal;
  }
}
}

// void result_check()
// {
//   int i, j;

//   for (i = 0; i < Ncb; i++)
//   {
//     if (W[i] != W_i[i]) printf("There is an error in location (%d)[%d, %d]\n", i, W_i[i], W[i]);
//   }
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
    
  for(int i=0; i< 512; i++){
      data[i] = (i*-1)*i;
  }
  for(int j = 0; j< 4; j++){
    for(int i=0; i< 512; i++){
      output[j][i] = 0;
    }
  }
//   for(int i=0; i< Ncb; i++){
//       W[i] = 0;
//       W_i[i] = 0;
//   }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
  
  // printf("CPU add finished!\n");
  start = rdcycle();
  /* Run kernel. */
  Detector();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

//   void* cgra_din_addr[2] = {fint, fint};
//   void* cgra_dout_addr[1] = {W};
//   start = rdcycle();
//   cgra_execute(cgra_din_addr, cgra_dout_addr);
//   volatile int result = fence(1);
//   end = rdcycle();
//   printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
//   printf("CGRA comput finished!\n");
//   result = fence(1);

  for (i=0;i<16; i++) {
	printf("%d\\", output[0][i]);
	// printf("%d", sizeof(C[i]));
	// printf("%s", ",,");
	// printf("%d\n", i);
  }
    
//   result_check();
  printf("Done!\n");

return 0;

}
