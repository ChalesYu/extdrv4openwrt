#! /bin/sh

openwrt_release_source_file=openwrt-v22.03.0-rc4.tar.gz
openwrt_release_source_dir=openwrt-v22.03.0-rc4
openwrt_release_sdk_file=openwrt-sdk-22.03.0-rc4-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64.tar.xz
openwrt_release_sdk_dir=openwrt-sdk-22.03.0-rc4-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64
backport_source_file=backports-5.15.33-1.tar.xz
backport_source_dir=backports-5.15.33-1

#Step3: Do some patch/prepare work

cp -rf drv/*  ${openwrt_release_sdk_dir}/package/

cp ${backport_source_file}  ${openwrt_release_sdk_dir}/dl/
cp -rf patch/backport-patch/*  ${openwrt_release_source_dir}/package/kernel/mac80211/patches/build/

patch -p1 -d ${openwrt_release_source_dir} < patch/mac80211-patch/001-strip-makefile.patch
patch -p1 -d ${openwrt_release_source_dir} < patch/mac80211-patch/002-add-xr819-package.patch

cp -rf ${openwrt_release_source_dir}/package/kernel/mac80211  ${openwrt_release_sdk_dir}/package/kernel/


