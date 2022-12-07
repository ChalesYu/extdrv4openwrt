// SPDX-License-Identifier: 
/*
 *
 * sun50i A63 platform dram controller init
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

#include "libdram_a63/dram_para.h"

unsigned long sunxi_dram_init(void)
{

__dram_para_t now_dram_para = {
//FIXME
//A63 SBC
#if 1
   .dram_clk = 792 ,
   .dram_type = 7 ,
   .dram_zq = 0x3b3bfb ,
   .dram_odt_en = 49 ,
   .dram_para1 = 283381988 ,
   .dram_para2 = 0 ,
   .dram_mr0 = 7280 ,
   .dram_mr1 = 64 ,
   .dram_mr2 = 24 ,
   .dram_mr3 = 2 ,
   .dram_tpr0 = 0x47194f ,
   .dram_tpr1 = 0x1b1a94b ,
   .dram_tpr2 = 0x61043 ,
   .dram_tpr3 = 0xb47d7d96 ,
   .dram_tpr4 = 0x0 ,
   .dram_tpr5 = 0x0 ,
   .dram_tpr6 = 0x0 ,
   .dram_tpr7 = 0x11271621 ,
   .dram_tpr8 = 0x0 ,
   .dram_tpr9 = 0x228 ,
   .dram_tpr10 = 0x8 ,
   .dram_tpr11 = 0x0 ,
   .dram_tpr12 = 0x0 ,
   .dram_tpr13 = 0x15000280 ,
#endif

// teclast m8
#if 0
   .dram_clk = 720 ,
   .dram_type = 7 ,
   .dram_zq = 0x3b3bfb ,
   .dram_odt_en = 49 ,
   .dram_para1 = 283381988 ,
   .dram_para2 = 0 ,
   .dram_mr0 = 7280 ,
   .dram_mr1 = 64 ,
   .dram_mr2 = 24 ,
   .dram_mr3 = 2 ,
   .dram_tpr0 = 0x47194f ,
   .dram_tpr1 = 0x1b1a94b ,
   .dram_tpr2 = 0x61043 ,
   .dram_tpr3 = 0xb47d7d96 ,
   .dram_tpr4 = 0x0 ,
   .dram_tpr5 = 0x0 ,
   .dram_tpr6 = 0x0 ,
   .dram_tpr7 = 0x11271621 ,
   .dram_tpr8 = 0x0 ,
   .dram_tpr9 = 0x0 ,
   .dram_tpr10 = 0x8 ,
   .dram_tpr11 = 0x44440000 ,
   .dram_tpr12 = 0x3333 ,
   .dram_tpr13 = 0x15002280 ,
#endif
	};

  unsigned long size=0;

  int t=7; //LPDDR3

  __dram_para_t * fantasy = NULL;

  fantasy = &now_dram_para;

  printf("Init DRAM controller for Allwinner A63\n");

  size = (unsigned long) init_DRAM( t, fantasy);

  printf("size = %d\n", size);

// size = 0 ?
// force set a value

//  printf("size FORCE set to 3072 ! \n");
//   size = 3072;
   return (size << 20);

};

