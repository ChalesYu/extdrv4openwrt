// SPDX-License-Identifier: 
/*
 *
 * sun50i H6 platform dram controller init
 * Based on dram_sun50i_h6.c
 */
#define DBG

#include <common.h>
#include <init.h>
#include <log.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/dram.h>
#include <asm/arch/cpu.h>
#include <asm/arch/prcm.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/kconfig.h>

#include "libdram_h6/dram_para.h"

unsigned long sunxi_dram_init(void)
{

__dram_para_t now_dram_para = {
//FIXME
//H6 SBC
#if 1
   .dram_clk = 0  ,
   .dram_type = 7  ,
   .dram_zq = 0x3b3bfb  ,
   .dram_odt_en = 49  ,
   .dram_para1 = 12538  ,
   .dram_para2 = 67108864  ,
   .dram_mr0 = 7280  ,
   .dram_mr1 = 64  ,
   .dram_mr2 = 24  ,
   .dram_mr3 = 1  ,
   .dram_mr4 = 0  ,
   .dram_mr5 = 1024  ,
   .dram_mr6 = 2120  ,
   .dram_tpr0 = 0x48a192  ,
   .dram_tpr1 = 0x1b1a94b  ,
   .dram_tpr2 = 0x61043  ,
   .dram_tpr3 = 0x78787896  ,
   .dram_tpr4 = 0x0  ,
   .dram_tpr5 = 0x0  ,
   .dram_tpr6 = 0x9090900  ,
   .dram_tpr7 = 0x4d462a3e  ,
   .dram_tpr8 = 0x0  ,
   .dram_tpr9 = 0x0  ,
   .dram_tpr10 = 0x0  ,
   .dram_tpr11 = 0x440000  ,
   .dram_tpr12 = 0x0  ,
   .dram_tpr13 = 0x8000  ,
#endif

	};

  unsigned long size=0;

  int t=7; //LPDDR3

  __dram_para_t * fantasy = NULL;

  fantasy = &now_dram_para;

  printf("Init DRAM controller for Allwinner H6\n");

  size = (unsigned long) init_DRAM( t, fantasy);

  printf("size = %d\n", size);

// size = 0 ?
// force set a value

//  printf("size FORCE set to 3072 ! \n");
//   size = 3072;
   return (size << 20);

};

