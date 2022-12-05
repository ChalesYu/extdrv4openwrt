#include "dram_base.h"

void  eye_delay_compensation(__dram_para_t *para)
{
  unsigned int dram_tpr11; // r2
  unsigned int dram_tpr12; // r3
  int i; // r1
  int j; // r1
  int k; // r1
  int m; // r1
  int v8; // r7
  int v9; // r6
  int v10; // r6
  int v11; // lr
  int v12; // r5
  unsigned int v13; // r2
  int v14; // r12
  int v15; // r3
  unsigned int dram_tpr10; // r3
  int n; // r2

  dram_tpr11 = para->dram_tpr11;
  dram_tpr12 = para->dram_tpr12;
  for ( i = 67121936; i != 67121972; i += 4 )
{
//    *(_DWORD *)i |= ((dram_tpr11 & 0xF) << 9) | (2 * (dram_tpr12 & 0xF));
	writel( readl( i ) | ((dram_tpr11 & 0xF) << 9) | (2 * (dram_tpr12 & 0xF)) , i );

}
  for ( j = 67122064; j != 67122100; j += 4 )
{
//    *(_DWORD *)j |= ((uint8_t)dram_tpr11 >> 4 << 9) | (2 * ((uint8_t)dram_tpr12 >> 4));
	writel( readl( j ) | ((uint8_t)dram_tpr11 >> 4 << 9) | (2 * ((uint8_t)dram_tpr12 >> 4)) , j );

}
  for ( k = 67122192; k != 67122228; k += 4 )
{
//    *(_DWORD *)k |= (((dram_tpr11 >> 8) & 0xF) << 9) | (2 * ((dram_tpr12 >> 8) & 0xF));
	writel( readl( k ) | (((dram_tpr11 >> 8) & 0xF) << 9) | (2 * ((dram_tpr12 >> 8) & 0xF)) , k );

}
  for ( m = 67122320; m != 67122356; m += 4 )
{
//    *(_DWORD *)m |= ((uint16_t)dram_tpr11 >> 12 << 9) | (2 * ((uint16_t)dram_tpr12 >> 12));
	writel( readl( m ) | ((uint16_t)dram_tpr11 >> 12 << 9) | (2 * ((uint16_t)dram_tpr12 >> 12)) , m );

}

  v8 = HIWORD(dram_tpr11) & 0xF;
  v9 = (v8 << 9) | (2 * (HIWORD(dram_tpr12) & 0xF));

//  MEMORY[0x4003100] &= ~0x4000000u;
//  MEMORY[0x4003334] |= v9;
//  MEMORY[0x4003338] |= v9;

	writel( readl(0x4003100) & ~0x4000000u , 0x4003100 );
	writel( readl(0x4003334) | v9 , 0x4003334 );
	writel( readl(0x4003338) | v9 , 0x4003338 );

  v10 = (dram_tpr11 >> 20) & 0xF;
  v11 = (v10 << 9) | (2 * ((dram_tpr12 >> 20) & 0xF));

//  MEMORY[0x40033B4] |= v11;
//  MEMORY[0x40033B8] |= v11;

	writel( readl(0x40033B4) | v11 , 0x40033B4 );
	writel( readl(0x40033B8) | v11 , 0x40033B8 );

  v12 = HIBYTE(dram_tpr11) & 0xF;
  v13 = dram_tpr11 >> 28;
  v14 = (v12 << 9) | (2 * (HIBYTE(dram_tpr12) & 0xF));

//  MEMORY[0x4003434] |= v14;
//  MEMORY[0x4003438] |= v14;

	writel( readl(0x4003434) | v14 , 0x4003434 );
	writel( readl(0x4003438) | v14 , 0x4003438 );

  v15 = (v13 << 9) | (2 * (dram_tpr12 >> 28));

//  MEMORY[0x40034B4] |= v15;
//  MEMORY[0x40034B8] |= v15;
//  MEMORY[0x400333C] |= v8 << 25;
//  MEMORY[0x40033BC] |= v10 << 25;

//  MEMORY[0x400343C] |= v12 << 25;
//  MEMORY[0x40034BC] |= v13 << 25;
//  MEMORY[0x4003100] |= 0x4000000u;

	writel( readl(0x40034B4) | v15 , 0x40034B4 );
	writel( readl(0x40034B8) | v15 , 0x40034B8 );
	writel( readl(0x400333C) | (v8 << 25) , 0x400333C );
	writel( readl(0x40033BC) | (v10 << 25) , 0x40033BC );

	writel( readl(0x400343C) | (v12 << 25) , 0x400343C );
	writel( readl(0x40034BC) | (v13 << 25) , 0x40034BC );

	writel( readl(0x4003100) | 0x4000000u , 0x4003100 );

  _usdelay(1);
  dram_tpr10 = para->dram_tpr10;
  for ( n = 67121728; n != 67121788; n += 4 )
{
//    *(_DWORD *)n |= (uint8_t)dram_tpr10 >> 4 << 8;
	writel( readl( n ) | ( (uint8_t)dram_tpr10 >> 4 << 8 ) , n );

}

//  MEMORY[0x4003218] |= (dram_tpr10 & 0xF) << 8;
//  MEMORY[0x400321C] |= dram_tpr10 & 0xF00;
//  MEMORY[0x4003280] |= (uint16_t)dram_tpr10 >> 12 << 8;

	writel( readl(0x4003218) | ((dram_tpr10 & 0xF) << 8) , 0x4003218 );
	writel( readl(0x400321C) | (dram_tpr10 & 0xF00) , 0x400321C );
	writel( readl(0x4003280) | ((uint16_t)dram_tpr10 >> 12 << 8) , 0x4003280 );

}