#
#arch/arm/mach-sunxi/Makefile
#obj-$(CONFIG_DRAM_SUN50I_H6)	+= dram_sun50i_a63.o
#

all:  main_test


main_test:   other_func
	$(CC) -o main_test dram_sun50i_a63.c \


other_func:
	$(CC) -c dram_sun50i_a63.c
clean:
	rm -f *.o  main_test tags cscope.*
	rm -fr *.mod.c *.mod *.o .*.cmd *.ko .tmp_versions Module.symvers modules.order

