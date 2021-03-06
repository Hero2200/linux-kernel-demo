# build_s3c6410.sh
source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=$PWD
find_devices
if [ "$selected_device" == "" ]; then
    exit
else
    adb -s $selected_device push $PWD/mutex.ko /data/local
    adb -s $selected_device push $PWD/test_mutex.sh /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "mutex")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod mutex
    fi
    adb -s $selected_device shell "insmod /data/local/mutex.ko"
fi

