#include "dram_base.h"

unsigned int auto_scan_dram_config(__dram_para_t *para)
{
  unsigned int v2; // r5
  unsigned int dram_tpr13; // r3


        printf("do auto_scan_dram_type !\n");

  if ( (para->dram_tpr13 & 0x2000) != 0 || (v2 = auto_scan_dram_type(para)) != 0 )
  {

        printf("do auto_scan_dram_rank_width !\n");

    if ( (para->dram_tpr13 & 0x4000) != 0 || (v2 = auto_scan_dram_rank_width(para)) != 0 )
    {

        printf("do auto_scan_dram_size !\n");

      if ( (para->dram_tpr13 & 1) != 0 || (v2 = auto_scan_dram_size(para)) != 0 )
      {
        dram_tpr13 = para->dram_tpr13;
        if ( (dram_tpr13 & 0x8000) == 0 )
          para->dram_tpr13 = dram_tpr13 | 0x6003;
        return 1;
      }
      else
      {
        printf("[ERROR DEBUG] auto scan dram size fail !\n");
      }
    }
    else
    {
      printf("[ERROR DEBUG] auto scan dram rank&width fail !\n");
    }
  }
  else
  {
    printf("[ERROR DEBUG] auto scan dram type fail !\n");
  }
  return v2;
}