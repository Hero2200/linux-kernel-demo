# build.sh
source /root/drivers/common.sh
make  -C  $UBUNTU_KERNEL_PATH  M=$PWD
insmod $PWD/bad_driver1.ko
insmod $PWD/bad_driver2.ko




