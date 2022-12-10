
///////////// drop this
void udelay ( int a);
unsigned int readb( unsigned int loc );
unsigned int readl( unsigned int loc );
unsigned int readw( unsigned int loc );
void writel( int data  , unsigned int loc );
void writew( int data  , unsigned int loc );
void dsb ();
////////////

// Dummy
void axp_set_aldo3 (int a , int b);

void dram_udelay(unsigned int n);
unsigned int dram_vol_set(__dram_para_t *para);
unsigned int auto_cal_timing(unsigned int time_ns,unsigned int clk);
void paraconfig(unsigned int *para, unsigned int mask, unsigned int value);

unsigned int  DRAMC_get_dram_size(__dram_para_t *para);

unsigned int dqs_gate_detect(__dram_para_t *para);
unsigned int gate_delay_repire(__dram_para_t *para);
void  gate_delay_save(__dram_para_t *para);
void  gate_delay_restore(__dram_para_t *para);
void phy_hard_reset();
void  set_address_map(__dram_para_t *para);
void  bit_delay_compensation(__dram_para_t *para);

unsigned int auto_scan_dram_config(__dram_para_t *para);
unsigned int auto_scan_dram_rank_width(__dram_para_t *para);
unsigned int auto_scan_dram_size(__dram_para_t *para);
unsigned int auto_scan_dram_type(__dram_para_t *para);
void auto_set_timing_para(__dram_para_t *para);

void ccm_set_pll_ddr0_sscg(__dram_para_t *para);
void ccm_set_pll_ddr_clk(unsigned int pll_clk, unsigned int PLL_ADDR, __dram_para_t *para);

unsigned int mctl_core_init(__dram_para_t *para);
unsigned int mctl_sys_init(__dram_para_t *para);
unsigned int mctl_channel_init(unsigned int ch_index, __dram_para_t *para);
void mctl_com_init(__dram_para_t *para);

unsigned int init_DRAM(int type, __dram_para_t *para);

unsigned int dramc_simple_wr_test(unsigned int dram_size, unsigned int test_length);


void set_master_priority();

