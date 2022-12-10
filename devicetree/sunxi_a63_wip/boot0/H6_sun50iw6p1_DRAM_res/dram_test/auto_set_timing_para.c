#include "dram_base.h"

void  auto_set_timing_para(__dram_para_t *para)
{
  unsigned int dram_clk; // r7
  unsigned int dram_type; // r9
  unsigned int v4; // r5
  unsigned int dram_tpr0; // r3
  unsigned int v6; // r8
  int v7; // r6
  int v8; // r2
  unsigned int dram_tpr1; // r3
  unsigned int v10; // r10
  int v11; // r2
  unsigned int v12; // r6
  unsigned int dram_tpr2; // r3
  unsigned int v14; // r0
  int v15; // r0
  uint16_t v16; // r0
  unsigned int v17; // r0
  int v18; // r0
  int v19; // r0
  int v20; // r2
  int v21; // r0
  unsigned int v22; // r0
  unsigned int v23; // r0
  int v24; // r0
  uint16_t v25; // r0
  int v26; // r0
  unsigned int v27; // r11
  int v28; // r6
  int v29; // r0
  uint16_t v30; // r0
  int v31; // r0
  int v32; // r0
  int v33; // r0
  int v34; // r9
  bool v35; // cc
  int v36; // r11
  int v37; // r3
  int v38; // r5
  int v39; // r12
  unsigned int v40; // r3
  unsigned int v41; // r5
  int v42; // r2
  int v43; // r1
  int v44; // r2
  int v45; // r7
  int v46; // r2
  bool v47; // cc
  int v48; // r2
  int v49; // r3
  unsigned int v50; // r11
  int v51; // r3
  unsigned int v52; // r11
  int v53; // r2
  int v54; // r2
  int v55; // r5
  int twtr_s; // [sp+Ch] [bp-ACh]
  int twtr_sa; // [sp+Ch] [bp-ACh]
  unsigned int twr; // [sp+10h] [bp-A8h]
  int tfaw; // [sp+14h] [bp-A4h]
  int txp; // [sp+18h] [bp-A0h]
  int tcl; // [sp+1Ch] [bp-9Ch]
  int trrd_s; // [sp+20h] [bp-98h]
  int mr1; // [sp+24h] [bp-94h]
  int tcke; // [sp+28h] [bp-90h]
  int trp; // [sp+2Ch] [bp-8Ch]
  int twtr; // [sp+30h] [bp-88h]
  int tcksre; // [sp+34h] [bp-84h]
  unsigned int tcksrea; // [sp+34h] [bp-84h]
  int t_rdata_en; // [sp+38h] [bp-80h]
  int tmod; // [sp+3Ch] [bp-7Ch]
  int trc; // [sp+40h] [bp-78h]
  int tras; // [sp+44h] [bp-74h]
  int trfc; // [sp+48h] [bp-70h]
  int txs; // [sp+4Ch] [bp-6Ch]
  int tccd; // [sp+50h] [bp-68h]
  int trefi; // [sp+54h] [bp-64h]
  int tckesr; // [sp+58h] [bp-60h]
  int txsr; // [sp+5Ch] [bp-5Ch]
  int tmrd; // [sp+60h] [bp-58h]
  int txsdll; // [sp+64h] [bp-54h]
  int twr2rd_s; // [sp+68h] [bp-50h]
  unsigned int tdinit0; // [sp+6Ch] [bp-4Ch]
  unsigned int tdinit1; // [sp+70h] [bp-48h]
  unsigned int tdinit2; // [sp+74h] [bp-44h]
  unsigned int tdinit3; // [sp+78h] [bp-40h]
  int mr3; // [sp+7Ch] [bp-3Ch]
  int twtp; // [sp+80h] [bp-38h]
  int trasmax; // [sp+84h] [bp-34h]
  int twr2rd; // [sp+88h] [bp-30h]
  int tccd_s; // [sp+8Ch] [bp-2Ch]

  dram_clk = para->dram_clk;
  dram_type = para->dram_type;
  v4 = para->dram_clk >> 1;
  if ( (para->dram_tpr13 & 2) != 0 )
  {
    dram_tpr0 = para->dram_tpr0;
    trrd_s = (dram_tpr0 >> 27) & 0xF;
    tccd_s = HIBYTE(dram_tpr0) & 7;
    v6 = (dram_tpr0 >> 11) & 0xF;
    v7 = (dram_tpr0 >> 15) & 0x3F;
    tccd = (dram_tpr0 >> 21) & 7;
    v8 = (dram_tpr0 >> 6) & 0x1F;
    trc = dram_tpr0 & 0x3F;
    dram_tpr1 = para->dram_tpr1;
    tfaw = v7;
    twr = v8;
    twtr_s = (dram_tpr1 >> 28) & 7;
    txp = (dram_tpr1 >> 23) & 0x1F;
    v10 = (dram_tpr1 >> 15) & 0x1F;
    v11 = (dram_tpr1 >> 6) & 0x1F;
    twtr = (dram_tpr1 >> 20) & 7;
    v12 = (dram_tpr1 >> 11) & 0xF;
    tras = dram_tpr1 & 0x3F;
    dram_tpr2 = para->dram_tpr2;
    trp = v11;
    txs = (dram_tpr2 >> 21) & 0x7F;
    trfc = (dram_tpr2 >> 12) & 0x1FF;
    trefi = dram_tpr2 & 0xFFF;
    goto LABEL_50;
  }
  if ( dram_type != 3 )
  {
    switch ( dram_type )
    {
      case 4u:
        tfaw = (uint8_t)auto_cal_timing(0x23u, para->dram_clk >> 1);
        v17 = (uint8_t)auto_cal_timing(8u, v4);
        if ( (uint8_t)v17 < 2u )
          v6 = 2;
        else
          v6 = v17;
        v18 = (uint8_t)auto_cal_timing(6u, v4);
        v10 = v6;
        if ( (uint8_t)v18 < 2u )
          v18 = 2;
        trrd_s = v18;
        twr = (uint8_t)auto_cal_timing(0xFu, v4);
        twtr = v6;
        trc = (uint8_t)auto_cal_timing(0x31u, v4);
        txp = trrd_s;
        v19 = (uint8_t)auto_cal_timing(3u, v4);
        if ( !(_BYTE)v19 )
          v19 = 1;
        twtr_s = v19;
        tras = (uint8_t)auto_cal_timing(0x22u, v4);
        trefi = (uint16_t)(auto_cal_timing(0x1E78u, v4) >> 5);
        trfc = (uint16_t)auto_cal_timing(0x15Eu, v4);
        v12 = twr;
        txs = (uint8_t)(auto_cal_timing(0x168u, v4) >> 5);
        v20 = 3;
        trp = twr;
        break;
      case 6u:
        v21 = (uint8_t)auto_cal_timing(0x32u, para->dram_clk >> 1);
        if ( (uint8_t)v21 <= 3u )
          v21 = 4;
        tfaw = v21;
        v6 = (uint8_t)auto_cal_timing(0xAu, v4);
        v22 = (uint8_t)auto_cal_timing(0x18u, v4);
        if ( !v6 )
          v6 = 1;
        if ( v22 <= 1 )
          v22 = 2;
        twr = v22;
        trc = (uint8_t)auto_cal_timing(0x46u, v4);
        v23 = (uint8_t)auto_cal_timing(8u, v4);
        txp = v23;
        if ( !(_BYTE)v23 || v23 == 1 )
        {
          v10 = 2;
          txp = 1;
        }
        else
        {
          v10 = v23;
        }
        v12 = (uint8_t)auto_cal_timing(0xFu, v4);
        v24 = (uint8_t)auto_cal_timing(0x12u, v4);
        if ( v12 <= 1 )
          v12 = 2;
        trp = v24;
        tras = (uint8_t)auto_cal_timing(0x2Au, v4);
        trefi = (uint16_t)(auto_cal_timing(0xF3Cu, v4) >> 5);
        v25 = auto_cal_timing(0xD2u, v4);
        twtr_s = 1;
        v20 = 2;
        trfc = v25;
        twtr = v10;
        trrd_s = 2;
        txs = 4;
        break;
      case 7u:
        v26 = (uint8_t)auto_cal_timing(0x32u, para->dram_clk >> 1);
        if ( (uint8_t)v26 <= 3u )
          v26 = 4;
        tfaw = v26;
        v6 = (uint8_t)auto_cal_timing(0xAu, v4);
        v27 = (uint8_t)auto_cal_timing(0x12u, v4);
        if ( v27 < 2 )
          v28 = 2;
        else
          v28 = v27;
        if ( !v6 )
          v6 = 1;
        twr = v28;
        trc = (uint8_t)auto_cal_timing(0x46u, v4);
        v10 = (uint8_t)auto_cal_timing(8u, v4);
        v12 = (uint8_t)auto_cal_timing(0xFu, v4);
        v29 = (uint8_t)auto_cal_timing(0x2Au, v4);
        if ( v12 <= 1 )
          v12 = 2;
        tras = v29;
        trefi = (uint16_t)(auto_cal_timing(0xF3Cu, v4) >> 5);
        v30 = auto_cal_timing(0xD2u, v4);
        if ( v10 <= 1 )
          v10 = 2;
        twtr_s = 1;
        trfc = v30;
        txp = v10;
        twtr = v10;
        trp = v27;
        trrd_s = 2;
        txs = 4;
        goto LABEL_46;
      default:
        txs = 4;
        twtr_s = 1;
        txp = 10;
        v10 = 3;
        trrd_s = 2;
        trfc = 128;
        tras = 14;
        trefi = 98;
        v6 = 3;
        trp = 6;
        v12 = 8;
        trc = 20;
        v20 = 2;
        tfaw = 16;
        twtr = 3;
        twr = 6;
        break;
    }
    tccd = v20;
    goto LABEL_49;
  }
  tfaw = (uint8_t)auto_cal_timing(0x32u, para->dram_clk >> 1);
  v6 = (uint8_t)auto_cal_timing(0xAu, v4);
  v14 = (uint8_t)auto_cal_timing(0xFu, v4);
  if ( v6 <= 1 )
    v6 = 2;
  twr = v14;
  trc = (uint8_t)auto_cal_timing(0x35u, v4);
  v10 = (uint8_t)auto_cal_timing(8u, v4);
  v12 = twr;
  v15 = (uint8_t)auto_cal_timing(0x26u, v4);
  if ( v10 <= 1 )
    v10 = 2;
  tras = v15;
  trefi = (uint16_t)(auto_cal_timing(0x1E78u, v4) >> 5);
  v16 = auto_cal_timing(0x15Eu, v4);
  if ( twr < 2 )
    v12 = 2;
  trfc = v16;
  txs = (uint8_t)(auto_cal_timing(0x168u, v4) >> 5);
  txp = v10;
  trp = twr;
  twtr = v10;
  twtr_s = 1;
  trrd_s = 2;
LABEL_46:
  tccd = 2;
LABEL_49:
  para->dram_tpr0 = trc | 0x2000000 | (twr << 6) | (v6 << 11) | (tfaw << 15) | (tccd << 21) | (trrd_s << 27);
  para->dram_tpr1 = (v12 << 11) | (trp << 6) | tras | (v10 << 15) | (twtr << 20) | (txp << 23) | (twtr_s << 28);
  para->dram_tpr2 = (txs << 21) | (trfc << 12) | trefi;
  tccd_s = 2;
LABEL_50:
  switch ( dram_type )
  {
    case 3u:
      v47 = v4 > 0x18F;
      v41 = 4116;
      if ( v47 )
        v48 = 7;
      else
        v48 = 6;
      if ( v47 )
        v49 = 9;
      else
        v49 = 7;
      tcl = v48;
      if ( !v47 )
        v41 = 4208;
      if ( v47 )
        v36 = 5;
      else
        v36 = 4;
      t_rdata_en = v49;
      if ( v47 )
        v40 = 32;
      else
        v40 = 24;
      mr1 = para->dram_mr1;
      tdinit0 = 500 * dram_clk + 1;
      tdinit2 = 200 * dram_clk + 1;
      tdinit1 = 360 * dram_clk / 0x3E8 + 1;
      tdinit3 = dram_clk + 1;
      switch ( 2 * (__int16)v12 )
      {
        case 8:
          v41 |= 0x800u;
          break;
        case 10:
          v41 |= 0xA00u;
          break;
        case 12:
          v41 |= 0xC00u;
          break;
        case 14:
          v41 |= 0xE00u;
          break;
        case 16:
          break;
        default:
          v41 |= 0x400u;
          break;
      }
      v34 = 4;
      v43 = 5;
      v39 = v48;
      twtp = (uint8_t)(v12 + 2 + v36);
      twr2rd_s = 8;
      trasmax = 24;
      twtr_sa = 2;
      tcke = 3;
      v46 = 0;
      twr2rd = (uint8_t)(twtr + 2 + v36);
      txsdll = 4;
      v45 = 5;
      txsr = 4;
      tckesr = 4;
      tcksrea = 4;
      tmod = 12;
      tmrd = 4;
      mr3 = 0;
      break;
    case 4u:
      v31 = (uint8_t)auto_cal_timing(0xFu, v4);
      if ( (uint8_t)v31 <= 0xBu )
        v31 = 12;
      tmod = v31;
      v32 = (uint8_t)auto_cal_timing(5u, v4);
      if ( (uint8_t)v32 <= 1u )
        v32 = 2;
      tcke = v32;
      v33 = (uint8_t)auto_cal_timing(0xAu, v4);
      if ( (uint8_t)v33 <= 2u )
        v33 = 3;
      tcksre = v33;
      tckesr = (uint8_t)(tcke + 1);
      trasmax = (uint8_t)(v4 / 0xF);
      v34 = (uint8_t)(auto_cal_timing(0xAAu, v4) >> 5);
      if ( v4 < 0x190 )
      {
        v36 = 5;
        v39 = 6;
        tcl = 7;
        t_rdata_en = 7;
        v40 = 0;
        v41 = 16;
      }
      else if ( v4 < 0x1D2 )
      {
        v36 = 5;
        t_rdata_en = 9;
        v39 = 7;
        v41 = 32;
        v40 = 8;
        tcl = 8;
      }
      else
      {
        v35 = v4 > 0x214;
        v36 = 6;
        if ( v4 <= 0x214 )
          v37 = 9;
        else
          v37 = 10;
        if ( v4 <= 0x214 )
          v38 = 11;
        else
          v38 = 12;
        tcl = v37;
        v39 = 8;
        t_rdata_en = v38;
        if ( v35 )
          v40 = 24;
        else
          v40 = 16;
        if ( v35 )
          v41 = 52;
        else
          v41 = 48;
      }
      mr1 = para->dram_mr1;
      tdinit0 = 500 * dram_clk + 1;
      tdinit1 = 360 * dram_clk / 0x3E8 + 1;
      v42 = 2 * (__int16)v12;
      tdinit2 = 200 * dram_clk + 1;
      switch ( v42 )
      {
        case 12:
          v41 |= 0x200u;
          break;
        case 14:
          v41 |= 0x400u;
          break;
        case 16:
          v41 |= 0x600u;
          break;
        case 18:
          v41 |= 0x800u;
          break;
        case 20:
          v41 |= 0xA00u;
          break;
        case 24:
          v41 |= 0xC00u;
          break;
        default:
          if ( v42 <= 9 )
            v12 = ( v12 - LOBYTE(v12) ) + 5;
          break;
      }
      txsdll = 16;
      v43 = tcksre;
      twtp = (uint8_t)(v12 + v36 + 2);
      tdinit3 = 1024;
      twr2rd = (uint8_t)(twtr + 2 + v36);
      v44 = (uint8_t)(twtr_s + 2 + v36);
      twtr_sa = 2;
      twr2rd_s = v44;
      mr3 = 512;
      v45 = (uint8_t)(v39 + 4 - v36);
      txsr = 4;
      tcksrea = 4;
      tmrd = 4;
      v46 = 0;
      break;
    case 6u:
      trasmax = (uint8_t)(v4 / 0x1E);
      v50 = 2500 * dram_clk % 0xF4240;
      if ( v50 )
        v50 = ( v50 - LOBYTE(v50) ) + 1;
      twtr_sa = (uint8_t)(2500 * dram_clk / 0xF4240 + v50);
      tcksrea = (uint8_t)(v50 + 5500 * dram_clk / 0xF4240);
      txsr = (uint8_t)auto_cal_timing(0x8Cu, v4);
      t_rdata_en = (uint8_t)(twtr_sa + 4);
      tdinit0 = 200 * dram_clk + 1;
      mr3 = para->dram_mr3;
      v51 = 2 * (__int16)v12;
      tdinit2 = 11 * dram_clk + 1;
      tdinit1 = 100 * dram_clk / 0x3E8 + 1;
      tdinit3 = dram_clk + 1;
      if ( (unsigned int)(v51 - 6) > 4 )
      {
        if ( v51 <= 4 ) 
         v12 = ( v12 - LOBYTE(v12) ) + 3;
        mr1 = 99;
      }
      else
      {
//        mr1 = CSWTCH_32[v51 - 6];
//may be ERROR
// change to   mr1 =  para->dram_mr1 ;  may help ?
	mr1 = 0x40 ;

      }
      v43 = 5;
      tckesr = 5;
      twtp = (uint8_t)(v12 + 5);
      v34 = 4;
      twr2rd_s = 8;
      v46 = 3;
      twr2rd = (uint8_t)(twtr + 5);
      v36 = 2;
      txsdll = 4;
      tcke = 2;
      v39 = 4;
      v45 = (tcksrea >> 1) + 5;
      tmod = 5;
      tmrd = 5;
      v40 = 6;
      tcl = 3;
      goto LABEL_125;
    case 7u:
      trasmax = (uint8_t)(v4 / 0x1E);
      v52 = 2500 * dram_clk % 0xF4240;
      if ( v52 )
        v52 = ( v52 - LOBYTE(v52) ) +  1;
      twtr_sa = (uint8_t)(2500 * dram_clk / 0xF4240 + v52);
      tcksrea = (uint8_t)(v52 + 5500 * dram_clk / 0xF4240);
      txsr = (uint8_t)auto_cal_timing(0xDCu, v4);
      if ( v4 >= 0x190 )
      {
        v36 = 4;
        v39 = 7;
        tcl = 7;
        t_rdata_en = (uint8_t)(twtr_sa + 10);
        v40 = 12;
      }
      else
      {
        v36 = 3;
        v39 = 6;
        t_rdata_en = (uint8_t)(twtr_sa + 8);
        tcl = 5;
        v40 = 10;
      }
      mr3 = para->dram_mr3;
      tdinit0 = 200 * dram_clk + 1;
      tdinit2 = 11 * dram_clk + 1;
      tdinit1 = 100 * dram_clk / 0x3E8 + 1;
      v53 = 2 * (__int16)v12;
      tdinit3 = dram_clk + 1;
      switch ( v53 )
      {
        case 8:
          goto LABEL_142;
        case 10:
          v55 = 227;
          goto LABEL_145;
        case 12:
          v40 |= 0x10u;
          v54 = 67;
          goto LABEL_143;
        case 14:
          v40 |= 0x10u;
          v55 = 131;
LABEL_145:
          mr1 = v55;
          break;
        case 16:
          v40 |= 0x10u;
LABEL_142:
          v54 = 195;
LABEL_143:
          mr1 = v54;
          break;
        default:
          if ( v53 <= 5 )
            v12 = ( v12 - LOBYTE(v12) ) + 3;
          mr1 = 131;
          break;
      }
      v43 = 5;
      v34 = 4;
      twr2rd_s = 8;
      twtp = (uint8_t)(v12 + v36 + 5);
      txsdll = 4;
      tckesr = 5;
      tmrd = 5;
      tcke = 3;
      v45 = (uint8_t)(v39 + (tcksrea >> 1) + 3 - v36);
      tmod = 12;
      v46 = 5;
      twr2rd = (uint8_t)(twtr + 3 + v36);
LABEL_125:
      v41 = 0;
      break;
    default:
      v34 = 4;
      twr2rd_s = 8;
      v36 = 3;
      tckesr = 3;
      twr2rd = 8;
      twtr_sa = 2;
      tcke = 2;
      v43 = 4;
      tmrd = 2;
      v46 = 0;
      twtp = 12;
      v45 = 4;
      tmod = 6;
      v39 = 3;
      v40 = 0;
      v41 = 0;
      trasmax = 27;
      txsdll = 4;
      txsr = 4;
      tcksrea = 4;
      tcl = 1;
      t_rdata_en = 1;
      mr3 = 0;
      mr1 = 0;
      tdinit3 = 0;
      tdinit2 = 0;
      tdinit1 = 0;
      tdinit0 = 0;
      break;
  }
  if ( v39 + 1 >= (int)(v10 + trp) )
    v10 = (uint8_t)(2 - trp + v39);
  if ( !HIWORD(para->dram_mr0) )
    para->dram_mr0 = v41;
  if ( !HIWORD(para->dram_mr1) )
    para->dram_mr1 = mr1;
  if ( !HIWORD(para->dram_mr2) )
    para->dram_mr2 = v40;
  if ( !HIWORD(para->dram_mr3) )
    para->dram_mr3 = mr3;
  if ( !HIWORD(para->dram_mr4) )
    para->dram_mr4 = HIWORD(para->dram_mr4);

//backup
/*
  MEMORY[0x4005180] = para->dram_mr0;
  MEMORY[0x4005184] = para->dram_mr1;
  MEMORY[0x4005188] = para->dram_mr2;
  MEMORY[0x400518C] = para->dram_mr3;
  MEMORY[0x4005190] = para->dram_mr4;
  MEMORY[0x4005194] = para->dram_mr5;
  MEMORY[0x4005198] = para->dram_mr6;
*/

	writel( para->dram_mr0 , 0x4005180 );
	writel( para->dram_mr1 , 0x4005184 );
	writel( para->dram_mr2 , 0x4005188 );
	writel( para->dram_mr3 , 0x400518C );
	writel( para->dram_mr4 , 0x4005190 );
	writel( para->dram_mr5 , 0x4005194 );
	writel( para->dram_mr6 , 0x4005198 );

//  if ( para->dram_type - 6 <= 1 )
//    MEMORY[0x40051AC] = (para->dram_odt_en >> 4) & 3;

  if ( para->dram_type - 6 <= 1 )
    writel( (para->dram_odt_en >> 4) & 3 , 0x40051AC );

//backup
/*
  MEMORY[0x4003100] = tras | (tfaw << 16) | (twtp << 24) | (trasmax << 8);
  MEMORY[0x4003104] = trc | (txp << 16) | (v10 << 8);
  MEMORY[0x4003108] = (v39 << 16) | (v36 << 24) | twr2rd | (v45 << 8);
  MEMORY[0x400310C] = (tmrd << 12) | (v46 << 20) | tmod;
  MEMORY[0x4003110] = (tccd << 16) | (twr << 24) | trp | (v6 << 8);
  MEMORY[0x4003114] = (v43 << 16) | (v43 << 24) | tcke | (tckesr << 8);
  MEMORY[0x4003118] = (txp + 2) | 0x2020000;
  MEMORY[0x4003120] = (v34 << 16) | (v34 << 24) | txs | (txsdll << 8);
  MEMORY[0x4003124] = (trrd_s << 8) | (tccd_s << 16) | (((para->dram_mr4 >> 12) & 1) << 30) | twr2rd_s;
  MEMORY[0x4003138] = txsr;
  MEMORY[0x40030D0] = MEMORY[0x40030D0] & 0x3FFFFFFF | 0x40000000;
  MEMORY[0x40031B0] = 0;
  MEMORY[0x40030F4] = MEMORY[0x40030F4] & 0xFFFFF000 | 0x660;
  MEMORY[0x4005110] = (v6 << 25) | (tras << 17) | (trp << 9) | (2 * v10);
  MEMORY[0x4005114] = (tfaw << 17) | 0x28000400 | (2 * tmrd);
  MEMORY[0x4005118] = ((txs << 6) - 1) | (tcke << 17);
  MEMORY[0x400511C] = twtr_sa | (tcksrea << 8) | ((txsdll << 22) - 0x10000);
  MEMORY[0x4005120] = (2 * txp) | (trfc << 17) | 0x800;
  MEMORY[0x4005124] = (trc << 17) | (twr << 9) | (2 * twtr);
  MEMORY[0x4005128] = 1285;
  MEMORY[0x4003190] = tcl | 0x2000200 | (t_rdata_en << 16) | 0x808000;
  MEMORY[0x4003194] = 262657;
  MEMORY[0x400504C] = tdinit0 | (tdinit1 << 20);
  MEMORY[0x4005050] = tdinit2 | (tdinit3 << 18);
  MEMORY[0x4003064] = trfc | (trefi << 16);
*/

	writel( tras | (tfaw << 16) | (twtp << 24) | (trasmax << 8)  , 0x4003100 );
	writel( trc | (txp << 16) | (v10 << 8)  , 0x4003104 );
	writel( (v39 << 16) | (v36 << 24) | twr2rd | (v45 << 8)  , 0x4003108 );
	writel( (tmrd << 12) | (v46 << 20) | tmod  , 0x400310C );
	writel( (tccd << 16) | (twr << 24) | trp | (v6 << 8)  , 0x4003110 );
	writel( (v43 << 16) | (v43 << 24) | tcke | (tckesr << 8)  , 0x4003114 );
	writel( (txp + 2) | 0x2020000  , 0x4003118 );
	writel( (v34 << 16) | (v34 << 24) | txs | (txsdll << 8)  , 0x4003120 );
	writel( (trrd_s << 8) | (tccd_s << 16) | (((para->dram_mr4 >> 12) & 1) << 30) | twr2rd_s  , 0x4003124 );
	writel( txsr  , 0x4003138 );
	writel( readl( 0x40030D0) & 0x3FFFFFFF | 0x40000000  , 0x40030D0 );
	writel( 0  , 0x40031B0 );
	writel( readl( 0x40030F4) & 0xFFFFF000 | 0x660  , 0x40030F4 );
	writel( (v6 << 25) | (tras << 17) | (trp << 9) | (2 * v10)  , 0x4005110 );
	writel( (tfaw << 17) | 0x28000400 | (2 * tmrd)  , 0x4005114 );
	writel( ((txs << 6) - 1) | (tcke << 17)  , 0x4005118 );
	writel( twtr_sa | (tcksrea << 8) | ((txsdll << 22) - 0x10000)  , 0x400511C );
	writel( (2 * txp) | (trfc << 17) | 0x800  , 0x4005120 );
	writel( (trc << 17) | (twr << 9) | (2 * twtr)  , 0x4005124 );
	writel( 1285  , 0x4005128 );
	writel( tcl | 0x2000200 | (t_rdata_en << 16) | 0x808000  , 0x4003190 );
	writel( 262657  , 0x4003194 );
	writel( tdinit0 | (tdinit1 << 20)  , 0x400504C );
	writel( tdinit2 | (tdinit3 << 18)  , 0x4005050 );
	writel( trfc | (trefi << 16)  , 0x4003064 );


}