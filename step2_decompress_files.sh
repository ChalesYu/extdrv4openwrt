#! /bin/sh

#Step2: Do decompress files
echo
echo Do decompress files...
echo

openwrt_release_source_file=openwrt-v22.03.3.tar.gz
openwrt_release_source_dir=openwrt-v22.03.3
openwrt_release_sdk_file=openwrt-sdk-22.03.3-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64.tar.xz
openwrt_release_sdk_dir=openwrt-sdk-22.03.3-ramips-rt305x_gcc-11.2.0_musl.Linux-x86_64
backport_source_file=backports-5.15.81-1.tar.xz
backport_source_dir=backports-5.15.81-1

echo OpenWRT release source code is ${openwrt_release_source_file}
echo OpenWRT SDK is ${openwrt_release_sdk_file}
echo Backport source code is ${backport_source_file}
sleep 2

echo Do decompress OpenWRT release source code ...
gzip -d -c ${openwrt_release_source_file} |tar xv

echo Do decompress OpenWRT SDK file ...
xzcat ${openwrt_release_sdk_file} |tar xv

echo Do decompress Backport source code ...
xzcat ${backport_source_file} |tar xv

