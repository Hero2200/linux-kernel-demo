# build_s3c6410.sh
source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=${PWD}
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/mempool_cache.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "mempool_cache")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod mempool_cache
    fi
    adb -s $selected_device shell "insmod /data/local/mempool_cache.ko"
fi
