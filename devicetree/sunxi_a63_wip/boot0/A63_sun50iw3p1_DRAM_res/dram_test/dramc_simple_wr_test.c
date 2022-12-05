#include "dram_base.h"

unsigned int dramc_simple_wr_test(unsigned int dram_size, unsigned int test_length)
{
  int v2; // r2
  unsigned int v3; // r0
  int i; // r3
  int v5; // r4
  int v6; // r4
  int j; // r3
  unsigned int v8; // r5
  int v9; // r7
  int v10; // r6
  int v11; // r6
  int v12; // r5

  v2 = 0x40000000;
  v3 = dram_size >> 1 << 20;
  for ( i = 0; i != test_length; ++i )
  {
//    *(_DWORD *)v2 = i + 19088743;
	writel (  i + 19088743 , v2 );

    v5 = i - 19088744;
 //   *(_DWORD *)(v2 + v3) = v5;
	writel ( v5 , (v2 + v3) );


    v2 += 4;
  }
  v6 = 0x40000000;
  for ( j = 0; j != test_length; ++j )
  {
    v8 = v6 + v3;
//    v9 = *(_DWORD *)(v6 + v3);
	v9 = readl( (v6 + v3) );

    v10 = j - 19088744;
    if ( v9 != (j - 19088744) )
    {
      printf("DRAM simple test FAIL.\n");
      printf("%x != %x at address %x\n", v9, v10, v8);
      return 1;
    }
//    v11 = *(_DWORD *)v6;
	v11 = readl( v6 );

    v12 = j + 19088743;

    if ( v11 != (j + 19088743) )
    {
      printf("DRAM simple test FAIL.\n");
      printf("%x != %x at address %x\n", v11, v12, v6);
      return 1;
    }
    v6 += 4;
  }
  printf("DRAM simple test OK.\n");
  return 0;
}