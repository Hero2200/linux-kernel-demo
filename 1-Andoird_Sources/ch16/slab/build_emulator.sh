# build_s3c6410.sh
source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=${PWD}
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/slab_cache.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "slab_cache")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod slab_cache
    fi
    adb -s $selected_device shell "insmod /data/local/slab_cache.ko"
fi
