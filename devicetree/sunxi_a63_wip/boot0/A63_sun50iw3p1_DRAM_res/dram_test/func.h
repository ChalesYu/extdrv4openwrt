

void dram_udelay(unsigned int n);
unsigned int dram_vol_set(__dram_para_t *para);
unsigned int auto_cal_timing(unsigned int time_ns,unsigned int clk);
void paraconfig(unsigned int *para, unsigned int mask, unsigned int value);

int DRAMC_get_dram_size();

unsigned int dqs_gate_detect(__dram_para_t *para);

unsigned int auto_scan_dram_config(__dram_para_t *para);
unsigned int auto_scan_dram_rank_width(__dram_para_t *para);
unsigned int auto_scan_dram_size(__dram_para_t *para);
unsigned int auto_scan_dram_type(__dram_para_t *para);
void auto_set_timing_para(__dram_para_t *para);
void  eye_delay_compensation(__dram_para_t *para);
unsigned int ccm_set_pll_ddr_sscg(__dram_para_t *para, unsigned int PLL_CTRL, unsigned int PLL_PAT);
unsigned int ccm_set_pll_ddr_clk(unsigned int pll, __dram_para_t *para);

unsigned int mctl_core_init(__dram_para_t *para);
unsigned int mctl_sys_init(__dram_para_t *para);
unsigned int mctl_channel_init(unsigned int ch_index, __dram_para_t *para);
void mctl_com_init(__dram_para_t *para);

int  init_DRAM(int type, __dram_para_t *para);

unsigned int dramc_simple_wr_test(unsigned int dram_size, unsigned int test_length);

void dram_enable_all_master();
void dram_disable_all_master();
void set_master_priority();
void set_master_priority_pad();
