#！/bin/bash
#this will move file a.ko.xz to a.ko
#decompress all xz to ko
for files in `find |grep xz`
do
#	mv $files `echo $files |sed 's/\.xz//' `
	xz -d $files
done

# cd /lib/modules/$(kernel_dir)
#push all ko  to soft-link
#ln -s  $(find |grep ko)  ./


