// SPDX-License-Identifier: 
/*
 * sun50i A63 platform dram controller init
 *
 */

//For Local Build Test
// Drop this to build as u-boot dram init driver
#define LOCAL_BUILD_TEST

#ifdef LOCAL_BUILD_TEST
#include <stdio.h>
#include <stdbool.h>
#endif

#define DBG

#ifndef LOCAL_BUILD_TEST
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
#endif


//#define printf debug
#define mctl_read_w readl
#define mctl_write_w writel
#define _usdelay udelay

// Drop this
// ONLY FOR CHECK PASS COMPILE !!!
////////////////
#ifdef LOCAL_BUILD_TEST
#define uint8_t int
#define uint16_t int
#define uint32_t int
#endif
////////////////


#define WORD uint16_t
#define DWORD uint32_t
#define _DWORD uint32_t
#define BYTE uint8_t
#define LOWORD(l)           ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))

//#define LOBYTE(w)           ((BYTE)(((DWORD)(w)) & 0xff))
//#define HIBYTE(w)           ((BYTE)((((DWORD)(w)) >> 8) & 0xff))

// data 0x12345678  32-bit
#define BYTE0(w)		((BYTE)(((DWORD)(w)) & 0xff))		// byte 0  0x78
#define BYTE1(w)		((BYTE)((((DWORD)(w)) >> 8) & 0xff))	// byte 1  0x56
#define BYTE2(w)		((BYTE)((((DWORD)(w)) >> 16) & 0xff))	// byte 2  0x34
#define BYTE3(w)		((BYTE)((((DWORD)(w)) >> 24) & 0xff))	// byte 3  0x12

#define LOBYTE(w)  BYTE0(w)
#define HIBYTE(w)  BYTE3(w)

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


///////////// drop this
#ifdef LOCAL_BUILD_TEST
void udelay ( int a);
unsigned int readl( unsigned int loc );
void writel( int data  , unsigned int loc );
#endif
////////////

void dram_udelay(unsigned int n);
unsigned int dram_vol_set(__dram_para_t *para);
unsigned int auto_cal_timing(unsigned int time_ns,unsigned int clk);
void paraconfig(unsigned int *para, unsigned int mask, unsigned int value);

int DRAMC_get_dram_size();

unsigned int dqs_gate_detect(__dram_para_t *para);

unsigned int auto_scan_dram_config(__dram_para_t *para);
unsigned int auto_scan_dram_rank_width(__dram_para_t *para);
unsigned int auto_scan_dram_size(__dram_para_t *para);
unsigned int auto_scan_dram_type(__dram_para_t *para);
void auto_set_timing_para(__dram_para_t *para);
void  eye_delay_compensation(__dram_para_t *para);
unsigned int ccm_set_pll_ddr_sscg(__dram_para_t *para, unsigned int PLL_CTRL, unsigned int PLL_PAT);
unsigned int ccm_set_pll_ddr_clk(unsigned int pll, __dram_para_t *para);

unsigned int mctl_core_init(__dram_para_t *para);
unsigned int mctl_sys_init(__dram_para_t *para);
unsigned int mctl_channel_init(unsigned int ch_index, __dram_para_t *para);
void mctl_com_init(__dram_para_t *para);

int  init_DRAM(int type, __dram_para_t *para);

unsigned int dramc_simple_wr_test(unsigned int dram_size, unsigned int test_length);

void dram_enable_all_master();
void dram_disable_all_master();
void set_master_priority();
void set_master_priority_pad();

////////////// drop this
#ifdef LOCAL_BUILD_TEST
void udelay ( int a)
{ int i=0 ; if (i) printf("hello"); };

unsigned int readl( unsigned int loc )
{ int i=0 ; if (i) printf("hello"); };

void writel( int data  , unsigned int loc ) 
{ int i=0 ; if (i) printf("hello"); };
#endif
////////////////

void dram_udelay(unsigned int n)
{
  _usdelay(n);
}

//Dummy func
unsigned int dram_vol_set(__dram_para_t *para)
{
  int dram_tpr3_high; // r3
  unsigned int v2; // r4

//      dram_tpr3_high = BYTE1(para->dram_tpr3);
	dram_tpr3_high = 124 ;
      v2 = 10 * dram_tpr3_high;
//      if ( !set_ddr_voltage(10 * dram_tpr3_high) )
	if (1)
        return v2;

      printf("[ERROR DEBUG]: POWER SETTING ERROR!\n");
      return 0;
}

unsigned int auto_cal_timing(unsigned int time_ns,unsigned int clk)
{
	unsigned int value ;
	value = (time_ns*clk)/1000 + ( ( ((time_ns*clk)%1000) != 0) ? 1 :0);
	return value;
}

void paraconfig(unsigned int *para, unsigned int mask, unsigned int value)
{
	*para = *para & (~mask) | value;
//	*para &= ~(mask);
//	*para |= value;
}

int DRAMC_get_dram_size()
{
  int v0; // r3

  v0 =  mctl_read_w(0x4002000) & 3;
  if (  (mctl_read_w(0x4002000) & 3) != 0 )
  {
    if (  mctl_read_w(0x4002004) << 30 )
      v0 = 1 << (( mctl_read_w(0x4002005) & 0xF) + ( mctl_read_w(0x4002004) >> 4) - 14 + (( mctl_read_w(0x4002004) >> 2) & 3));
    else
      v0 = 1 << (( mctl_read_w(0x4002001) & 0xF) + ( mctl_read_w(0x4002000) >> 4) - 14 + (( mctl_read_w(0x4002000) >> 2) & 3));
  }
  return v0 + (1 << (( mctl_read_w(0x4002001) & 0xF) + ( mctl_read_w(0x4002000) >> 4) - 14 + (( mctl_read_w(0x4002000) >> 2) & 3)));
}

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

unsigned int auto_scan_dram_size(__dram_para_t *para)
{
  int v3; // r10
  int v4; // r5
  int v5; // r4
  char v6; // r9
  int v7; // r6
  int v8; // r3
  int *v9; // r2
  int i; // r3
  int v11; // r1
  int v12; // r3
  int v13; // r0
  int v14; // r2
  unsigned int v15; // r1
  int v16; // r1
  int v17; // r2
  int v18; // r3
  int v19; // r3
  int v20; // r0
  int j; // r2
  int v22; // r1
  int v23; // r3
  unsigned int v24; // r3
  unsigned int v25; // [sp+0h] [bp-38h]
  unsigned int reg_val[11]; // [sp+Ch] [bp-2Ch] BYREF

  reg_val[0] = 0;
  if ( mctl_core_init(para) )
  {
    v3 = 0;
    v4 = 67117056;
    v5 = 0x40000000;
    v6 = 12;
    v7 = 0x40000000;
    if ( (uint16_t)para->dram_para2 >> 12 == 1 )
      v8 = 2;
    else
      v8 = 1;
    v25 = v8;
    while ( 2 )
    {
     
      v9 = (int *)v7;
      for ( i = 0; i != 64; ++i )
      {
        if ( (i & 1) != 0 )
          v11 = (int)v9;
        else
          v11 = ~v7 - 4 * i;
        *v9++ = v11;
      }

//ERROR!!!
/*  //possible fix:
      for ( i = 0; i != 64; ++i )
      {
        if ( (i & 1) != 0 )
          v11 = v7;
        else
          v11 = ~v7 - 4 * i;

        writel( v11 , v7 );

	  v7++;
      }
*/

//      reg_val[0] = *(_DWORD *)v4;
	reg_val[0] = readl( v4 );

      paraconfig(reg_val, 0xF00u, 0x600u);
      paraconfig(reg_val, 0xCu, 0);
//      *(_DWORD *)v4 = reg_val[0] | 0xF0;
	writel( reg_val[0] | 0xF0 , v4 );


      v12 = 11;
      while ( 2 )
      {
        v13 = v5;
        v14 = 0;
        while ( 1 )
        {
          v15 = (v14 & 1) != 0 ? (v13) : (~v5 - 4 * v14);

//          if ( v15 != *(_DWORD *)((1 << (v12 + 11)) + v7 - v5 + v13) )
//            break;

		if (     v15 !=  readl(  (1 << (v12 + 11)) + v7 - v5 + v13  )     )  break;

          ++v14;
          v13 += 4;
          if ( v14 == 64 )
          {
            reg_val[0] = v15;
            goto LABEL_23;
          }
        }
        if ( ++v12 != 17 ) continue;
        break;
      }
      v12 = 16;
      reg_val[0] = v15;
LABEL_23:
      paraconfig(&para->dram_para1, 255 << (v6 - 8), v12 << (v6 - 8));
      if ( v3 )
      {
        v7 = 1082130432;
        reg_val[0] = readl( 0x4002000 );
        paraconfig(reg_val, 0xF0u, 0xA0u);
        paraconfig(reg_val, 0xCu, 4u);
        paraconfig(reg_val, 0xF00u, 0x600u);
        writel( reg_val[0] , 0x4002000 );
      }

//      reg_val[0] = *(_DWORD *)v4;
	reg_val[0] = readl( v4 );

      paraconfig(reg_val, 0xF0u, 0xA0u);
      paraconfig(reg_val, 0xCu, 4u);
      paraconfig(reg_val, 0xF00u, 0x600u);
      v16 = v5;
      v17 = 0;
//      *(_DWORD *)v4 = reg_val[0];
	writel( reg_val[0] , v4 );

      do
      {
        if ( (v17 & 1) != 0 )
          v18 = v16;
        else
          v18 = (~v5 - 4 * v17);

//        if ( v18 != *(_DWORD *)(2048 - v5 + v7 + v16) )
//          break;

		if (  v18 != readl( 2048 - v5 + v7 + v16 )  ) break;

        ++v17;
        v16 += 4;
      }
      while ( v17 != 64 );
      reg_val[0] = v18;
      paraconfig(&para->dram_para1, 15 << v6, (v17 != 64) << v6);
      if ( v3 )
      {
        v7 = 1140850688;
        reg_val[0] = readl( 0x4002000 );
        paraconfig(reg_val, 0xF0u, 0xA0u);
        paraconfig(reg_val, 0xCu, 0);
        paraconfig(reg_val, 0xF00u, 0xA00u);
        writel( reg_val[0] , 0x4002000 );
      }

//      reg_val[0] = *(_DWORD *)v4;
	reg_val[0] = readl( v4 );

      paraconfig(reg_val, 0xF0u, 0xA0u);
      paraconfig(reg_val, 0xCu, 0);
      paraconfig(reg_val, 0xF00u, 0xA00u);
//      *(_DWORD *)v4 = reg_val[0];

	writel( reg_val[0] , v4 );

      v19 = 9;
LABEL_34:
      v20 = v5;
      for ( j = 0; j != 64; ++j )
      {
        if ( (j & 1) != 0 )
          v22 = v20;
        else
          v22 = (~v5 - 4 * j);

//        if ( v22 != *(_DWORD *)((1 << v19) + v7 - v5 + v20) )

		if (  v22 != readl( (1 << v19) + v7 - v5 + v20 )  )

        {
          if ( ++v19 != 14 )
            goto LABEL_34;
          reg_val[0] = v22;
//          LOBYTE(v19) = 13; //maybe error ?
		v19 = (v19 - LOBYTE(v19)) + 13;
          goto LABEL_44;
        }
        v20 += 4;
      }
      reg_val[0] = v22;
      if ( v19 == 13 || v19 != 9 )
      {
LABEL_44:
        v23 = 1 << (v19 - 10);
        goto LABEL_46;
      }
      v23 = 0;
LABEL_46:
      paraconfig(&para->dram_para1, 15 << (16 * v3), v23 << (16 * v3));
      if ( v3 + 1 < v25 )
      {
        v7 = 1207959552;
        v4 += 4;
        reg_val[0] = readl( 0x4002000 );
        v6 += 16;
        paraconfig(reg_val, 0xF0u, 0xF0u);
        v5 = 1207959552;
        paraconfig(reg_val, 0xCu, 0);
        v3 = 1;
        paraconfig(reg_val, 0xF00u, 0x600u);
        writel( reg_val[0] , 0x4002000 );
        reg_val[0] = readl( 0x4002004 );
        paraconfig(reg_val, 0xF0u, 0xF0u);
        paraconfig(reg_val, 0xCu, 0);
        paraconfig(reg_val, 0xF00u, 0x600u);
        reg_val[0] |= 1u;
        writel( reg_val[0] , 0x4002004 );
        continue;
      }
      break;
    }
    if ( v25 == 2 )
    {
      v24 = para->dram_para2 & 0xFFFFF0FF;
      if ( (uint16_t)para->dram_para1 != HIWORD(para->dram_para1) )
        v24 |= 0x100u;
      para->dram_para2 = v24;
    }
    return 1;
  }
  else
  {
    printf("[ERROR DEBUG] DRAM initial error : 0!\n");
    return 0;
  }
}


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


void auto_set_timing_para(__dram_para_t *para)
{
  unsigned int dram_clk; // r6
  unsigned int v3; // r4
  unsigned int dram_tpr0; // r7
  int v5; // r2
  unsigned int dram_tpr1; // r3
  unsigned int v7; // r10
  int v8; // r7
  int v9; // r8
  int v10; // r11
  int v11; // r9
  unsigned int v12; // r0
  unsigned int v13; // r0
  unsigned int v14; // r0
  int v15; // r3
  unsigned int v16; // r1
  unsigned int v17; // r0
  unsigned int v18; // r0
  unsigned int v19; // r0
  unsigned int v20; // r0
  int v21; // r3
  unsigned int v22; // r0
  unsigned int v23; // r0
  unsigned int v24; // r0
  unsigned int v25; // r0
  unsigned int v26; // r0
  unsigned int v27; // r0
  int v28; // r3
  unsigned int v29; // r0
  unsigned int v30; // r0
  unsigned int v31; // r0
  unsigned int v32; // r0
  unsigned int v33; // r0
  unsigned int v34; // r0
  int v35; // r3
  unsigned int v36; // r0
  bool v37; // cf
  int v38; // r3
  int v39; // r4
  int v40; // r3
  int v41; // r1
  int v42; // r0
  int v43; // r3
  int v44; // r2
  unsigned int v45; // r0
  int v46; // r3
  int v47; // r4
  int v48; // r3
  int v49; // r2
  int v50; // r12
  unsigned int v51; // r0
  int v52; // r3
  int v53; // r12
  int v54; // r3
  int v55; // r4
  int v56; // r2
  int dram_mr3_low; // r8
  unsigned int dram_odt_en; // r5
  unsigned int v59; // r3
  int v60; // r3
  int v61; // [sp+0h] [bp-90h]
  unsigned int tcwl; // [sp+4h] [bp-8Ch]
  unsigned int tcwla; // [sp+4h] [bp-8Ch]
  unsigned int mr3; // [sp+8h] [bp-88h]
  unsigned int mr3a; // [sp+8h] [bp-88h]
  int txp; // [sp+Ch] [bp-84h]
  int trc; // [sp+10h] [bp-80h]
  int tfaw; // [sp+14h] [bp-7Ch]
  int trefi; // [sp+18h] [bp-78h]
  int tras; // [sp+1Ch] [bp-74h]
  int trfc; // [sp+20h] [bp-70h]
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
  int mr1; // [sp+4Ch] [bp-44h]
  int mr2; // [sp+50h] [bp-40h]
  unsigned int twtp; // [sp+54h] [bp-3Ch]
  int trasmax; // [sp+58h] [bp-38h]
  unsigned int twr2rd; // [sp+5Ch] [bp-34h]
  int trtp; // [sp+60h] [bp-30h]
  int tccd; // [sp+64h] [bp-2Ch]

  dram_clk = para->dram_clk;
  v3 = para->dram_clk >> 1;
  mr3 = para->dram_tpr13;
  tcwl = para->dram_type;
  if ( (mr3 & 2) != 0 )
  {
    dram_tpr0 = para->dram_tpr0;
    txp = (dram_tpr0 >> 11) & 0xF;
    v5 = (dram_tpr0 >> 15) & 0x3F;
    dram_tpr1 = para->dram_tpr1;
    v7 = (dram_tpr0 >> 6) & 0x1F;
    tccd = (dram_tpr0 >> 21) & 7;
    trc = dram_tpr0 & 0x3F;
    v8 = (dram_tpr1 >> 23) & 0x1F;
    v9 = (dram_tpr1 >> 20) & 7;
    v10 = (dram_tpr1 >> 11) & 0xF;
    v11 = (dram_tpr1 >> 6) & 0x1F;
    tras = dram_tpr1 & 0x3F;
    tfaw = v5;
    trtp = (dram_tpr1 >> 15) & 0x1F;
    trfc = (para->dram_tpr2 >> 12) & 0x1FF;
    trefi = para->dram_tpr2 & 0xFFF;
  }
  else
  {
    switch ( tcwl )
    {
      case 3u:
        if ( dram_clk > 0x320 )
        {
          tfaw = auto_cal_timing(0x23u, v3);
          v17 = auto_cal_timing(6u, v3);
          if ( v17 < 2 )
            v17 = 2;
          txp = v17;
          v7 = auto_cal_timing(0xEu, v3);
          trc = auto_cal_timing(0x30u, v3);
          v8 = txp;
          v18 = auto_cal_timing(8u, v3);
          if ( v18 <= 1 )
            v9 = 2;
          else
            v9 = v18;
          v19 = auto_cal_timing(0xFu, v3);
          if ( v19 <= 1 )
            v10 = 2;
          else
            v10 = v19;
          tras = auto_cal_timing(0x22u, v3);
          v14 = auto_cal_timing(0x1E78u, v3);
          v15 = v14 & 0x1F;
          v16 = v3;
          if ( (v14 & 0x1F) != 0 )
            v15 = 1;
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
          v16 = v3;
          if ( (v14 & 0x1F) != 0 )
            v15 = 1;
        }
        trefi = v15 + (v14 >> 5);
        trfc = auto_cal_timing(0x15Eu, v16);
        v11 = v7;
        break;
      case 2u:
        tfaw = auto_cal_timing(0x32u, v3);
        txp = auto_cal_timing(0xAu, v3);
        v7 = auto_cal_timing(0x14u, v3);
        trc = auto_cal_timing(0x41u, v3);
        v9 = auto_cal_timing(8u, v3);
        v10 = auto_cal_timing(0xFu, v3);
        v11 = v10;
        tras = auto_cal_timing(0x2Du, v3);
        v20 = auto_cal_timing(0x1E78u, v3);
        v21 = v20 & 0x1F;
        if ( (v20 & 0x1F) != 0 )
          v21 = 1;
        trefi = v21 + (v20 >> 5);
        v8 = 2;
        trfc = auto_cal_timing(0x148u, v3);
        break;
      case 6u:
        v22 = auto_cal_timing(0x32u, v3);
        if ( v22 <= 3 )
          v22 = 4;
        tfaw = v22;
        v23 = auto_cal_timing(0xAu, v3);
        if ( !v23 )
          v23 = 1;
        txp = v23;
        v24 = auto_cal_timing(0x18u, v3);
        if ( v24 <= 1 )
          v7 = 2;
        else
          v7 = v24;
        trc = auto_cal_timing(0x46u, v3);
        v25 = auto_cal_timing(8u, v3);
        v8 = v25;
        if ( v25 && v25 > 1 )
        {
          v9 = v25;
        }
        else
        {
          v8 = 1;
          v9 = 2;
        }
        v26 = auto_cal_timing(0xFu, v3);
        if ( v26 <= 1 )
          v10 = 2;
        else
          v10 = v26;
        v11 = auto_cal_timing(0x11u, v3);
        tras = auto_cal_timing(0x2Au, v3);
        v27 = auto_cal_timing(0xF3Cu, v3);
        v28 = v27 & 0x1F;
        if ( (v27 & 0x1F) != 0 )
          v28 = 1;
        trefi = v28 + (v27 >> 5);
        trfc = auto_cal_timing(0xD2u, v3);
        break;
      case 7u:
        v29 = auto_cal_timing(0x32u, v3);
        if ( v29 <= 3 )
          v29 = 4;
        tfaw = v29;
        v30 = auto_cal_timing(0xAu, v3);
        if ( !v30 )
          v30 = 1;
        txp = v30;
        v31 = auto_cal_timing(0x12u, v3);
        if ( v31 < 2 )
          v7 = 2;
        else
          v7 = v31;
        v11 = v31;
        trc = auto_cal_timing(0x3Cu, v3);
        v32 = auto_cal_timing(8u, v3);
        if ( v32 <= 1 )
          v8 = 2;
        else
          v8 = v32;
        v33 = auto_cal_timing(0xFu, v3);
        if ( v33 <= 1 )
          v10 = 2;
        else
          v10 = v33;
        tras = auto_cal_timing(0x2Au, v3);
        v34 = auto_cal_timing(0xF3Cu, v3);
        v35 = v34 & 0x1F;
        if ( (v34 & 0x1F) != 0 )
          v35 = 1;
        trefi = v35 + (v34 >> 5);
        trfc = auto_cal_timing(0xD2u, v3);
        if ( (mr3 & 0x1000000) != 0 )
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
    para->dram_tpr0 = trc | 0x400000 | (v7 << 6) | (txp << 11) | (tfaw << 15);
    para->dram_tpr1 = (v10 << 11) | (v11 << 6) | tras | (v9 << 15) | (v9 << 20) | (v8 << 23);
    para->dram_tpr2 = trefi | (trfc << 12);
    tccd = 2;
  }
  switch ( tcwl )
  {
    case 2u:
      v36 = v3 / 0xF;
      v37 = v3 >= 0xCD;
      if ( v3 >= 0xCD )
        v38 = 4;
      else
        v38 = 3;
      if ( v3 >= 0xCD )
        v39 = 2;
      else
        v39 = 1;
      tcl = v38;
      v40 = 3699;
      mr1 = para->dram_mr1;
      if ( !v37 )
        v40 = 2659;
      trasmax = v36;
      mr0 = v40;
      v61 = v39;
      tdinit0 = 400 * dram_clk + 1;
      tdinit2 = 200 * dram_clk + 1;
      tdinit1 = 500 * dram_clk / 0x3E8 + 1;
      tdinit3 = dram_clk + 1;
      v41 = 4;
      v42 = 3;
      tmod = 12;
      v43 = 0;
      twtp = v10 + 5;
      v44 = 5;
      twr2rd = v9 + 5;
      trd2wr = 4;
      tmrd = 2;
      tcwla = 3;
      wr_latency = 1;
      mr3a = 0;
      mr2 = 0;
      break;
    case 3u:
      v45 = v3 / 0xF;
      if ( dram_clk <= 0x320 )
        v46 = 6;
      else
        v46 = 7;
      if ( dram_clk <= 0x320 )
        v47 = 2;
      else
        v47 = 3;
      tcl = v46;
      v48 = 7280;
      mr1 = para->dram_mr1;
      if ( dram_clk <= 0x320 )
        v49 = 24;
      else
        v49 = 32;
      mr2 = v49;
      if ( dram_clk <= 0x320 )
      {
        v50 = 4;
      }
      else
      {
        v48 = 7700;
        v50 = 5;
      }
      trasmax = v45;
      mr0 = v48;
      wr_latency = v47;
      tdinit0 = 500 * dram_clk + 1;
      v61 = v50;
      tdinit2 = 200 * dram_clk + 1;
      tdinit3 = dram_clk + 1;
      tdinit1 = 360 * dram_clk / 0x3E8 + 1;
      twtp = v10 + 2 + v50;
      twr2rd = v9 + 2 + v50;
      if ( ((mr3 >> 2) & 3) == 1 )
      {
        v41 = 4;
        v42 = 3;
        tmod = 12;
        tcwla = v50;
        v44 = 5;
        trd2wr = 5;
      }
      else
      {
        if ( dram_clk <= 0x390 )
        {
          v41 = 4;
          v42 = 3;
          v44 = 5;
          trd2wr = 5;
          tcwla = v50;
        }
        else
        {
          tcwla = v50;
          v44 = 5;
          v41 = 4;
          trd2wr = 6;
          v42 = 3;
        }
        tmod = 12;
      }
      v43 = 0;
      tmrd = 4;
      mr3a = 0;
      break;
    case 6u:
      trasmax = v3 / 0x1E;
      mr3a = para->dram_mr3;
      tdinit0 = 200 * dram_clk + 1;
      tdinit2 = 11 * dram_clk + 1;
      trd2wr = 10;
      v44 = 5;
      tdinit1 = 100 * dram_clk / 0x3E8 + 1;
      tdinit3 = dram_clk + 1;
      v42 = 2;
      v43 = 3;
      wr_latency = 1;
      twtp = v10 + 5;
      twr2rd = v9 + 5;
      v41 = 5;
      tmod = 5;
      tmrd = 5;
      tcwla = 2;
      tcl = 4;
      v61 = 3;
      mr2 = 6;
      goto LABEL_112;
    case 7u:
      v51 = v3 / 0x1E;
      if ( dram_clk <= 0x320 )
        v52 = 3;
      else
        v52 = 4;
      if ( dram_clk <= 0x320 )
        v53 = 2;
      else
        v53 = 3;
      tcwla = v52;
      if ( dram_clk <= 0x320 )
        v54 = 10;
      else
        v54 = 12;
      if ( dram_clk <= 0x320 )
        v55 = 6;
      else
        v55 = 7;
      trasmax = v51;
      mr3a = para->dram_mr3;
      if ( dram_clk <= 0x320 )
        v56 = 5;
      else
        v56 = 6;
      mr2 = v54;
      tcl = v55;
      wr_latency = v53;
      v61 = v56;
      tdinit0 = 200 * dram_clk + 1;
      v44 = 5;
      tdinit2 = 11 * dram_clk + 1;
      tdinit1 = 100 * dram_clk / 0x3E8 + 1;
      v41 = 5;
      trd2wr = 13;
      v42 = 3;
      v43 = 5;
      tdinit3 = dram_clk + 1;
      twtp = v10 + 5 + tcwla;
      twr2rd = v9 + 5 + tcwla;
      tmod = 12;
      tmrd = 5;
LABEL_112:
      mr1 = 195;
      mr0 = 0;
      break;
    default:
      v41 = 3;
      v44 = 4;
      twr2rd = 8;
      trasmax = 27;
      v42 = 2;
      v43 = 0;
      twtp = 12;
      trd2wr = 4;
      tmod = 6;
      tmrd = 2;
      tcwla = 3;
      tcl = 3;
      wr_latency = 1;
      v61 = 1;
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
  if ( !HIWORD(para->dram_mr0) )
    para->dram_mr0 = mr0;
  if ( !HIWORD(para->dram_mr1) )
    para->dram_mr1 = mr1;
  if ( !HIWORD(para->dram_mr2) )
    para->dram_mr2 = mr2;
  if ( !HIWORD(para->dram_mr3) )
    para->dram_mr3 = mr3a;

//  MEMORY[0x4003030] = LOWORD(para->dram_mr0);
//  MEMORY[0x4003034] = LOWORD(para->dram_mr1);
//  MEMORY[0x4003038] = LOWORD(para->dram_mr2);

	writel( LOWORD(para->dram_mr0) , 0x4003030);
	writel( LOWORD(para->dram_mr1) , 0x4003034);
	writel( LOWORD(para->dram_mr2) , 0x4003038);

  dram_mr3_low = LOWORD(para->dram_mr3);
  dram_odt_en = para->dram_odt_en;

//  MEMORY[0x400303C] = dram_mr3_low;
//  MEMORY[0x400302C] = (dram_odt_en >> 4) & 3;
//  MEMORY[0x4003058] = tras | (tfaw << 16) | (twtp << 24) | (trasmax << 8);
//  MEMORY[0x400305C] = trc | (v8 << 16) | (trtp << 8);
//  MEMORY[0x4003060] = (tcl << 16) | (tcwla << 24) | twr2rd | (trd2wr << 8);
//  MEMORY[0x4003064] = (tmrd << 12) | (v43 << 16) | tmod;
//  MEMORY[0x4003068] = (tccd << 16) | (v7 << 24) | v11 | (txp << 8);
//  MEMORY[0x400306C] = v42 | (v44 << 16) | (v44 << 24) | (v41 << 8);

	writel( dram_mr3_low , 0x400303C);
	writel( (dram_odt_en >> 4) & 3 , 0x400302C);
	writel( tras | (tfaw << 16) | (twtp << 24) | (trasmax << 8) , 0x4003058);
	writel( trc | (v8 << 16) | (trtp << 8) , 0x400305C);
	writel( (tcl << 16) | (tcwla << 24) | twr2rd | (trd2wr << 8) , 0x4003060);
	writel( (tmrd << 12) | (v43 << 16) | tmod , 0x4003064);
	writel( (tccd << 16) | (v7 << 24) | v11 | (txp << 8) , 0x4003068);
	writel( v42 | (v44 << 16) | (v44 << 24) | (v41 << 8) , 0x400306C);

//  v59 = (MEMORY[0x4003078] | 0xF0000000) >> 16 << 16;
  v59 = ( readl(0x4003078) | 0xF0000000) >> 16 << 16;

  if ( dram_clk > 0x320 )
    v60 = v59 | 0x7600;
  else
    v60 = v59 | 0x6600;


//  MEMORY[0x4003078] = v60 | 0x10;
//  MEMORY[0x4003080] = wr_latency | 0x2000100 | (v61 << 16);
//  MEMORY[0x4003050] = tdinit0 | (tdinit1 << 20);
//  MEMORY[0x4003054] = tdinit2 | (tdinit3 << 20);
//  MEMORY[0x4003090] = trfc | (trefi << 16);
//  MEMORY[0x4003094] = (trefi << 15) & 0xFFF0000;

	writel( v60 | 0x10 , 0x4003078);
	writel( wr_latency | 0x2000100 | (v61 << 16) , 0x4003080);
	writel( tdinit0 | (tdinit1 << 20) , 0x4003050);
	writel( tdinit2 | (tdinit3 << 20) , 0x4003054);
	writel( trfc | (trefi << 16) , 0x4003090);
	writel( (trefi << 15) & 0xFFF0000 , 0x4003094);

}

void  eye_delay_compensation(__dram_para_t *para)
{
  unsigned int dram_tpr11; // r2
  unsigned int dram_tpr12; // r3
  int i; // r1
  int j; // r1
  int k; // r1
  int m; // r1
  int v8; // r7
  int v9; // r6
  int v10; // r6
  int v11; // lr
  int v12; // r5
  unsigned int v13; // r2
  int v14; // r12
  int v15; // r3
  unsigned int dram_tpr10; // r3
  int n; // r2

  dram_tpr11 = para->dram_tpr11;
  dram_tpr12 = para->dram_tpr12;
  for ( i = 67121936; i != 67121972; i += 4 )
{
//    *(_DWORD *)i |= ((dram_tpr11 & 0xF) << 9) | (2 * (dram_tpr12 & 0xF));
	writel( readl( i ) | ((dram_tpr11 & 0xF) << 9) | (2 * (dram_tpr12 & 0xF)) , i );

}
  for ( j = 67122064; j != 67122100; j += 4 )
{
//    *(_DWORD *)j |= ((uint8_t)dram_tpr11 >> 4 << 9) | (2 * ((uint8_t)dram_tpr12 >> 4));
	writel( readl( j ) | ((uint8_t)dram_tpr11 >> 4 << 9) | (2 * ((uint8_t)dram_tpr12 >> 4)) , j );

}
  for ( k = 67122192; k != 67122228; k += 4 )
{
//    *(_DWORD *)k |= (((dram_tpr11 >> 8) & 0xF) << 9) | (2 * ((dram_tpr12 >> 8) & 0xF));
	writel( readl( k ) | (((dram_tpr11 >> 8) & 0xF) << 9) | (2 * ((dram_tpr12 >> 8) & 0xF)) , k );

}
  for ( m = 67122320; m != 67122356; m += 4 )
{
//    *(_DWORD *)m |= ((uint16_t)dram_tpr11 >> 12 << 9) | (2 * ((uint16_t)dram_tpr12 >> 12));
	writel( readl( m ) | ((uint16_t)dram_tpr11 >> 12 << 9) | (2 * ((uint16_t)dram_tpr12 >> 12)) , m );

}

  v8 = HIWORD(dram_tpr11) & 0xF;
  v9 = (v8 << 9) | (2 * (HIWORD(dram_tpr12) & 0xF));

//  MEMORY[0x4003100] &= ~0x4000000u;
//  MEMORY[0x4003334] |= v9;
//  MEMORY[0x4003338] |= v9;

	writel( readl(0x4003100) & ~0x4000000u , 0x4003100 );
	writel( readl(0x4003334) | v9 , 0x4003334 );
	writel( readl(0x4003338) | v9 , 0x4003338 );

  v10 = (dram_tpr11 >> 20) & 0xF;
  v11 = (v10 << 9) | (2 * ((dram_tpr12 >> 20) & 0xF));

//  MEMORY[0x40033B4] |= v11;
//  MEMORY[0x40033B8] |= v11;

	writel( readl(0x40033B4) | v11 , 0x40033B4 );
	writel( readl(0x40033B8) | v11 , 0x40033B8 );

  v12 = HIBYTE(dram_tpr11) & 0xF;
  v13 = dram_tpr11 >> 28;
  v14 = (v12 << 9) | (2 * (HIBYTE(dram_tpr12) & 0xF));

//  MEMORY[0x4003434] |= v14;
//  MEMORY[0x4003438] |= v14;

	writel( readl(0x4003434) | v14 , 0x4003434 );
	writel( readl(0x4003438) | v14 , 0x4003438 );

  v15 = (v13 << 9) | (2 * (dram_tpr12 >> 28));

//  MEMORY[0x40034B4] |= v15;
//  MEMORY[0x40034B8] |= v15;
//  MEMORY[0x400333C] |= v8 << 25;
//  MEMORY[0x40033BC] |= v10 << 25;

//  MEMORY[0x400343C] |= v12 << 25;
//  MEMORY[0x40034BC] |= v13 << 25;
//  MEMORY[0x4003100] |= 0x4000000u;

	writel( readl(0x40034B4) | v15 , 0x40034B4 );
	writel( readl(0x40034B8) | v15 , 0x40034B8 );
	writel( readl(0x400333C) | (v8 << 25) , 0x400333C );
	writel( readl(0x40033BC) | (v10 << 25) , 0x40033BC );

	writel( readl(0x400343C) | (v12 << 25) , 0x400343C );
	writel( readl(0x40034BC) | (v13 << 25) , 0x40034BC );

	writel( readl(0x4003100) | 0x4000000u , 0x4003100 );

  _usdelay(1);
  dram_tpr10 = para->dram_tpr10;
  for ( n = 67121728; n != 67121788; n += 4 )
{
//    *(_DWORD *)n |= (uint8_t)dram_tpr10 >> 4 << 8;
	writel( readl( n ) | ( (uint8_t)dram_tpr10 >> 4 << 8 ) , n );

}

//  MEMORY[0x4003218] |= (dram_tpr10 & 0xF) << 8;
//  MEMORY[0x400321C] |= dram_tpr10 & 0xF00;
//  MEMORY[0x4003280] |= (uint16_t)dram_tpr10 >> 12 << 8;

	writel( readl(0x4003218) | ((dram_tpr10 & 0xF) << 8) , 0x4003218 );
	writel( readl(0x400321C) | (dram_tpr10 & 0xF00) , 0x400321C );
	writel( readl(0x4003280) | ((uint16_t)dram_tpr10 >> 12 << 8) , 0x4003280 );

}

unsigned int  ccm_set_pll_ddr_sscg(__dram_para_t *para, unsigned int PLL_CTRL, unsigned int PLL_PAT)
{
  int v3; // r3
  unsigned int result; // r0


//  if ( (*(_DWORD *)PLL_CTRL & 2) != 0 )
//    *(_DWORD *)PLL_PAT |= 0x80000u;
  if ( ( readl( PLL_CTRL ) & 2) != 0 )
	writel( readl( PLL_PAT ) | 0x80000u , PLL_PAT );


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
//  *(_DWORD *)PLL_PAT = v3;
	writel( v3 , PLL_PAT );

  result = 0;
//  *(_DWORD *)PLL_CTRL |= 0x1000000u;
	writel( readl( PLL_CTRL ) | 0x1000000u , PLL_CTRL );

  return result;
}

unsigned int ccm_set_pll_ddr_clk(unsigned int pll, __dram_para_t *para)
{
  unsigned int v3; // r7
  unsigned int v4; // r5
  unsigned int dram_clk; // r0
  unsigned int v6; // r0
  int v7; // r3
  unsigned int v8; // r4
  unsigned int v9; // r3

  v3 = 50336016;
  v4 = 50335760;
  if ( pll )
    v3 = 50336024;
  if ( pll )
    v4 = 50335768;
  if ( ((para->dram_tpr13 >> 6) & 1) == pll )
    dram_clk = para->dram_clk;
  else
    dram_clk = para->dram_tpr9;
  v6 = 2 * dram_clk / 0x18;
  if ( v6 <= 0xB )
    v7 = 12;
  else
    v7 = v6;
  v8 = v6;
//  v9 = *(_DWORD *)v4 & 0x7FFF80FC | 0x80000000 | ((v7 - 1) << 8);
    v9 = readl( v4 ) & 0x7FFF80FC | 0x80000000 | ((v7 - 1) << 8);

//  *(_DWORD *)v4 = v9;
	writel ( v9 , v4 );

  v9 &= ~0x20000000u;
//  *(_DWORD *)v4 = v9;
	writel ( v9 , v4 );

//  *(_DWORD *)v4 = v9 | 0x20000000;
	writel ( v9 | 0x20000000 , v4 );

//  while ( (*(_DWORD *)v4 & 0x10000000) == 0 )
//    ;
  while ( ( readl( v4 ) & 0x10000000) == 0 );

  _usdelay(20);

  if ( (para->dram_tpr13 & 0x800000) != 0 )
    ccm_set_pll_ddr_sscg(para, v4, v3);
  return 24 * v8;
}

unsigned int mctl_core_init(__dram_para_t *para)
{
printf("do mctl_sys_init !\n");
  mctl_sys_init(para);
printf("do mctl_com_init !\n");
  mctl_com_init(para);
printf("do auto_set_timing_para !\n");
  auto_set_timing_para(para);
printf("do mctl_channel_init !\n");
  return mctl_channel_init(0, para);
}

unsigned int mctl_sys_init(__dram_para_t *para)
{
  unsigned int v2; // r0
  unsigned int dram_tpr9; // r3
  unsigned int v4; // r0
  unsigned int v5; // r0
  unsigned int v6; // r3

//  MEMORY[0x3001540] &= ~0x80000000;
//  MEMORY[0x3001540] &= ~0x40000000u;
//  MEMORY[0x300180C] &= ~1u;
//  MEMORY[0x300180C] &= ~0x10000u;

//  MEMORY[0x3001010] &= ~0x80000000;
//  MEMORY[0x3001010] |= 0x40000000u;
//  MEMORY[0x3001018] &= ~0x80000000;
//  MEMORY[0x3001018] |= 0x40000000u;

//  MEMORY[0x3001800] &= ~0x40000000u;

	writel( readl(0x3001540) & ~0x80000000 , 0x3001540 );
	writel( readl(0x3001540) & ~0x40000000u , 0x3001540 );
	writel( readl(0x300180C) & ~1u , 0x300180C );
	writel( readl(0x300180C) & ~0x10000u , 0x300180C );

	writel( readl(0x3001010) & ~0x80000000 , 0x3001010 );
	writel( readl(0x3001010) | 0x40000000u , 0x3001010 );
	writel( readl(0x3001018) & ~0x80000000 , 0x3001018 );
	writel( readl(0x3001018) | 0x40000000u , 0x3001018 );

	writel( readl(0x3001800) & ~0x40000000u , 0x3001800 );


  _usdelay(100);
  if ( (para->dram_tpr13 & 0x40) != 0 )
  {
    v2 = ccm_set_pll_ddr_clk(1u, para);
//    MEMORY[0x3001800] = MEMORY[0x3001800] & 0xFCFFFFFF | 0x1000000;

	writel( readl(0x3001800) & 0xFCFFFFFF | 0x1000000 , 0x3001800 );

    dram_tpr9 = para->dram_tpr9;
    para->dram_clk = v2 >> 1;
    if ( dram_tpr9 )
    {
      v4 = 0;
LABEL_6:
      para->dram_tpr9 = ccm_set_pll_ddr_clk(v4, para) >> 1;
    }
  }
  else
  {
    v5 = ccm_set_pll_ddr_clk(0, para);
//    MEMORY[0x3001800] &= 0xFCFFFFFF;

	writel( readl(0x3001800) & 0xFCFFFFFF , 0x3001800 );

    v6 = para->dram_tpr9;
    para->dram_clk = v5 >> 1;
    if ( v6 )
    {
      v4 = 1;
      goto LABEL_6;
    }
  }
  _usdelay(1000);
//  MEMORY[0x3001800] = MEMORY[0x3001800] & 0xF7FFFFFC | 0x8000000;
//  MEMORY[0x300180C] |= 0x10000u;
//  MEMORY[0x300180C] |= 1u;

	writel( readl(0x3001800) & 0xF7FFFFFC | 0x8000000 , 0x3001800 );
	writel( readl(0x300180C) | 0x10000u , 0x300180C );
	writel( readl(0x300180C) | 1u , 0x300180C );

  dram_disable_all_master();
//  MEMORY[0x3001540] |= 0x40000000u;
//  MEMORY[0x3001540] |= 0x80000000;
//  MEMORY[0x3001800] |= 0x40000000u;

	writel( readl(0x3001540) | 0x40000000u , 0x3001540 );
	writel( readl(0x3001540) | 0x80000000 , 0x3001540 );
	writel( readl(0x3001800) | 0x40000000u , 0x3001800 );

  _usdelay(5);

//  MEMORY[0x400300C] = 0x8000;

	writel( 0x8000 , 0x400300C );

  _usdelay(10);
  return 0;
}

unsigned int mctl_channel_init(unsigned int ch_index, __dram_para_t *para)
{
  unsigned int v3; // r6
  unsigned int dram_clk; // r0
  int v5; // r5
  int i; // r3
  unsigned int v7; // r2
  unsigned int v8; // r2
  unsigned int v9; // r2
  int v10; // r2
  int v11; // r3
  int v12; // r5

  v3 = (para->dram_tpr13 >> 2) & 3;
  dram_clk = para->dram_clk;
  v5 = 32 * !(para->dram_odt_en & 1);
//  MEMORY[0x400200C] = MEMORY[0x400200C] & 0xFFFFF000 | 0x18F;
//  MEMORY[0x4003108] = MEMORY[0x4003108] & 0xFFFFF0FF | 0x300;

	writel( readl(0x400200C) & 0xFFFFF000 | 0x18F  , 0x400200C );
	writel( readl(0x4003108) & 0xFFFFF0FF | 0x300  , 0x4003108 );

  for ( i = 67121988; i != 67122500; i += 128 )
  {
//    v7 = *(_DWORD *)i & 0xFFFF0FC1 | v5;
//    if ( dram_clk > 0x2A0 ) v7 = *(_DWORD *)i & 0xFFFF09C1 | v5 & 0xFFFFF9FF | 0x400;
//    *(_DWORD *)i = v7;

	v7 = readl( i ) & 0xFFFF0FC1 | v5;
	if ( dram_clk > 0x2A0 ) v7 = readl( i ) & 0xFFFF09C1 | v5 & 0xFFFFF9FF | 0x400;
	writel( v7 , i );

  }
//  MEMORY[0x4003208] |= 2u;

	writel( readl(0x4003208) | 2u , 0x4003208 );

  eye_delay_compensation(para);
  if ( v3 == 1 )
  {
//    MEMORY[0x4003108] &= 0xFFFFFF3F;
//    MEMORY[0x40030BC] &= 0xFFFFFEF8;

	writel( readl(0x4003108) & 0xFFFFFF3F , 0x4003108 );
	writel( readl(0x40030BC) & 0xFFFFFEF8 , 0x40030BC );

  }
  else if ( v3 == 2 )
  {
//    MEMORY[0x4003108] = MEMORY[0x4003108] & 0xFFFFFF3F | 0x80;
//    MEMORY[0x40030BC] = MEMORY[0x40030BC] & 0xFFFFFEF8 | 0x100 | ((HIWORD(MEMORY[0x4003060]) & 0x1F) - 2);
//    MEMORY[0x400311C] = MEMORY[0x400311C] & 0x77FFFFFF | 0x8000000;

	writel( readl(0x4003108) & 0xFFFFFF3F | 0x80 , 0x4003108 );
	writel( readl(0x40030BC) & 0xFFFFFEF8 | 0x100 | ((HIWORD(readl(0x4003060)) & 0x1F) - 2) , 0x40030BC );
	writel( readl(0x400311C) & 0x77FFFFFF | 0x8000000 , 0x400311C );

  }
  else
  {
//    MEMORY[0x4003108] &= ~0x40u;

	writel( readl(0x4003108) & ~0x40u , 0x4003108 );

    _usdelay(10);
//    MEMORY[0x4003108] |= 0xC0u;

	writel( readl(0x4003108) | 0xC0u , 0x4003108 );

  }
  if ( (para->dram_type - 6) <= 1 )
  {
    if ( v3 == 1 )
//      v8 = MEMORY[0x400311C] & 0x77FFFF3F | 0x80000000;
	v8 = readl(0x400311C) & 0x77FFFF3F | 0x80000000;
    else
//      v8 = MEMORY[0x400311C] & 0x88FFFFFF | 0x22000000;
	v8 = readl(0x400311C) & 0x88FFFFFF | 0x22000000;

//    MEMORY[0x400311C] = v8;
	writel( v8 , 0x400311C );

  }
//  v9 = MEMORY[0x40030C0] & 0xF0000000;
	v9 = readl(0x40030C0) & 0xF0000000;

  if ( (para->dram_para2 & 0x1000) != 0 )
    v10 = v9 | 0x3000000;
  else
    v10 = v9 | 0x1000000;

//  MEMORY[0x40030C0] = v10 | 1;
//  MEMORY[0x4003140] = MEMORY[0x4003140] & 0xFC000000 | para->dram_zq & 0xFFFFFF | 0x2000000;

  writel( v10 | 1 , 0x40030C0 );
  writel( readl(0x4003140) & 0xFC000000 | para->dram_zq & 0xFFFFFF | 0x2000000  , 0x4003140 );

  if ( v3 == 1 )
  {
//    MEMORY[0x4003000] = 83;
	writel( 83 , 0x4003000 );

//    while ( (MEMORY[0x4003010] & 1) == 0 )
//      ;

	while ( (readl(0x4003010) & 1) == 0 );

    _usdelay(10);
    if ( para->dram_type == 3 )
      v11 = 1440;
    else
      v11 = 1312;
  }
  else if ( para->dram_type == 3 )
  {
    v11 = 498;
  }
  else
  {
    v11 = 370;
  }
//  MEMORY[0x4003000] = v11 | 1;
	writel( v11 | 1 , 0x4003000 );

  _usdelay(10);
//  while ( (MEMORY[0x4003010] & 1) == 0 )
//    ;

	while ( (readl(0x4003010) & 1) == 0 );

//  if ( (unsigned __int8)(MEMORY[0x4003010] >> 20) )
if ( (uint8_t)(readl(0x4003010) >> 20) )
  {
//    v12 = MEMORY[0x4003010] & 0x100000;
	v12 = readl(0x4003010) & 0x100000;

//    if ( (MEMORY[0x4003010] & 0x100000) != 0 )
	if ( (readl(0x4003010) & 0x100000) != 0 )
    {
      v12 = 0;
      printf("ZQ calibration error,check external 240 ohm resistor.\n");
      return v12;
    }
  }
  else
  {
    v12 = 1;
  }
//  while ( (MEMORY[0x4003018] & 1) == 0 )
//    ;

	while ( (readl(0x4003018) & 1) == 0 );

//  MEMORY[0x400308C] |= 0x80000000;
//  _usdelay(10);
//  MEMORY[0x400308C] &= ~0x80000000;
//  _usdelay(10);
//  MEMORY[0x4002014] |= 0x80000000;
//  _usdelay(10);
//  MEMORY[0x400310C] &= 0xF9FFFFFF;
//  if ( v3 == 1 )
//    MEMORY[0x400311C] = MEMORY[0x400311C] & 0xFFFFFF3F | 0x40;

	writel( readl(0x400308C) | 0x80000000 , 0x400308C );
	_usdelay(10);
	writel( readl(0x400308C) & ~0x80000000 , 0x400308C );
	_usdelay(10);
	writel( readl(0x4002014) | 0x80000000 , 0x4002014 );
	_usdelay(10);
	writel( readl(0x400310C) & 0xF9FFFFFF , 0x400310C );
	if ( v3 == 1 )
		writel( readl(0x400311C) & 0xFFFFFF3F | 0x40 , 0x400311C );

  return v12;
}

void mctl_com_init(__dram_para_t *para)
{
  unsigned int dram_para2; // r3
  int v2; // r12
  int v3; // r5
  unsigned int dram_tpr13; // r1
  bool v5; // cc
  unsigned int v6; // r2
  unsigned int v7; // r7
  unsigned int dram_para1; // r6
  int v9; // r3
  int v10; // r5
  char v11; // r4
  unsigned int v12; // r1
  unsigned int v13; // r2
  int v14; // r2
  int v15; // r2
  unsigned int dram_tpr4; // r3

  dram_para2 = para->dram_para2;
  v2 = dram_para2 & 1;
  if ( (dram_para2 & 1) != 0 )
    v3 = 0;
  else
    v3 = 4096;
  dram_tpr13 = para->dram_type - 6;
  v5 = dram_tpr13 > 1;
//  v6 = MEMORY[0x4002000] & 0xFF000FFF | 0x400000 | ((para->dram_type & 7) << 16) | v3;

	v6 = readl(0x4002000) & 0xFF000FFF | 0x400000 | ((para->dram_type & 7) << 16) | v3;

  if ( dram_tpr13 <= 1 )
    v6 |= 0x80000u;
  else
    dram_tpr13 = para->dram_tpr13;
  if ( v5 )
    v6 |= ((dram_tpr13 >> 5) & 1) << 19;
//  MEMORY[0x4002000] = v6;

	writel( v6 , 0x4002000 );

  if ( (dram_para2 & 0x100) != 0 )
  {
    if ( (uint16_t)dram_para2 >> 12 == 1 )
      v7 = 2;
    else
      v7 = 1;
  }
  else
  {
    v7 = 1;
  }
  dram_para1 = para->dram_para1;
  v9 = (dram_para2 >> 12) & 3;
  v10 = 67117056;
  v11 = 12;
  v12 = 0;
  do
  {
//    v13 = *(_DWORD *)v10 & 0xFFFFF000 | v9 | (4 * ((dram_para1 >> v11) & 1)) | (uint8_t)(16 * ((dram_para1 >> (v11 - 8)) - 1));

    v13 = readl( v10 ) & 0xFFFFF000 | v9 | (4 * ((dram_para1 >> v11) & 1)) | (uint8_t)(16 * ((dram_para1 >> (v11 - 8)) - 1));

    switch ( (dram_para1 >> (16 * v12)) & 0xF )
    {
      case 1u:
        v14 = v13 | 0x700;
        break;
      case 2u:
        v14 = v13 | 0x800;
        break;
      case 4u:
        v14 = v13 | 0x900;
        break;
      case 8u:
        v14 = v13 | 0xA00;
        break;
      default:
        v14 = v13 | 0x600;
        break;
    }
    ++v12;
    v11 += 16;
//    *(_DWORD *)v10 = v14;
	writel( v14 , v10 );

    v10 += 4;
  }
  while ( v12 < v7 );
  v15 = 513;

//  if ( (MEMORY[0x4002000] & 1) != 0 ) v15 = 771;
//  MEMORY[0x4003120] = v15;

	if ( ( readl(0x4002000) & 1) != 0 ) v15 = 771;
	writel( v15 , 0x4003120 );

  if ( v2 )
  {
//    MEMORY[0x4003444] = 0;
//    MEMORY[0x40034C4] = 0;

	writel( 0 , 0x4003444 );
	writel( 0 , 0x40034C4 );

  }
  dram_tpr4 = para->dram_tpr4;
  if ( dram_tpr4 )
  {
//    MEMORY[0x4002000] |= (para->dram_tpr4 & 3) << 25;
//    MEMORY[0x4002004] |= ((dram_tpr4 >> 2) & 0x1FF) << 12;

	writel( readl(0x4002000) | ( (para->dram_tpr4 & 3) << 25 ) , 0x4002000 );
	writel( readl(0x4002004) | ( ((dram_tpr4 >> 2) & 0x1FF) << 12 ) , 0x4002004 );

  }
}


int init_DRAM(int type, __dram_para_t *para)
{
  unsigned int dram_size; // r5
  int v4; // r0
  int v5; // r1
  signed int dram_para2; // r5
  unsigned int v7; // r1
  unsigned int dram_tpr8; // r2
  const char *v9; // r0
  unsigned int dram_tpr13; // r3
  unsigned int v11; // r1
  unsigned int v12; // r1

//  MEMORY[0x7010310] |= 0x100u;
//  MEMORY[0x7010318] = 0;
  writel ( ( readl(0x7010310) | 0x100u) , 0x7010310);
  writel (  0 , 0x7010318);

  _usdelay(10);

//  dram_size = bond_id_check();

// MUST let bond_id_check return 1
// Add
  dram_size = 1;


  if ( dram_size )
  {
    printf("chip id check OK\n");
    if ( ((para->dram_tpr13 & 0x2000) == 0 || (v4 = dram_vol_set(para)) != 0)
      && ((para->dram_tpr13 & 1) != 0 || (v4 = auto_scan_dram_config(para)) != 0) )
//  disable auto_scan_dram_config func temporary
//if (1)
    {
      printf("DRAM BOOT DRIVE INFO: %s\n", "V0.573");
      printf("DRAM CLK = %d MHZ\n", para->dram_clk);
      printf("DRAM Type = %d (2:DDR2,3:DDR3,6:LPDDR2,7:LPDDR3)\n", para->dram_type);
      printf("DRAM ZQ value: 0x%x\n", para->dram_zq);
      dram_size = mctl_core_init(para);
      if ( dram_size )
      {
        dram_para2 = para->dram_para2;
        if ( dram_para2 >= 0 )
        {
          dram_size = DRAMC_get_dram_size();
          v7 = dram_size;
          if ( dram_size >= 0xC00 )
            dram_size = 3072;
          printf("DRAM SIZE =%d M\n", v7);
          para->dram_para2 = LOWORD(para->dram_para2) | (dram_size << 16);
        }
        else
        {
          dram_size = HIWORD(dram_para2) & 0x7FFF;
        }
        if ( (para->dram_tpr13 & 0x40000000) != 0 )
        {
          dram_tpr8 = para->dram_tpr8;
          v5 = 268435968;
          v9 = "Enable Auto SR\n";
          if ( !dram_tpr8 )
            dram_tpr8 = 268435968;
//          MEMORY[0x40030A0] = dram_tpr8;
//          MEMORY[0x400309C] = 1034;
//          MEMORY[0x4003004] |= 1u;

		writel ( dram_tpr8 , 0x40030A0);
		writel ( 1034 , 0x400309C);
		writel ( ( readl(0x4003004) | 1u) , 0x4003004);

        }
        else
        {
          v9 = "Disable Auto SR\n";

//          MEMORY[0x40030A0] = HIWORD(MEMORY[0x40030A0]) << 16;
//          MEMORY[0x4003004] &= ~1u;

		writel ( (  HIWORD(readl(0x40030A0)) << 16  ) , 0x40030A0);
		writel ( ( (readl(0x4003004)) & (~1u) ) , 0x4003004);

        }
        printf(v9, v5);
        dram_tpr13 = para->dram_tpr13;
        if ( (dram_tpr13 & 0x200) != 0 || para->dram_type == 6 )
{
//          v11 = MEMORY[0x4003100] & 0xFFFF0FFF | 0x5000;

          v11 = (readl(0x4003100) & 0xFFFF0FFF) | 0x5000;

}
        else
{
//          v11 = MEMORY[0x4003100] & 0xFFFF0FFF;

          v11 = readl(0x4003100) & 0xFFFF0FFF;

}

//        MEMORY[0x4003100] = v11;
//        MEMORY[0x4003140] |= 0x80000000;

	writel( v11 , 0x4003100 );
	writel( (readl(0x4003140) | 0x80000000 ) , 0x4003140 );

        if ( (dram_tpr13 & 0x100) != 0 )
{
//          MEMORY[0x40030B8] |= 0x300u;

	writel( ( readl(0x40030B8) | 0x300u ) , 0x40030B8 );

}
        if ( (dram_tpr13 & 0x4000000) != 0 )
{
//          v12 = MEMORY[0x4003108] & 0xFFFFDFFF;

		v12 = readl(0x4003108) & 0xFFFFDFFF;

}
        else
{
//          v12 = MEMORY[0x4003108] | 0x2000;

		v12 = readl(0x4003108) | 0x2000;

}
//        MEMORY[0x4003108] = v12;

		writel ( v12 , 0x4003108 );

        if ( para->dram_type == 7 )
{
//          MEMORY[0x400307C] = MEMORY[0x400307C] & 0xFFF0FFFF | 0x10000;

		writel ( ( readl(0x400307C) & 0xFFF0FFFF | 0x10000 ) , 0x400307C);

}
        if ( (dram_tpr13 & 0x8000000) == 0 )
        {
          if ( (dram_tpr13 & 0x1000000) != 0 )
            set_master_priority_pad();
          else
            set_master_priority();
        }
        dram_enable_all_master();
// disable dramc_simple_wr_test
        if ( (para->dram_tpr13 & 0x10000000) != 0 && dramc_simple_wr_test(dram_size, 0x1000u) )
          return 0;
      }
      else
      {
        printf("DRAM initial error : 1 !\n");
      }
    }
    else
    {
      return v4;
    }
  }
  else
  {
    printf("ic cant match axp, please check...\n");
  }
  return dram_size;
}


unsigned int dramc_simple_wr_test(unsigned int dram_size, unsigned int test_length)
{
  int v2; // r2
  unsigned int v3; // r0
  int i; // r3
  int v5; // r4
  int v6; // r4
  int j; // r3
  unsigned int v8; // r5
  int v9; // r7
  int v10; // r6
  int v11; // r6
  int v12; // r5

  v2 = 0x40000000;
  v3 = dram_size >> 1 << 20;
  for ( i = 0; i != test_length; ++i )
  {
//    *(_DWORD *)v2 = i + 19088743;
	writel (  i + 19088743 , v2 );

    v5 = i - 19088744;
 //   *(_DWORD *)(v2 + v3) = v5;
	writel ( v5 , (v2 + v3) );


    v2 += 4;
  }
  v6 = 0x40000000;
  for ( j = 0; j != test_length; ++j )
  {
    v8 = v6 + v3;
//    v9 = *(_DWORD *)(v6 + v3);
	v9 = readl( (v6 + v3) );

    v10 = j - 19088744;
    if ( v9 != (j - 19088744) )
    {
      printf("DRAM simple test FAIL.\n");
      printf("%x != %x at address %x\n", v9, v10, v8);
      return 1;
    }
//    v11 = *(_DWORD *)v6;
	v11 = readl( v6 );

    v12 = j + 19088743;

    if ( v11 != (j + 19088743) )
    {
      printf("DRAM simple test FAIL.\n");
      printf("%x != %x at address %x\n", v11, v12, v6);
      return 1;
    }
    v6 += 4;
  }
  printf("DRAM simple test OK.\n");
  return 0;
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

#ifdef LOCAL_BUILD_TEST
int main ()
{
#else
unsigned long sunxi_dram_init(void)
{
#endif


__dram_para_t now_dram_para = {

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

#ifndef LOCAL_BUILD_TEST
  return (size << 20);
#else
  return 0;
#endif

};



