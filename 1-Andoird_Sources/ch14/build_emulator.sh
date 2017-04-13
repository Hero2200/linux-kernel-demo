# build_s3c6410.sh
source /root/drivers/common.sh
make  -C  $EMULATOR_KERNEL_PATH  M=${PWD}
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/tasklet.ko /data/local
    adb -s $selected_device push ${PWD}/wq.ko /data/local
    testing=$(adb -s $selected_device shell lsmod | grep  "tasklet")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod tasklet
    fi
    testing=$(adb -s $selected_device shell lsmod | grep  "wq")
    if [ "$testing" != "" ]; then
	adb -s $selected_device shell rmmod wq
    fi
    adb -s $selected_device shell "insmod /data/local/tasklet.ko"
    adb -s $selected_device shell "insmod /data/local/wq.ko"
fi
