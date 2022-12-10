#include "dram_base.h"

unsigned int auto_cal_timing(unsigned int time_ns,unsigned int clk)
{
	unsigned int value ;
	value = (time_ns*clk)/1000 + ( ( ((time_ns*clk)%1000) != 0) ? 1 :0);
	return value;
}
