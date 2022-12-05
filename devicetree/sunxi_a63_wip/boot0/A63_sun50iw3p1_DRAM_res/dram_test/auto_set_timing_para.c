#include "dram_base.h"

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