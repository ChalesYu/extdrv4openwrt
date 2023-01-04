#include "dram_base.h"

unsigned int  dramc_simple_wr_test(unsigned int dram_size, unsigned int test_length)
{
  int v2; // r2
  unsigned int v4; // r0
  int i; // r3
  int v6; // r1
  int v7; // r3
  int j; // r6

  v2 = 0x40000000;
  v4 = dram_size >> 1 << 20;
  for ( i = 0; i != test_length; ++i )
  {
//    *(_DWORD *)v2 = i + 19088743;
    writel( (i + 19088743) , v2 );
    
    v6 = i - 19088744;
    
//    *(_DWORD *)(v2 + v4) = v6;
	writel( v6 , v2 + v4 );

     v2 += 4;
  }
  v7 = 0x40000000;
  printf("DRAM simple test: fill value OK.\n");
  printf("DRAM simple test: Now start read back.\n");
  for ( j = 0; j != test_length; ++j )
  {

    if (  readl( v7+v4 ) != (j - 19088744)  )
    {
      printf("DRAM simple test FAIL-----%x != %x at address %x\n");
      return 1;
    }

    if ( readl( v7 ) != (j + 19088743)  )
    {
      printf("DRAM simple test FAIL-----%x != %x at address %x\n");
      return 1;
    }

    v7 += 4;
  }
  printf("DRAM simple test OK.\n");
  return 0;
}
