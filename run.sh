
#rm -rf mac80211 openwrt-sdk-19.07.7-ramips-mt7621_gcc-7.5.0_musl.Linux-x86_64
xzcat openwrt-sdk-19.07.7-ramips-mt7621_gcc-7.5.0_musl.Linux-x86_64.tar.xz |tar xv

#FIXME
#Need maintain a stripped mac80211 packaged
unzip mac80211.zip
cd mac80211
patch -p1 < ../0001-strip-mf.patch
cd ..
cp -rf mac80211 openwrt-sdk-19.07.7-ramips-mt7621_gcc-7.5.0_musl.Linux-x86_64/package
cp -rf backports-4.19.161-1.tar.xz openwrt-sdk-19.07.7-ramips-mt7621_gcc-7.5.0_musl.Linux-x86_64/dl

cd openwrt-sdk-19.07.7-ramips-mt7621_gcc-7.5.0_musl.Linux-x86_64

#FIXME
#cleanup build linux ipk package for fast compile
#rm package/linux/modules/*
#rm target/linux/*/modules.mk

make V=s defconfig
make V=s package/mac80211/compile

#TODO
#add other out-of-tree driver to mac80211 package here
# edit mac80211 Makefile , edit part Build/Prepare: , do some add out-of-tree driver work.
#

#touch package/mac80211/Makefile
#make V=s package/mac80211/compile

