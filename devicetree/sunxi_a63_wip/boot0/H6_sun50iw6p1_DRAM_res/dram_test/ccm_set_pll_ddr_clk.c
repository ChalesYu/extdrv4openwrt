#include "dram_base.h"

void ccm_set_pll_ddr_clk(unsigned int pll_clk, unsigned int PLL_ADDR, __dram_para_t *para)
{
  unsigned int v4; // r6

//  *(_DWORD *)PLL_ADDR &= ~0x20000000u;
	writel( readl( PLL_ADDR ) & ~0x20000000u , PLL_ADDR );

//  v4 = *(_DWORD *)PLL_ADDR & 0xFFFF00FC | ((pll_clk / 0x18 - 1) << 8);
  v4 = readl( PLL_ADDR ) & 0xFFFF00FC | ((pll_clk / 0x18 - 1) << 8);

//  *(_DWORD *)PLL_ADDR = v4;
	writel( v4 , PLL_ADDR );

//  *(_DWORD *)PLL_ADDR = v4 | 0x80000000;
	writel( v4 | 0x80000000 , PLL_ADDR );

  ccm_set_pll_ddr0_sscg(para);

//  *(_DWORD *)PLL_ADDR = v4 | 0xA0000000;
	writel( v4 | 0xA0000000 , PLL_ADDR );

//  while ( (*(_DWORD *)PLL_ADDR & 0x10000000) == 0 )
//    ;

  while ( ( readl( PLL_ADDR ) & 0x10000000) == 0 );

  _usdelay(5u);

}