#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#include "include/encoding.h"
#include "include/ISA.h"

#define TYPE int
#define N 4096
TYPE XR0[N] __attribute__((aligned(16)));
TYPE XR1[N] __attribute__((aligned(16)));
TYPE XR2[N] __attribute__((aligned(16)));
TYPE XR3[N] __attribute__((aligned(16)));
TYPE XI0[N] __attribute__((aligned(16)));
TYPE XI1[N] __attribute__((aligned(16)));
TYPE XI2[N] __attribute__((aligned(16)));
TYPE XI3[N] __attribute__((aligned(16)));
TYPE YR0[N] __attribute__((aligned(16)));
TYPE YR1[N] __attribute__((aligned(16)));
TYPE YR2[N] __attribute__((aligned(16)));
TYPE YR3[N] __attribute__((aligned(16)));
TYPE YI0[N] __attribute__((aligned(16)));
TYPE YI1[N] __attribute__((aligned(16)));
TYPE YI2[N] __attribute__((aligned(16)));
TYPE YI3[N] __attribute__((aligned(16)));
TYPE ZR0[N] __attribute__((aligned(16)));
TYPE ZR1[N] __attribute__((aligned(16)));
TYPE ZR2[N] __attribute__((aligned(16)));
TYPE ZR3[N] __attribute__((aligned(16)));
TYPE ZI0[N] __attribute__((aligned(16)));
TYPE ZI1[N] __attribute__((aligned(16)));
TYPE ZI2[N] __attribute__((aligned(16)));
TYPE ZI3[N] __attribute__((aligned(16)));


void cgra_execute(void** din_addr, void** dout_addr)
{
	volatile unsigned short cin[80][5] __attribute__((aligned(16))) = {
		{0x5000, 0x0000, 0x0100, 0x0000, 0x0002},
		{0x0000, 0x8000, 0x4047, 0x0000, 0x0003},
		{0x7000, 0x0000, 0x0100, 0x0000, 0x0004},
		{0x0000, 0x8000, 0x4047, 0x0000, 0x0005},
		{0x6000, 0x0000, 0x0100, 0x0000, 0x0006},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0007},
		{0x4000, 0x0000, 0x0100, 0x0000, 0x0008},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x0009},
		{0x6000, 0x0000, 0x0100, 0x0000, 0x000a},
		{0x0000, 0x8000, 0x0048, 0x0000, 0x000b},
		{0x5000, 0x0000, 0x0100, 0x0000, 0x000c},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x000d},
		{0x4000, 0x0000, 0x0100, 0x0000, 0x000e},
		{0x0000, 0x8000, 0x0047, 0x0000, 0x000f},
		{0x7000, 0x0000, 0x0100, 0x0000, 0x0010},
		{0x0000, 0x8000, 0x0048, 0x0000, 0x0011},
		{0x0003, 0x0000, 0x0000, 0x0000, 0x0016},
		{0x0000, 0x0010, 0x0000, 0x0000, 0x0018},
		{0x0000, 0x001c, 0x0000, 0x0000, 0x001a},
		{0x0020, 0x0000, 0x0000, 0x0000, 0x001c},
		{0x0000, 0x0014, 0x0000, 0x0000, 0x001e},
		{0x0020, 0x0000, 0x0000, 0x0000, 0x0020},
		{0x0030, 0x0000, 0x0000, 0x0000, 0x0022},
		{0x0000, 0x0000, 0x4001, 0x0002, 0x002a},
		{0x0000, 0x0000, 0x1041, 0x0002, 0x002c},
		{0x0000, 0x0000, 0x3002, 0x0002, 0x002e},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x003a},
		{0xdc00, 0x0000, 0x0000, 0x0000, 0x003c},
		{0x3c04, 0x0621, 0x0000, 0x0000, 0x003e},
		{0x000c, 0x0004, 0x0000, 0x0000, 0x0040},
		{0x1c00, 0x00c0, 0x0000, 0x0000, 0x0042},
		{0x0200, 0x0000, 0x0000, 0x0000, 0x0044},
		{0x0000, 0x0020, 0x0000, 0x0000, 0x0046},
		{0x0000, 0x0000, 0x2002, 0x0001, 0x004c},
		{0x0000, 0x0000, 0xa402, 0x0000, 0x004e},
		{0x0000, 0x0000, 0xb202, 0x0000, 0x0050},
		{0x0000, 0x0000, 0xa001, 0x0000, 0x0052},
		{0x0000, 0x0000, 0xc001, 0x0000, 0x0054},
		{0x0000, 0x0000, 0x9002, 0x0001, 0x0056},
		{0x0000, 0x0100, 0x0000, 0x0000, 0x0060},
		{0x1c20, 0x0020, 0x0000, 0x0000, 0x0062},
		{0x0000, 0x0020, 0x0000, 0x0000, 0x0064},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0066},
		{0x04c3, 0x0000, 0x0000, 0x0000, 0x0068},
		{0x0000, 0x0008, 0x0000, 0x0000, 0x006a},
		{0x0000, 0x0000, 0x2001, 0x0002, 0x0072},
		{0x0000, 0x0000, 0xb001, 0x0000, 0x0074},
		{0x0000, 0x0000, 0xa041, 0x0001, 0x0078},
		{0x0000, 0x0000, 0xb202, 0x0000, 0x007a},
		{0x0000, 0x0218, 0x0000, 0x0000, 0x0084},
		{0x0434, 0x0004, 0x0000, 0x0000, 0x0086},
		{0x0000, 0x0020, 0x0000, 0x0000, 0x0088},
		{0x0040, 0x0640, 0x0000, 0x0000, 0x008a},
		{0x0020, 0x0020, 0x0000, 0x0000, 0x008c},
		{0x0000, 0x0000, 0xc041, 0x0001, 0x0096},
		{0x0000, 0x0000, 0xb002, 0x0000, 0x0098},
		{0x0000, 0x0000, 0xb402, 0x0001, 0x009a},
		{0x0000, 0x0010, 0x0000, 0x0000, 0x00a6},
		{0x2080, 0x0020, 0x0000, 0x0000, 0x00a8},
		{0x0000, 0x0024, 0x0000, 0x0000, 0x00aa},
		{0x0060, 0x0000, 0x0000, 0x0000, 0x00ac},
		{0x0300, 0x0000, 0x0000, 0x0000, 0x00ae},
		{0x0000, 0x0030, 0x0000, 0x0000, 0x00b0},
		{0x0200, 0x0000, 0x0000, 0x0000, 0x00b2},
		{0x4000, 0x0000, 0x0100, 0x0000, 0x00b6},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00b7},
		{0x7000, 0x0000, 0x0100, 0x0000, 0x00b8},
		{0x0000, 0x8000, 0x4047, 0x0000, 0x00b9},
		{0x6000, 0x0000, 0x0100, 0x0000, 0x00ba},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00bb},
		{0x5000, 0x0000, 0x0100, 0x0000, 0x00bc},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00bd},
		{0x4000, 0x0000, 0x0100, 0x0000, 0x00be},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00bf},
		{0x5000, 0x0000, 0x0100, 0x0000, 0x00c0},
		{0x0000, 0x8000, 0x0047, 0x0000, 0x00c1},
		{0x7000, 0x0000, 0x0100, 0x0000, 0x00c2},
		{0x0000, 0x8000, 0x0000, 0x0000, 0x00c3},
		{0x6000, 0x0000, 0x0100, 0x0000, 0x00c4},
		{0x0000, 0x8000, 0x0048, 0x0000, 0x00c5},
	};

	load_cfg((void*)cin, 0x40000, 800, 7, 0);
	load_data(din_addr[0], 0x30000, 16384, 0, 7, 0);
	load_data(din_addr[1], 0x14000, 16384, 0, 7, 0);
	load_data(din_addr[2], 0x8000, 16384, 0, 7, 0);
	load_data(din_addr[3], 0x3c000, 16384, 0, 7, 0);
	load_data(din_addr[4], 0x20000, 16384, 0, 7, 0);
	load_data(din_addr[5], 0x24000, 16384, 0, 7, 0);
	load_data(din_addr[6], 0x28000, 16384, 0, 7, 0);
	load_data(din_addr[7], 0x0, 16384, 0, 7, 3);
	config(0x0, 80, 7, 0);
	execute(0xffff, 7, 1);
	store(dout_addr[0], 0x2c000, 16384, 7, 0);
	store(dout_addr[1], 0x34000, 16384, 7, 0);
	store(dout_addr[2], 0x18000, 16384, 7, 0);
	store(dout_addr[3], 0x10000, 16384, 7, 0);
	store(dout_addr[4], 0x38000, 16384, 7, 0);
	store(dout_addr[5], 0xc000, 16384, 7, 0);
	store(dout_addr[6], 0x1c000, 16384, 7, 0);
	store(dout_addr[7], 0x4000, 16384, 7, 0);
}



#define cmplx_M_x(a_x, a_y, b_x, b_y) (a_x*b_x - a_y *b_y)
#define cmplx_M_y(a_x, a_y, b_x, b_y) (a_x*b_y + a_y *b_x)
#define cmplx_MUL_x(a_x, a_y, b_x, b_y ) (a_x*b_x - a_y*b_y)
#define cmplx_MUL_y(a_x, a_y, b_x, b_y ) (a_x*b_y + a_y*b_x)
#define cmplx_mul_x(a_x, a_y, b_x, b_y) (a_x*b_x - a_y*b_y)
#define cmplx_mul_y(a_x, a_y, b_x, b_y) (a_x*b_y + a_y*b_x)
#define cmplx_add_x(a_x, b_x) (a_x + b_x)
#define cmplx_add_y(a_y, b_y) (a_y + b_y)
#define cmplx_sub_x(a_x, b_x) (a_x - b_x)
#define cmplx_sub_y(a_y, b_y) (a_y - b_y)
#define cm_fl_mul_x(a_x, b) (b*a_x)
#define cm_fl_mul_y(a_y, b) (b*a_y)

#define FF2(a0_x, a0_y, a1_x, a1_y){			\
    TYPE c0_x = a0_x;		\
    TYPE c0_y = a0_y;		\
    a0_x = cmplx_add_x(c0_x, a1_x);	\
    a0_y = cmplx_add_y(c0_y, a1_y);	\
    a1_x = cmplx_sub_x(c0_x, a1_x);	\
    a1_y = cmplx_sub_y(c0_y, a1_y);	\
}

#define FFT4(a0_x, a0_y, a1_x, a1_y, a2_x, a2_y, a3_x, a3_y){           \
    TYPE exp_1_44_x;		\
    TYPE exp_1_44_y;		\
    TYPE tmp;			\
    exp_1_44_x =  0;		\
    exp_1_44_y =  -1;		\
    FF2( a0_x, a0_y, a2_x, a2_y);   \
    FF2( a1_x, a1_y, a3_x, a3_y);   \
    tmp = a3_x;			\
    a3_x = a3_x*exp_1_44_x-a3_y*exp_1_44_y;     	\
    a3_y = tmp*exp_1_44_y - a3_y*exp_1_44_x;    	\
    FF2( a0_x, a0_y, a1_x, a1_y );                  \
    FF2( a2_x, a2_y, a3_x, a3_y );                  \
}

/* Array initialization. */
void init_array()
{
    int i;
    for (i = 0; i < N; i++) {
        XR0[i] = i;
        XR1[i] = i+1;
        XR2[i] = i+2;
        XR3[i] = i+3;
        XI0[i] = i+4;
        XI1[i] = i+5;
        XI2[i] = i+6;
        XI3[i] = i+7;
    }    
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
//__attribute__((noinline))
void fft4(){
    int i;
    for(i = 0; i < N; i++){
//    please_map_me();
        TYPE a0_x = XR0[i];
        TYPE a0_y = XI0[i];
        TYPE a1_x = XR1[i];
        TYPE a1_y = XI1[i];
        TYPE a2_x = XR2[i];
        TYPE a2_y = XI2[i];
        TYPE a3_x = XR3[i];
        TYPE a3_y = XI3[i];
        FFT4(a0_x, a0_y, a1_x, a1_y, a2_x, a2_y, a3_x, a3_y);
        ZR0[i] = a0_x;
        ZI0[i] = a0_y;
        ZR1[i] = a1_x;
        ZI1[i] = a1_y;
        ZR2[i] = a2_x;
        ZI2[i] = a2_y;
        ZR3[i] = a3_x;
        ZI3[i] = a3_y;
    }
}


void result_check()
{
  int i, j;

  for (i = 0; i < N; i++)
  {
    if (ZR0[i] != YR0[i] ||
        ZI0[i] != YI0[i] ||
        ZR1[i] != YR1[i] ||
        ZI1[i] != YI1[i] ||
        ZR2[i] != YR2[i] ||
        ZI2[i] != YI2[i] ||
        ZR3[i] != YR3[i] ||
        ZI3[i] != YI3[i])
        printf("There is an error in location (%d)[%d, %d]\n", i, ZR0[i], YR0[i]);
  }
}


int main(int argc, char** argv)
{
  long long unsigned start;
  long long unsigned end;
  init_array();
  printf("Initialization finished!\n");
  printf("%x, %x, %x, %x, %x, %x, %x, %x\n", XI0, XI1, XI2, XI3, XR0, XR1, XR2, XR3);
  printf("%x, %x, %x, %x, %x, %x, %x, %x\n", YR0, YI0, YR1, YI1, YR2, YI2, YR3, YI3);

  start = rdcycle();
  /* Run kernel. */
  fft4();
  end = rdcycle();
  printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[8] = {XI0, XI1, XI2, XI3, XR0, XR2, XR3, XR1};
  void* cgra_dout_addr[8] = {YR0, YI0, YR1, YI1, YR2, YI2, YR3, YI3};
  start = rdcycle();
  cgra_execute(cgra_din_addr, cgra_dout_addr);
  volatile int result = fence(1);
  end = rdcycle();
  printf("It takes %d cycles for CGRA to finish the task(%d).\n", end - start, result);

  result_check();
  printf("Done!\n");

  return 0;
}