source /root/drivers/common.sh
make  -C  $UBUNTU_KERNEL_PATH  M=$PWD
testing=$(lsmod | grep  "symbol_consumer")
#  如果symbol_consumer驱动已安装，先卸载symbol_consumer驱动
if [ "$testing" != "" ]; then
    rmmod symbol_consumer
fi
testing=$(lsmod | grep  "symbol_producer")
#  如果symbol_producer驱动已安装，先卸载symbol_producer驱动
if [ "$testing" != "" ]; then
    rmmod symbol_producer
fi
#  安装linux_driver驱动
insmod $PWD/symbol_producer.ko
#  安装linux_driver驱动
insmod $PWD/symbol_consumer.ko


