#include "dram_base.h"

void mctl_com_init(__dram_para_t *para)
{
  unsigned int dram_para2; // r3
  int v2; // r12
  int v3; // r5
  unsigned int dram_tpr13; // r1
  bool v5; // cc
  unsigned int v6; // r2
  unsigned int v7; // r7
  unsigned int dram_para1; // r6
  int v9; // r3
  int v10; // r5
  char v11; // r4
  unsigned int v12; // r1
  unsigned int v13; // r2
  int v14; // r2
  int v15; // r2
  unsigned int dram_tpr4; // r3

  dram_para2 = para->dram_para2;
  v2 = dram_para2 & 1;
  if ( (dram_para2 & 1) != 0 )
    v3 = 0;
  else
    v3 = 4096;
  dram_tpr13 = para->dram_type - 6;
  v5 = dram_tpr13 > 1;
//  v6 = MEMORY[0x4002000] & 0xFF000FFF | 0x400000 | ((para->dram_type & 7) << 16) | v3;

	v6 = readl(0x4002000) & 0xFF000FFF | 0x400000 | ((para->dram_type & 7) << 16) | v3;

  if ( dram_tpr13 <= 1 )
    v6 |= 0x80000u;
  else
    dram_tpr13 = para->dram_tpr13;
  if ( v5 )
    v6 |= ((dram_tpr13 >> 5) & 1) << 19;
//  MEMORY[0x4002000] = v6;

	writel( v6 , 0x4002000 );

  if ( (dram_para2 & 0x100) != 0 )
  {
    if ( (uint16_t)dram_para2 >> 12 == 1 )
      v7 = 2;
    else
      v7 = 1;
  }
  else
  {
    v7 = 1;
  }
  dram_para1 = para->dram_para1;
  v9 = (dram_para2 >> 12) & 3;
  v10 = 67117056;
  v11 = 12;
  v12 = 0;
  do
  {
//    v13 = *(_DWORD *)v10 & 0xFFFFF000 | v9 | (4 * ((dram_para1 >> v11) & 1)) | (uint8_t)(16 * ((dram_para1 >> (v11 - 8)) - 1));

    v13 = readl( v10 ) & 0xFFFFF000 | v9 | (4 * ((dram_para1 >> v11) & 1)) | (uint8_t)(16 * ((dram_para1 >> (v11 - 8)) - 1));

    switch ( (dram_para1 >> (16 * v12)) & 0xF )
    {
      case 1u:
        v14 = v13 | 0x700;
        break;
      case 2u:
        v14 = v13 | 0x800;
        break;
      case 4u:
        v14 = v13 | 0x900;
        break;
      case 8u:
        v14 = v13 | 0xA00;
        break;
      default:
        v14 = v13 | 0x600;
        break;
    }
    ++v12;
    v11 += 16;
//    *(_DWORD *)v10 = v14;
	writel( v14 , v10 );

    v10 += 4;
  }
  while ( v12 < v7 );
  v15 = 513;

//  if ( (MEMORY[0x4002000] & 1) != 0 ) v15 = 771;
//  MEMORY[0x4003120] = v15;

	if ( ( readl(0x4002000) & 1) != 0 ) v15 = 771;
	writel( v15 , 0x4003120 );

  if ( v2 )
  {
//    MEMORY[0x4003444] = 0;
//    MEMORY[0x40034C4] = 0;

	writel( 0 , 0x4003444 );
	writel( 0 , 0x40034C4 );

  }
  dram_tpr4 = para->dram_tpr4;
  if ( dram_tpr4 )
  {
//    MEMORY[0x4002000] |= (para->dram_tpr4 & 3) << 25;
//    MEMORY[0x4002004] |= ((dram_tpr4 >> 2) & 0x1FF) << 12;

	writel( readl(0x4002000) | ( (para->dram_tpr4 & 3) << 25 ) , 0x4002000 );
	writel( readl(0x4002004) | ( ((dram_tpr4 >> 2) & 0x1FF) << 12 ) , 0x4002004 );

  }
}