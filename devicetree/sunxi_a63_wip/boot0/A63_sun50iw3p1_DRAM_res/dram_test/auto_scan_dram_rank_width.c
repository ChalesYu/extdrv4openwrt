#include "dram_base.h"

unsigned int auto_scan_dram_rank_width(__dram_para_t *para)
{
  unsigned int dram_para1; // r6
  unsigned int dram_tpr13; // r5
  unsigned int result; // r0

  dram_para1 = para->dram_para1;
  para->dram_para1 = 11534512;
  dram_tpr13 = para->dram_tpr13;
  para->dram_para2 = para->dram_para2 & 0xFFFFEFF0 | 0x1000;
  para->dram_tpr13 = dram_tpr13 | 5;
  mctl_core_init(para);
  if ( ( readl(0x4003010) & 0x100000) != 0 )
    return 0;
  result = dqs_gate_detect(para);
  if ( result )
  {
    para->dram_tpr13 = dram_tpr13;
    result = 1;
    para->dram_para1 = dram_para1;
  }
  return result;
}