#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"

__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[36][3] __attribute__((aligned(16))) = {
		{0x2001, 0x0000, 0x0010},
		{0x0001, 0x0000, 0x0011},
		{0x0000, 0x0510, 0x0012},
		{0x0001, 0x0800, 0x0013},
		{0x2000, 0x0000, 0x0020},
		{0x0001, 0x0000, 0x0021},
		{0x0000, 0x0510, 0x0022},
		{0x0001, 0x0800, 0x0023},
		{0x0002, 0x0000, 0x0050},
		{0x0002, 0x0000, 0x0060},
		{0x0000, 0x0008, 0x00f8},
		{0x0000, 0x0008, 0x0108},
		{0x0000, 0x0008, 0x01a0},
		{0x0000, 0x0008, 0x01b0},
		{0x0000, 0x0000, 0x0248},
		{0x0000, 0x0000, 0x0258},
		{0x0001, 0x0024, 0x02b9},
		{0x0001, 0x0024, 0x02c9},
		{0x0000, 0x0000, 0x02f8},
		{0x0000, 0x0000, 0x0308},
		{0x2001, 0x0000, 0x0360},
		{0x0001, 0x0000, 0x0361},
		{0x0000, 0x0010, 0x0362},
		{0x0041, 0x0000, 0x0363},
		{0x2001, 0x0000, 0x0368},
		{0x0001, 0x0000, 0x0369},
		{0x0000, 0x8010, 0x036a},
		{0x0041, 0x0000, 0x036b},
		{0x2000, 0x0000, 0x0370},
		{0x0001, 0x0000, 0x0371},
		{0x0000, 0x0010, 0x0372},
		{0x0041, 0x0000, 0x0373},
		{0x2000, 0x0000, 0x0378},
		{0x0001, 0x0000, 0x0379},
		{0x0000, 0x8010, 0x037a},
		{0x0041, 0x0000, 0x037b},
	};

	load_cfg((void*)cin, 0xc000, 216, 0, 0);
	load_data(din_addr[0], 0x8000, 4096, 1, 0, 0, 1, 0);
	load_data(din_addr[0], 0x9000, 4096, 0, 0, 0, 1, 0);
	load_data(din_addr[1], 0xa000, 4096, 1, 0, 0, 1, 0);
	load_data(din_addr[1], 0xb000, 4096, 0, 0, 0, 1, 0);
	config(0x0, 36, 0, 0);
	execute(0xf0a, 0, 0);
	store(dout_addr[0], 0x0, 4096, 1, 0, 0, 1, 0);
	store(dout_addr[0], 0x1000, 4096, 0, 0, 0, 1, 0);
}


#define SIZE 1024
    int x[SIZE];
	int x_i[SIZE];
    int y[SIZE];
    int z[SIZE];

void add() { 
    for ( int k=0 ; k<SIZE ; k++ ) {
        x_i[k] = y[k] + z[k];
    }      
}


void result_check()
{
  	for (int i=0 ; i < SIZE ; i++) {
    	if (x_i[i] != x[i]) printf("There is an error in location (%d)[%d, %d]\n", i, x_i[i], x[i]);
  	}
}


int main(){

//   int i,j;
  	long long unsigned start;
  	long long unsigned end;

    for (int i=0 ; i < SIZE ; i++) {
		x[i] = 0;
		y[i] = i;
		z[i] = i;
		x_i[i] = 0;
	}
  	printf("Initialization finished!\n");
  
	printf("CPU add finished!\n");
  	start = rdcycle();
  	/* Run kernel. */
  	add();
  	end = rdcycle();
  	printf("It takes %d cycles for CPU to finish the task.\n", end - start);
 
	void* cgra_din_addr[2] = {y, z};
	void* cgra_dout_addr[1] = {x};

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
