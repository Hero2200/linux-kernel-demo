# build_s3c6410.sh
source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=$PWD
find_devices
if [ "$selected_device" == "" ]; then
    exit
else
    adb -s $selected_device push $PWD/completion.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "completion")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod completion
    fi
    adb -s $selected_device shell "insmod /data/local/completion.ko completion_type=$completion_type"
fi

