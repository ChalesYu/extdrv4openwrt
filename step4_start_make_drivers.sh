#! /bin/sh

#Step4: Now start make drivers

openwrt_release_source_file=openwrt-v22.03.3.tar.gz
openwrt_release_source_dir=openwrt-v22.03.3
openwrt_release_sdk_file=openwrt-sdk-22.03.3-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64.tar.xz
openwrt_release_sdk_dir=openwrt-sdk-22.03.3-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64
backport_source_file=backports-5.15.81-1.tar.xz
backport_source_dir=backports-5.15.81-1

cd ${openwrt_release_sdk_dir}/
make V=s defconfig

make V=s package/sr9700-jl/compile -j4
#make V=s package/ac200/compile -j4


#make V=s package/kernel/mac80211/prepare -j4
#make V=s package/kernel/mac80211/compile -j4

#make V=s package/mt7603u-hk/compile -j4
#make V=s package/mt7601u-kh/compile -j4

