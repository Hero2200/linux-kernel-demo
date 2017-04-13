# build.sh
source /root/drivers/common.sh
make  -C  $UBUNTU_KERNEL_PATH  M=$PWD
testing=$(lsmod | grep  "multi_file_driver")
#  如果multi_file_driver驱动已安装，先卸载multi_file_driver驱动
if [ "$testing" != "" ]; then
    rmmod multi_file_driver
fi
#  安装linux_driver驱动
insmod $PWD/multi_file_driver.ko

