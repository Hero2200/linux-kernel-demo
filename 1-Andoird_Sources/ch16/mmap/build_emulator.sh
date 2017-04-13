source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=${PWD}
arm-none-linux-gnueabi-gcc -static  -o user_mmap ${PWD}/user_mmap.c
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/mmap_shared.ko /data/local
    adb -s $selected_device push ${PWD}/user_mmap /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "mmap_shared")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod mmap_shared
    fi
    adb -s $selected_device shell "insmod /data/local/mmap_shared.ko"
fi


