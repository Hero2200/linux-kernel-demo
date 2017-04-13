# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=${PWD}
arm-none-linux-gnueabi-gcc -static  ${PWD}/test_aio_rw.c -o test_aio_rw  -lrt -lpthread
arm-none-linux-gnueabi-gcc -static  ${PWD}/test_read_signal.c -o test_read_signal  -lrt -lpthread
arm-none-linux-gnueabi-gcc -static  ${PWD}/test_callback.c -o test_callback  -lrt -lpthread
find_devices 
if [ "$selected_device" == "" ]; then  
    exit
else
    adb -s $selected_device push ${PWD}/test_aio_rw /data/local
    adb -s $selected_device push ${PWD}/test_aio_rw.c /data/local
    adb -s $selected_device push ${PWD}/test.txt /data/local
    adb -s $selected_device push ${PWD}/test_read_signal /data/local
    adb -s $selected_device push ${PWD}/test_callback /data/local 
    adb -s $selected_device push ${PWD}/aio_signal.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "aio_signal")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod aio_signal
    fi
    adb -s $selected_device shell "insmod /data/local/aio_signal.ko"
fi
 
