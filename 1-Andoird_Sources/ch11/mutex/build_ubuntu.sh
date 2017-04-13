# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=$PWD
testing=$(lsmod | grep  "mutex")
if [ "$testing" != "" ]; then
    rmmod mutex
fi
insmod $PWD/mutex.ko

