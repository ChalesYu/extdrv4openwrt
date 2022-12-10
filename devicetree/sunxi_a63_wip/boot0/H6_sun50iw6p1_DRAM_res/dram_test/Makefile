
all:  main_test


main_test:   other_func
	$(CC) -o main_test main.c \
			init_DRAM.o \
			readwritel.o \
			dqs_gate_detect.o \
			phy_hard_reset.o \
			set_address_map.o \
			bit_delay_compensation.o \
			gate_delay_repire.o \
			gate_delay_save.o \
			gate_delay_restore.o \
			ccm_set_pll_ddr0_sscg.o \
			ccm_set_pll_ddr_clk.o \
			auto_scan_dram_config.o \
			auto_scan_dram_size.o \
			auto_scan_dram_type.o \
			auto_scan_dram_rank_width.o \
			auto_set_timing_para.o \
			mctl_core_init.o \
			mctl_com_init.o \
			mctl_sys_init.o \
			mctl_channel_init.o \
			dramc_simple_wr_test.o \
			set_master_priority.o 

other_func:
	$(CC) -c init_DRAM.c
	$(CC) -c ccm_set_pll_ddr0_sscg.c
	$(CC) -c ccm_set_pll_ddr_clk.c
	$(CC) -c mctl_core_init.c
	$(CC) -c mctl_com_init.c
	$(CC) -c mctl_sys_init.c
	$(CC) -c mctl_channel_init.c
	$(CC) -c dramc_simple_wr_test.c
	$(CC) -c set_master_priority.c
	$(CC) -c auto_scan_dram_size.c
	$(CC) -c auto_scan_dram_type.c
	$(CC) -c auto_scan_dram_rank_width.c
	$(CC) -c auto_scan_dram_config.c
	$(CC) -c auto_set_timing_para.c
	$(CC) -c dqs_gate_detect.c
	$(CC) -c gate_delay_restore.c
	$(CC) -c gate_delay_repire.c
	$(CC) -c gate_delay_save.c
	$(CC) -c phy_hard_reset.c
	$(CC) -c set_address_map.c
	$(CC) -c bit_delay_compensation.c
	$(CC) -c readwritel.c


clean:
	rm -f *.o  main_test tags cscope.*
	rm -fr *.mod.c *.mod *.o .*.cmd *.ko .tmp_versions Module.symvers modules.order

