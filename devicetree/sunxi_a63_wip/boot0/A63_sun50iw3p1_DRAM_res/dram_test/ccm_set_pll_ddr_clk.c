#include "dram_base.h"

unsigned int ccm_set_pll_ddr_clk(unsigned int pll, __dram_para_t *para)
{
  unsigned int v3; // r7
  unsigned int v4; // r5
  unsigned int dram_clk; // r0
  unsigned int v6; // r0
  int v7; // r3
  unsigned int v8; // r4
  unsigned int v9; // r3

  v3 = 50336016;
  v4 = 50335760;
  if ( pll )
    v3 = 50336024;
  if ( pll )
    v4 = 50335768;
  if ( ((para->dram_tpr13 >> 6) & 1) == pll )
    dram_clk = para->dram_clk;
  else
    dram_clk = para->dram_tpr9;
  v6 = 2 * dram_clk / 0x18;
  if ( v6 <= 0xB )
    v7 = 12;
  else
    v7 = v6;
  v8 = v6;
//  v9 = *(_DWORD *)v4 & 0x7FFF80FC | 0x80000000 | ((v7 - 1) << 8);
    v9 = readl( v4 ) & 0x7FFF80FC | 0x80000000 | ((v7 - 1) << 8);

//  *(_DWORD *)v4 = v9;
	writel ( v9 , v4 );

  v9 &= ~0x20000000u;
//  *(_DWORD *)v4 = v9;
	writel ( v9 , v4 );

//  *(_DWORD *)v4 = v9 | 0x20000000;
	writel ( v9 | 0x20000000 , v4 );

//  while ( (*(_DWORD *)v4 & 0x10000000) == 0 )
//    ;
  while ( ( readl( v4 ) & 0x10000000) == 0 );

  _usdelay(20);

  if ( (para->dram_tpr13 & 0x800000) != 0 )
    ccm_set_pll_ddr_sscg(para, v4, v3);
  return 24 * v8;
}