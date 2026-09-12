H3C NX18 Plus OpenWRT

这个路由器和TX1801Plus用的一个主板，硬件上改了一些电阻，把128M的NAND存储芯片换成了16M的SPI-NOR,不用考虑NAND坏快管理的问题了.
winbond 25Q128JVSQ Flash上的分区表是： 192k(u-boot),64k(u-boot-env),64k(exp),256k(factory),-(firmware)

openwrt-nx18plus-kernel-sysupgrade.bin openwrt 版本是 25.12.5

问&答

问：固件修改了什么？
答： 
   1. 解包TX1801Plus的initramfs固件，提取并修改设备树，详见patch。
   2. 解包了wodesys_wd-r1802u的sysupgrade固件 ， 替换了修改后的TX1801Plus的设备树，重新打包为 openwrt-nx18plus-kernel-sysupgrade.bin 


问：如何刷机？
答： 开始前务必用编程器备份SPI-NOR Flash，以防止变砖和需要恢复官方固件时刷回。
   1. 参考TX1801Plus的刷机方法，tftp传入这个设备的initramfs.bin : openwrt-25.12.5-ramips-mt7621-wodesys_wd-r1802u-initramfs-kernel.bin
   2. TTL串口输入bootm启动，网线一头插蓝色WAN口，一头插电脑网口。
   3. 等路由器启动完成，电脑网口获取到IP地址。
   4. 浏览器打开 OpenWrt LuCI 页面 http://192.168.1.1 
   5. 在 LuCI 中选择xxxx-squashfs-sysupgrade.bin 进行固件升级，等待重启。我选的是 openwrt-nx18plus-kernel-sysupgrade.bin ，这文件是修改后重打包的，校验肯定通不过，勾上 -F 强制刷写那个选项。
   6. 刷写完路由重启后TTL串口输入:
                                setenv openwrtspinor 'sf probe ; sf read 0x80010000 0x90000 0xf70000 ; bootm '
                                setenv bootcmd 'run openwrtspinor'
                                saveenv
                                reset
   7. 等路由器启动完成，Enjoy。




问：为什么不发补丁到主线，让上游支持这个设备？
答：
   1.上游已经支持TX1801Plus了，拿到device-tree,重新修改修改，再打包固件，也能用。
   2.16M 的flash有点小，可能两三年后OpenWRT固件体积变大了就安不了什么软件了
   3.国内的运营商，奇妙的GFW,github有时上得去有时上不去。不考虑挂VPN,像什么v2ray,酸酸乳什么的.
   4.一个自用的家用路由器，也不是大批量刷机，没必要费心思提交补丁，还得写什么commit到上游。
   5.挣不到钱，没什么利益可言，买硬件适配都是成本，自己玩玩的东西，再说运营商的一体光猫都集成WIFI6了。



