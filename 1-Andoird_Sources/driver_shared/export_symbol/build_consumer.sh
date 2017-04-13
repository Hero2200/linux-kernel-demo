# build.sh
source ~/drivers/common.sh
make  -C  $UBUNTU_KERNEL_PATH  M=/root/drivers/driver_shared/export_symbol
testing=$(lsmod | grep  "symbol_consumer")
#  如果symbol_consumer驱动已安装，先卸载symbol_consumer驱动
if [ "$testing" != "" ]; then
    rmmod symbol_consumer
fi
#  安装linux_driver驱动
insmod /root/drivers/driver_shared/export_symbol/symbol_consumer.ko
echo 'symbol_consumer模块已成功安装'
dmesg | tail -n 4

