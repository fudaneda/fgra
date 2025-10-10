#include <string.h>
#include <stdio.h>
#include "include/encoding.h"
#include "include/ISA.h"



__attribute__((noinline))
void cgra_execute(void** din_addr, void** dout_addr)
{
	static unsigned short cin[101][3] __attribute__((aligned(16))) = {
		{0x1000, 0x2c00, 0x0008},
		{0x0000, 0x00b0, 0x0009},
		{0x0008, 0x8840, 0x000a},
		{0x0006, 0x1000, 0x000b},
		{0x0800, 0x2c02, 0x0010},
		{0xb080, 0x00bf, 0x0011},
		{0x3eac, 0x8840, 0x0012},
		{0x0201, 0x0000, 0x0013},
		{0x9fe7, 0x2c00, 0x0020},
		{0xec80, 0x00bf, 0x0021},
		{0x3fa4, 0x0840, 0x0022},
		{0x0603, 0x0000, 0x0023},
		{0x0002, 0x0000, 0x0048},
		{0x0000, 0x0000, 0x0050},
		{0x0000, 0x0000, 0x0060},
		{0x0030, 0x0000, 0x0090},
		{0x0000, 0x0000, 0x00f0},
		{0x0300, 0x0600, 0x00f8},
		{0x0000, 0x0600, 0x0108},
		{0xc000, 0x0030, 0x0139},
		{0x0800, 0x0000, 0x0141},
		{0x000f, 0x0000, 0x0160},
		{0x8003, 0x0002, 0x0162},
		{0x0283, 0x0015, 0x016a},
		{0xfffb, 0xffff, 0x0170},
		{0x8001, 0x0002, 0x0172},
		{0x0003, 0x0000, 0x0178},
		{0x0005, 0x0010, 0x017a},
		{0x0100, 0x0600, 0x01a0},
		{0x0008, 0x0000, 0x01a8},
		{0x0c01, 0x0001, 0x01b0},
		{0x0000, 0xc000, 0x01e0},
		{0x0000, 0x0188, 0x01e1},
		{0x0000, 0x2000, 0x01e8},
		{0x0000, 0x0400, 0x01e9},
		{0x0011, 0x0001, 0x0212},
		{0x0000, 0x0000, 0x0214},
		{0x2000, 0x2c00, 0x0215},
		{0x0790, 0x0200, 0x0216},
		{0x0001, 0x0000, 0x0218},
		{0x0011, 0x0020, 0x021a},
		{0x0000, 0x0000, 0x021b},
		{0x02a0, 0x0000, 0x021c},
		{0x6000, 0x0001, 0x021d},
		{0x00b0, 0xc200, 0x021e},
		{0x0000, 0x0000, 0x0220},
		{0x0006, 0x0008, 0x0222},
		{0x0180, 0x0000, 0x0223},
		{0x0004, 0x0000, 0x0224},
		{0x2000, 0x0000, 0x0248},
		{0x0000, 0x0608, 0x0289},
		{0x0300, 0x0000, 0x0290},
		{0x0800, 0x0000, 0x0291},
		{0x8203, 0x0015, 0x02b2},
		{0x0001, 0x0000, 0x02b8},
		{0x0011, 0x0000, 0x02ba},
		{0x0000, 0x0000, 0x02bc},
		{0x2000, 0x000f, 0x02bd},
		{0x1000, 0xc002, 0x02be},
		{0x0001, 0x0000, 0x02c0},
		{0x0011, 0x01c0, 0x02c2},
		{0x1000, 0x0000, 0x02c3},
		{0x02b0, 0x0000, 0x02c4},
		{0x2000, 0x0000, 0x02c5},
		{0x00b0, 0xd600, 0x02c6},
		{0x0801, 0x0012, 0x02ca},
		{0x0004, 0x0000, 0x02f0},
		{0x0000, 0x0000, 0x02f8},
		{0x0410, 0x0000, 0x0300},
		{0x0300, 0x0000, 0x0329},
		{0x0000, 0x0a01, 0x0331},
		{0x0000, 0x0000, 0x0338},
		{0x0000, 0x0000, 0x0339},
		{0x0000, 0x0000, 0x0358},
		{0x0006, 0x0014, 0x035a},
		{0x0180, 0x0000, 0x035b},
		{0x0006, 0x0000, 0x035c},
		{0x0011, 0x0001, 0x0362},
		{0x0000, 0x0000, 0x0364},
		{0x2000, 0x2c00, 0x0365},
		{0x0790, 0x0200, 0x0366},
		{0xfffb, 0xffff, 0x0368},
		{0x0001, 0x0001, 0x036a},
		{0x00ff, 0x0000, 0x0370},
		{0x0005, 0x0008, 0x0372},
		{0x0108, 0x0000, 0x0398},
		{0x0000, 0x0004, 0x03a0},
		{0x0000, 0x0028, 0x03d9},
		{0x000f, 0x0000, 0x0408},
		{0x2003, 0x0000, 0x0409},
		{0x0000, 0x0000, 0x0440},
		{0x0000, 0x0000, 0x0448},
		{0x0060, 0x0000, 0x0480},
		{0x0000, 0x2c00, 0x04a8},
		{0x0000, 0x00b0, 0x04a9},
		{0x0008, 0x8840, 0x04aa},
		{0x0006, 0x1000, 0x04ab},
		{0x9fe7, 0x2c00, 0x04b8},
		{0xec80, 0x00bf, 0x04b9},
		{0x3fa4, 0x0840, 0x04ba},
		{0x0603, 0x0000, 0x04bb},
	};

	load_cfg((void*)cin, 0x18000, 606, 0, 0);
	load_data(din_addr[0], 0x2000, 684, 0, 0, 0);
	load_data(din_addr[1], 0x10000, 4184, 0, 0, 0);
	load_data(din_addr[2], 0x0, 4184, 0, 0, 0);
	config(0x0, 101, 0, 0);
	execute(0x28b, 0, 0);
	store(dout_addr[0], 0x4000, 4084, 0, 0);
	store(dout_addr[1], 0x8000, 4084, 0, 0);
}


#define size 1088
#define rows 256
#define columns 4
#define gaussian_row 16
#define gaussian_col 16
int uniformH[size]__attribute__((aligned(16)));
int uniformV[size]__attribute__((aligned(16)));
int m_GaussianKernel[gaussian_row][gaussian_col]__attribute__((aligned(16)));
int m_DispH_i[size]__attribute__((aligned(16)));
int m_DispV_i[size]__attribute__((aligned(16)));
int m_DispH[size]__attribute__((aligned(16)));
int m_DispV[size]__attribute__((aligned(16)));

void GenerateDistortionMap( )
{
	int row, col;

	int fConvolvedH, fConvolvedV;
	int fSampleH, fSampleV;
	int elasticScale = 15;
	int xxx, yyy, xxxDisp, yyyDisp;
	int iiMid = 11/2;  // GAUSSIAN_FIELD_SIZE is strictly odd

	for ( row=0; row<rows; ++row )
	{
		fConvolvedH = 0;
		fConvolvedV = 0;

		for ( xxx=0; xxx<11; ++xxx )
		{
			for ( yyy=0; yyy<11; ++yyy )
			{
				xxxDisp = 0 - iiMid + xxx;
				yyyDisp = row - iiMid + yyy;

				if ( xxxDisp<0 || xxxDisp>=columns || yyyDisp<0 || yyyDisp>=rows )
				{
					fSampleH = 0;
					fSampleV = 0;
				}
				else
				{
					int location = yyyDisp * columns + xxxDisp;
					fSampleH = uniformH[ location ];
					fSampleV = uniformV[ location ]; 
				}

				fConvolvedH += fSampleH * m_GaussianKernel[ yyy ][ xxx ];
				fConvolvedV += fSampleV * m_GaussianKernel[ yyy ][ xxx ];
			}
		}
		// int location = row * columns + col;
		int location = row * columns;
		m_DispH_i[ location ] = elasticScale * fConvolvedH;
		m_DispV_i[ location ] = elasticScale * fConvolvedV;
	}
}


void result_check()
{
  int i, j;

  for (i = 0; i < size; i++)
  {
	if(i%4 ==0){
    if (m_DispH_i[i] != m_DispH[i]) printf("There is an error m_DispH in location (%d)[%d, %d]\n", i, m_DispH_i[i], m_DispH[i]);
    if (m_DispV_i[i] != m_DispV[i]) printf("There is an error m_DispH in location (%d)[%d, %d]\n", i, m_DispV_i[i], m_DispV[i]);
  }
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
 
for(int i=0; i<gaussian_row; i++){
	for(int j =0; j<gaussian_col; j++){
		m_GaussianKernel[i][j] = i*j;
	}
}

  for(int i=0; i<size; i++){
	uniformH[i] = i;
	uniformH[i] = i;
	m_DispH[i] = 0;
	m_DispV[i] = 0;
  }
// for (i=0;i<SIZE; i++) printf("%d\n", C[i]);

  printf("Initialization finished!\n");
  
  // printf("CPU add finished!\n");
//   start = rdcycle();
//   /* Run kernel. */
//   GenerateDistortionMap();
// //   matching();
//   end = rdcycle();
//   printf("It takes %d cycles for CPU to finish the task.\n", end - start);

  void* cgra_din_addr[3] = {m_GaussianKernel, uniformH, uniformV};
  void* cgra_dout_addr[2] = {m_DispH, m_DispV};
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
    
//   printf("Checking results!\n");
//   result_check();
  printf("Done!\n");

return 0;

}
