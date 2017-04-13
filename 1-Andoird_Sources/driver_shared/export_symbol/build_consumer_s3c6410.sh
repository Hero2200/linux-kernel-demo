# build.sh
source ~/drivers/common.sh
make  -C  $S3C6410_KERNEL_PATH  M=/root/drivers/driver_shared/export_symbol
adb push ~/drivers/driver_shared/export_symbol/symbol_consumer.ko /data/local
testing=$(adb shell lsmod | grep  "symbol_consumer")
#  如果symbol_consumer驱动已安装，先卸载symbol_consumer驱动
if [ "$testing" != "" ]; then
    adb shell rmmod symbol_consumer
fi
#  安装linux_driver驱动
adb shell insmod /data/local/symbol_consumer.ko 
echo 'symbol_consumer模块已成功安装'
adb shell 'dmesg | tail -n 4'



