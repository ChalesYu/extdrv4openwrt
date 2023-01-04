#include "dram_base.h"

unsigned int mctl_sys_init(__dram_para_t *para)
{
  unsigned int result; // r0

/*
  MEMORY[0x3001540] &= ~0x80000000;
  MEMORY[0x3001540] &= ~0x40000000u;
  MEMORY[0x300180C] &= ~1u;

  MEMORY[0x300180C] &= ~0x10000u;
  MEMORY[0x3001010] &= ~0x80000000;
  MEMORY[0x3001800] &= ~0x40000000u;
*/

	writel( readl( 0x3001540 ) & ~0x80000000 , 0x3001540 );
	writel( readl( 0x3001540 ) & ~0x40000000u , 0x3001540 );
	writel( readl( 0x300180C ) & ~1u , 0x300180C );

	writel( readl( 0x300180C ) & ~0x10000u , 0x300180C );
	writel( readl( 0x3001010 ) & ~0x80000000 , 0x3001010 );
	writel( readl( 0x3001800 ) & ~0x40000000u , 0x3001800 );

  _usdelay(5u);
  ccm_set_pll_ddr_clk(2 * para->dram_clk, 0x3001010u, para);

/*
  MEMORY[0x3001800] &= 0xFCFFFFFF;
  MEMORY[0x3001800] = MEMORY[0x3001800] & 0xF7FFFFFC | 0x8000000;
  MEMORY[0x300180C] |= 0x10000u;
  MEMORY[0x300180C] |= 1u;

  MEMORY[0x4002020] = 0;
  MEMORY[0x4002024] = 0;
  MEMORY[0x4002028] = 0;
  MEMORY[0x3001540] |= 0x40000000u;

  MEMORY[0x3001540] |= 0x80000000;
  MEMORY[0x3001800] |= 0x40000000u;
*/

	writel( readl( 0x3001800 ) & 0xFCFFFFFF , 0x3001800 );
	writel( readl( 0x3001800 ) & 0xF7FFFFFC | 0x8000000 , 0x3001800 );
	writel( readl( 0x300180C ) | 0x10000u , 0x300180C );
	writel( readl( 0x300180C ) | 1u , 0x300180C );

	writel( 0 , 0x4002020 );
	writel( 0 , 0x4002024 );
	writel( 0 , 0x4002028 );
	writel( readl( 0x3001540 ) | 0x40000000u , 0x3001540 );

	writel( readl( 0x3001540 ) | 0x80000000 , 0x3001540 );
	writel( readl( 0x3001800 ) | 0x40000000u , 0x3001800 );


  _usdelay(5u);
  result = 0;

//  MEMORY[0x400300C] = 0x8000;
	writel( 0x8000 , 0x400300C );

  return result;
}