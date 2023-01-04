#include "dram_base.h"

unsigned int  auto_scan_dram_size(__dram_para_t *para)
{
  unsigned int v2; // r3
  __int16 v3; // r3
  __int16 v4; // r8
  unsigned int result; // r0
  int v6; // r2
  int i; // r3
  int v8; // r1
  int v9; // r7
  int v10; // r3
  int j; // r2
  int v12; // r1
  int k; // r5
  int v14; // r3
  int v15; // r2
  int v16; // r1
  int v17; // r8
  int v18; // r2
  int v19; // r3
  int v20; // r1
  int v21; // r6
  unsigned int v22; // r3
  __int16 v23; // r3
  __int16 v24; // r8
  int v25; // r2
  int m; // r3
  int v27; // r1
  int n; // r3
  int v29; // r2
  int v30; // r1
  int v31; // r0

  if ( para->dram_type == 4 )
    v2 = 45291;
  else
    v2 = 12523;
  para->dram_para1 = v2;
  if ( (para->dram_para2 & 0xF) != 0 )
    v3 = 1;
  else
    v3 = 2;
  v4 = ((uint16_t)para->dram_para1 >> 14) + v3;
  result = mctl_core_init(para);
  if ( result )
  {
    v6 = 0x40000000;
    for ( i = 0; i != 16; ++i )
    {
      if ( (i & 1) != 0 )
        v8 = v6;
      else
        v8 = ~v6;

//      *(_DWORD *)v6 = v8;
	writel( v8 , v6 );

      v6 += 4;

//      __dsb(0xFu);
	dsb();

    }
    v9 = 1;
LABEL_14:
    v10 = 0x40000000;
    for ( j = 0; j != 16; ++j )
    {
      if ( (j & 1) != 0 )
        v12 = v10;
      else
        v12 = ~v10;
//      if ( v12 != *(_DWORD *)(v10 + (1 << (v9 + 5))) )
      if (  v12 != readl( v10 + (1 << (v9 + 5)) )  )
      {
        if ( ++v9 != 3 )
          goto LABEL_14;
        goto LABEL_23;
      }
      v10 += 4;
    }
    if ( v9 == 1 )
      goto LABEL_26;
LABEL_23:
    if ( para->dram_type == 4 )
      v9 = 2;
    else
      v9 = 0;
LABEL_26:
    for ( k = 7; k != 11; ++k )
    {
      v14 = 0x40000000;
      v15 = 0;
      while ( 1 )
      {
        v16 = (v15 & 1) != 0 ? v14 : ~v14;

//        if ( v16 != *(_DWORD *)(v14 + (1 << (k + v4))) )  break;
        if ( v16 != readl( v14 + (1 << (k + v4)) ) )  break;

        ++v15;
        v14 += 4;
        if ( v15 == 16 )
          goto LABEL_35;
      }
    }
LABEL_35:
    v17 = 1 << (v4 + 13);
    v18 = 0;
    v19 = 0x40000000;
    while ( 1 )
    {
      v20 = (v18 & 1) != 0 ? v19 : ~v19;
//      if ( v20 != *(_DWORD *)(v19 + v17) ) break;
      if ( v20 != readl( v19 + v17 ) ) break;
      ++v18;
      v19 += 4;
      if ( v18 == 16 )
      {
        v21 = 2;
        goto LABEL_43;
      }
    }
    v21 = 3;
LABEL_43:
    if ( para->dram_type == 4 )
      v22 = 24856;
    else
      v22 = 8472;
    para->dram_para1 = v22;
    if ( (para->dram_para2 & 0xF) != 0 )
      v23 = 1;
    else
      v23 = 2;
    v24 = ((uint16_t)para->dram_para1 >> 14) + 10 + v23;
    result = mctl_core_init(para);
    if ( result )
    {
      v25 = 0x40000000;
      for ( m = 0; m != 16; ++m )
      {
        if ( (m & 1) != 0 )
          v27 = v25;
        else
          v27 = ~v25;

//        *(_DWORD *)v25 = v27;
        writel( v27 , v25 );

        v25 += 4;

//        __dsb(0xFu);
	dsb();

      }
      for ( n = 14; n != 17; ++n )
      {
        v29 = 0x40000000;
        v30 = 0;
        while ( 1 )
        {
          v31 = (v30 & 1) != 0 ? v29 : ~v29;
//          if ( v31 != *(_DWORD *)(v29 + (1 << (n + v24))) )  break;
          if ( v31 != readl( v29 + (1 << (n + v24)) ) )  break;
          ++v30;
          v29 += 4;
          if ( v30 == 16 )
            goto LABEL_64;
        }
      }
LABEL_64:
      result = 1;
      para->dram_para1 = k | (v9 << 14) | (v21 << 12) | (16 * n);
    }
  }
  return result;
}