#include "dram_base.h"

unsigned int mctl_sys_init(__dram_para_t *para)
{
  unsigned int v2; // r0
  unsigned int dram_tpr9; // r3
  unsigned int v4; // r0
  unsigned int v5; // r0
  unsigned int v6; // r3

//  MEMORY[0x3001540] &= ~0x80000000;
//  MEMORY[0x3001540] &= ~0x40000000u;
//  MEMORY[0x300180C] &= ~1u;
//  MEMORY[0x300180C] &= ~0x10000u;

//  MEMORY[0x3001010] &= ~0x80000000;
//  MEMORY[0x3001010] |= 0x40000000u;
//  MEMORY[0x3001018] &= ~0x80000000;
//  MEMORY[0x3001018] |= 0x40000000u;

//  MEMORY[0x3001800] &= ~0x40000000u;

	writel( readl(0x3001540) & ~0x80000000 , 0x3001540 );
	writel( readl(0x3001540) & ~0x40000000u , 0x3001540 );
	writel( readl(0x300180C) & ~1u , 0x300180C );
	writel( readl(0x300180C) & ~0x10000u , 0x300180C );

	writel( readl(0x3001010) & ~0x80000000 , 0x3001010 );
	writel( readl(0x3001010) | 0x40000000u , 0x3001010 );
	writel( readl(0x3001018) & ~0x80000000 , 0x3001018 );
	writel( readl(0x3001018) | 0x40000000u , 0x3001018 );

	writel( readl(0x3001800) & ~0x40000000u , 0x3001800 );


  _usdelay(100);
  if ( (para->dram_tpr13 & 0x40) != 0 )
  {
    v2 = ccm_set_pll_ddr_clk(1u, para);
//    MEMORY[0x3001800] = MEMORY[0x3001800] & 0xFCFFFFFF | 0x1000000;

	writel( readl(0x3001800) & 0xFCFFFFFF | 0x1000000 , 0x3001800 );

    dram_tpr9 = para->dram_tpr9;
    para->dram_clk = v2 >> 1;
    if ( dram_tpr9 )
    {
      v4 = 0;
LABEL_6:
      para->dram_tpr9 = ccm_set_pll_ddr_clk(v4, para) >> 1;
    }
  }
  else
  {
    v5 = ccm_set_pll_ddr_clk(0, para);
//    MEMORY[0x3001800] &= 0xFCFFFFFF;

	writel( readl(0x3001800) & 0xFCFFFFFF , 0x3001800 );

    v6 = para->dram_tpr9;
    para->dram_clk = v5 >> 1;
    if ( v6 )
    {
      v4 = 1;
      goto LABEL_6;
    }
  }
  _usdelay(1000);
//  MEMORY[0x3001800] = MEMORY[0x3001800] & 0xF7FFFFFC | 0x8000000;
//  MEMORY[0x300180C] |= 0x10000u;
//  MEMORY[0x300180C] |= 1u;

	writel( readl(0x3001800) & 0xF7FFFFFC | 0x8000000 , 0x3001800 );
	writel( readl(0x300180C) | 0x10000u , 0x300180C );
	writel( readl(0x300180C) | 1u , 0x300180C );

  dram_disable_all_master();
//  MEMORY[0x3001540] |= 0x40000000u;
//  MEMORY[0x3001540] |= 0x80000000;
//  MEMORY[0x3001800] |= 0x40000000u;

	writel( readl(0x3001540) | 0x40000000u , 0x3001540 );
	writel( readl(0x3001540) | 0x80000000 , 0x3001540 );
	writel( readl(0x3001800) | 0x40000000u , 0x3001800 );

  _usdelay(5);

//  MEMORY[0x400300C] = 0x8000;

	writel( 0x8000 , 0x400300C );

  _usdelay(10);
  return 0;
}