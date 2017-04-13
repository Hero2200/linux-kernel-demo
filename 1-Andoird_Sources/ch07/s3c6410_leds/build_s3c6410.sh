# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=${PWD}
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/s3c6410_leds.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "s3c6410_leds")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod s3c6410_leds
    fi
    adb -s $selected_device shell "insmod /data/local/s3c6410_leds.ko"
    adb -s $selected_device shell  "chmod 777 /dev/s3c6410_leds"

fi

