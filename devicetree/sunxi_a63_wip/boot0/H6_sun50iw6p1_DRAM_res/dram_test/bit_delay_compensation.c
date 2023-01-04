#include "dram_base.h"

void  bit_delay_compensation(__dram_para_t *para)
{
  int v1; // r2
  int v2; // r3
  char v4; // r1
  int v5; // r1
  int v6; // r3
  char v7; // r2
  int i; // r3
  int v9; // r2

  v1 = 0;
  v2 = 67131200;
  do
  {
    v4 = 4 * v1++;

//backup
/*
    *(_DWORD *)v2 += (2 * ((para->dram_tpr11 >> v4) & 0xF)) | (((para->dram_tpr11 >> v4) & 0xF) << 9) | (((para->dram_tpr11 >> v4) & 0xF) << 17) | (((para->dram_tpr11 >> v4) & 0xF) << 25);
    *(_DWORD *)(v2 + 4) += (2 * ((para->dram_tpr11 >> v4) & 0xF)) | (((para->dram_tpr11 >> v4) & 0xF) << 9) | (((para->dram_tpr11 >> v4) & 0xF) << 17) | (((para->dram_tpr11 >> v4) & 0xF) << 25);
    *(_DWORD *)(v2 + 8) += (((para->dram_tpr11 >> (v4 + 16)) & 0xF) << 9) | (((para->dram_tpr11 >> (v4 + 16)) & 0xF) << 17) | (2 * ((para->dram_tpr11 >> v4) & 0xF));
*/

	writel( readl( v2 ) + (
	(2 * ((para->dram_tpr11 >> v4) & 0xF)) |
		 (((para->dram_tpr11 >> v4) & 0xF) << 9) |
		 (((para->dram_tpr11 >> v4) & 0xF) << 17) |
		 (((para->dram_tpr11 >> v4) & 0xF) << 25)
					) , v2 );
	writel( readl( v2 + 4 ) + (
	(2 * ((para->dram_tpr11 >> v4) & 0xF)) |
		 (((para->dram_tpr11 >> v4) & 0xF) << 9) |
		 (((para->dram_tpr11 >> v4) & 0xF) << 17) |
		 (((para->dram_tpr11 >> v4) & 0xF) << 25)
					) , v2 + 4 );
	writel( readl( v2 + 8 ) + (
	(((para->dram_tpr11 >> (v4 + 16)) & 0xF) << 9) |
		 (((para->dram_tpr11 >> (v4 + 16)) & 0xF) << 17) |
		 (2 * ((para->dram_tpr11 >> v4) & 0xF))
					) , v2 + 8 );

    v2 += 256;
  }
  while ( v1 != 4 );
  v5 = 0;

//  MEMORY[0x4005010] &= ~0x4000000u;
	writel( readl( 0x4005010 ) & ~0x4000000u , 0x4005010 );

  v6 = 67131216;
  do
  {
    v7 = 4 * v5++;

//backup
/*
    *(_DWORD *)v6 += (2 * ((para->dram_tpr12 >> v7) & 0xF)) | (((para->dram_tpr12 >> v7) & 0xF) << 9) | (((para->dram_tpr12 >> v7) & 0xF) << 17) | (((para->dram_tpr12 >> v7) & 0xF) << 25);
    *(_DWORD *)(v6 + 4) += (2 * ((para->dram_tpr12 >> v7) & 0xF)) | (((para->dram_tpr12 >> v7) & 0xF) << 9) | (((para->dram_tpr12 >> v7) & 0xF) << 17) | (((para->dram_tpr12 >> v7) & 0xF) << 25);
    *(_DWORD *)(v6 + 8) += (((para->dram_tpr12 >> (v7 + 16)) & 0xF) << 17) | (((para->dram_tpr12 >> (v7 + 16)) & 0xF) << 9) | (2 * ((para->dram_tpr12 >> v7) & 0xF));
    *(_DWORD *)(v6 + 16) += (((para->dram_tpr12 >> v7) & 0xF) << 9) | (((para->dram_tpr12 >> v7) & 0xF) << 17);
*/

	writel( readl( v6 ) + (
	(2 * ((para->dram_tpr12 >> v7) & 0xF)) |
		 (((para->dram_tpr12 >> v7) & 0xF) << 9) |
		 (((para->dram_tpr12 >> v7) & 0xF) << 17) |
		 (((para->dram_tpr12 >> v7) & 0xF) << 25)
					) , v6 );

	writel( readl( v6 + 4 ) + (
	(2 * ((para->dram_tpr12 >> v7) & 0xF)) |
		 (((para->dram_tpr12 >> v7) & 0xF) << 9) |
		 (((para->dram_tpr12 >> v7) & 0xF) << 17) |
		 (((para->dram_tpr12 >> v7) & 0xF) << 25)
					) , v6 + 4 );

	writel( readl( v6 + 8 ) + (
	(((para->dram_tpr12 >> (v7 + 16)) & 0xF) << 17) |
		 (((para->dram_tpr12 >> (v7 + 16)) & 0xF) << 9) |
		 (2 * ((para->dram_tpr12 >> v7) & 0xF))
					) , v6 + 8 );

	writel( readl( v6 + 16 ) + (
	(((para->dram_tpr12 >> v7) & 0xF) << 9) |
		 (((para->dram_tpr12 >> v7) & 0xF) << 17)
					) , v6 + 16 );


    v6 += 256;
  }
  while ( v5 != 4 );

//  MEMORY[0x4005010] |= 0x4000000u;
	writel( readl( 0x4005010 ) | 0x4000000u , 0x4005010 );

  _usdelay(1u);
  for ( i = 67130692; i != 67130744; i += 4 )
  {
    v9 = (uint8_t)para->dram_tpr10 >> 4;

//    *(_DWORD *)i += (v9 << 16) | (v9 << 8) | v9 | (v9 << 24);
	writel( readl( i ) + ( (v9 << 16) | (v9 << 8) | v9 | (v9 << 24) ) , i );

  }

//  MEMORY[0x4005540] += ((para->dram_tpr10 & 0xF) << 16) | ((para->dram_tpr10 & 0xF) << 8) | para->dram_tpr10 & 0xF | ((para->dram_tpr10 & 0xF) << 24);

	writel( readl( 0x4005540 ) + (
	((para->dram_tpr10 & 0xF) << 16) |
		 ((para->dram_tpr10 & 0xF) << 8) |
		 para->dram_tpr10 & 0xF |
		 ((para->dram_tpr10 & 0xF) << 24)
					) , 0x4005540 );

}