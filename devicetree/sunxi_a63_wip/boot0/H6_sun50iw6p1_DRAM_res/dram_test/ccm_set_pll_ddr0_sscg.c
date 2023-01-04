#include "dram_base.h"

void ccm_set_pll_ddr0_sscg(__dram_para_t *para)
{
  int v1; // r2

  switch ( (para->dram_tpr13 >> 20) & 7 )
  {
    case 0u:
      goto LABEL_8;
    case 1u:
      v1 = -460927796;
      goto LABEL_7;
    case 2u:
      v1 = -385443431;
      goto LABEL_7;
    case 3u:
      v1 = -309959066;
      goto LABEL_7;
    case 5u:
      v1 = -175767552;
      goto LABEL_7;
    default:
      v1 = -234474701;
LABEL_7:
//      MEMORY[0x3001110] = v1;
	writel( v1 , 0x3001110 );

LABEL_8:
//      MEMORY[0x3001010] |= 0x1000000u;
	writel( readl(0x3001010) | 0x1000000u , 0x3001010 );	

      return;
  }
}