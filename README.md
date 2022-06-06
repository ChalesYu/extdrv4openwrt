# extdrv4openwrt

attempt to make openwrt support more drivers.

## instruction

This repo's aim is to build more useable driver to support more hardhare.

A prepare work has been provided as follows in `.sh` files.

```
step1_dl_file.sh
step2_decompress_files.sh
step3_prepare_files.sh
step4_start_make_drivers.sh
```

But please note some of this script is not completed, maybe need edit manually.


## about vendor driver

Some wifi hardware need vendor driver to work.

These driver usually come from vendor's BSP , need some patch to let it build with upstream kernel,

then need other patch to build with backport, OpenWRT use backport to support wifi hardware.

Vendor always focus on sell next-gen hardware and give their employer NDA.

So , Finally the modified vendor wifi driver can build and work basicly with OpenWRT, but without any warry.

But it looks better than hardware completely didn't work and collect dust.


