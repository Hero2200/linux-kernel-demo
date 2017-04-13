# build_s3c6410.sh
source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=${PWD}
arm-none-linux-gnueabi-gcc -static  ${PWD}/test_signal.c -o test_signal
arm-none-linux-gnueabi-gcc -static  ${PWD}/test_io_signal.c -o test_io_signal
arm-none-linux-gnueabi-gcc -static  ${PWD}/test_rw_signal.c -o test_rw_signal
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/test_signal /data/local
    adb -s $selected_device push ${PWD}/test_io_signal /data/local
    adb -s $selected_device push ${PWD}/test_rw_signal /data/local
    adb -s $selected_device push ${PWD}/signal.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "signal")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod signal
    fi
    adb -s $selected_device shell "insmod /data/local/signal.ko"

fi
