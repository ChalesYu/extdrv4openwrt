#include "dram_base.h"

void  mctl_com_init(__dram_para_t *para)
{
  unsigned int v2; // r3
  int v3; // r2
  unsigned int v4; // r2
  unsigned int v5; // r3
  bool v6; // cc
  int v7; // r3
  int v8; // r1
  int v9; // r3
  unsigned int v10; // r3
  int v11; // r1
  int v12; // r1
  int v13; // r3
  int v14; // r3
  int v15; // r0
  int v16; // r3
  int v17; // r2
  unsigned int v18; // r0
  int v19; // r0
  int v20; // r5

  set_address_map(para);
  v2 = readl( 0x4002000 ) | 0x80000000;

  if ( readl( 0x3006100 ) == 7 )
  {
    v2 = readl( 0x4002000 ) & 0x77FFFFFF | 0x80000000;
  }
  else if ( readl( 0x3006100 ) == 3 )
  {
    v2 = readl( 0x4002000 ) | 0x88000000;
  }

  writel( v2 , 0x4002000 );

  if ( para->dram_clk > 0xF6 )
  {
    v4 = readl( 0x4002008 ) & 0xFFFFC0FF;
    if ( para->dram_clk > 0x198 )
      v3 = v4 | 0xF00;
    else
      v3 = v4 | 0x1F00;
  }
  else
  {
    v3 = readl( 0x4002008 ) | 0x3F00;
  }

  writel( v3 , 0x4002008 );

  v5 = (para->dram_type & 0xF) - 4;
  v6 = v5 > 3;
  if ( v5 <= 3 )
//    v5 += (unsigned int)CSWTCH_32;
//ERROR: unknown CSWTCH_32
	v5 += v5;

  if ( v6 )
    v7 = 1;
  else
    v7 = readb(v5 + 5);
  if ( (para->dram_tpr13 & 0x20) != 0 )
    v8 = 0;
  else
    v8 = 1024;
  v9 = v8 | v7;
  if ( para->dram_type - 6 <= 1 )
    v9 &= ~0x400u;

  writel( v9 | ((((para->dram_para2 >> 12) & 3) << 25) + 0x1000000) | ((para->dram_para2 & 1) << 12) | 0x80040000 , 0x4003000 );

  v10 = (para->dram_type & 7) - 4;
  if ( v10 > 3 )
    v11 = 3;
  else
//    v11 = CSWTCH_32[v10 + 9];
//ERROR - CSWTCH_32
	v11 = v10 + 9;

  v12 = v11 | 0x400;
  if ( ((para->dram_para1 >> 12) & 3) == 3 )
    v13 = 8;
  else
    v13 = 0;
  v14 = v13 | v12;
  if ( (para->dram_tpr13 & 0x20) != 0 )
    v15 = 0;
  else
    v15 = 0x10000000;
  v16 = v14 | v15;
  if ( para->dram_type - 6 <= 1 )
    v16 &= ~0x10000000u;

  writel( v16 , 0x4005100 );

  v17 = 513;
  if ( (para->dram_para2 & 0x1000) != 0 )
    v17 = 771;

  writel( v17 , 0x4003244 );

  v18 = para->dram_type & 7;
  switch ( v18 )
  {
    case 4u:
      v19 = ((((para->dram_mr4 >> 12) & 1) + 6) << 24) | 0x400 | (((para->dram_mr4 >> 6) & 7) << 16);
      break;
    case 7u:
      if ( para->dram_clk < 0x190 )
        v20 = 3;
      else
        v20 = 4;
      v19 = (((signed int)(7 * para->dram_clk) / 2000 + 7) << 24) | 0x400 | ((v20
                                                                            - (signed int)(7 * para->dram_clk) / 2000) << 16);
      break;
    case 3u:
      v19 = 100664320;
      break;
    default:
      v19 = 67109888;
      break;
  }

  writel( v19 , 0x4003240 );

  if ( (para->dram_para2 & 1) != 0 )
  {

    writel( 0 , 0x4005900 );
    writel( 0 , 0x4005A00 );

  }
}