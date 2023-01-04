#include "dram_base.h"

unsigned int auto_scan_dram_type(__dram_para_t *para)
{
  unsigned int dram_tpr13; // r6
  unsigned int dram_clk; // r5
  unsigned int dram_para1; // r8
  unsigned int dram_para2; // r7
  unsigned int v6; // r3
  unsigned int result; // r0

  dram_tpr13 = para->dram_tpr13;
  dram_clk = para->dram_clk;
  dram_para1 = para->dram_para1;
  para->dram_tpr13 = dram_tpr13 | 1;
  para->dram_para1 = 8375;
  dram_para2 = para->dram_para2;
  para->dram_para2 = 1;
  if ( !dram_clk )
    para->dram_clk = 12 * LOBYTE(para->dram_tpr7);

  para->dram_type = 7;
//  if ( MEMORY[0x3006100] == 7 )
  if ( readl( 0x3006100 ) == 7 )
  {
    para->dram_tpr10 = 160;
    para->dram_tpr11 = 0x200000;
    v6 = 8738;
LABEL_7:
    para->dram_tpr12 = v6;
    goto LABEL_8;
  }
//  if ( MEMORY[0x3006100] == 3 )
  if ( readl( 0x3006100 ) == 3 )
  {
    para->dram_tpr10 = 0;
    para->dram_tpr11 = 1714749440;
    v6 = 268435505;
    goto LABEL_7;
  }
LABEL_8:
  result = dram_vol_set(para);
  if ( result )
  {
    if ( mctl_core_init(para) )
      goto LABEL_32;
    para->dram_clk = dram_clk;
    para->dram_para1 = 8375;
    if ( !dram_clk )
      para->dram_clk = 12 * BYTE1(para->dram_tpr7);
    para->dram_type = 6;
    para->dram_tpr10 = 0;
    para->dram_tpr11 = 0;
    para->dram_tpr12 = 0;
    if ( mctl_core_init(para) )
      goto LABEL_32;
    para->dram_clk = dram_clk;
    para->dram_para1 = 24759;
    if ( !dram_clk )
      para->dram_clk = 12 * HIBYTE(para->dram_tpr7);
    para->dram_type = 4;
//   if ( MEMORY[0x3006100] == 7 )
   if ( readl( 0x3006100 ) == 7 )
    {
      para->dram_tpr10 = 0;
//      if ( MEMORY[0x300621C] >> 5 == 3 )
      if ( ( readl( 0x300621C ) >> 5 ) == 3 )
      {
        para->dram_tpr11 = 1379074048;
        para->dram_tpr13 |= 0x100u;
      }
      else
      {
        para->dram_tpr11 = 288423936;
      }
      para->dram_tpr12 = 0;
    }
//    else if ( MEMORY[0x3006100] == 3 )
    else if ( readl( 0x3006100 ) == 3 )
    {
      para->dram_tpr10 = 4;
      para->dram_tpr11 = 1127415808;
      para->dram_tpr12 = 587202576;
      para->dram_tpr13 |= 0x100u;
    }
    para->dram_mr1 = 513;
    axp_set_aldo3(2500, 1);
    if ( mctl_core_init(para) )
      goto LABEL_32;
    para->dram_clk = dram_clk;
    para->dram_para1 = 8375;
    if ( !dram_clk )
      para->dram_clk = 12 * BYTE2(para->dram_tpr7);
    para->dram_type = 3;
//    if ( MEMORY[0x3006100] == 7 )
    if ( readl( 0x3006100 ) == 7 )
    {
      para->dram_tpr10 = 0;
      para->dram_tpr11 = 0;
      para->dram_tpr12 = 32;
    }
//    else if ( MEMORY[0x3006100] == 3 )
    else if ( readl( 0x3006100 ) == 3 )
    {
      para->dram_clk = dram_clk;
      para->dram_zq = 3881977;
      para->dram_tpr10 = 13;
      para->dram_tpr11 = 587202578;
      para->dram_tpr12 = 0;
      if ( !dram_clk )
        para->dram_clk = 792;
    }
    para->dram_mr1 = 64;
    result = dram_vol_set(para);
    if ( result )
    {
      result = mctl_core_init(para);
      if ( result )
      {
LABEL_32:
        result = 1;
        para->dram_tpr13 = dram_tpr13;
        para->dram_para1 = dram_para1;
        para->dram_para2 = dram_para2;
      }
    }
  }
  return result;
}