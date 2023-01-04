#include "dram_base.h"

void  gate_delay_restore(__dram_para_t *para)
{
  writel( 0 , 0x40054DC );   //  0
  writel( ((uint16_t)para->dram_tpr4 >> 11) | 0x20000 , 0x40057C0 );   //  ((uint16_t)para->dram_tpr4 >> 11) | 0x20000
  writel( (para->dram_tpr4 >> 27) | 0x20000 , 0x40058C0 );   //  (para->dram_tpr4 >> 27) | 0x20000
  writel( ((uint16_t)para->dram_tpr5 >> 11) | 0x20000 , 0x40059C0 );   //  ((uint16_t)para->dram_tpr5 >> 11) | 0x20000
  writel( (para->dram_tpr5 >> 27) | 0x20000 , 0x4005AC0 );   //  (para->dram_tpr5 >> 27) | 0x20000
  writel( para->dram_tpr4 & 0x1FF , 0x4005788 );   //  para->dram_tpr4 & 0x1FF
  writel( HIWORD(para->dram_tpr4) & 0x1FF , 0x4005888 );   //  HIWORD(para->dram_tpr4) & 0x1FF
  writel( para->dram_tpr5 & 0x1FF , 0x4005988 );   //  para->dram_tpr5 & 0x1FF
  writel( HIWORD(para->dram_tpr5) & 0x1FF , 0x4005A88 );   //  HIWORD(para->dram_tpr5) & 0x1FF
  writel( 65537 , 0x40054DC );   //  65537
  writel( ((uint16_t)para->dram_tpr8 >> 11) | 0x20000 , 0x40057C0 );   //  ((uint16_t)para->dram_tpr8 >> 11) | 0x20000
  writel( (para->dram_tpr8 >> 27) | 0x20000 , 0x40058C0 );   //  (para->dram_tpr8 >> 27) | 0x20000
  writel( ((uint16_t)para->dram_tpr9 >> 11) | 0x20000 , 0x40059C0 );   //  ((uint16_t)para->dram_tpr9 >> 11) | 0x20000
  writel( (para->dram_tpr9 >> 27) | 0x20000 , 0x4005AC0 );   //  (para->dram_tpr9 >> 27) | 0x20000
  writel( para->dram_tpr8 & 0x1FF , 0x4005788 );   //  para->dram_tpr8 & 0x1FF
  writel( HIWORD(para->dram_tpr8) & 0x1FF , 0x4005888 );   //  HIWORD(para->dram_tpr8) & 0x1FF
  writel( para->dram_tpr9 & 0x1FF , 0x4005988 );   //  para->dram_tpr9 & 0x1FF
  writel( HIWORD(para->dram_tpr9) & 0x1FF , 0x4005A88 );   //  HIWORD(para->dram_tpr9) & 0x1FF
}
