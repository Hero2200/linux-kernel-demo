# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=$PWD
arm-none-linux-gnueabi-gcc -static  -o ta $PWD/test_atomic.c
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push $PWD/atomic.ko /data/local
    adb -s $selected_device push $PWD/ta /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "atomic")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod atomic
    fi
    adb -s $selected_device shell "insmod /data/local/atomic.ko atom=$atom"
fi

