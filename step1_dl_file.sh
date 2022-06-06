#! /bin/sh

#Step1: Download files

#wget https://github.com/openwrt/openwrt/archive/refs/tags/v22.03.0-rc1.tar.gz
#wget https://gitlab.com/openwrt/openwrt/openwrt/-/archive/v22.03.0-rc1/openwrt-v22.03.0-rc1.tar.gz

#wget https://downloads.openwrt.org/releases/22.03.0-rc1/targets/ramips/rt305x/openwrt-sdk-22.03.0-rc1-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64.tar.xz
#wget https://cdn.kernel.org/pub/linux/kernel/projects/backports/stable/v5.15.33/backports-5.15.33-1.tar.xz

md5sum v22.03.0-rc1.tar.gz
md5sum openwrt-v22.03.0-rc1.tar.gz

md5sum openwrt-sdk-22.03.0-rc1-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64.tar.xz
md5sum backports-5.15.33-1.tar.xz

echo
echo Download build needed files complete.
echo

