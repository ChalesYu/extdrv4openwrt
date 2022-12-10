#include "dram_base.h"

unsigned int  mctl_channel_init(unsigned int ch_index, __dram_para_t *para)
{
  unsigned int dram_clk; // r1
  int v4; // r5
  unsigned int v5; // r0
  int v6; // r3
  int i; // r3
  unsigned int v8; // r0
  unsigned int v9; // r3
  int v10; // r3
  unsigned int v11; // r2
  unsigned int v12; // r3
  int v13; // r3
  int j; // r3
  unsigned int dram_type; // r2
  int v16; // r3
  unsigned int dram_tpr13; // r1
  int v18; // r5
  int v19; // r6
  int k; // r5
  int v21; // r2
  int v22; // r1
  int v23; // r6
  int m; // r2
  unsigned int dram_tpr6; // r3
  unsigned int v26; // r3
  unsigned int v27; // r3
  unsigned int v28; // r1
  int n; // r3
  int v30; // r2
  int ii; // r3
  int v32; // r5
  int v33; // r7
  int v34; // r6
  int v35; // r2
  int v36; // r1
  unsigned int v37; // r3
  int v38; // r3
  unsigned int result; // r0

/*
  MEMORY[0x40031A0] |= 0xC0000000;
  MEMORY[0x4003180] |= 0xC0000000;
  MEMORY[0x4003250] = 12037;

  MEMORY[0x4003054] |= 0xF0000u;
  MEMORY[0x4003060] |= 1u;
  MEMORY[0x40031B0] |= 1u;
*/

	writel( readl( 0x40031A0 ) | 0xC0000000 , 0x40031A0 );
	writel( readl( 0x4003180 ) | 0xC0000000 , 0x4003180 );
	writel( 12037 , 0x4003250 );

	writel( readl( 0x4003054 ) | 0xF0000u , 0x4003054 );
	writel( readl( 0x4003060 ) | 1u , 0x4003060 );
	writel( readl( 0x40031B0 ) | 1u , 0x40031B0 );

  if ( (para->dram_tpr13 & 0x20000000) != 0 )
	writel( readl( 0x40031C0 ) | 4u , 0x40031C0 );	
//    MEMORY[0x40031C0] |= 4u;

/*
  MEMORY[0x400300C] |= 0x100u;
  MEMORY[0x4005014] = readl( 0x4005014 ) & 0xFFFFFE3F | 0xC0;
*/

	writel( readl( 0x400300C ) | 0x100u , 0x400300C );
	writel( readl( 0x4005014 ) & 0xFFFFFE3F | 0xC0 , 0x4005014 );

  dram_clk = para->dram_clk;
  if ( para->dram_type - 3 > 1 )
    v5 = 3900;
  else
    v5 = 7800;
  v4 = readl( 0x4005018 ) >> 18 << 18;

//  MEMORY[0x4005018] = auto_cal_timing(v5, dram_clk) | v4;

	writel( auto_cal_timing(v5, dram_clk) | v4 , 0x4005018 );

  if ( (para->dram_tpr13 & 0x20000000) != 0 )
	writel( readl( 0x400501C ) | 0x4000000u , 0x400501C );
//    MEMORY[0x400501C] |= 0x4000000u;

/*
  MEMORY[0x4005028] &= ~1u;
  MEMORY[0x4005088] = readl( 0x4005088 ) & 0xFFFFF11F | 0x220;
*/

	writel( readl( 0x4005028 ) & ~1u , 0x4005028 );
	writel( readl( 0x4005088 ) & 0xFFFFF11F | 0x220 , 0x4005088 );

  v6 = readl( 0x4005090 ) | 0x440000;
  if ( readl( 0x300621C ) >> 5 == 3 || para->dram_type == 4 )
    v6 = readl( 0x4005090 ) | 0xC40000;

//  MEMORY[0x4005090] = v6 & 0xFFFFFFFE | (para->dram_tpr13 >> 8) & 1;
   writel( v6 & 0xFFFFFFFE | (para->dram_tpr13 >> 8) & 1 , 0x4005090 );


  if ( para->dram_type == 4 )
	writel( para->dram_mr6 & 0x3F | readl( 0x4005528 ) & 0xFFFFFFC0 | 0x10000000 , 0x4005528 );
//    MEMORY[0x4005528] = para->dram_mr6 & 0x3F | readl( 0x4005528 ) & 0xFFFFFFC0 | 0x10000000;

/*
  MEMORY[0x400552C] &= ~2u;
  MEMORY[0x4005700] = MEMORY[0x4005700] & 0xFFFFF1FF | 0x800;
  MEMORY[0x4005800] = MEMORY[0x4005800] & 0xFFFFF1FF | 0x800;
  MEMORY[0x4005900] = MEMORY[0x4005900] & 0xFFFFF1FF | 0x800;
  MEMORY[0x4005A00] = MEMORY[0x4005A00] & 0xFFFFF1FF | 0x800;
*/

	writel( readl( 0x400552C ) & ~2u , 0x400552C );
	writel( readl( 0x4005700 ) & 0xFFFFF1FF | 0x800 , 0x4005700 );
	writel( readl( 0x4005800 ) & 0xFFFFF1FF | 0x800 , 0x4005800 );
	writel( readl( 0x4005900 ) & 0xFFFFF1FF | 0x800 , 0x4005900 );
	writel( readl( 0x4005A00 ) & 0xFFFFF1FF | 0x800 , 0x4005A00 );

  for ( i = 67131144; i != 67132168; i += 256 )
  {

//    *(_DWORD *)i = (HIWORD(*(_DWORD *)i) << 16) | 0x5555;
	writel( (HIWORD( readl( i ) ) << 16) | 0x5555 , i );

//    *(_DWORD *)(i + 4) = *(_DWORD *)(i + 4) & 0xFFFFCFCF | 0x1010;
	writel( readl( i + 4 ) & 0xFFFFCFCF | 0x1010 , i + 4 );

  }
  if ( (para->dram_tpr13 & 0x2000000) != 0 )
    v8 = 3000;
  else
    v8 = 300000;
  _usdelay(v8);
  if ( (para->dram_para2 & 0x1000) != 0 )
    v9 = readl( 0x4005204 ) | 0x30000;
  else
    v9 = readl( 0x4005204 ) & 0xFFFCFFFF;
  if ( (para->dram_para2 & 0x1000) == 0 )
    v9 |= 0x10000u;
  if ( para->dram_type - 6 <= 1 )
    v9 &= ~2u;

/*
  MEMORY[0x4005204] = v9;
  MEMORY[0x40054DC] = 0;
  MEMORY[0x4005098] = 0x10000;
*/

	writel( v9 , 0x4005204 );
	writel( 0 , 0x40054DC );
	writel( 0x10000 , 0x4005098 );

  if ( (para->dram_para2 & 0x1000) != 0 )
  {
/*
    MEMORY[0x40054DC] = 65537;
    MEMORY[0x4005098] = 0x20000;
*/

	writel( 65537 , 0x40054DC );
	writel( 0x20000 , 0x4005098 );

  }
  v10 = readl( 0x4005200 ) & 0xFFFFFFF | 0x10000000;
  if ( para->dram_type == 7 )
    v10 = readl( 0x4005200 ) & 0xFFFFFBF | 0x10000040;

//  MEMORY[0x4005200] = v10;
  writel( v10 , 0x4005200 );

  v11 = para->dram_clk;
  v12 = readl( 0x4005680 ) & 0xFFFFF8FF;
  if ( para->dram_clk <= 0x318 )
  {
    if ( v11 <= 0x2A0 )
    {
      if ( v11 <= 0x258 )
        v13 = v12 | 0x300;
      else
        v13 = v12 | 0x400;
    }
    else
    {
      v13 = v12 | 0x500;
    }
  }
  else
  {
    v13 = v12 | 0x600;
  }

  writel( v13 , 0x4005680 );

/*
  MEMORY[0x4005684] = MEMORY[0x4005684] & 0xFFFFFF00 | LOBYTE(para->dram_zq);
  MEMORY[0x4005694] = ((HIWORD(MEMORY[0x4005694]) << 16) | (uint8_t)BYTE1(para->dram_zq) | ((((para->dram_zq >> 8) & 0xF) - 1) << 8) | (uint16_t)((uint16_t)(para->dram_zq >> 8) << 12)) & 0xFFF0FFFF | ((uint16_t)para->dram_zq >> 12 << 16);
  MEMORY[0x40056A4] = ((HIWORD(MEMORY[0x40056A4]) << 16) | (uint8_t)BYTE2(para->dram_zq) | (((HIWORD(para->dram_zq) & 0xF) - 1) << 8) | (uint16_t)(HIWORD(para->dram_zq) << 12)) & 0xFFF0FFFF | (((para->dram_zq >> 20) & 0xF) << 16);
*/


	writel( readl( 0x4005684 ) & 0xFFFFFF00 | LOBYTE(para->dram_zq) , 0x4005684 );
	writel( ((HIWORD(readl( 0x4005694 )) << 16) |
		 (uint8_t)BYTE1(para->dram_zq) |
		 ((((para->dram_zq >> 8) & 0xF) - 1) << 8) |
		 (uint16_t)((uint16_t)(para->dram_zq >> 8) << 12)) & 0xFFF0FFFF |
		 ((uint16_t)para->dram_zq >> 12 << 16)
											, 0x4005694 );
	writel( ((HIWORD(readl( 0x40056A4 )) << 16) |
		 (uint8_t)BYTE2(para->dram_zq) |
		 (((HIWORD(para->dram_zq) & 0xF) - 1) << 8) |
		 (uint16_t)(HIWORD(para->dram_zq) << 12)) & 0xFFF0FFFF |
		 (((para->dram_zq >> 20) & 0xF) << 16)
											, 0x40056A4 );


  if ( para->dram_type == 7 )
  {
    for ( j = 67130692; j != 67130744; j += 4 )
	writel( 101058054 , j );
  }
  dram_type = para->dram_type;
  switch ( dram_type )
  {
    case 3u:
      v16 = (write_level_flag << 9) | 0xF5E2;
      break;
    case 4u:
      v16 = (write_level_flag << 9) | 0x2F5E2;
      break;
    case 6u:
      v16 = 1378;
      break;
    case 7u:
      v16 = 62818;
      break;
    default:
      v16 = 1506;
      break;
  }
  dram_tpr13 = para->dram_tpr13;
  if ( ((dram_tpr13 >> 2) & 3) == 1 )
    v16 &= ~0x400u;
  if ( (dram_tpr13 & 0x1000000) != 0 )
    v16 &= ~0x20000u;
  v18 = v16 | 1;
  if ( dram_type != 7 )
  {

//    MEMORY[0x4005004] = v16 | 1;
	writel( v16 | 1 , 0x4005004 );

    _usdelay(1u);
    while ( (readl( 0x4005034 ) & 1) == 0 )
      ;
LABEL_62:
    v23 = 1;
    _usdelay(1u);
    goto LABEL_63;
  }

	writel( v16 & 0xFFE | 1 , 0x4005004 );
//  MEMORY[0x4005004] = v16 & 0xFFE | 1;

  _usdelay(1u);
  while ( (readl( 0x4005034 ) & 1) == 0 )
    ;
  _usdelay(1u);
  if ( !(uint8_t)(readl( 0x4005034 ) >> 20) )
  {
    gate_delay_repire(para);

/*
    MEMORY[0x40054DC] = 65537;
    MEMORY[0x4005004] = v18 & 0xFFFFF000 | 1;
*/
	writel( 65537 , 0x40054DC );
	writel( v18 & 0xFFFFF000 | 1 , 0x4005004 );

    _usdelay(1u);
    while ( (readl( 0x4005034 ) & 1) == 0 )
      ;
    goto LABEL_62;
  }
  v19 = 67131344;
  for ( k = 0; k != 4; ++k )
  {
    v21 = readl( v19 );
    v22 = k;
    v19 += 256;
    printf("BYTE%d GATE ERRO IS = %x\n", v22, v21 & 3);
  }
  v23 = (readl( 0x4005034 ) >> 20) & 1;
  if ( v23 )
  {
    v23 = 0;
    printf("ZQ calibration error.\n");
  }
LABEL_63:
  if ( (readl( 0x4005034 ) & 0xF000000) != 0 )
  {
    // MEMORY[0x4005004] = 61441;
	writel( 61441 , 0x4005004 );

    _usdelay(1u);
    while ( (readl( 0x4005034 ) & 1) == 0 )
      ;
    _usdelay(1u);
  }
  for ( m = 67131156; m != 67132180; m += 256 )
  {
    dram_tpr6 = para->dram_tpr6;
    switch ( para->dram_type )
    {
      case 4u:
        v26 = para->dram_tpr6 & 0x3F;
        goto LABEL_72;
      case 6u:
        v26 = HIBYTE(dram_tpr6) & 0x3F;
        goto LABEL_72;
      case 7u:
        v26 = HIWORD(dram_tpr6) & 0x3F;
LABEL_72:
        v27 = v26 | (v26 << 8);
        break;
      default:
        v27 = para->dram_tpr6 & 0x3F00 | (para->dram_tpr6 >> 8) & 0x3F;
        break;
    }
    writel( v27 , m );
  }
  if ( (para->dram_odt_en & 3) != 0 )
  {
    v28 = (para->dram_odt_en & 3) - 1;
    for ( n = 67131144; n != 67132168; n += 256 )
    {
      v30 = HIWORD( readl(n) ) << 16;
      if ( v28 == 1 )
        v30 |= 0x5555u;
	writel( v30 , n );
	writel( readl(n + 4) & (0xFFFFCFCF | ((16 * v28) & (0xFFFFCFFF | (v28 << 12)))) , n + 4 );
    }
  }
  else
  {
    for ( ii = 67131144; ii != 67132168; ii += 256 )
    {
	writel( (HIWORD( readl(ii) ) << 16) | 0xAAAA , ii );
	writel( readl(ii + 4) & 0xFFFFCFCF | 0x2020 , ii + 4 );
    }
  }
  bit_delay_compensation(para);
  _usdelay(1u);
  if ( (para->dram_tpr13 & 0x100) != 0 )
  {
/*
    MEMORY[0x4005028] = readl( 0x4005028 ) & 0xFFFF0006 | 0xFFF8;
    MEMORY[0x400570C] = ~((unsigned int)~(MEMORY[0x400570C] << 14) >> 14);
    MEMORY[0x400580C] = ~((unsigned int)~(MEMORY[0x400580C] << 14) >> 14);
    MEMORY[0x400590C] = ~((unsigned int)~(MEMORY[0x400590C] << 14) >> 14);
    MEMORY[0x4005A0C] = ~((unsigned int)~(MEMORY[0x4005A0C] << 14) >> 14);
*/

	writel( readl( 0x4005028 ) & 0xFFFF0006 | 0xFFF8 , 0x4005028 );
	writel( ~((unsigned int)~(readl( 0x400570C ) << 14) >> 14) , 0x400570C );
	writel( ~((unsigned int)~(readl( 0x400580C ) << 14) >> 14) , 0x400580C );
	writel( ~((unsigned int)~(readl( 0x400590C ) << 14) >> 14) , 0x400590C );
	writel( ~((unsigned int)~(readl( 0x4005A0C ) << 14) >> 14) , 0x4005A0C );

  }
  else
  {
/*
    MEMORY[0x4005028] = readl( 0x4005028 ) & 0xFFFF0006 | 1;
    MEMORY[0x400570C] &= 0x3FFFFu;
    MEMORY[0x400580C] &= 0x3FFFFu;
    MEMORY[0x400590C] &= 0x3FFFFu;
    MEMORY[0x4005A0C] &= 0x3FFFFu;
*/

	writel( readl( 0x4005028 ) & 0xFFFF0006 | 1 , 0x4005028 );
	writel( readl( 0x400570C ) & 0x3FFFFu , 0x400570C );
	writel( readl( 0x400580C ) & 0x3FFFFu , 0x400580C );
	writel( readl( 0x400590C ) & 0x3FFFFu , 0x400590C );
	writel( readl( 0x4005A0C ) & 0x3FFFFu , 0x4005A0C );

  }
  _usdelay(1u);
  writel( v32 , 0x4005034 );
  if ( (uint8_t)( readl( 0x4005034 ) >> 20) )
  {
    v33 = 67131344;
    v34 = 0;
    printf("MP_PGSR0 IS = %x\n", readl( 0x4005034 ) );
    do
    {
      v35 = readl( v33 );
      v36 = v34++;
      v33 += 256;
      printf("BYTE%d GATE ERRO IS = %x\n", v36, v35 & 3);
    }
    while ( v34 != 4 );
    v23 = v32 & 0x100000;
    if ( (v32 & 0x100000) != 0 )
    {
      v23 = 0;
      printf("ZQ calibration error.\n");
    }
  }
  if ( para->dram_type - 6 <= 1 )
  {
    v37 = readl( 0x4005090 ) & 0xFFFFFF3F;
    if ( ((para->dram_tpr13 >> 2) & 3) == 1 )
      v38 = v37 | 0xC0;
    else
      v38 = v37 | 0x40;
//    MEMORY[0x4005090] = v38;
	writel( 0x4005090 , v38 );
  }

/*
  MEMORY[0x4005014] &= ~0x40u;
  MEMORY[0x40031B0] &= ~1u;
  MEMORY[0x4003320] = 1;
*/

	writel( readl( 0x4005014 ) & ~0x40u , 0x4005014 );
	writel( readl( 0x40031B0 ) & ~1u , 0x40031B0 );
	writel( 1 , 0x4003320 );

  while ( readl( 0x4003324 ) != 1 )
    ;
  result = v23;

/*
  MEMORY[0x4003060] &= ~1u;
  MEMORY[0x4002014] |= 0x80000000;
  MEMORY[0x4002020] = -1;
  MEMORY[0x4002024] = 2047;
  MEMORY[0x4002028] = 0xFFFF;
*/

	writel( readl( 0x4003060 ) & ~1u , 0x4003060 );
	writel( readl( 0x4002014 ) | 0x80000000 , 0x4002014 );
	writel( -1 , 0x4002020 );
	writel( 2047 , 0x4002024 );
	writel( 0xFFFF , 0x4002028 );

 return result;
}