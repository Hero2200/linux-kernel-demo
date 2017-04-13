# build_s3c6410.sh

source /root/drivers/common.sh

make  -C  $EMULATOR_KERNEL_PATH  M=$PWD
arm-none-linux-gnueabi-gcc -static -g -o gdb_debug $PWD/gdb_debug.c
find_devices
if [ "$selected_device" == "" ]; then
    exit
else
    adb -s $selected_device push $PWD/printk_demo.ko /data/local
    adb -s $selected_device push $PWD/proc_demo.ko /data/local
    adb -s $selected_device push $PWD/bug_demo.ko /data/local
    adb -s $selected_device push $PWD/gdb_debug /data/local

    testing=$(adb -s $selected_device shell lsmod | grep  "printk_demo")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod printk_demo
    fi
    testing=$(adb -s $selected_device shell lsmod | grep  "proc_demo")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod proc_demo
    fi

    testing=$(adb -s $selected_device shell lsmod | grep  "bug_demo")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod bug_demo
    fi

    adb -s $selected_device shell insmod /data/local/printk_demo.ko	
    adb -s $selected_device shell insmod /data/local/proc_demo.ko	
    adb -s $selected_device shell insmod /data/local/bug_demo.ko	
fi

