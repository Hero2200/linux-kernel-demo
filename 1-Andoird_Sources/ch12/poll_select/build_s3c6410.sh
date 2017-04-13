# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=${PWD}
arm-none-linux-gnueabi-gcc -static  -o test_select ${PWD}/test_select.c
find_devices
if [ "$selected_device" == "" ]; then
    exit
else
    adb -s $selected_device push ${PWD}/poll_select.ko /data/local
    adb -s $selected_device push ${PWD}/test_select /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "poll_select")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod poll_select
    fi
    adb -s $selected_device shell "insmod /data/local/poll_select.ko"
fi

