# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=$PWD
arm-none-linux-gnueabi-gcc -static  -o test_rw_lock $PWD/test_rw_lock.c
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push $PWD/spin_lock.ko /data/local
    adb -s $selected_device push $PWD/rw_lock.ko /data/local
    adb -s $selected_device push $PWD/seq_lock.ko /data/local
    adb -s $selected_device push $PWD/test_rw_lock /data/local
    adb -s $selected_device push $PWD/test_rw_lock.sh /data/local
    adb -s $selected_device push $PWD/test_seq_lock.sh /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "spin_lock")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod spin_lock
    fi
    testing=$(adb -s $selected_device shell lsmod | grep  "rw_lock")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod rw_lock
    fi
    testing=$(adb -s $selected_device shell lsmod | grep  "seq_lock")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod seq_lock
    fi

    adb -s $selected_device shell "insmod /data/local/spin_lock.ko"
    adb -s $selected_device shell "insmod /data/local/rw_lock.ko"
    adb -s $selected_device shell "insmod /data/local/seq_lock.ko"
fi

