defenv
setenv bootcmd "run start_autoscript; run storeboot;"
setenv start_autoscript "if usb start ; then run start_usb_autoscript; fi; if mmcinfo; then run start_mmc_autoscript; fi; run start_emmc_autoscript;"
setenv start_emmc_autoscript "if fatload mmc 1 1020000 emmc_autoscript; then autoscr 1020000; fi;"
setenv start_mmc_autoscript "if fatload mmc 0 1020000 s905_autoscript; then autoscr 1020000; fi;"
setenv start_usb_autoscript "if fatload usb 0 1020000 s905_autoscript; then autoscr 1020000; fi; if fatload usb 1 1020000 s905_autoscript; then autoscr 1020000; fi; if fatload usb 2 1020000 s905_autoscript; then autoscr 1020000; fi; if fatload usb 3 1020000 s905_autoscript; then autoscr 1020000; fi;"
setenv upgrade_step "2"
saveenv
sleep 1
reboot


# Rebuilt
# mkimage -A arm64 -O linux -T script -C none -a 0 -e 0 -n "aml autoscript" -d ./aml_autoscript.cmd ./aml_autoscript

