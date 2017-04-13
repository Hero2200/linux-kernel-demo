# build_s3c6410.sh
source /root/drivers/common.sh
make  -C $S3C6410_KERNEL_PATH  M=${PWD}
echo '本例需要做开发板上安装，如果有多个设备，请选择开发板'
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

