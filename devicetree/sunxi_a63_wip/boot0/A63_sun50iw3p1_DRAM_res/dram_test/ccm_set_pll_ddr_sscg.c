#include "dram_base.h"

unsigned int  ccm_set_pll_ddr_sscg(__dram_para_t *para, unsigned int PLL_CTRL, unsigned int PLL_PAT)
{
  int v3; // r3
  unsigned int result; // r0


//  if ( (*(_DWORD *)PLL_CTRL & 2) != 0 )
//    *(_DWORD *)PLL_PAT |= 0x80000u;
  if ( ( readl( PLL_CTRL ) & 2) != 0 )
	writel( readl( PLL_PAT ) | 0x80000u , PLL_PAT );


  switch ( (para->dram_tpr13 >> 20) & 7 )
  {
    case 1u:
      v3 = -460927796;
      break;
    case 2u:
      v3 = -385443431;
      break;
    case 3u:
      v3 = -309959066;
      break;
    case 5u:
      v3 = -175767552;
      break;
    default:
      v3 = -234474701;
      break;
  }
//  *(_DWORD *)PLL_PAT = v3;
	writel( v3 , PLL_PAT );

  result = 0;
//  *(_DWORD *)PLL_CTRL |= 0x1000000u;
	writel( readl( PLL_CTRL ) | 0x1000000u , PLL_CTRL );

  return result;
}