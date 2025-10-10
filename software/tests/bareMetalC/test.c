#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[29][3] __attribute__((aligned(16))) = {
		{0x1841, 0x0001, 0x00d9},
		{0x0000, 0x0200, 0x0100},
		{0xc000, 0x0000, 0x0108},
		{0x0030, 0x0000, 0x0110},
		{0x0000, 0x0000, 0x0118},
		{0x1801, 0x0001, 0x0179},
		{0x1811, 0x0000, 0x0181},
		{0x0000, 0x00c0, 0x0182},
		{0xf820, 0x1f00, 0x0183},
		{0x0000, 0x0000, 0x0184},
		{0x0200, 0x0000, 0x01a8},
		{0x0004, 0x0000, 0x01b0},
		{0x0000, 0x0000, 0x01b8},
		{0x1021, 0x0f80, 0x0210},
		{0x8020, 0x000f, 0x0211},
		{0x0000, 0x0830, 0x0212},
		{0x2004, 0x0080, 0x0213},
		{0x1001, 0x0f80, 0x0218},
		{0x8020, 0x000f, 0x0219},
		{0x0000, 0x0130, 0x021a},
		{0x0104, 0x0000, 0x021b},
		{0x1000, 0x0f80, 0x0220},
		{0x8020, 0x000f, 0x0221},
		{0x0000, 0x0130, 0x0222},
		{0x0104, 0x0000, 0x0223},
		{0x0020, 0x0f80, 0x0228},
		{0x8200, 0x000f, 0x0229},
		{0x0000, 0x0030, 0x022a},
		{0x0104, 0x0000, 0x022b},
	};

	load_cfg((void*)cin, 0xc000, 174, 0, 0);
	load_data(din_addr[0], 0x8000, 4096, 1, 0, 0, 1, 0);
	load_data(din_addr[0], 0x9000, 4096, 0, 0, 0, 1, 0);
	config(0x0, 29, 0, 0);
	execute(0xf00, 0, 0);
	store(dout_addr[0], 0x8000, 4096, 1, 0, 0, 1, 0);
	store(dout_addr[0], 0x9000, 4096, 0, 0, 0, 1, 0);
}
// #define N 8
	#define NUM 32
    int a[NUM][NUM]__attribute__((aligned(16)));
    int a_i[NUM][NUM]__attribute__((aligned(16)));
   //kernel 23
void wave() { 
      
    for (int i=1 ; i < NUM ; i++) {
          for (int j=1 ; j < NUM ; j++){
            a_i[i][j] = a_i[i-1][j] + a_i[i][j-1] + a_i[i-1][j-1];
 	}
 	} 
                 

}

void result_check()
{
  for (int i=1 ; i < NUM ; i++) {
          for (int j=1 ; j < NUM ; j++){
    		if (a_i[i][j] != a[i][j]) printf("There is an error in location (%d)[%d, %d]\n", i*NUM+j, a[i][j], a_i[i][j]);
        } 
  }
	// if(i == 8) continue;


}


int main(){

  printf("Hello piggy!\n");
  printf("Hello piggy!\n");
  printf("Hello piggy!\n");
//   int A = 3;
  printf("Test operations: 1 + 1 = %d \n", 1+1);
  

return 0;

}
