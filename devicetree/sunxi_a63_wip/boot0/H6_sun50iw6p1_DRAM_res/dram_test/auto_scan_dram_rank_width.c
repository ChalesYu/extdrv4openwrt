#include "dram_base.h"

unsigned int  auto_scan_dram_rank_width(__dram_para_t *para)
{
  unsigned int dram_tpr13; // r5
  unsigned int dram_para1; // r6
  unsigned int v4; // r3
  unsigned int result; // r0

  dram_tpr13 = para->dram_tpr13;
  dram_para1 = para->dram_para1;
  para->dram_tpr13 = dram_tpr13 | 1;
  if ( para->dram_type == 4 )
    v4 = 24759;
  else
    v4 = 8375;
  para->dram_para1 = v4;
  para->dram_para2 = 4096;
  mctl_core_init(para);
  result = dqs_gate_detect(para);
  if ( result )
  {
    result = 1;
    para->dram_tpr13 = dram_tpr13;
    para->dram_para1 = dram_para1;
  }
  return result;
}