#include "dram_base.h"

unsigned int init_DRAM(int type, __dram_para_t *para)
{
  unsigned int v3; // r0
  unsigned int dram_size; // r5
  signed int dram_para2; // r5
  unsigned int v6; // r1
  unsigned int dram_tpr13; // r2

  printf("DRAM VERSION IS V2_76\n");

//  MEMORY[0x7010310] |= 0x100u;
//  MEMORY[0x7010318] &= 0xFFFFFFC0;

	writel( readl( 0x7010310 ) | 0x100u , 0x7010310 );
	writel( readl( 0x7010318 ) & 0xFFFFFFC0 , 0x7010318 );

// Skip dram_vol_set
//  v3 = dram_vol_set(para);
//  if ( !v3 )
//    return v3;

  if ( (para->dram_tpr13 & 1) == 0 )
  {
    v3 = auto_scan_dram_config(para);
    if ( !v3 )
      return v3;
  }
  printf("DRAM CLK =%d MHZ\n", para->dram_clk);
  printf("DRAM Type =%d (3:DDR3,4:DDR4,6:LPDDR2,7:LPDDR3)\n", para->dram_type);
  printf("DRAM zq value: %x\n", para->dram_zq);
  write_level_flag = 1;
  dram_size = mctl_core_init(para);
  write_level_flag = 0;
//  printf("IPRD=%x--PGCR0=%x--PLL=%x\n", MEMORY[0x40057A0], MEMORY[0x4005034], MEMORY[0x3001010]);
  printf("IPRD=%x--PGCR0=%x--PLL=%x\n", readl( 0x40057A0 ), readl( 0x4005034 ), readl( 0x3001010 ) );
  if ( dram_size )
  {
    dram_para2 = para->dram_para2;
    if ( dram_para2 >= 0 )
    {
      dram_size = DRAMC_get_dram_size(para);
      v6 = dram_size;
      if ( dram_size >= 0xC00 )
        dram_size = 3072;
      printf("Actual DRAM SIZE =%d M\n", v6);
      para->dram_para2 = LOWORD(para->dram_para2) | (dram_size << 16);
    }
    else
    {
      dram_size = HIWORD(dram_para2) & 0x7FFF;
    }
    printf("DRAM SIZE =%d M,para1 = %x,para2 = %x\n", dram_size, para->dram_para1, para->dram_para2);
//    MEMORY[0x4002000] = MEMORY[0x4002000] & 0xFFFFFF0F | (16 * (dram_size >> 8));

	writel( readl( 0x4002000 ) & 0xFFFFFF0F | (16 * (dram_size >> 8))  , 0x4002000 ); 

    if ( (para->dram_tpr13 & 0x8000000) == 0 )
      set_master_priority();
    if ( dramc_simple_wr_test(dram_size, 0x1000u) )
    {
      return 0;
    }
    else
    {
      dram_tpr13 = para->dram_tpr13;
      if ( (dram_tpr13 & 0x4001) != 0 && para->dram_type == 7 && (dram_tpr13 & 0x40000000) == 0 )
      {
        gate_delay_save(para);
        para->dram_tpr13 |= 0x40000000u;
      }
    }
  }
  else
  {
    printf("DRAM initial error : 1 !\n");
  }
  return dram_size;
}