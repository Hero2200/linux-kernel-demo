# build.sh
source ~/drivers/common.sh
kernel_path=$EMULATOR_KERNEL_PATH
if [ "$2" == "6410" ]; then
    kernel_path=$S3C6410_KERNEL_PATH
fi

make  -C $kernel_path  M=/root/drivers/force_kill_driver/bad_driver
which_device=""
if [ "$1" != "" ]; then 
    which_device="-s $1"
fi
adb $which_device push /root/drivers/force_kill_driver/bad_driver/bad_driver1.ko /data/local
adb $which_device push /root/drivers/force_kill_driver/bad_driver/bad_driver2.ko /data/local

adb $which_device shell insmod /data/local/bad_driver1.ko
adb $which_device shell insmod /data/local/bad_driver2.ko




