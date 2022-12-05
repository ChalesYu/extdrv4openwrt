#include "dram_base.h"

unsigned int dqs_gate_detect(__dram_para_t *para)
{
  int v1; // r1
  int v2; // r4
  int v3; // r6
  int v4; // r5
  unsigned int v5; // r3
  unsigned int result; // r0

  if ( (readl(0x4003010) & 0x400000) != 0 )
  {
    v1 = HIBYTE(readl(0x4003348)) & 3;
    v2 = HIBYTE(readl(0x40033C8)) & 3;
    v3 = HIBYTE(readl(0x4003448)) & 3;
    v4 = HIBYTE(readl(0x40034C8)) & 3;
    if ( v1 == 2 )
    {
      if ( v2 == 2 )
      {
        v5 = para->dram_para2 & 0xFFFF0FF0;
        if ( v3 == 2 && v4 == 2 )
          goto LABEL_11;
        goto LABEL_10;
      }
    }
    else if ( !v1 && !v2 )
    {
      v5 = para->dram_para2 & 0xFFFFEFF0 | 0x1000;
LABEL_10:
      v5 |= 1u;
LABEL_11:
      para->dram_para2 = v5;
      return 1;
    }
    result = para->dram_tpr13 & 0x20000000;
    if ( result )
    {
      printf("DX0 state:%d\n", v1);
      printf("DX1 state:%d\n", v2);
      printf("DX2 state:%d\n", v3);
      printf("DX3 state:%d\n", v4);
      return 0;
    }
  }
  else
  {
    para->dram_para2 = para->dram_para2 & 0xFFFFEFF0 | 0x1000;
    return 1;
  }
  return result;
}