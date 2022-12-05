#include "dram_base.h"

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