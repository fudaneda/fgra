#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	
}
#define size 1024
#define bound 32
volatile int input[size];
volatile int data[size];
volatile int data0[size];
// granularity: 0 represents 1 word; 1 represents 2 words
void kernel()
{
    loop_begin();
	for (int i = 0; i < bound; i++)
	{
		for (int j = 0; j < bound; j++)
		{

		}
	}
    loop_end();
}



void result_check()
{
  	for (int i=0 ; i < size ; i++) {
    	if (data0[i] != data[i]) printf("There is an error in location (%d)[%d, %d]\n", i, data0[i], data[i]);
  	}
}


int main(){

//   int i,j;
  	long long unsigned start;
  	long long unsigned end;

    for (int i=0 ; i < size ; i++) {
        input[i]=i;
		data[i]=0;
        data0[i]=0;
	}
  	printf("Initialization finished!\n");
  
	printf("CPU add finished!\n");
  	start = rdcycle();
  	/* Run kernel. */
  	kernel();
  	end = rdcycle();
  	printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
	void* cgra_din_addr[1] = {input};
	void* cgra_dout_addr[1] = {data};

  	start = rdcycle();
  	cgra_execute(cgra_din_addr, cgra_dout_addr);
  	volatile int result = fence(1);
  	end = rdcycle();
  	printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, 1);
  	printf("CGRA comput finished!\n");
  	result = fence(1);
    
  	printf("Checking results!\n");
  	result_check();
  	printf("Done!\n");

	return 0;

}
