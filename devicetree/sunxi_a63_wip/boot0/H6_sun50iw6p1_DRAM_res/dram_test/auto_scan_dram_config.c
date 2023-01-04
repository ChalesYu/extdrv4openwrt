#include "dram_base.h"

unsigned int auto_scan_dram_config(__dram_para_t *para)
{
  unsigned int v2; // r5
  unsigned int dram_clk; // r5
  bool v4; // cc
  int v5; // r8
  unsigned int dram_tpr13; // r3

        printf("do auto_scan_dram_type !\n");
  if ( (para->dram_tpr13 & 0x2000) != 0 || (v2 = auto_scan_dram_type(para)) != 0 )
  {
    dram_clk = para->dram_clk;
    v4 = para->dram_clk > 0x1E0;
    v5 = write_level_flag;
    write_level_flag = 0;
    if ( v4 )      para->dram_clk = dram_clk >> 1;

    printf("do auto_scan_dram_rank_width !\n");
    if ( (para->dram_tpr13 & 0x4000) != 0 || auto_scan_dram_rank_width(para) )
    {
      write_level_flag = v5;
      para->dram_clk = dram_clk;

      printf("do auto_scan_dram_size !\n");
      v2 = auto_scan_dram_size(para);
      if ( v2 )
      {
        dram_tpr13 = para->dram_tpr13;
        if ( (dram_tpr13 & 0x8000) == 0 )
          para->dram_tpr13 = dram_tpr13 | 0x6003;
        return 1;
      }
      else
      {
        printf("scan dram size fail !\n");
      }
    }
    else
    {
      v2 = 0;
      printf("scan dram rank&width fail !\n");
    }
  }
  else
  {
    printf("scan dram type fail !\n");
  }
  return v2;
}