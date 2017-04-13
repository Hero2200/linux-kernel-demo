# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=${PWD}
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/wait_queue.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "wait_queue")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod wait_queue
    fi
    adb -s $selected_device shell "insmod /data/local/wait_queue.ko"

fi

