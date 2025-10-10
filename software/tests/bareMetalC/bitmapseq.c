#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"



// __attribute__((noinline))


#define MAX_N 2048
#define NUM_SEQ 16
#define N 120

unsigned rule_bitseq[NUM_SEQ][N]__attribute__((aligned(16)));
unsigned out_bitseq[N]__attribute__((aligned(16)));
// int revert_flag[1];
// int rule_select_bitmap[1];
// int bitseq_op[1];

int kernel(int rule_select_bitmap, int bitseq_op, int revert_flag) {

#ifdef CGRA_COMPILER
	loop_begin();
#endif   
    for (int i = 0; i < N; i++) {
        int tem = bitseq_op ? 0xffffffff : 0x0; // initialize out_bitseq with bitseq_op
        for (int j = 0; j < NUM_SEQ; j++) {
        // please_map_me();
            if (rule_select_bitmap & (1 << j)) { // if the j-th bit is set
                if (bitseq_op) { // bitwise AND
                    tem &= rule_bitseq[j][i];
                } else { // bitwise OR
                    tem |= rule_bitseq[j][i];
                }
            }
        }        
        if (revert_flag) {
            out_bitseq[i] = ~tem; // invert the bit if revert_flag is set
        }else{
            out_bitseq[i] = tem;
        }
    }
#ifdef CGRA_COMPILER
	loop_end();
#endif

    return 0;
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
    
  for(int i=0; i< NUM_SEQ; i++){
	for(int j =0; j < N; j++){
		rule_bitseq[i][j] = i*j;
	}
  }
  for(int i=0; i<N; i++){
	out_bitseq[i] = 0;
  }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
  
  // printf("CPU add finished!\n");
  start = rdcycle();
  /* Run kernel. */
  kernel(16, 1, 1);
//   matching();
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
