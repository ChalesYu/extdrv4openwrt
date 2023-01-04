#include "dram_base.h"

void  set_address_map(__dram_para_t *para)
{
  unsigned int dram_para1; // r3
  int v2; // r2
  int v3; // r7
  int v4; // r8
  int v5; // r3
  int v6; // r12
  int v7; // r6
  int v8; // r5
  int v9; // r9
  int v10; // r6
  int v11; // r4
  int v12; // r6
  int v13; // r1
  int v14; // r1
  int v15; // r1
  int v16; // r2
  int v17; // r3
  int v18; // r12
  int v19; // r3

  dram_para1 = para->dram_para1;
  v2 = dram_para1 & 0xF;
  v3 = (uint8_t)(dram_para1 >> 4);
  v4 = (dram_para1 >> 12) & 3;
  v5 = (uint16_t)dram_para1 >> 14;
  if ( para->dram_para2 << 28 )
    --v2;
  v6 = v5 << 16;
  v7 = v5 << 8;
  v8 = v5 << 24;
  v9 = (v5 << 16) | (v5 << 8);
//  MEMORY[0x4003208] = v9 | (v5 << 24);

	writel( v9 | (v5 << 24) , 0x4003208 );

  switch ( v2 )
  {
    case 8:
      v10 = v7 | v5 | 0x1F1F0000;
      goto LABEL_6;
    case 9:
      v10 = v7 | v5 | 0x1F000000 | v6;
LABEL_6:
//      MEMORY[0x400320C] = v10;
	writel( v10 , 0x400320C );

      goto LABEL_7;
    case 10:
//      MEMORY[0x400320C] = v9 | v5 | v8;
	writel( v9 | v5 | v8 , 0x400320C );
LABEL_7:
      v11 = 7967;
      goto LABEL_8;
    case 11:
//      MEMORY[0x400320C] = v9 | v5 | v8;
	writel( v9 | v5 | v8 , 0x400320C );
      v11 = v5 | 0x1F00;
LABEL_8:
//      MEMORY[0x4003210] = v11;
	writel( v11 , 0x4003210 );
      break;
    default:
      v12 = v7 | v5;
//      MEMORY[0x400320C] = v8 | v6 | v12;
	writel( v8 | v6 | v12 , 0x400320C );
//      MEMORY[0x4003210] = v12;
	writel( v12 , 0x4003210 );
      break;
  }
  if ( v5 == 2 )
  {
    v13 = 257;
  }
  else
  {
    v13 = 16129;
    if ( v5 != 1 )
      v13 = 16191;
  }
//  MEMORY[0x4003220] = v13;
	writel( v13 , 0x4003220 );
  v14 = v5 - 2 + v2;
  if ( v4 == 3 )
    v15 = v14 | (v14 << 16) | (v14 << 8);
  else
    v15 = v14 | 0x3F0000 | (v14 << 8);

//  MEMORY[0x4003204] = v15;
  writel( v15 , 0x4003204 );

  v16 = v5 + v4 + v2;
  v17 = (v16 - 6) | ((v16 - 6) << 8);
  v18 = v17 | ((v16 - 6) << 16);

//  MEMORY[0x4003214] = v18 | ((v16 - 6) << 24);
  writel( v18 | ((v16 - 6) << 24) , 0x4003214 );

  switch ( v3 )
  {
    case 14:
      v19 = v17 | 0xF0F0000;
      goto LABEL_23;
    case 15:
      v19 = v18 | 0xF000000;
LABEL_23:
//      MEMORY[0x4003218] = v19;
	writel( v19 , 0x4003218 );

      goto LABEL_24;
    case 16:
//      MEMORY[0x4003218] = v18 | ((v16 - 6) << 24);
	writel( v18 | ((v16 - 6) << 24) , 0x4003218 );

LABEL_24:
      v17 = 3855;
      goto LABEL_28;
    case 17:
//      MEMORY[0x4003218] = v18 | ((v16 - 6) << 24);
	writel( v18 | ((v16 - 6) << 24) , 0x4003218 );

//      MEMORY[0x400321C] = (v16 - 6) | 0xF00;
	writel( (v16 - 6) | 0xF00 , 0x400321C );

      goto LABEL_29;
    default:
//      MEMORY[0x4003218] = v18 | ((v16 - 6) << 24);
	writel( v18 | ((v16 - 6) << 24) , 0x4003218 );
LABEL_28:
//      MEMORY[0x400321C] = v17;
	writel( v17 , 0x400321C );
LABEL_29:
      if ( (para->dram_para2 & 0x1000) != 0 )
//        MEMORY[0x4003200] = v3 - 6 + v16;
	writel( v3 - 6 + v16 , 0x4003200 );

      else
//        MEMORY[0x4003200] = 31;
	writel( 31 , 0x4003200 );

      return;
  }
}