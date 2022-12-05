#include "dram_base.h"

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