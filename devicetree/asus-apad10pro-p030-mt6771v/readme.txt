Hardware Spec:
NAME:  ASUS Adol apad 10 pro (P030)
SoC:  MT6771V/MT8183
CPU:  4xCortexA53+4xCortexA73
GPU:  Mali-G72 MP3
RAM:  4G/6G
Flash: 64/128GB UFS




get sn number from UART port in android shell:
   dd if=/dev/block/sdc of=/sdcard/sn.bin bs=1M skip=306 count=1
   cat /sdcard/sn.bin


preloader lives in mmcblk0boot0, sometimes it can be erased by accident.
a way to recovery by mtkclient:
   python mtk printgpt --preloader=preloader.bin

wait a moment and using 'python mtk_gui' as usual.
