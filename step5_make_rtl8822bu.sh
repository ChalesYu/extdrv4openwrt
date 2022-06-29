#! /bin/sh

# Need Skip Step4
#Step5: Now start make vendor drivers

openwrt_release_source_file=openwrt-v22.03.0-rc4.tar.gz
openwrt_release_source_dir=openwrt-v22.03.0-rc4
openwrt_release_sdk_file=openwrt-sdk-22.03.0-rc4-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64.tar.xz
openwrt_release_sdk_dir=openwrt-sdk-22.03.0-rc4-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64
backport_source_file=backports-5.15.33-1.tar.xz
backport_source_dir=backports-5.15.33-1


mkdir -p ${openwrt_release_sdk_dir}/package/kernel/linux/modules/rm
mv ${openwrt_release_sdk_dir}/package/kernel/linux/modules/*.mk ${openwrt_release_sdk_dir}/package/kernel/linux/modules/rm/

mkdir -p ${openwrt_release_sdk_dir}/target/linux/ramips/rm
mv ${openwrt_release_sdk_dir}/target/linux/ramips/modules.mk  ${openwrt_release_sdk_dir}/target/linux/ramips/rm/

#git clone https://gitlab.com/ChalesYu/buildroot_platform_hardware_wifi_mtk_drivers_mt7603.git -b pub-test-v20220304
#mv  buildroot_platform_hardware_wifi_mtk_drivers_mt7603 ${openwrt_release_sdk_dir}/mt7603_usb

rm -rf ${openwrt_release_sdk_dir}/rtl8822bu

cp -rf rtl8822bs-aml ${openwrt_release_sdk_dir}/rtl8822bu

patch -p1 -d ${openwrt_release_source_dir} < patch/mac80211-patch/004-dirty-rtl8822bu-vendor-driver.patch

cp -rf ${openwrt_release_source_dir}/package/kernel/mac80211  ${openwrt_release_sdk_dir}/package/kernel/


cd ${openwrt_release_sdk_dir}/
make V=s defconfig

#make V=s package/kernel/mac80211/prepare -j4
#make V=s package/kernel/mac80211/compile -j4


# ignore error and get 88x2bu.ko
# ${openwrt_release_sdk_dir}/build_dir/target-mipsel_24kc_musl/linux-ramips_rt305x/backports-5.15.33-1/drivers/net/wireless/rtl8822bu/88x2bu.ko