#include "dram_base.h"

void  gate_delay_save(__dram_para_t *para)
{
//  para->dram_tpr4 = (MEMORY[0x40058C0] << 27) | MEMORY[0x4005788] & 0x1FF | (MEMORY[0x4005888] << 16) & 0x1FFFFFF | (uint16_t)(MEMORY[0x40057C0] << 11);
//  para->dram_tpr5 = (MEMORY[0x4005AC0] << 27) | MEMORY[0x4005988] & 0x1FF | (MEMORY[0x4005A88] << 16) & 0x1FFFFFF | (uint16_t)(MEMORY[0x40059C0] << 11);

  para->dram_tpr4 = (readl( 0x40058C0 ) << 27) | readl( 0x4005788 ) & 0x1FF | (readl( 0x4005888 ) << 16) & 0x1FFFFFF | (uint16_t)(readl( 0x40057C0 ) << 11);
  para->dram_tpr5 = (readl( 0x4005AC0 ) << 27) | readl( 0x4005988 ) & 0x1FF | (readl( 0x4005A88 ) << 16) & 0x1FFFFFF | (uint16_t)(readl( 0x40059C0 ) << 11);


//  MEMORY[0x40054DC] = 65537;
	writel( 65537 , 0x40054DC );

//  para->dram_tpr8 = (MEMORY[0x40058C0] << 27) | MEMORY[0x4005788] & 0x1FF | (MEMORY[0x4005888] << 16) & 0x1FFFFFF | (uint16_t)(MEMORY[0x40057C0] << 11);
//  para->dram_tpr9 = (MEMORY[0x4005AC0] << 27) | MEMORY[0x4005988] & 0x1FF | (MEMORY[0x4005A88] << 16) & 0x1FFFFFF | (uint16_t)(MEMORY[0x40059C0] << 11);

  para->dram_tpr8 = (readl( 0x40058C0 ) << 27) | readl( 0x4005788 ) & 0x1FF | (readl( 0x4005888 ) << 16) & 0x1FFFFFF | (uint16_t)(readl( 0x40057C0 ) << 11);
  para->dram_tpr9 = (readl( 0x4005AC0 ) << 27) | readl( 0x4005988 ) & 0x1FF | (readl( 0x4005A88 ) << 16) & 0x1FFFFFF | (uint16_t)(readl( 0x40059C0 ) << 11);


}