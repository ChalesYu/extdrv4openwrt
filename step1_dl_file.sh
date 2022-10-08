#! /bin/sh

#Step1: Download files

#wget https://github.com/openwrt/openwrt/archive/refs/tags/v22.03.0.tar.gz
#wget https://gitlab.com/openwrt/openwrt/openwrt/-/archive/v22.03.0/openwrt-v22.03.0.tar.gz

#wget https://downloads.openwrt.org/releases/22.03.0/targets/ramips/rt305x/openwrt-sdk-22.03.0-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64.tar.xz
#wget https://kernel.org/pub/linux/kernel/projects/backports/stable/v5.15.58/backports-5.15.58-1.tar.xz

md5sum v22.03.0.tar.gz
md5sum openwrt-v22.03.0.tar.gz

md5sum openwrt-sdk-22.03.0-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64.tar.xz
md5sum backports-5.15.58-1.tar.xz

echo
echo Download build needed files complete.
echo

