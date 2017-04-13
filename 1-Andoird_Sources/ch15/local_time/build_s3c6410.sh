# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=${PWD}
arm-none-linux-gnueabi-gcc -static  -o user_local_time ${PWD}/user_local_time.c
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/local_time.ko /data/local
    adb -s $selected_device push ${PWD}/user_local_time /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "local_time")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod local_time
    fi
    adb -s $selected_device shell "insmod /data/local/local_time.ko"
fi
