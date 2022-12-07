#include "dram_base.h"

unsigned int auto_scan_dram_type(__dram_para_t *para)
{
  unsigned int dram_tpr13; // r6
  unsigned int v3; // r5
  unsigned int dram_para1; // r8
  unsigned int dram_para2; // r7
  unsigned int result; // r0

  dram_tpr13 = para->dram_tpr13;
  v3 = 1 - para->dram_clk;
  dram_para1 = para->dram_para1;
  if ( para->dram_clk > 1 )
    v3 = 0;
  para->dram_para1 = 11534512;
  dram_para2 = para->dram_para2;
  para->dram_para2 = 0;
  para->dram_tpr13 = dram_tpr13 | 5;
  if ( v3 )
    para->dram_clk = 24 * LOBYTE(para->dram_tpr7);
  para->dram_type = 7;
  if ( para->dram_clk <= 0x294 )
  {
    para->dram_zq = 3881979;
  }
  else
  {
    para->dram_zq = 4013563;
    para->dram_tpr3 = -1266844266;
  }
  para->dram_tpr10 = 8;
  para->dram_tpr11 = 1145307136;
  para->dram_tpr12 = 13107;
  para->dram_mr3 = 2;
  result = dram_vol_set(para);
  if ( result )
  {
    mctl_core_init(para);
    if ( dqs_gate_detect(para) )
      goto LABEL_21;
    if ( v3 )
      para->dram_clk = 24 * BYTE1(para->dram_tpr7);
    para->dram_type = 6;
    para->dram_zq = 3881977;
    para->dram_tpr10 = 8;
    para->dram_tpr11 = 1145307136;
    para->dram_tpr12 = 13107;
    para->dram_mr3 = 2;
    mctl_core_init(para);
    if ( dqs_gate_detect(para) )
      goto LABEL_21;
    if ( v3 )
      para->dram_clk = 24 * BYTE2(para->dram_tpr7);
    para->dram_type = 3;
    para->dram_zq = 3881979;
    para->dram_tpr10 = 8;
    para->dram_tpr11 = 1413742592;
    para->dram_tpr12 = 13364;
    para->dram_mr1 = 64;
    result = dram_vol_set(para);
    if ( result )
    {
      mctl_core_init(para);
      if ( dqs_gate_detect(para) )
        goto LABEL_21;
      if ( v3 )
        para->dram_clk = 24 * HIBYTE(para->dram_tpr7);
      para->dram_type = 2;
      para->dram_zq = 3881977;
      para->dram_tpr10 = 0;
      para->dram_tpr11 = 0;
      para->dram_tpr12 = 0;
      para->dram_mr1 = 64;
      result = dram_vol_set(para);
      if ( result )
      {
        mctl_core_init(para);
        result = dqs_gate_detect(para);
        if ( result )
        {
LABEL_21:
          result = 1;
          para->dram_tpr13 = dram_tpr13;
          para->dram_para1 = dram_para1;
          para->dram_para2 = dram_para2;
        }
      }
    }
  }
  return result;
}
