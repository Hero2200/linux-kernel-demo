# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=${PWD}
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else 
    adb -s $selected_device push ${PWD}/pwm_driver.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "pwm_driver")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod pwm_driver
    fi
    adb -s $selected_device shell "insmod /data/local/pwm_driver.ko"
fi

