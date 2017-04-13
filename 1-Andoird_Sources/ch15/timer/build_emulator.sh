# build_s3c6410.sh
source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=${PWD}
arm-none-linux-gnueabi-gcc -static  -o test_timer ${PWD}/test_timer.c
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/timer_demo.ko /data/local
    adb -s $selected_device push ${PWD}/test_timer /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "timer_demo")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod timer_demo
    fi
    adb -s $selected_device shell "insmod /data/local/timer_demo.ko"
fi
