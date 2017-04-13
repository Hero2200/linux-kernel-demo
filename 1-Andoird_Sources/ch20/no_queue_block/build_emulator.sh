# build_s3c6410.sh

source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=$PWD

find_devices
if [ "$selected_device" == "" ]; then
    exit
else
    adb -s $selected_device push $PWD/no_queue_block.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "no_queue_block")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod no_queue_block
    fi
    adb -s $selected_device shell insmod /data/local/no_queue_block.ko	
	
fi

