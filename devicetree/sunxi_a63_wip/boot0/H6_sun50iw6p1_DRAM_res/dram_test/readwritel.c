#include "dram_base.h"

////////////// Dummy
////////////// drop this
void udelay ( int a)
{ int i=0 ; if (i) printf("hello"); };

unsigned int readb( unsigned int loc )
{ int i=0 ; if (i) printf("hello"); };

unsigned int readl( unsigned int loc )
{ int i=0 ; if (i) printf("hello"); };

unsigned int readw( unsigned int loc )
{ int i=0 ; if (i) printf("hello"); };

void writew( int data  , unsigned int loc ) 
{ int i=0 ; if (i) printf("hello"); };

void writel( int data  , unsigned int loc ) 
{ int i=0 ; if (i) printf("hello"); };

void dsb ( )
{ int i=0 ; if (i) printf("hello"); };
////////////////

void axp_set_aldo3 (int a , int b)
{ int i=0 ; if (i) printf("hello"); };

void dram_udelay(unsigned int n)
{
  _usdelay(n);
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


unsigned int  DRAMC_get_dram_size(__dram_para_t *para)
{
  unsigned int dram_para2; // r2
  unsigned int v2; // r0

  dram_para2 = para->dram_para2;
  v2 = (uint8_t)(para->dram_para1 >> 4)
     + ((para->dram_para1 >> 12) & 3)
     + (para->dram_para1 & 0xF)
     + ((uint16_t)para->dram_para1 >> 14)
     + ((uint16_t)dram_para2 >> 12);
  if ( (dram_para2 & 0xF) != 0 )
    return 1 << (v2 - 19);
  else
    return 1 << (v2 - 18);
}

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

