#include "dram_base.h"

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