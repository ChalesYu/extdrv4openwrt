#include "dram_base.h"

unsigned int gate_delay_repire(__dram_para_t *para)
{
  unsigned int dram_para2; // r2
  unsigned int v2; // r9
  unsigned int v3; // r6
  unsigned int v4; // r4
  unsigned int v5; // r7
  unsigned int v6; // r1
  unsigned int v7; // r10
  uint16_t *v8; // r3
  int v9; // r2
  int v10; // r5
  int v11; // r0
  int v12; // lr
  int v13; // r0
  unsigned int v14; // r0
  unsigned int v15; // r3
  uint16_t (*v16)[4]; // r1
  unsigned int v17; // r5
  unsigned int v18; // r2
  unsigned int v19; // lr
  _QWORD *v20; // r5
  unsigned int v21; // r8
  unsigned int v22; // r11
  int v23; // r1
  uint16_t gate_delay[4][4]; // [sp+8h] [bp-48h] BYREF
  _QWORD v26[5]; // [sp+28h] [bp-28h] BYREF

  dram_para2 = para->dram_para2;
  if ( (dram_para2 & 0xF000) != 0 )
    v2 = 2;
  else
    v2 = 1;
  if ( (dram_para2 & 1) != 0 )
    v3 = 2;
  else
    v3 = 4;

//  MEMORY[0x4005010] &= ~0x4000000u;

	writel( readl( 0x4005010 ) & ~0x4000000u , 0x4005010 );

  v4 = para->dram_tpr13 & 0x40000000;
  if ( v4 )
  {
    gate_delay_restore(para);
  }
  else
  {
    v5 = 0;
    do
    {
//      LOBYTE(v6) = 0;
	v6 = v6 - LOBYTE(v6);

      v7 = 0;
//      MEMORY[0x40054DC] = v4 | (v4 << 16);

	writel( v4 | (v4 << 16) , 0x40054DC );

      v8 = &gate_delay[0][2];
      v9 = 67131296;
      do
      {
//backup
/*
        v6 = (uint8_t)(v6 + 1);
        *(v8 - 2) = HIWORD(*(_DWORD *)v9) & 0x1FF;
        v10 = *(v8 - 2);
        *(v8 - 1) = *(_DWORD *)(v9 + 32) & 0x1F;
        v11 = *(_DWORD *)(v9 - 24);
        v9 += 256;
        v12 = *(v8 - 1);
        v13 = v11 & 0x1FF;
        *v8 = v13;
        v8 += 4;
        v7 += v13 + v12 * v10;
*/

        v6 = (uint8_t)(v6 + 1);
	writel( HIWORD( readl(v9) ) & 0x1FF , (unsigned int)(v8 - 2) );
        v10 = readl((unsigned int)(v8 - 2));
	writel( readl( v9 + 32 ) & 0x1F , (unsigned int)(v8 - 1) );
        v11 = readl(v9 - 24);
        v9 += 256;
        v12 = readl((unsigned int)(v8 - 1));
        v13 = v11 & 0x1FF;
	writel( v13 ,(unsigned int) v8 );
        v8 += 4;
        v7 += v13 + v12 * v10;

      }
      while ( v6 < v3 );
      v14 = v7 / v3;
      v15 = 0;
      v16 = gate_delay;
      v17 = 0;
      do
      {
        v18 = (*v16)[2] + (*v16)[1] * readw((unsigned int)v16);
        if ( v18 <= v14 )
          v19 = v14 - v18;
        else
          v19 = v18 - v14;
        if ( v19 > v17 )
        {
          v5 = v15;
          if ( v18 <= v14 )
            v17 = v14 - v18;
          else
            v17 = v18 - v14;
        }
        ++v16;
        v15 = (uint8_t)(v15 + 1);
      }
      while ( v15 < v3 );
      v20 = &v26[v5];
      ++v4;

//backup
/*
      v21 = *((unsigned __int16 *)v20 - 16);
      v22 = (v7 - (*((unsigned __int16 *)v20 - 14) + *((unsigned __int16 *)v20 - 15) * v21)) / (v3 - 1);
      *((_WORD *)v20 - 15) = (v22 / v21) & 0x1F;
      v23 = (v22 % v21) & 0x1FF;
      *(_DWORD *)((v5 << 8) + 0x40057C0) = (v22 / v21) & 0x1F | 0x20000;
      *((_WORD *)v20 - 14) = v23;
      *(_DWORD *)((v5 << 8) + 0x4005788) = v23;
*/

      v21 = readl((unsigned int)((uint16_t *)v20 - 16));
      v22 = (v7 - ( readl( (unsigned int)((uint16_t *)v20 - 14)) + readl( (unsigned int)((uint16_t *) v20 - 15) ) * v21)) / (v3 - 1);
	writel(  (v22 / v21) & 0x1F , ( unsigned int)((_WORD *)v20 - 15) );
      v23 = (v22 % v21) & 0x1FF;
	writel( (v22 / v21) & 0x1F | 0x20000 , ((v5 << 8) + 0x40057C0) );
	writel( v23 , ( unsigned int)((_WORD *)v20 - 14) );
	writel( v23 , ((v5 << 8) + 0x4005788) );


    }
    while ( (uint8_t)v4 < v2 );
  }
//  MEMORY[0x4005010] |= 0x4000000u;

	writel( readl( 0x4005010 ) | 0x4000000u , 0x4005010 );

  _usdelay(1u);
  return 1;
}
