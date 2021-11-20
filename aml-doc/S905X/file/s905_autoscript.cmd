echo "Starting S905 autoscript..."

#B860V2.1-A: Fix for MT7668RSN-WIFI
gpio clean GPIODV_27
gpio set GPIODV_27
#B860V2.1-A: GPIODV_26 is GREEN LED;GPIODV_24 is RED LED
gpio set GPIODV_26
#gpio clean GPIODV_26
#gpio set GPIODV_24
gpio clean GPIODV_24

#switch new uboot
usb start
#fatload mmc 1 1000000 u-boot-cc.bin
fatload usb 0 1000000 u-boot-cc.bin
go 1000000

# Rebuilt
# mkimage -A arm64 -O linux -T script -C none -a 0 -e 0 -n "S905 autoscript" -d ./s905_autoscript.cmd ./s905_autoscript
# mkimage -A arm64 -O linux -T script -C none -a 0 -e 0 -n "S905 autoscript" -d /boot/s905_autoscript.cmd /boot/boot.scr
