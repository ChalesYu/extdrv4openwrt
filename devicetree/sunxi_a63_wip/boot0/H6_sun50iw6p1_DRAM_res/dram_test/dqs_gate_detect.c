#include "dram_base.h"

unsigned int dqs_gate_detect(__dram_para_t *para)
{
  unsigned int v1; // r3

//  if ( (MEMORY[0x4005034] & 0x400000) == 0 )

	  if ( (readl( 0x4005034 ) & 0x400000) == 0 )

  {
    v1 = para->dram_para2 & 0xFFFFEFF0 | 0x1000;
LABEL_9:
    para->dram_para2 = v1;
    return 1;
  }
//  if ( (MEMORY[0x40057D0] & 3) == 2 )
  if ( (readl( 0x40057D0 ) & 3) == 2 )
  {
//    if ( (MEMORY[0x40058D0] & 3) == 2 )
    if ( (readl( 0x40058D0 ) & 3) == 2 )
    {
      v1 = para->dram_para2 & 0xFFFF0FF0;
//      if ( (MEMORY[0x40059D0] & 3) == 2 && (MEMORY[0x4005AD0] & 3) == 2 )
      if ( (readl( 0x40059D0 ) & 3) == 2 && (readl( 0x4005AD0 ) & 3) == 2 )
        goto LABEL_9;
      goto LABEL_8;
    }
    return 0;
  }
//  if ( (MEMORY[0x40057D0] & 3) != 0 )
  if ( (readl( 0x40057D0 ) & 3) != 0 )
    return 0;
//  if ( (MEMORY[0x40058D0] & 3) == 0 )
  if ( (readl( 0x40058D0 ) & 3) == 0 )
  {
    v1 = para->dram_para2 & 0xFFFFEFF0 | 0x1000;
LABEL_8:
    v1 |= 1u;
    goto LABEL_9;
  }
//  return MEMORY[0x40057D0] & 3;
  return ( readl( 0x40057D0 ) & 3 );
}