// SPDX-License-Identifier: 
/*
 * sun50i A63 platform dram controller init
 *
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

//#define printf debug
#define mctl_read_w readl
#define mctl_write_w writel
#define _usdelay udelay

#define WORD uint16_t
#define DWORD uint32_t
#define _DWORD uint32_t
#define BYTE uint8_t
#define LOWORD(l)           ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD)(w) >> 8))

//Find and replace
//#define (u_nsigned __int16) (WORD)
//#define (u_nsigned __int8) (BYTE)

typedef struct __DRAM_PARA
{
	unsigned int        dram_clk;
	unsigned int        dram_type;
	unsigned int        dram_zq;
	unsigned int		dram_odt_en;
	unsigned int		dram_para1;
	unsigned int		dram_para2;
	unsigned int		dram_mr0;
	unsigned int		dram_mr1;
	unsigned int		dram_mr2;
	unsigned int		dram_mr3;
	unsigned int		dram_tpr0;
	unsigned int		dram_tpr1;
	unsigned int		dram_tpr2;
	unsigned int		dram_tpr3;
	unsigned int		dram_tpr4;
	unsigned int		dram_tpr5;
	unsigned int		dram_tpr6;
	unsigned int		dram_tpr7;
	unsigned int		dram_tpr8;
	unsigned int		dram_tpr9;
	unsigned int		dram_tpr10;
	unsigned int		dram_tpr11;
	unsigned int		dram_tpr12;
	unsigned int		dram_tpr13;
	unsigned int		dram_tpr14;
	unsigned int		dram_tpr15;
	unsigned int		dram_tpr16;
	unsigned int		dram_tpr17;
	unsigned int		dram_tpr18;
	unsigned int		dram_tpr19;
	unsigned int		dram_tpr20;
	unsigned int		dram_tpr21;
}__dram_para_t;

/*****************************************************************************
作用：timing计算函数
参数：timing(ns)值,时钟
返回值：计算值
*****************************************************************************/
unsigned int auto_cal_timing(unsigned int time_ns,unsigned int clk)
{
	unsigned int value ;
	value = (time_ns*clk)/1000 + ( ( ((time_ns*clk)%1000) != 0) ? 1 :0);
	return value;
}

unsigned int ccm_set_pll_ddr_sscg(__dram_para_t *para, unsigned int* PLL_CTRL, unsigned int PLL_PAT)
{
  signed int v3; // r3
  unsigned int result; // r0

  if ( mctl_read_w(PLL_CTRL) & 2 )
    mctl_write_w((mctl_read_w(PLL_PAT) | 0x80000u), PLL_PAT);
  switch ( (para->dram_tpr13 >> 20) & 7 )
  {
    case 1u:
      v3 = -460927796;
      break;
    case 2u:
      v3 = -385443431;
      break;
    case 3u:
      v3 = -309959066;
      break;
    case 5u:
      v3 = -175767552;
      break;
    default:
      v3 = -234474701;
      break;
  }
  mctl_write_w(v3, PLL_PAT);
  result = 0;
  mctl_write_w((mctl_read_w(PLL_CTRL) | 0x1000000u), PLL_CTRL);
  return result;
}

unsigned int ccm_set_pll_ddr_clk(unsigned int pll, __dram_para_t *para)
{
  __dram_para_t *v2; // r6
  unsigned int v3; // r7
  unsigned int *v4; // r5
  unsigned int v5; // r0
  unsigned int v6; // r0
  signed int v7; // r3
  unsigned int v8; // r4
  unsigned int v9; // r3

  v2 = para;
  v3 = 50336016;
  v4 = (unsigned int *)50335760;
  if ( pll )
    v3 = 50336024;
  if ( pll )
    v4 = (unsigned int *)50335768;
  if ( ((para->dram_tpr13 >> 6) & 1) == pll )
    v5 = para->dram_clk;
  else
    v5 = para->dram_tpr9;
  v6 = 2 * v5 / 0x18;
  if ( v6 <= 0xB )
    v7 = 12;
  else
    v7 = v6;
  v8 = v6;
  v9 = mctl_read_w(v4) & 0xFFFF80FC | 0x80000000 | ((v7 - 1) << 8);
  mctl_write_w(v9 , v4);
  v9 &= 0xDFFFFFFF;
  mctl_write_w(v9 , v4);
  mctl_write_w((v9 | 0x20000000) , v4);
  while ( !(mctl_read_w(v4) & 0x10000000) )
    ;
  _usdelay(20);
  if ( v2->dram_tpr13 & 0x800000 )
    ccm_set_pll_ddr_sscg(v2, v4, v3);
  return 24 * v8;
}

unsigned int mctl_sys_init(__dram_para_t *para)
{
  __dram_para_t *v1; // r4
  unsigned int v2; // r0
  unsigned int v3; // r3
  unsigned int v4; // r0
  unsigned int v5; // r0
  unsigned int v6; // r3

  v1 = para;
  mctl_write_w((mctl_read_w(0x3001540) & 0x7FFFFFFFu) , 0x3001540);
  mctl_write_w((mctl_read_w(0x3001540) & 0xBFFFFFFF) , 0x3001540);
  mctl_write_w((mctl_read_w(0x300180C) & 0xFFFFFFFE) , 0x300180C);
  mctl_write_w((mctl_read_w(0x300180C) & 0xFFFEFFFF) , 0x300180C);
  mctl_write_w((mctl_read_w(0x3001010) & 0x7FFFFFFFu) , 0x3001010);
  mctl_write_w((mctl_read_w(0x3001010) | 0x40000000u) , 0x3001010);
  mctl_write_w((mctl_read_w(0x3001018) & 0x7FFFFFFFu) , 0x3001018);
  mctl_write_w((mctl_read_w(0x3001018) | 0x40000000u) , 0x3001018);
  mctl_write_w((mctl_read_w(0x3001800) & 0xBFFFFFFF) , 0x3001800);
  _usdelay(100);
  if ( v1->dram_tpr13 & 0x40 )
  {
    v2 = ccm_set_pll_ddr_clk(1u, v1);
    mctl_write_w((mctl_read_w(0x3001800) & 0xFCFFFFFF | 0x1000000) , 0x3001800);
    v3 = v1->dram_tpr9;
    v1->dram_clk = v2 >> 1;
    if ( v3 )
    {
      v4 = 0;
LABEL_6:
      v1->dram_tpr9 = ccm_set_pll_ddr_clk(v4, v1) >> 1;
      goto LABEL_7;
    }
  }
  else
  {
    v5 = ccm_set_pll_ddr_clk(0, v1);
    mctl_write_w((mctl_read_w(0x3001800) & 0xFCFFFFFF) , 0x3001800);
    v6 = v1->dram_tpr9;
    v1->dram_clk = v5 >> 1;
    if ( v6 )
    {
      v4 = 1;
      goto LABEL_6;
    }
  }
LABEL_7:
  _usdelay(1000);
  mctl_write_w((mctl_read_w(0x3001800) & 0xFFFFFFFC | 0x8000000) , 0x3001800);
  mctl_write_w((mctl_read_w(0x300180C) | 0x10000u) , 0x300180C);
  mctl_write_w((mctl_read_w(0x300180C) | 1u) , 0x300180C);
  dram_disable_all_master();
  mctl_write_w((mctl_read_w(0x300180C) | 0x40000000u) , 0x3001540);
  mctl_write_w((mctl_read_w(0x300180C) | 0x80000000) , 0x3001540);
  mctl_write_w((mctl_read_w(0x300180C) | 0x40000000u) , 0x3001800);
  _usdelay(5);
  mctl_write_w(0x8000 , 0x400300C);
  _usdelay(10);
  return 0;
}


void  auto_set_timing_para(__dram_para_t *para)
{
  unsigned int v1; // r6
  __dram_para_t *v2; // r5
  unsigned int v3; // r4
  unsigned int v4; // r7
  int v5; // r2
  unsigned int v6; // r3
  unsigned int v7; // r10
  int v8; // r7
  signed int v9; // r8
  int v10; // r11
  signed int v11; // r9
  unsigned int v12; // r0
  unsigned int v13; // r0
  unsigned int v14; // r0
  int v15; // r3
  unsigned int v16; // r0
  unsigned int v17; // r0
  unsigned int v18; // r0
  unsigned int v19; // r0
  int v20; // r3
  unsigned int v21; // r0
  unsigned int v22; // r0
  int v23; // r3
  unsigned int v24; // r0
  unsigned int v25; // r0
  unsigned int v26; // r0
  unsigned int v27; // r0
  unsigned int v28; // r0
  unsigned int v29; // r0
  int v30; // r3
  unsigned int v31; // r0
  unsigned int v32; // r0
  unsigned int v33; // r0
  unsigned int v34; // r0
  unsigned int v35; // r0
  unsigned int v36; // r0
  int v37; // r3
  unsigned int v38; // r0
  bool v39; // cf
  signed int v40; // r3
  signed int v41; // r4
  signed int v42; // r3
  signed int v43; // r1
  signed int v44; // r0
  signed int v45; // r3
  signed int v46; // r2
  unsigned int v47; // r0
  signed int v48; // r3
  signed int v49; // r4
  signed int v50; // r3
  signed int v51; // r2
  signed int v52; // r12
  unsigned int v53; // r0
  signed int v54; // r3
  signed int v55; // r12
  signed int v56; // r3
  signed int v57; // r4
  signed int v58; // r2
  int v59; // r8
  unsigned int v60; // r5
  unsigned int v61; // r3
  signed int v62; // [sp+0h] [bp-90h]
  unsigned int tcwl; // [sp+4h] [bp-8Ch]
  unsigned int tcwla; // [sp+4h] [bp-8Ch]
  unsigned int mr3; // [sp+8h] [bp-88h]
  unsigned int mr3a; // [sp+8h] [bp-88h]
  signed int txp; // [sp+Ch] [bp-84h]
  signed int trc; // [sp+10h] [bp-80h]
  signed int tfaw; // [sp+14h] [bp-7Ch]
  int trefi; // [sp+18h] [bp-78h]
  signed int tras; // [sp+1Ch] [bp-74h]
  signed int trfc; // [sp+20h] [bp-70h]
  unsigned int tcl; // [sp+24h] [bp-6Ch]
  unsigned int tmrd; // [sp+28h] [bp-68h]
  unsigned int tmod; // [sp+2Ch] [bp-64h]
  unsigned int trd2wr; // [sp+30h] [bp-60h]
  unsigned int wr_latency; // [sp+34h] [bp-5Ch]
  unsigned int tdinit0; // [sp+38h] [bp-58h]
  unsigned int tdinit1; // [sp+3Ch] [bp-54h]
  unsigned int tdinit2; // [sp+40h] [bp-50h]
  unsigned int tdinit3; // [sp+44h] [bp-4Ch]
  unsigned int mr0; // [sp+48h] [bp-48h]
  unsigned int mr1; // [sp+4Ch] [bp-44h]
  unsigned int mr2; // [sp+50h] [bp-40h]
  unsigned int twtp; // [sp+54h] [bp-3Ch]
  signed int trasmax; // [sp+58h] [bp-38h]
  unsigned int twr2rd; // [sp+5Ch] [bp-34h]
  int trtp; // [sp+60h] [bp-30h]
  int tccd; // [sp+64h] [bp-2Ch]

  v1 = para->dram_clk;
  v2 = para;
  v3 = para->dram_clk >> 1;
  mr3 = para->dram_tpr13;
  tcwl = para->dram_type;
  if ( mr3 & 2 )
  {
    v4 = para->dram_tpr0;
    txp = (v4 >> 11) & 0xF;
    v5 = (v4 >> 15) & 0x3F;
    v6 = para->dram_tpr1;
    v7 = (v4 >> 6) & 0x1F;
    tccd = (v4 >> 21) & 7;
    trc = para->dram_tpr0 & 0x3F;
    v8 = (v6 >> 23) & 0x1F;
    v9 = (v6 >> 20) & 7;
    v10 = (v6 >> 11) & 0xF;
    v11 = (v6 >> 6) & 0x1F;
    tras = para->dram_tpr1 & 0x3F;
    tfaw = v5;
    trtp = (v6 >> 15) & 0x1F;
    trfc = (para->dram_tpr2 >> 12) & 0x1FF;
    trefi = para->dram_tpr2 & 0xFFF;
  }
  else
  {
    switch ( tcwl )
    {
      case 3u:
        if ( v1 > 0x320 )
        {
          tfaw = auto_cal_timing(0x23u, v3);
          v16 = auto_cal_timing(6u, v3);
          if ( v16 < 2 )
            v16 = 2;
          txp = v16;
          v7 = auto_cal_timing(0xEu, v3);
          trc = auto_cal_timing(0x30u, v3);
          v8 = txp;
          v17 = auto_cal_timing(8u, v3);
          if ( v17 <= 1 )
            v9 = 2;
          else
            v9 = v17;
          v18 = auto_cal_timing(0xFu, v3);
          if ( v18 <= 1 )
            v10 = 2;
          else
            v10 = v18;
          tras = auto_cal_timing(0x22u, v3);
          v19 = auto_cal_timing(0x1E78u, v3);
          v20 = v19 & 0x1F;
          if ( v19 & 0x1F )
            v20 = 1;
          trefi = v20 + (v19 >> 5);
          trfc = auto_cal_timing(0x15Eu, v3);
        }
        else
        {
          tfaw = auto_cal_timing(0x32u, v3);
          v12 = auto_cal_timing(0xAu, v3);
          if ( v12 <= 1 )
            v12 = 2;
          txp = v12;
          v7 = auto_cal_timing(0xFu, v3);
          if ( v7 < 2 )
            v10 = 2;
          else
            v10 = v7;
          trc = auto_cal_timing(0x35u, v3);
          v13 = auto_cal_timing(8u, v3);
          if ( v13 <= 1 )
            v8 = 2;
          else
            v8 = v13;
          v9 = v8;
          tras = auto_cal_timing(0x26u, v3);
          v14 = auto_cal_timing(0x1E78u, v3);
          v15 = v14 & 0x1F;
          if ( v14 & 0x1F )
            v15 = 1;
          trefi = v15 + (v14 >> 5);
          trfc = auto_cal_timing(0x15Eu, v3);
        }
        v11 = v7;
        break;
      case 2u:
        tfaw = auto_cal_timing(0x32u, v3);
        txp = auto_cal_timing(0xAu, v3);
        v7 = auto_cal_timing(0x14u, v3);
        trc = auto_cal_timing(0x41u, v3);
        v9 = auto_cal_timing(8u, v3);
        v21 = auto_cal_timing(0xFu, v3);
        v10 = v21;
        v11 = v21;
        tras = auto_cal_timing(0x2Du, v3);
        v22 = auto_cal_timing(0x1E78u, v3);
        v23 = v22 & 0x1F;
        if ( v22 & 0x1F )
          v23 = 1;
        trefi = v23 + (v22 >> 5);
        v8 = 2;
        trfc = auto_cal_timing(0x148u, v3);
        break;
      case 6u:
        v24 = auto_cal_timing(0x32u, v3);
        if ( v24 <= 3 )
          v24 = 4;
        tfaw = v24;
        v25 = auto_cal_timing(0xAu, v3);
        if ( !v25 )
          v25 = 1;
        txp = v25;
        v26 = auto_cal_timing(0x18u, v3);
        if ( v26 <= 1 )
          v7 = 2;
        else
          v7 = v26;
        trc = auto_cal_timing(0x46u, v3);
        v27 = auto_cal_timing(8u, v3);
        v8 = v27;
        if ( v27 && v27 > 1 )
        {
          v9 = v27;
        }
        else
        {
          v8 = 1;
          v9 = 2;
        }
        v28 = auto_cal_timing(0xFu, v3);
        if ( v28 <= 1 )
          v10 = 2;
        else
          v10 = v28;
        v11 = auto_cal_timing(0x11u, v3);
        tras = auto_cal_timing(0x2Au, v3);
        v29 = auto_cal_timing(0xF3Cu, v3);
        v30 = v29 & 0x1F;
        if ( v29 & 0x1F )
          v30 = 1;
        trefi = v30 + (v29 >> 5);
        trfc = auto_cal_timing(0xD2u, v3);
        break;
      case 7u:
        v31 = auto_cal_timing(0x32u, v3);
        if ( v31 <= 3 )
          v31 = 4;
        tfaw = v31;
        v32 = auto_cal_timing(0xAu, v3);
        if ( !v32 )
          v32 = 1;
        txp = v32;
        v33 = auto_cal_timing(0x12u, v3);
        if ( v33 < 2 )
          v7 = 2;
        else
          v7 = v33;
        v11 = v33;
        trc = auto_cal_timing(0x3Cu, v3);
        v34 = auto_cal_timing(8u, v3);
        if ( v34 <= 1 )
          v8 = 2;
        else
          v8 = v34;
        v35 = auto_cal_timing(0xFu, v3);
        if ( v35 <= 1 )
          v10 = 2;
        else
          v10 = v35;
        tras = auto_cal_timing(0x2Au, v3);
        v36 = auto_cal_timing(0xF3Cu, v3);
        v37 = v36 & 0x1F;
        if ( v36 & 0x1F )
          v37 = 1;
        trefi = v37 + (v36 >> 5);
        trfc = auto_cal_timing(0xD2u, v3);
        if ( mr3 & 0x1000000 )
        {
          v9 = v8;
        }
        else
        {
          v11 = auto_cal_timing(0x11u, v3);
          v9 = v8;
          trc = auto_cal_timing(0x3Bu, v3);
          v7 = v11;
          tfaw = auto_cal_timing(0x2Cu, v3);
        }
        break;
      default:
        trfc = 128;
        v9 = 3;
        trefi = 98;
        v11 = 6;
        v8 = 10;
        v10 = 8;
        tras = 14;
        tfaw = 16;
        v7 = 6;
        trc = 20;
        txp = 3;
        break;
    }
    trtp = v9;
    v2->dram_tpr0 = trc | 0x400000 | (v7 << 6) | (txp << 11) | (tfaw << 15);
    v2->dram_tpr1 = (v10 << 11) | (v11 << 6) | tras | (v9 << 15) | (v9 << 20) | (v8 << 23);
    v2->dram_tpr2 = trefi | (trfc << 12);
    tccd = 2;
  }
  switch ( tcwl )
  {
    case 2u:
      v38 = v3 / 0xF;
      v39 = v3 >= 0xCD;
      if ( v3 >= 0xCD )
        v40 = 4;
      else
        v40 = 3;
      if ( v3 >= 0xCD )
        v41 = 2;
      else
        v41 = 1;
      tcl = v40;
      v42 = 3699;
      mr1 = v2->dram_mr1;
      if ( !v39 )
        v42 = 2659;
      trasmax = v38;
      mr0 = v42;
      v62 = v41;
      tdinit0 = 400 * v1 + 1;
      tdinit2 = 200 * v1 + 1;
      tdinit1 = 500 * v1 / 0x3E8 + 1;
      tdinit3 = v1 + 1;
      v43 = 4;
      v44 = 3;
      tmod = 12;
      v45 = 0;
      twtp = v10 + 5;
      v46 = 5;
      twr2rd = v9 + 5;
      trd2wr = 4;
      tmrd = 2;
      tcwla = 3;
      wr_latency = 1;
      mr3a = 0;
      mr2 = 0;
      break;
    case 3u:
      v47 = v3 / 0xF;
      if ( v1 <= 0x320 )
        v48 = 6;
      else
        v48 = 7;
      if ( v1 <= 0x320 )
        v49 = 2;
      else
        v49 = 3;
      tcl = v48;
      v50 = 7280;
      mr1 = v2->dram_mr1;
      if ( v1 <= 0x320 )
        v51 = 24;
      else
        v51 = 32;
      mr2 = v51;
      if ( v1 <= 0x320 )
      {
        v52 = 4;
      }
      else
      {
        v50 = 7700;
        v52 = 5;
      }
      trasmax = v47;
      mr0 = v50;
      wr_latency = v49;
      tdinit0 = 500 * v1 + 1;
      v62 = v52;
      tdinit2 = 200 * v1 + 1;
      tdinit3 = v1 + 1;
      tdinit1 = 360 * v1 / 0x3E8 + 1;
      twtp = v10 + 2 + v52;
      twr2rd = v9 + 2 + v52;
      if ( ((mr3 >> 2) & 3) == 1 )
      {
        v43 = 4;
        v44 = 3;
        tmod = 12;
        tcwla = v52;
        v46 = 5;
        trd2wr = 5;
      }
      else
      {
        if ( v1 <= 0x390 )
        {
          v43 = 4;
          v44 = 3;
          v46 = 5;
          trd2wr = 5;
          tcwla = v52;
        }
        else
        {
          tcwla = v52;
          v46 = 5;
          v43 = 4;
          trd2wr = 6;
          v44 = 3;
        }
        tmod = 12;
      }
      v45 = 0;
      tmrd = 4;
      mr3a = 0;
      break;
    case 6u:
      trasmax = v3 / 0x1E;
      mr3a = v2->dram_mr3;
      tdinit0 = 200 * v1 + 1;
      tdinit2 = 11 * v1 + 1;
      trd2wr = 10;
      v46 = 5;
      tdinit1 = 100 * v1 / 0x3E8 + 1;
      tdinit3 = v1 + 1;
      v44 = 2;
      v45 = 3;
      wr_latency = 1;
      twtp = v10 + 5;
      twr2rd = v9 + 5;
      v43 = 5;
      tmod = 5;
      tmrd = 5;
      tcwla = 2;
      tcl = 4;
      v62 = 3;
      mr2 = 6;
      goto LABEL_113;
    case 7u:
      v53 = v3 / 0x1E;
      if ( v1 <= 0x320 )
        v54 = 3;
      else
        v54 = 4;
      if ( v1 <= 0x320 )
        v55 = 2;
      else
        v55 = 3;
      tcwla = v54;
      if ( v1 <= 0x320 )
        v56 = 10;
      else
        v56 = 12;
      if ( v1 <= 0x320 )
        v57 = 6;
      else
        v57 = 7;
      trasmax = v53;
      mr3a = v2->dram_mr3;
      if ( v1 <= 0x320 )
        v58 = 5;
      else
        v58 = 6;
      mr2 = v56;
      tcl = v57;
      wr_latency = v55;
      v62 = v58;
      tdinit0 = 200 * v1 + 1;
      v46 = 5;
      tdinit2 = 11 * v1 + 1;
      tdinit1 = 100 * v1 / 0x3E8 + 1;
      v43 = 5;
      trd2wr = 13;
      v44 = 3;
      v45 = 5;
      tdinit3 = v1 + 1;
      twtp = v10 + 5 + tcwla;
      twr2rd = v9 + 5 + tcwla;
      tmod = 12;
      tmrd = 5;
LABEL_113:
      mr1 = 195;
      mr0 = 0;
      break;
    default:
      v43 = 3;
      v46 = 4;
      twr2rd = 8;
      trasmax = 27;
      v44 = 2;
      v45 = 0;
      twtp = 12;
      trd2wr = 4;
      tmod = 6;
      tmrd = 2;
      tcwla = 3;
      tcl = 3;
      wr_latency = 1;
      v62 = 1;
      mr3a = 0;
      mr2 = 0;
      mr1 = 0;
      mr0 = 0;
      tdinit3 = 0;
      tdinit2 = 0;
      tdinit1 = 0;
      tdinit0 = 0;
      break;
  }
  if ( trtp + v11 < tcl + 2 )
    trtp = 2 - v11 + tcl;
  if ( !HIWORD(v2->dram_mr0) )
    v2->dram_mr0 = mr0;
  if ( !HIWORD(v2->dram_mr1) )
    v2->dram_mr1 = mr1;
  if ( !HIWORD(v2->dram_mr2) )
    v2->dram_mr2 = mr2;
  if ( !HIWORD(v2->dram_mr3) )
    v2->dram_mr3 = mr3a;
  mctl_write_w(LOWORD(v2->dram_mr0) ,  0x4003030); // LOWORD(v2->dram_mr0);
  mctl_write_w(LOWORD(v2->dram_mr1) ,  0x4003034); // LOWORD(v2->dram_mr1);
  mctl_write_w(LOWORD(v2->dram_mr2) ,  0x4003038); // LOWORD(v2->dram_mr2);
  v59 = LOWORD(v2->dram_mr3);
  v60 = v2->dram_odt_en;
  mctl_write_w(v59 ,  0x400303C); // v59;
  mctl_write_w((v60 >> 4) & 3 ,  0x400302C); // (v60 >> 4) & 3;
  mctl_write_w((tras | (tfaw << 16) | (twtp << 24) | (trasmax << 8)) ,  0x4003058); // tras | (tfaw << 16) | (twtp << 24) | (trasmax << 8);
  mctl_write_w((trc | (v8 << 16) | (trtp << 8)) ,  0x400305C); // trc | (v8 << 16) | (trtp << 8);
  mctl_write_w(((tcl << 16) | (tcwla << 24) | twr2rd | (trd2wr << 8)) ,  0x4003060); // (tcl << 16) | (tcwla << 24) | twr2rd | (trd2wr << 8);
  mctl_write_w(((tmrd << 12) | (v45 << 16) | tmod) ,  0x4003064); // (tmrd << 12) | (v45 << 16) | tmod;
  mctl_write_w(((tccd << 16) | (v7 << 24) | v11 | (txp << 8)) ,  0x4003068); // (tccd << 16) | (v7 << 24) | v11 | (txp << 8);
  mctl_write_w((v44 | (v46 << 16) | (v46 << 24) | (v43 << 8)) ,  0x400306C); // v44 | (v46 << 16) | (v46 << 24) | (v43 << 8);
  if ( v1 > 0x320 )
    v61 = ((mctl_read_w(0x4003078) | 0xF0000000) >> 16 << 16) | 0x7600;
  else
    v61 = ((mctl_read_w(0x4003078) | 0xF0000000) >> 16 << 16) | 0x6600;
  mctl_write_w(v61 | 0x10 ,  0x4003078); // v61 | 0x10;
  mctl_write_w((wr_latency | 0x2000100 | (v62 << 16)) ,  0x4003080); // wr_latency | 0x2000100 | (v62 << 16);
  mctl_write_w((tdinit0 | (tdinit1 << 20)) ,  0x4003050); // tdinit0 | (tdinit1 << 20);
  mctl_write_w((tdinit2 | (tdinit3 << 20)) ,  0x4003054); // tdinit2 | (tdinit3 << 20);
  mctl_write_w((trfc | (trefi << 16)) ,  0x4003090); // trfc | (trefi << 16);
  mctl_write_w(((trefi << 15) & 0xFFF0000) ,  0x4003094); // (trefi << 15) & 0xFFF0000;
}





void mctl_com_init(__dram_para_t *para)
{
  unsigned int v1; // r3
  unsigned int v2; // r12
  signed int v3; // r5
  unsigned int v4; // r1
  bool v5; // cf
  bool v6; // zf
  unsigned int v7; // r2
  unsigned int v8; // r7
  unsigned int v9; // r6
  int v10; // r3
  int *v11; // r5
  char v12; // r4
  unsigned int v13; // r1
  unsigned int v14; // r2
  int v15; // r2
  signed int v16; // r2
  unsigned int v17; // r3

  v1 = para->dram_para2;
  v2 = para->dram_para2 & 1;
  if ( v1 & 1 )
    v3 = 0;
  else
    v3 = 4096;
  v4 = para->dram_type - 6;
  v5 = v4 >= 1;
  v6 = v4 == 1;
  v7 = mctl_read_w(0x4002000) & 0xFF000FFF | 0x400000 | ((para->dram_type & 7) << 16) | v3;
  if ( v4 <= 1 )
    v7 |= 0x80000u;
  else
    v4 = para->dram_tpr13;
  if ( !v6 && v5 )
    v7 |= ((v4 >> 5) & 1) << 19;
  mctl_write_w(v7, 0x4002000);
  if ( v1 & 0x100 )
  {
    if ( (WORD)v1 >> 12 == 1 )
      v8 = 2;
    else
      v8 = 1;
  }
  else
  {
    v8 = 1;
  }
  v9 = para->dram_para1;
  v10 = (v1 >> 12) & 3;
  v11 = (int *)67117056;
  v12 = 12;
  v13 = 0;
  do
  {
    v14 = *v11 & 0xFFFFF000 | v10 | 4 * ((v9 >> v12) & 1) | (BYTE)(16 * ((v9 >> (v12 - 8)) - 1));
    switch ( (v9 >> 16 * v13) & 0xF )
    {
      case 1u:
        v15 = v14 | 0x700;
        break;
      case 2u:
        v15 = v14 | 0x800;
        break;
      case 4u:
        v15 = v14 | 0x900;
        break;
      case 8u:
        v15 = v14 | 0xA00;
        break;
      default:
        v15 = v14 | 0x600;
        break;
    }
    ++v13;
    v12 += 16;
    *v11 = v15;
    ++v11;
  }
  while ( v13 < v8 );
  v16 = 513;
  if ( mctl_read_w(0x4002000) & 1 ) v16 = 771;
  mctl_write_w(v16, 0x4003120);
  if ( v2 )
  {
    mctl_write_w(0, 0x4003444);
    mctl_write_w(0, 0x40034C4);
  }
  v17 = para->dram_tpr4;
  if ( v17 )
  {
    mctl_write_w((mctl_read_w(0x4002000) | (para->dram_tpr4 & 3) << 25) , 0x4002000);
    mctl_write_w((mctl_read_w(0x4002004) | ((v17 >> 2) & 0x1FF) << 12) , 0x4002004);
  }
}

void eye_delay_compensation(__dram_para_t *para)
{
  unsigned int v1; // r2
  __dram_para_t *v2; // r4
  unsigned int v3; // r3
  _DWORD *v4; // r1
  _DWORD *v5; // r1
  _DWORD *v6; // r1
  _DWORD *v7; // r1
  int v8; // r7
  int v9; // r6
  int v10; // r6
  int v11; // lr
  int v12; // r5
  unsigned int v13; // r2
  int v14; // r12
  int v15; // r3
  unsigned int v16; // r3
  _DWORD *v17; // r2

  v1 = para->dram_tpr11;
  v2 = para;
  v3 = para->dram_tpr12;
  v4 = (_DWORD *)67121936;
  do
  {
    mctl_write_w((mctl_read_w(v4) | ((v1 & 0xF) << 9) | 2 * (v3 & 0xF)) , v4);
    ++v4;
  }
  while ( v4 != (_DWORD *)67121972 );
  v5 = (_DWORD *)67122064;
  do
  {
    mctl_write_w((mctl_read_w(v5) | ((BYTE)v1 >> 4 << 9) | 2 * ((BYTE)v3 >> 4)) , v5);
    ++v5;
  }
  while ( v5 != (_DWORD *)67122100 );
  v6 = (_DWORD *)67122192;
  do
  {
    mctl_write_w((mctl_read_w(v6) | (((v1 >> 8) & 0xF) << 9) | 2 * ((v3 >> 8) & 0xF)) , v6);
    ++v6;
  }
  while ( v6 != (_DWORD *)67122228 );
  v7 = (_DWORD *)67122320;
  do
  {
    mctl_write_w((mctl_read_w(v7) | ((WORD)v1 >> 12 << 9) | 2 * ((WORD)v3 >> 12)) , v7);
    ++v7;
  }
  while ( v7 != (_DWORD *)67122356 );
  v8 = (v1 >> 16) & 0xF;
  v9 = (v8 << 9) | 2 * ((v3 >> 16) & 0xF);
  mctl_write_w((mctl_read_w(0x4003100) & 0xFBFFFFFF) , 0x4003100);
  mctl_write_w((mctl_read_w(0x4003334) | v9) , 0x4003334);
  mctl_write_w((mctl_read_w(0x4003338) | v9) , 0x4003338);
  v10 = (v1 >> 20) & 0xF;
  v11 = (v10 << 9) | 2 * ((v3 >> 20) & 0xF);
  mctl_write_w((mctl_read_w(0x40033B4) | v11) , 0x40033B4);
  mctl_write_w((mctl_read_w(0x40033B8) | v11) , 0x40033B8);
  v12 = (v1 >> 24) & 0xF;
  v13 = v1 >> 28;
  v14 = (v12 << 9) | 2 * ((v3 >> 24) & 0xF);
  mctl_write_w((mctl_read_w(0x4003434) | v14) , 0x4003434);
  mctl_write_w((mctl_read_w(0x4003438) | v14) , 0x4003438);
  v15 = (v13 << 9) | 2 * (v3 >> 28);
  mctl_write_w((mctl_read_w(0x40034B4) | v15) , 0x40034B4);
  mctl_write_w((mctl_read_w(0x40034B8) | v15) , 0x40034B8);
  mctl_write_w((mctl_read_w(0x400333C) | (v8 << 25)) , 0x400333C);
  mctl_write_w((mctl_read_w(0x40033BC) | (v10 << 25)) , 0x40033BC);
  mctl_write_w((mctl_read_w(0x400343C) | (v12 << 25)) , 0x400343C);
  mctl_write_w((mctl_read_w(0x40034BC) | (v13 << 25)) , 0x40034BC);
  mctl_write_w((mctl_read_w(0x4003100) | 0x4000000u ) , 0x4003100);
  _usdelay(1);
  v16 = v2->dram_tpr10;
  v17 = (_DWORD *)67121728;
  do
  {
    mctl_write_w((mctl_read_w(v17) | ((BYTE)v16 >> 4 << 8)) , v17);
    ++v17;
  }
  while ( v17 != (_DWORD *)67121788 );

  mctl_write_w((mctl_read_w(0x4003218) | ((v16 & 0xF) << 8) ) , 0x4003218);
  mctl_write_w((mctl_read_w(0x400321C) | (v16 & 0xF00) ) , 0x400321C);
  mctl_write_w((mctl_read_w(0x4003280) | ((WORD)v16 >> 12 << 8) ) , 0x4003280);
}

unsigned int mctl_channel_init(unsigned int ch_index, __dram_para_t *para)
{
  __dram_para_t *v2; // r4
  unsigned int v3; // r6
  unsigned int v4; // r0
  unsigned int v5; // r5
  unsigned int *v6; // r3
  unsigned int v7; // r2
  unsigned int v8; // r2
  unsigned int v9; // r2
  int v10; // r2
  signed int v11; // r3
  int v12; // r5

  v2 = para;
  v3 = (para->dram_tpr13 >> 2) & 3;
  v4 = para->dram_clk;
  v5 = 32 * (para->dram_odt_en & 1 ^ 1);
  mctl_write_w((mctl_read_w(0x400200C) & 0xFFFFF000 | 0x18F), 0x400200C);
  mctl_write_w((mctl_read_w(0x4003108) & 0xFFFFF0FF | 0x300), 0x4003108);
  v6 = (unsigned int *)67121988;
  do
  {
    v7 = mctl_read_w(v6) & 0xFFFF0FC1 | v5;
    if ( v4 > 0x2A0 )
      v7 = v7 & 0xFFFFF9FF | 0x400;
    mctl_write_w(v7, v6);
    v6 += 32;
  }
  while ( v6 != (unsigned int *)67122500 );
  mctl_write_w((mctl_read_w(0x4003208) | 2u), 0x4003208);
  eye_delay_compensation(para);
  if ( v3 == 1 )
  {
    mctl_write_w((mctl_read_w(0x4003108) & 0xFFFFFF3F), 0x4003108);
    mctl_write_w((mctl_read_w(0x40030BC) & 0xFFFFFEF8), 0x40030BC);
  }
  else if ( v3 == 2 )
  {
    mctl_write_w((mctl_read_w(0x4003108) & 0xFFFFFF3F | 0x80), 0x4003108);
    mctl_write_w((mctl_read_w(0x40030BC) & 0xFFFFFEF8 | 0x100 | (((mctl_read_w(0x4003060) >> 16) & 0x1F) - 2)), 0x40030BC);
    mctl_write_w(((mctl_read_w(0x400311C) | 0x8000000) & 0x7FFFFFFF), 0x400311C);
  }
  else
  {
    mctl_write_w((mctl_read_w(0x4003108) & 0xFFFFFFBF), 0x4003108);
    _usdelay(10);
    mctl_write_w((mctl_read_w(0x4003108) | 0xC0u), 0x4003108);
  }
  if ( v2->dram_type - 6 <= 1 )
  {
    if ( v3 == 1 )
      v8 = (mctl_read_w(0x400311C) | 0x80000000) & 0xF7FFFF3F;
    else
      v8 = mctl_read_w(0x400311C) & 0x88FFFFFF | 0x22000000;

    mctl_write_w(v8 , 0x400311C);
  }
  v9 = mctl_read_w(0x40030C0) & 0xF0000000;
  if ( v2->dram_para2 & 0x1000 )
    v10 = v9 | 0x3000000;
  else
    v10 = v9 | 0x1000000;

  mctl_write_w((v10 | 1) , 0x40030C0);
  mctl_write_w((mctl_read_w(0x4003140) & 0xFC000000 | v2->dram_zq & 0xFFFFFF | 0x2000000) , 0x4003140);
  if ( v3 == 1 )
  {
    mctl_write_w(83 , 0x4003000);
    while ( !(mctl_read_w(0x4003010) & 1) );

    _usdelay(10);
    if ( v2->dram_type == 3 )
      v11 = 1440;
    else
      v11 = 1312;
  }
  else if ( v2->dram_type == 3 )
  {
    v11 = 498;
  }
  else
  {
    v11 = 370;
  }

  mctl_write_w((v11 | 1) , 0x4003000);
  _usdelay(10);
  while ( !(mctl_read_w(0x4003010) & 1) );

  if ( (mctl_read_w(0x4003010) >> 20) & 0xFF )
  {
    v12 = mctl_read_w(0x4003010) & 0x100000;
    if ( mctl_read_w(0x4003010) & 0x100000 )
    {
      v12 = 0;
      printf("ZQ calibration error,check external 240 ohm resistor.\n", mctl_read_w(0x4003010) << 31);
      return v12;
    }
  }
  else
  {
    v12 = 1;
  }
  while ( !(mctl_read_w(0x4003018) & 1) )
    ;
  mctl_write_w((mctl_read_w(0x400308C) | 0x80000000) , 0x400308C);
  _usdelay(10);
  mctl_write_w((mctl_read_w(0x400308C) & 0x7FFFFFFFu) , 0x400308C);
  _usdelay(10);
  mctl_write_w((mctl_read_w(0x4002014) | 0x80000000) , 0x4002014);
  _usdelay(10);
  mctl_write_w((mctl_read_w(0x400310C) & 0xF9FFFFFF) , 0x400310C);
  if ( v3 == 1 )
    mctl_write_w((mctl_read_w(0x400311C) & 0xFFFFFF3F | 0x40) , 0x400311C);

  return v12;
}


unsigned int mctl_core_init(__dram_para_t *para)
{
  __dram_para_t *v1; // r4

  v1 = para;
  mctl_sys_init(para);
  mctl_com_init(v1);
  auto_set_timing_para(v1);
  return mctl_channel_init(0, v1);
}


int DRAMC_get_dram_size()
{
  int v0; // r3

  v0 =  mctl_read_w(0x4002000) & 3;
  if (  mctl_read_w(0x4002000) & 3 )
  {
    if (  mctl_read_w(0x4002004) << 30 )
      v0 = 1 << (( mctl_read_w(0x4002005) & 0xF) + ( mctl_read_w(0x4002004) >> 4) - 14 + (( mctl_read_w(0x4002004) >> 2) & 3));
    else
      v0 = 1 << (( mctl_read_w(0x4002001) & 0xF) + ( mctl_read_w(0x4002000) >> 4) - 14 + (( mctl_read_w(0x4002000) >> 2) & 3));
  }
  return v0 + (1 << (( mctl_read_w(0x4002001) & 0xF) + ( mctl_read_w(0x4002000) >> 4) - 14 + (( mctl_read_w(0x4002000) >> 2) & 3)));
}

void set_master_priority()
{
  mctl_write_w(399, 0x400200C); // 399
  mctl_write_w(0x10000, 0x4002200); // 0x10000
  mctl_write_w(536870927, 0x4002210); // 536870927
  mctl_write_w(327685500, 0x4002214); // 327685500
  mctl_write_w(100664585, 0x4002220); // 100664585
  mctl_write_w(16778616, 0x4002224); // 16778616;
  mctl_write_w(33554445, 0x4002230); // 33554445;
  mctl_write_w(6291712, 0x4002234); // 6291712;
  mctl_write_w(16777225, 0x4002240); // 16777225;
  mctl_write_w(5242980, 0x4002244); // 5242980;
  mctl_write_w(536871437, 0x4002250); // 536871437;
  mctl_write_w(327685500, 0x4002254); // 327685500;
  mctl_write_w(6554121, 0x4002260); // 6554121;
  mctl_write_w(2097216, 0x4002264); // 2097216;
  mctl_write_w(16777225, 0x4002290); // 16777225;
  mctl_write_w(4194432, 0x4002294); // 4194432;
  mctl_write_w(16777225, 0x40022C0); // 16777225;
  mctl_write_w(6553728, 0x40022C4); // 6553728;
  mctl_write_w(536870925, 0x4002310); // 536870925;
  mctl_write_w(157289200, 0x4002314); // 157289200;
  mctl_write_w(6553613, 0x40023A0); // 6553613;
  mctl_write_w(2097216, 0x40023A4); // 2097216;
  mctl_write_w(536871437, 0x40023B0); // 536871437;
  mctl_write_w(327685500, 0x40023B4); // 327685500;
  mctl_write_w(536871437, 0x4002480); // 536871437;
  mctl_write_w(327685500, 0x4002484); // 327685500;
  mctl_write_w(41955077, 0x40031C0); // 41955077;
  mctl_write_w(63, 0x40031C4); // 63;
  mctl_write_w(251658303, 0x40031C8); // 251658303;
}

void set_master_priority_pad()
{
  mctl_write_w(399, 0x400200C); // 399
  mctl_write_w(0x10000, 0x4002200); // 0x10000
  mctl_write_w(16777225, 0x4002210); // 16777225;
  mctl_write_w(5242980, 0x4002214); // 5242980;
  mctl_write_w(100663305, 0x4002220); // 100663305;
  mctl_write_w(16778240, 0x4002224); // 16778240;
  mctl_write_w(33554445, 0x4002230); // 33554445;
  mctl_write_w(6291712, 0x4002234); // 6291712;
  mctl_write_w(16777225, 0x4002240); // 16777225;
  mctl_write_w(5242980, 0x4002244); // 5242980;
  mctl_write_w(536871433, 0x4002250); // 536871433;
  mctl_write_w(327685500, 0x4002254); // 327685500;
  mctl_write_w(6554121, 0x4002260); // 6554121;
  mctl_write_w(2097216, 0x4002264); // 2097216;
  mctl_write_w(16777225, 0x4002290); // 16777225;
  mctl_write_w(4194432, 0x4002294); // 4194432;
  mctl_write_w(16777225, 0x40022C0); // 16777225;
  mctl_write_w(6553728, 0x40022C4); // 6553728;
  mctl_write_w(536887052, 0x4002310); // 536887052;
  mctl_write_w(327685500, 0x4002314); // 327685500;
  mctl_write_w(6553613, 0x40023A0); // 6553613;
  mctl_write_w(2097216, 0x40023A4); // 2097216;
  mctl_write_w(536872203, 0x40023B0); // 536872203;
  mctl_write_w(327685500, 0x40023B4); // 327685500;
  mctl_write_w(536871433, 0x4002480); // 536871433;
  mctl_write_w(327685500, 0x4002484); // 327685500;
  mctl_write_w(41955077, 0x40031C0); // 41955077;
  mctl_write_w(251658495, 0x40031C8); // 251658495;
  mctl_write_w(95, 0x40031CC); // 95;
  mctl_write_w(1056964703, 0x40031D0); // 1056964703;
}

void dram_enable_all_master()
{
  mctl_write_w(-1, 0x4002020);
  mctl_write_w(255, 0x4002024);
  mctl_write_w(0xFFFF, 0x4002028);
  _usdelay(10);
}

void dram_disable_all_master()
{
  mctl_write_w(1, 0x4002020);
  mctl_write_w(0, 0x4002024);
  _usdelay(10);
}

unsigned int dramc_simple_wr_test(unsigned int dram_size, unsigned int test_length)
{
  int v2; // r3
  _DWORD *v3; // r2
  unsigned int v4; // r0
  int v5; // r3
  int v6; // r4
  _DWORD *v7; // r4
  int v8; // r3
  int v9; // r5
  int v10; // r7
  int v11; // r6
  int v12; // r1
  int v13; // r2
  _DWORD *v14; // r3
  int v15; // r6
  int v16; // r5
  int v18; // [sp+0h] [bp-18h]

  v18 = v2;
  v3 = (_DWORD *)0x40000000;
  v4 = dram_size >> 1 << 20;
  v5 = 0;
  while ( v5 != test_length )
  {
    mctl_write_w((v5 + 19088743), v3);
    v6 = v5++ - 19088744;
    *(_DWORD *)((char *)v3 + v4) = v6;
    ++v3;
  }
  v7 = (_DWORD *)0x40000000;
  v8 = 0;
  while ( v8 != test_length )
  {
    v9 = mctl_read_w(v7) + v4;
    v10 = (mctl_read_w(v7) + v4);
    v11 = v8 - 19088744;
    if ( v10 != v8 - 19088744 )
    {
      printf("DRAM simple test FAIL.\n");
      v12 = v10;
      v13 = v11;
      mctl_write_w(v9, v14);
LABEL_9:
      printf("%x != %x at address %x\n", v12, v13, v14, v18);
      return 1;
    }
    v15 = mctl_read_w(v7);
    v16 = v8 + 19088743;
    if ( mctl_read_w(v7) != v8 + 19088743 )
    {
      printf("DRAM simple test FAIL.\n");
      v12 = v15;
      v13 = v16;
      v14 = v7;
      goto LABEL_9;
    }
    ++v8;
    ++v7;
  }
  printf("DRAM simple test OK.\n");
  return 0;
}

static __dram_para_t now_dram_para = {
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

unsigned long sunxi_dram_init(void)
{



  __dram_para_t *v2; // r4
  unsigned int v3; // r5
  const char *v4; // r0
  int v5; // r0
  signed int v6; // r1
  unsigned int v7; // r5
  unsigned int v8; // r1
  signed int v9; // r2
  const char *v10; // r0
  unsigned int v11; // r3
  unsigned int v12; // r1
  unsigned int v13; // r1


	unsigned long size=0;

  v2 = &now_dram_para;
  mctl_write_w((mctl_read_w(0x7010310)| 0x100u),0x7010310);
  mctl_write_w(0 ,0x7010318);
  _usdelay(10);
  v3 = 1; //skip check
//  v3 = bond_id_check();
  if ( !v3 )
  {
    v4 = "ic cant match axp, please check...\n";
IC_NOT_MATCH_AXP:
    printf(v4);
    return v3;
  }
  printf("chip id check OK\n");
/*
//skip dram_vol_set
  if ( v2->dram_tpr13 & 0x2000 )
  {
    v5 = dram_vol_set(v2);
    if ( !v5 )
      return v5;
  }
*/
/*
//skip auto_scan_dram_config
  if ( !(v2->dram_tpr13 & 1) )
  {
    v5 = auto_scan_dram_config(v2);
    if ( !v5 )
      return v5;
  }
*/
  printf("DRAM BOOT DRIVE INFO: %s\n", "V0.573");
  printf("DRAM CLK = %d MHZ\n", v2->dram_clk);
  printf("DRAM Type = %d (2:DDR2,3:DDR3,6:LPDDR2,7:LPDDR3)\n", v2->dram_type);
  printf("DRAM ZQ value: 0x%x\n", v2->dram_zq);
  v3 = mctl_core_init(v2);
  if ( !v3 )
  {
    v4 = "DRAM initial error : 1 !\n";
    goto IC_NOT_MATCH_AXP;
  }
  v7 = v2->dram_para2;
  if ( (v7 & 0x80000000) == 0 )
  {
    v3 = DRAMC_get_dram_size();
    v8 = v3;
    if ( v3 >= 0xC00 )
      v3 = 3072;
    printf("DRAM SIZE =%d M\n", v8);
    v2->dram_para2 = LOWORD(v2->dram_para2) | (v3 << 16);
  }
  else
  {
    v3 = (v7 >> 16) & 0x7FFF;
  }
  if ( v2->dram_tpr13 & 0x40000000 )
  {
    v9 = v2->dram_tpr8;
    v6 = 268435968;
    v10 = "Enable Auto SR\n";
    if ( !v9 )
      v9 = 268435968;
    mctl_write_w(v9, 0x40030A0);
    mctl_write_w(1034, 0x400309C);
    mctl_write_w((mctl_read_w(0x4003004)| 1u),0x4003004);
  }
  else
  {
    v10 = "Disable Auto SR\n";
    mctl_write_w((mctl_read_w(0x40030A0) >> 16 << 16),0x40030A0);
    mctl_write_w((mctl_read_w(0x4003004) & 0xFFFFFFFE),0x4003004);
  }
  printf(v10, v6);
  v11 = v2->dram_tpr13;
  if ( v11 & 0x200 || v2->dram_type == 6 )
    v12 = mctl_read_w(0x4003100) & 0xFFFF0FFF | 0x5000;
  else
    v12 = mctl_read_w(0x4003100) & 0xFFFF0FFF;

  mctl_write_w(v12 ,0x4003100);
  mctl_write_w((mctl_read_w(0x4003140)| 0x80000000),0x4003140);
  if ( v11 & 0x100 )
    mctl_write_w((mctl_read_w(0x40030B8)| 0x300u),0x40030B8);
  if ( v11 & 0x4000000 )
    v13 = mctl_read_w(0x4003108) & 0xFFFFDFFF;
  else
    v13 = mctl_read_w(0x4003108) | 0x2000;
  mctl_write_w(v13 ,0x4003108);
  if ( v2->dram_type == 7 )
    mctl_write_w((mctl_read_w(0x400307C) & 0xFFF0FFFF | 0x10000),0x400307C);

  if ( !(v11 & 0x8000000) )
  {
    if ( v11 & 0x1000000 )
      set_master_priority_pad();
    else
      set_master_priority();
  }
  dram_enable_all_master();

//  if ( v2->dram_tpr13 & 0x10000000 && dramc_simple_wr_test(v3, 0x1000u) )
//  		v3 = 0;

   size = v8;
   return size;
};

