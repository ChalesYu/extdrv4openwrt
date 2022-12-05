#include "dram_base.h"


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

