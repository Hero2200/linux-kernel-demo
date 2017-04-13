# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=$PWD
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push $PWD/semaphore.ko /data/local
    adb -s $selected_device push $PWD/rw_semaphore.ko /data/local
    adb -s $selected_device push $PWD/test_semaphore.sh /data/local
    adb -s $selected_device push $PWD/test_rw_semaphore.sh /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "semaphore")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod semaphore
    fi
    testing=$(adb -s $selected_device shell lsmod | grep  "rw_semaphore")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod rw_semaphore
    fi

    adb -s $selected_device shell "insmod /data/local/semaphore.ko"
    adb -s $selected_device shell "insmod /data/local/rw_semaphore.ko"

fi

