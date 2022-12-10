#include "dram_base.h"

void phy_hard_reset()
{
  int v0; // r5

//  MEMORY[0x4005010] &= ~0x4000000u;

	writel( readl( 0x4005010 ) & ~0x4000000u , 0x4005010 );

//  v0 = MEMORY[0x4005010] | 0x4000000;

  v0 = readl( 0x4005010 ) | 0x4000000;

  _usdelay(0xAu);
//  MEMORY[0x4005010] = v0;

	writel( v0 , 0x4005010 );

  _usdelay(0xAu);
}
