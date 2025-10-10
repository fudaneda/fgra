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

#define SIZE 4096

//typedef struct Acceleration Acceleration;
//struct Acceleration {
//    int x;
//    int y;
//    int z;
//};

//unsigned char second = 0;
//unsigned char minute = 0;
//unsigned char hour = 0;
//unsigned char state = 0;
//unsigned char I1_flag = 0;
//unsigned char I2_flag = 0;
//unsigned char timerFlag1 = 0;
//unsigned char timerFlag2 = 0;
//unsigned char aux=0;
//char Int_SourceSystem =0;
//char Int_SourceTrans=0;
//unsigned char length;
//char buffer[14];
//int step[SIZE]={};
//int km[SIZE]={};
int acc_vector[SIZE];
int res_vector[SIZE];

//int i;
//int sub_x;
//int sub_y;
//int sub_z;
int acceleration_x[SIZE] __attribute__((aligned(16)));
int acceleration_y[SIZE] __attribute__((aligned(16)));
int acceleration_z[SIZE] __attribute__((aligned(16)));
int acc_avg_x[SIZE] __attribute__((aligned(16)));
int acc_avg_y[SIZE] __attribute__((aligned(16)));
int acc_avg_z[SIZE] __attribute__((aligned(16)));

//long long unsigned start;
//long long unsigned end;
//int result;

void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[38][5] __attribute__((aligned(16))) = {
		{0x6000, 0x0000, 0x0100, 0x0000, 0x0004},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0005},
		{0x4000, 0x0000, 0x0100, 0x0000, 0x0006},
		{0x0000, 0x8000, 0x4048, 0x0000, 0x0007},
		{0x5000, 0x0000, 0x0100, 0x0000, 0x0008},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0009},
		{0x6000, 0x0000, 0x0100, 0x0000, 0x000a},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000b},
		{0x5000, 0x0000, 0x0100, 0x0000, 0x000c},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000d},
		{0x0000, 0x0010, 0x0000, 0x0000, 0x0016},
		{0x0003, 0x0000, 0x0000, 0x0000, 0x001a},
		{0x2100, 0x0000, 0x0000, 0x0000, 0x001c},
		{0x0000, 0x0011, 0x0000, 0x0000, 0x001e},
		{0x0000, 0x0000, 0xa001, 0x0001, 0x002c},
		{0x0000, 0x0000, 0x9002, 0x0000, 0x002e},
		{0x0000, 0x0000, 0xb003, 0x0001, 0x0030},
		{0x0300, 0x0000, 0x0000, 0x0000, 0x003a},
		{0x0140, 0x0000, 0x0000, 0x0000, 0x003e},
		{0x0000, 0x0600, 0x0000, 0x0000, 0x0042},
		{0x0000, 0x0000, 0x9002, 0x0001, 0x004c},
		{0x0000, 0x0000, 0xb003, 0x0001, 0x004e},
		{0x0000, 0x0000, 0x1001, 0x0002, 0x0050},
		{0x00c0, 0x0000, 0x0000, 0x0000, 0x005e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0060},
		{0x000c, 0x0000, 0x0000, 0x0000, 0x0064},
		{0x8000, 0x0000, 0x0000, 0x0000, 0x0066},
		{0x0000, 0x0000, 0x3002, 0x0001, 0x0076},
		{0x0000, 0x0020, 0x0000, 0x0000, 0x0082},
		{0x0000, 0x0100, 0x0000, 0x0000, 0x0086},
		{0x0520, 0x0000, 0x0000, 0x0000, 0x0088},
		{0x0000, 0x0000, 0x9003, 0x0000, 0x009a},
		{0x0000, 0x0004, 0x0000, 0x0000, 0x00a6},
		{0x0000, 0x0004, 0x0000, 0x0000, 0x00aa},
		{0x5000, 0x0000, 0x0100, 0x0000, 0x00b6},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00b7},
		{0x6000, 0x0000, 0x0100, 0x0000, 0x00ba},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00bb},
	};

	load_cfg((void*)cin, 0x401c0, 380, 5, 0);
	load_data(din_addr[0], 0x24000, 16384, 0, 5, 0);
	load_data(din_addr[1], 0x4000, 16384, 0, 5, 0);
	load_data(din_addr[2], 0x14000, 16384, 0, 5, 0);
	load_data(din_addr[3], 0x8000, 16384, 0, 5, 0);
	load_data(din_addr[4], 0x18000, 16384, 0, 5, 0);
	load_data(din_addr[5], 0x28000, 16384, 0, 5, 0);
	config(0x1c, 38, 5, 0);
	execute(0x53e, 5, 0);
	store(dout_addr[0], 0x0, 16384, 5, 0);
}


/* Array initialization. */
void init_array()
{
	for(int i=0;i<SIZE;i++){
    	acceleration_x[i] = 3*i;
    	acceleration_y[i] = 3*i+1;
    	acceleration_z[i] = 3*i+2;
    
    	acc_avg_x[i] = i;
    	acc_avg_y[i] = i;
    	acc_avg_z[i] = i;
 	}
}


__attribute__((noinline))
void pedometer(){//(int input[], int output[], int coefficients[])
	for(int i=0;i<SIZE;i++){
	    int sub_x = acceleration_x[i]- acc_avg_x[i];
        int sub_y = acceleration_y[i]- acc_avg_y[i];
        int sub_z = acceleration_z[i]-acc_avg_z[i];
        res_vector[i] = sub_x * sub_x+  sub_y * sub_y+ sub_z * sub_z;
//		res_vector[i] = (acceleration_x[i]- acc_avg_x[i]) * (acceleration_x[i]- acc_avg_x[i])+
//		(acceleration_y[i]- acc_avg_y[i]) * (acceleration_y[i]- acc_avg_y[i])+
//		(acceleration_z[i]-acc_avg_z[i]) * (acceleration_z[i]-acc_avg_z[i]) ;
	}
}


void result_check()
{
  int i, j;

  for (i = 0; i < SIZE; i++)
  {
    if (acc_vector[i] != res_vector[i]) printf("There is an error in location (%d)[%d, %d]\n", i, acc_vector[i], res_vector[i]);
  }
}


int main(int argc, char** argv)
{
  long long unsigned start;
  long long unsigned end;
  init_array();
  printf("Initialization finished!\n");

  start = rdcycle();
  /* Run kernel. */
  pedometer();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[6] = {acc_avg_x, acc_avg_y, acc_avg_z, acceleration_x, acceleration_y, acceleration_z};
  void* cgra_dout_addr[1] = {acc_vector};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}