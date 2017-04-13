# build.sh
source ~/drivers/common.sh
make  -C  $UBUNTU_KERNEL_PATH  M=/root/drivers/driver_shared/multi_file_driver 
testing=$(lsmod | grep  "multi_file_driver")
#  如果multi_file_driver驱动已安装，先卸载multi_file_driver驱动
if [ "$testing" != "" ]; then
    rmmod multi_file_driver
fi
#  安装linux_driver驱动
insmod /root/drivers/driver_shared/multi_file_driver/multi_file_driver.ko
echo 'multi_file_driver模块已成功安装'
dmesg | tail -n 4

