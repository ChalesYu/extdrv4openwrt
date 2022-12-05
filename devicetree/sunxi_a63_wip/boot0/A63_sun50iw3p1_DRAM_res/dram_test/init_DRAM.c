#include "dram_base.h"

int init_DRAM(int type, __dram_para_t *para)
{
  unsigned int dram_size; // r5
  int v4; // r0
  int v5; // r1
  signed int dram_para2; // r5
  unsigned int v7; // r1
  unsigned int dram_tpr8; // r2
  const char *v9; // r0
  unsigned int dram_tpr13; // r3
  unsigned int v11; // r1
  unsigned int v12; // r1

//  MEMORY[0x7010310] |= 0x100u;
//  MEMORY[0x7010318] = 0;
  writel ( ( readl(0x7010310) | 0x100u) , 0x7010310);
  writel (  0 , 0x7010318);

  _usdelay(10);

//  dram_size = bond_id_check();

// MUST let bond_id_check return 1
// Add
  dram_size = 1;


  if ( dram_size )
  {
    printf("chip id check OK\n");
//    if ( ((para->dram_tpr13 & 0x2000) == 0 || (v4 = dram_vol_set(para)) != 0)
//      && ((para->dram_tpr13 & 1) != 0 || (v4 = auto_scan_dram_config(para)) != 0) )
//  disable auto_scan_dram_config func temporary
//  to avoid hang
if (1)
    {
      printf("DRAM BOOT DRIVE INFO: %s\n", "V0.573");
      printf("DRAM CLK = %d MHZ\n", para->dram_clk);
      printf("DRAM Type = %d (2:DDR2,3:DDR3,6:LPDDR2,7:LPDDR3)\n", para->dram_type);
      printf("DRAM ZQ value: 0x%x\n", para->dram_zq);
      dram_size = mctl_core_init(para);
      if ( dram_size )
      {
        dram_para2 = para->dram_para2;
        if ( dram_para2 >= 0 )
        {
          dram_size = DRAMC_get_dram_size();
          v7 = dram_size;
          if ( dram_size >= 0xC00 )
            dram_size = 3072;
          printf("DRAM SIZE =%d M\n", v7);
          para->dram_para2 = LOWORD(para->dram_para2) | (dram_size << 16);
        }
        else
        {
          dram_size = HIWORD(dram_para2) & 0x7FFF;
        }
        if ( (para->dram_tpr13 & 0x40000000) != 0 )
        {
          dram_tpr8 = para->dram_tpr8;
          v5 = 268435968;
          v9 = "Enable Auto SR\n";
          if ( !dram_tpr8 )
            dram_tpr8 = 268435968;
//          MEMORY[0x40030A0] = dram_tpr8;
//          MEMORY[0x400309C] = 1034;
//          MEMORY[0x4003004] |= 1u;

		writel ( dram_tpr8 , 0x40030A0);
		writel ( 1034 , 0x400309C);
		writel ( ( readl(0x4003004) | 1u) , 0x4003004);

        }
        else
        {
          v9 = "Disable Auto SR\n";

//          MEMORY[0x40030A0] = HIWORD(MEMORY[0x40030A0]) << 16;
//          MEMORY[0x4003004] &= ~1u;

		writel ( (  HIWORD(readl(0x40030A0)) << 16  ) , 0x40030A0);
		writel ( ( (readl(0x4003004)) & (~1u) ) , 0x4003004);

        }
        printf(v9, v5);
        dram_tpr13 = para->dram_tpr13;
        if ( (dram_tpr13 & 0x200) != 0 || para->dram_type == 6 )
{
//          v11 = MEMORY[0x4003100] & 0xFFFF0FFF | 0x5000;

          v11 = (readl(0x4003100) & 0xFFFF0FFF) | 0x5000;

}
        else
{
//          v11 = MEMORY[0x4003100] & 0xFFFF0FFF;

          v11 = readl(0x4003100) & 0xFFFF0FFF;

}

//        MEMORY[0x4003100] = v11;
//        MEMORY[0x4003140] |= 0x80000000;

	writel( v11 , 0x4003100 );
	writel( (readl(0x4003140) | 0x80000000 ) , 0x4003140 );

        if ( (dram_tpr13 & 0x100) != 0 )
{
//          MEMORY[0x40030B8] |= 0x300u;

	writel( ( readl(0x40030B8) | 0x300u ) , 0x40030B8 );

}
        if ( (dram_tpr13 & 0x4000000) != 0 )
{
//          v12 = MEMORY[0x4003108] & 0xFFFFDFFF;

		v12 = readl(0x4003108) & 0xFFFFDFFF;

}
        else
{
//          v12 = MEMORY[0x4003108] | 0x2000;

		v12 = readl(0x4003108) | 0x2000;

}
//        MEMORY[0x4003108] = v12;

		writel ( v12 , 0x4003108 );

        if ( para->dram_type == 7 )
{
//          MEMORY[0x400307C] = MEMORY[0x400307C] & 0xFFF0FFFF | 0x10000;

		writel ( ( readl(0x400307C) & 0xFFF0FFFF | 0x10000 ) , 0x400307C);

}
        if ( (dram_tpr13 & 0x8000000) == 0 )
        {
          if ( (dram_tpr13 & 0x1000000) != 0 )
            set_master_priority_pad();
          else
            set_master_priority();
        }
        dram_enable_all_master();
// disable dramc_simple_wr_test
        if ( (para->dram_tpr13 & 0x10000000) != 0 && dramc_simple_wr_test(dram_size, 0x1000u) )
          return 0;
      }
      else
      {
        printf("DRAM initial error : 1 !\n");
      }
    }
    else
    {
      return v4;
    }
  }
  else
  {
    printf("ic cant match axp, please check...\n");
  }
  return dram_size;
}