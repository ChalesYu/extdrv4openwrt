sunxi-fel -v spl ./boot0/a63_boot0_RAM3G.bin
sunxi-fel ver
sunxi-fel ver
sunxi-fel -v -p write 0x4a000000 ./u-boot/u-boot.bin
sunxi-fel -v -p write 0x104000 ./arm-trusted-firmware/build/sun50i_a63/debug/bl31.bin
sunxi-fel -v -p reset64 0x104000

